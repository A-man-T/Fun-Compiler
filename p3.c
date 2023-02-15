#include "cslice.h"
#include "oldInterp.h"
#include "linkedlist.h"
#include "functionlinkedlist.h"
#include "scope.h"
#include "optionalSlice.h"
#include "optionalInt.h"
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdnoreturn.h>
#include <inttypes.h>

uint64_t globalReturnValue = 0;
// bool to keep track if the current function has returned
bool returned;
int labelCounter = 0;

struct Interpreter;



uint64_t expression(bool effects, Interpreter *interp);
void statements(bool effects, Interpreter *interp);
void runFunction(bool effects, Interpreter *interp, optionalSlice id);

void skip(Interpreter *interp)
{
    while (isspace(*interp->current))
    {
        interp->current += 1;
    }
}

bool consume(char *str, Interpreter *interp)
{
    skip(interp);

    size_t i = 0;
    while (true)
    {
        char expected = str[i];
        char found = interp->current[i];
        if (expected == 0)
        {
            /* survived to the end of the expected string */
            interp->current += i;
            return true;
        }
        if (expected != found)
        {
            return false;
        }
        // assertion: found != 0
        i += 1;
    }
}

// function that skips the interp->current pointer to the end of the loop and/or function by keeping track of curly braces
void skipCurlyBraces(bool effects, Interpreter *interp)
{
    uint64_t countBraces = 1;
    while (countBraces != 0)
    {
        if (consume("{", interp))
        {
            countBraces++;
        }
        else if (consume("}", interp))
        {
            countBraces--;
        }
        else
        {
            interp->current += 1;
        }
    }
}

noreturn void fail(Interpreter *interp)
{
    printf("failed at offset %ld\n", (interp->current - interp->program));
    printf("%s\n", interp->current);
    exit(1);
}

void end_or_fail(Interpreter *interp)
{
    while (isspace(*interp->current))
    {
        interp->current += 1;
    }
    if (*interp->current != 0)
        fail(interp);
}

void consume_or_fail(char *str, Interpreter *interp)
{
    if (!consume(str, interp))
    {
        fail(interp);
    }
}

optionalSlice consume_identifier(Interpreter *interp)
{
    skip(interp);

    if (isalpha(*interp->current))
    {
        char *start = interp->current;
        do
        {
            interp->current += 1;
        } while (isalnum(*interp->current));
        Slice s1 = {start, interp->current - start};
        optionalSlice os1 = {true, s1};
        return os1;
    }
    else
    {
        Slice s1 = {};
        optionalSlice os1 = {false, s1};
        return os1;
    }
}

optionalInt consume_literal(Interpreter *interp)
{
    skip(interp);

    if (isdigit(*interp->current))
    {
        uint64_t v = 0;
        do
        {
            v = (10 * v + ((*interp->current) - '0'));
            interp->current += 1;
        } while (isdigit(*interp->current));
        optionalInt oi1 = {true, v};
        return oi1;
    }
    else
    {
        optionalInt oi1 = {false, 0};
        return oi1;
    }
}

Interpreter newInterp(char *prog)
{
    Interpreter i1 = {prog, prog};
    return i1;
}

// The plan is to honor as many C operators as possible with
// the same precedence and associativity
// e<n> implements operators with precedence 'n' (smaller is higher)

// () [] . -> ...
uint64_t e1(bool effects, Interpreter *interp)
{
    if (consume("(", interp))
    {
        uint64_t v = expression(effects, interp);
        consume(")", interp);
        return v;
    }
    optionalInt v = consume_literal(interp);
    if (v.hasValue)
    {
        printf("      mov $%lu,%%r13\n", v.value);
        puts("      push %r13");

        // puts("      mov $" (char)v);
        return v.value;
    }

    optionalSlice id = consume_identifier(interp);

    if (id.hasValue)
    {
        // Treats print as a function if evaluated as an expression
        if (equals(id.value, "print") && consume("(", interp))
        {

            expression(effects, interp);

            puts("      call ._print");
            puts("      pop %r13");
            consume(")", interp);
            return 0;
        }

        // keep going from here

        // Calls a function
        if (consume("(", interp))
        {
            runFunction(effects, interp, id);
            puts("      push %rax");
            int64_t tempHold = globalReturnValue;
            globalReturnValue = 0;
            return tempHold;
        }
        // Effects is used to indicate if we are in a function, if we aren't effects = true, and we only check the globalScope
        else if (effects)
        {
            uint64_t v = find(id.value).value;
            return v;
        }
        // Otherwise we check the local, then global, then insert into the local per the spec
        else
        {
            int offset = 0;
            optionalInt v = findPosition(id.value);
            if (v.value + 1 > localScope->numParams)
            {
                offset = -8 * (v.value + 1 - localScope->numParams);
            }
            else
            {
                offset = 8 * (localScope->numParams - v.value + 1);
            }
            printf("      mov %i(%%rbp),%%rdi", offset);
            printf("\n");
            puts("      push %rdi");
            uint64_t x = find(id.value).value;
            return x;
        }
    }
    else
    {
        fail(interp);
        // never hit here
        return 0;
    }
}

// ++ -- unary+ unary- ... (Right)
uint64_t e2(bool effects, Interpreter *interp)
{
    uint64_t counter = 0;

    while (consume("!", interp))
    {
        counter++;
    }
    e1(effects, interp);
    if (counter == 0)
        return 0;
    else if (counter % 2 == 0)
    {
        puts("      pop %rax");
        puts("      test %rax,%rax");
        puts("      mov $0,%rax");
        puts("      setz %al");
        puts("      push %rax");
        puts("      pop %rax");
        puts("      test %rax,%rax");
        puts("      mov $0,%rax");
        puts("      setz %al");
        puts("      push %rax");
        return 0;
    }
    else
    {
        puts("      pop %rax");
        puts("      test %rax,%rax");
        puts("      mov $0,%rax");
        puts("      setz %al");
        puts("      push %rax");
        return 0;
    }
}

// * / % (Left)
uint64_t e3(bool effects, Interpreter *interp)
{
    uint64_t v = e2(effects, interp);

    while (true)
    {
        if (consume("*", interp))
        {
            e2(effects, interp);
            puts("      pop %rdx");
            puts("      pop %rax");
            puts("      imul %rdx, %rax");
            puts("      push %rax");
        }
        else if (consume("/", interp))
        {
            e2(effects, interp);
            puts("      xor %rdx,%rdx");
            puts("      pop %rdi");
            puts("      pop %rax");
            puts("      divq %rdi");
            puts("      push %rax");
        }
        else if (consume("%", interp))
        {
            e2(effects, interp);
            puts("      xor %rdx,%rdx");
            puts("      pop %rdi");
            puts("      pop %rax");
            puts("      divq %rdi");
            puts("      push %rdx");
        }
        else
        {
            return v;
        }
    }
}

// (Left) + -
uint64_t e4(bool effects, Interpreter *interp)
{
    uint64_t v = e3(effects, interp);

    while (true)
    {
        if (consume("+", interp))
        {

            e3(effects, interp);
            puts("      pop %rdx");
            puts("      pop %rax");
            puts("      add %rdx, %rax");
            puts("      push %rax");
        }
        else if (consume("-", interp))
        {
            e3(effects, interp);
            puts("      pop %rdx");
            puts("      pop %rax");
            puts("      sub %rdx, %rax");
            puts("      push %rax");
        }
        else
        {
            return v;
        }
    }
}

// << >>
uint64_t e5(bool effects, Interpreter *interp)
{
    return e4(effects, interp);
}

// < <= > >=
uint64_t e6(bool effects, Interpreter *interp)
{
    uint64_t v = e5(effects, interp);

    while (true)
    {
        if (consume("<=", interp))
        {
            e5(effects, interp);
            puts("      pop %rdx");
            puts("      pop %rax");
            puts("      cmp %rdx, %rax");
            puts("      mov $0,%rax");
            puts("      setbe %al");
            puts("      push %rax");

            // v = (v <= e5(effects, interp));
        }
        else if (consume("<", interp))
        {
            e5(effects, interp);
            puts("      pop %rdx");
            puts("      pop %rax");
            puts("      cmp %rdx, %rax");
            puts("      mov $0,%rax");
            puts("      setb %al");
            puts("      push %rax");
        }
        else if (consume(">=", interp))
        {
            e5(effects, interp);
            puts("      pop %rdx");
            puts("      pop %rax");
            puts("      cmp %rdx, %rax");
            puts("      mov $0,%rax");
            puts("      setae %al");
            puts("      push %rax");
        }
        else if (consume(">", interp))
        {
            e5(effects, interp);
            puts("      pop %rdx");
            puts("      pop %rax");
            puts("      cmp %rdx, %rax");
            puts("      mov $0,%rax");
            puts("      seta %al");
            puts("      push %rax");
        }
        else
        {
            return v;
        }
    }
}

// == !=
uint64_t e7(bool effects, Interpreter *interp)
{

    uint64_t v = e6(effects, interp);

    while (true)
    {
        if (consume("==", interp))
        {
            e6(effects, interp);
            puts("      pop %rdx");
            puts("      pop %rax");
            puts("      cmp %rdx, %rax");
            puts("      mov $0,%rax");
            puts("      sete %al");
            puts("      push %rax");
        }
        else if (consume("!=", interp))
        {
            e6(effects, interp);
            puts("      pop %rdx");
            puts("      pop %rax");
            puts("      cmp %rdx, %rax");
            puts("      mov $0,%rax");
            puts("      setne %al");
            puts("      push %rax");
        }
        else
        {
            return v;
        }
    }
}

// (left) &
uint64_t e8(bool effects, Interpreter *interp)
{
    return e7(effects, interp);
}

// ^
uint64_t e9(bool effects, Interpreter *interp)
{
    return e8(effects, interp);
}

// |
uint64_t e10(bool effects, Interpreter *interp)
{
    return e9(effects, interp);
}

// &&
uint64_t e11(bool effects, Interpreter *interp)
{

    uint64_t v = e10(effects, interp);

    while (true)
    {
        if (consume("&&", interp))
        {
            e10(effects, interp);
            puts("      pop %rdi");
            puts("      pop %rax");
            puts("      test %rax,%rax");
            puts("      mov $0,%rax");
            puts("      setnz %al");
            puts("      test %rdi,%rdi");
            puts("      mov $0,%rdi");
            puts("      setnz %dil");
            puts("      and %rdi,%rax");
            puts("      push %rax");
        }
        else
        {
            return v;
        }
    }
}

// ||
uint64_t e12(bool effects, Interpreter *interp)
{
    uint64_t v = e11(effects, interp);

    while (true)
    {
        if (consume("||", interp))
        {
            e11(effects, interp);
            puts("      pop %rdi");
            puts("      pop %rax");
            puts("      test %rax,%rax");
            puts("      mov $0,%rax");
            puts("      setnz %al");
            puts("      test %rdi,%rdi");
            puts("      mov $0,%rdi");
            puts("      setnz %dil");
            puts("      or %rdi,%rax");
            puts("      push %rax");
        }
        else
        {
            return v;
        }
    }
}

// (right with special treatment for middle expression) ?:
uint64_t e13(bool effects, Interpreter *interp)
{
    return e12(effects, interp);
}

// = += -= ...
uint64_t e14(bool effects, Interpreter *interp)
{
    return e13(effects, interp);
}

// ,
uint64_t e15(bool effects, Interpreter *interp)
{
    return e14(effects, interp);
}

uint64_t expression(bool effects, Interpreter *interp)
{
    //check if all are nonalphabet if they are push onto stack and return
    
    char * ptr = interp->current;
    bool noAlpha = 1;
     while (!(*interp->current == '\n') && !(*interp->current == 0))
        {
            if(isalpha(*interp->current)){
                noAlpha = 0;
                break;
            }
            interp->current++;
        }
    interp->current = ptr;
    if(noAlpha){
        uint64_t v = Ie15(effects, interp);
        printf("      mov $%lu,%%r13\n", v);
        puts("      push %r13");
        
        return 0;
    }
    
    return e15(effects, interp);
}

bool statement(bool effects, Interpreter *interp)
{
    if (consume("#", interp))
    {
        while (!(*interp->current == '\n') && !(*interp->current == 0))
        {
            interp->current++;
        }
        if (*interp->current == 0)
            return false;
        return true;
    }

    optionalSlice id = consume_identifier(interp);

    if (equals(id.value, "print") && consume("(", interp))
    {

        // print ...
        expression(effects, interp);

        puts("      call ._print");
        puts("      pop %r13");
        consume(")", interp);
        return true;
    }
    // Stores the function information in the function linkedlist
    else if (equals(id.value, "fun"))
    {

        optionalSlice v = consume_identifier(interp);
        printf("._");
        printSlice(v.value);
        printf(":");
        printf("\n");
        char *ptr = interp->current;
        uint64_t numParams = 0;
        consume("(", interp);
        // counts number of parameters
        while (!consume(")", interp))
        {
            consume_identifier(interp);
            numParams++;
            consume(",", interp);
        }
        // insertFunction(v.value, ptr, numParams);
        // functionNode *toEdit = findFunction(v.value);

        localScope = getNewLocalScope(numParams);

        interp->current = ptr;
        int currentVar = 0;
        consume_identifier(interp);
        consume("(", interp);
        // stores the names of the parameters
        while (!consume(")", interp))
        {
            optionalSlice c = consume_identifier(interp);
            localScope->names[currentVar] = c.value;
            currentVar++;
            consume(",", interp);
        }
        consume("{", interp);

        if (numParams == 0)
        {
            localScope->filledTo = 0;
        }
        else
        {
            localScope->filledTo = numParams - 1;
        }

        ptr = interp->current;

        optionalSlice varName;
        uint64_t countBraces = 1;
        while (countBraces != 0)
        {
            if (varName = consume_identifier(interp), varName.hasValue)
            {
                if (consume("=", interp))
                    insertLocal(varName.value, 0);
            }
            else if (consume("{", interp))
            {
                countBraces++;
            }
            else if (consume("}", interp))
            {
                countBraces--;
            }
            else
            {
                interp->current += 1;
            }
        }
        interp->current = ptr;

        int offset = -8 * (localScope->filledTo + 1 - numParams);
        // if (numParams == 0 && localScope->filledTo == 0)
        //   offset = 0;

        puts("      push %rbp");
        puts("      mov %rsp,%rbp");
        printf("      add $%i,%%rsp \n", offset);

        statements(false, interp);

        consume("}", interp);

        puts("      mov $0,%rax");
        printf("      sub $%i,%%rsp \n", offset);
        puts("      pop %rbp");
        puts("      retq");
        freeInside();
        free(localScope);

        return true;
    }
    // This allows the rest of the program to know that we need to return out of a fucntion
    else if (equals(id.value, "return"))
    {
        expression(false, interp);
        puts("      pop %rax");
        puts("      mov %rbp, %rsp");
        puts("      pop %rbp");
        puts("      retq");
        returned = true;
        return true;
    }
    else if (equals(id.value, "if"))
    {
        int currentLabelCounter = labelCounter;
        labelCounter++;
        labelCounter++;
        expression(effects, interp);
        consume("{", interp);
        puts("      pop %rdi");
        puts("      test %rdi,%rdi");
        printf("        jz .%i\n", currentLabelCounter);
        statements(effects, interp);
        consume("}", interp);
        printf("        jmp .%i\n", currentLabelCounter + 1);
        printf(".%i:\n", currentLabelCounter);
        char *ptr = interp->current;
        if (consume("else", interp)&&consume("{", interp))
        {
            
            statements(effects, interp);
            consume("}", interp);
        }
        else{
            interp->current = ptr;
        }
        printf(".%i:\n", currentLabelCounter + 1);

        /*
        uint64_t v = expression(effects, interp);
        consume("{", interp);

        if (v)
        {

            statements(effects, interp);
            if (returned)
            {
                // Stops the rest of the if statement
                return false;
            }
            consume("}", interp);
            char *temp = interp->current;
            if (consume("else", interp))
            {
                if (consume("{", interp))
                    skipCurlyBraces(effects, interp);
                else
                {
                    interp->current = temp;
                    return true;
                }
            }
        }

        else
        {
            skipCurlyBraces(effects, interp);
            char *temp = interp->current;
            if (consume("else", interp))
            {
                if (consume("{", interp))
                {
                    statements(effects, interp);
                    if (returned)
                    {

                        return false;
                    }

                    consume("}", interp);
                }
                else
                {
                    interp->current = temp;
                }
            }
        }
        */
        return true;
    }
    else if (equals(id.value, "while"))
    {

        int currentLabelCounter = labelCounter;
        labelCounter++;
        labelCounter++;
        printf(".%i:\n", currentLabelCounter);
        expression(effects, interp);
        consume("{", interp);
        puts("      pop %rdi");
        puts("      test %rdi,%rdi");
        printf("        jz .%i\n", currentLabelCounter + 1);
        statements(effects, interp);
        printf("        jmp .%i\n", currentLabelCounter);
        printf(".%i:\n", currentLabelCounter + 1);
        consume("}", interp);

        /*
        char *reeval = interp->current;
        uint64_t v = expression(effects, interp);
        char *commands = interp->current;
        while (v)
        {
            consume("{", interp);
            statements(effects, interp);
            if (returned)
            {
                // returned = false;
                return false;
            }
            consume("}", interp);
            interp->current = reeval;
            v = expression(effects, interp);
        }

        interp->current = commands;
        consume("{", interp);
        skipCurlyBraces(effects, interp);
        */
        return true;
    }

    else if (id.hasValue)
    {
        // x = ...
        if (consume("=", interp))
        {
            uint64_t v = expression(effects, interp);
            // Runs if in global Scope
            if (effects)
            {
                insert(id.value, v);
            }
            // If in local Scope check if in local, then check global, then add to local
            else
            {
                optionalInt v = findPosition(id.value);
                int offset = 0;

                if (v.value + 1 > localScope->numParams)
                {
                    offset = -8 * (v.value + 1 - localScope->numParams);
                }
                else
                {
                    offset = 8 * (localScope->numParams - v.value + 1);
                }
                puts("      pop %rdi");

                printf("      mov %%rdi,%i(%%rbp)\n", offset);
                // uint64_t x = find(id.value).value;
            }
            return true;
        }
        // Run a function

        else
        {
            consume("(", interp);
            runFunction(effects, interp, id);
            globalReturnValue = 0;
            return true;
        }
        /*
        //if (findFunction(id.value) != NULL)
        else
        {
            fail(interp);
        }
        */
    }
    return false;
}

void statements(bool effects, Interpreter *interp)
{
    while (statement(effects, interp))
        ;
}

void run(Interpreter *interp)
{
    statements(true, interp);
    end_or_fail(interp);
}

// code to run a function
void runFunction(bool effects, Interpreter *interp, optionalSlice id)
{
    uint64_t args = 0;

    // push args
    while (!consume(")", interp))
    {
        expression(effects, interp);
        consume(",", interp);
        args++;
    }
    printf("      call ._");
    printSlice(id.value);
    printf("\n");
    int offset = 8 * args;
    printf("      add $%i,%%rsp\n", offset);

    // pop args

    /*
    globalReturnValue = 0;
    returned = false;
    struct functionNode *funcSpecs = findFunction(id.value);
    struct localScopeVariables *funcValues = getNewLocalScope(funcSpecs->numParams);
    consume("(", interp);
    // stores the params
    for (uint64_t counter = 0; counter < funcSpecs->numParams; counter++)
    {
        uint64_t v = expression(effects, interp);
        funcValues->values[counter] = v;
        funcValues->names[counter] = funcSpecs->params[counter];
        consume(",", interp);
    }
    if (funcSpecs->numParams == 0)
    {
        funcValues->filledTo = 0;
    }
    else
    {
        funcValues->filledTo = funcSpecs->numParams - 1;
    }
    consume(")", interp);
    char *oldLocation = interp->current;
    struct localScopeVariables *oldScope = localScope;
    localScope = funcValues;

    interp->current = funcSpecs->location;
    consume_identifier(interp);
    consume("(", interp);
    while (!consume(")", interp))
    {
        consume_identifier(interp);
        consume(",", interp);
    }
    consume("{", interp);

    statements(false, interp);

    returned = false;

    interp->current = oldLocation;
    freeInside();
    free(localScope);
    localScope = oldScope;
    */
}

int main()
{

    uint64_t inputLen = 10000;
    char *prog = (char *)(malloc(sizeof(char)*inputLen));
    char c;
    uint64_t index = 0;
    while ((c = getchar()) != EOF)
    {
        prog[index++] = c;
    }
    prog[index++] = 0;

    puts("    .data");
    puts("format: .byte '%', 'l', 'u', 10, 0");
    puts("    .text");

    puts("._print:");
    puts("      push %rbp");
    puts("      mov %rsp, %rbp");
    puts("      and $-16,%rsp");
    puts("      mov 16(%rbp), %rsi");
    puts("      lea format(%rip),%rdi");
    puts("      xor %rax,%rax");
    puts("      .extern printf");
    puts("      call printf");
    puts("      mov %rbp,%rsp");
    puts("      pop %rbp");
    puts("      retq");

    puts("    .global main");
    puts("main:");
    puts("      push %rbp");
    puts("      push %rbx");
    puts("      push %r12");
    puts("      push %r13");
    puts("      push %r14");
    puts("      push %r15");
    puts("      call ._main");
    puts("      pop %r15");
    puts("      pop %r14");
    puts("      pop %r13");
    puts("      pop %r12");
    puts("      pop %rbx");
    puts("      pop %rbp");
    puts("      retq");

    // puts("._main:");

    /*
    puts("    mov $0,%rax");
    puts("    lea format(%rip),%rdi");
    puts("    mov $42,%rsi");
    puts("    .extern printf");
    puts("    call printf");
    puts("    mov $0,%rax");
    puts("    ret");
    */

    Interpreter x = newInterp(prog);
    run(&x);
    free(prog);

    // puts("      retq");
    return 0;
}

// vim: tabstop=4 shiftwidth=2 expandtab
//._main