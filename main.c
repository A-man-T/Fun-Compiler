#include "cslice.h"
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
// #include "p3.c"

uint64_t globalReturnValue = 0;
// bool to keep track if the current function has returned
bool returned;

typedef struct Interpreter
{
    char const *const program;
    char const *current;
} Interpreter;

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

bool consume(const char *str, Interpreter *interp)
{
    skip(interp);

    size_t i = 0;
    while (true)
    {
        char const expected = str[i];
        char const found = interp->current[i];
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

void consume_or_fail(const char *str, Interpreter *interp)
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
        char const *start = interp->current;
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

Interpreter newInterp(char const *prog)
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
        return v.value;
    }

    optionalSlice id = consume_identifier(interp);

    if (id.hasValue)
    {
        // Treats print as a function if evaluated as an expression
        if (equals(id.value, "print") && consume("(", interp))
        {

            uint64_t v = expression(effects, interp);
            printf("%" PRIu64 "\n", v);
            consume(")", interp);
            return 0;
        }
        // Calls a function
        if (consume("(", interp))
        {
            runFunction(effects, interp, id);
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
            optionalInt v = findLocal(id.value);
            if (v.hasValue)
                return v.value;
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
    if (counter == 0)
        return e1(effects, interp);
    else if (counter % 2 == 0)
    {
        return !!e1(effects, interp);
    }
    else
        return !e1(effects, interp);
}

// * / % (Left)
uint64_t e3(bool effects, Interpreter *interp)
{
    uint64_t v = e2(effects, interp);

    while (true)
    {
        if (consume("*", interp))
        {
            v = v * e2(effects, interp);
        }
        else if (consume("/", interp))
        {
            uint64_t right = e2(effects, interp);
            v = (right == 0) ? 0 : v / right;
        }
        else if (consume("%", interp))
        {
            uint64_t right = e2(effects, interp);
            v = (right == 0) ? 0 : v % right;
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
            v = v + e3(effects, interp);
        }
        else if (consume("-", interp))
        {
            v = v - e3(effects, interp);
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
            v = (v <= e5(effects, interp));
        }
        else if (consume("<", interp))
        {
            v = (v < e5(effects, interp));
        }
        else if (consume(">=", interp))
        {
            v = (v >= e5(effects, interp));
        }
        else if (consume(">", interp))
        {
            v = (v > e5(effects, interp));
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
            v = (v == e6(effects, interp));
        }
        else if (consume("!=", interp))
        {
            v = (v != e6(effects, interp));
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
            v = (e10(effects, interp) && v);
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
            v = (e11(effects, interp) || v);
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
    return e15(effects, interp);
}

bool statement(bool effects, Interpreter *interp)
{
    optionalSlice id = consume_identifier(interp);

    if (equals(id.value, "print") && consume("(", interp))
    {

        // print ...
        uint64_t v = expression(effects, interp);
        printf("%" PRIu64 "\n", v);
        consume(")", interp);
        return true;
    }
    // Stores the function information in the function linkedlist
    else if (equals(id.value, "fun"))
    {
        char const *ptr = interp->current;
        optionalSlice v = consume_identifier(interp);
        uint64_t numParams = 0;
        consume("(", interp);
        // counts number of parameters
        while (!consume(")", interp))
        {
            consume_identifier(interp);
            numParams++;
            consume(",", interp);
        }
        insertFunction(v.value, ptr, numParams);
        functionNode *toEdit = findFunction(v.value);
        interp->current = ptr;
        int currentVar = 0;
        consume_identifier(interp);
        consume("(", interp);
        // stores the names of the parameters
        while (!consume(")", interp))
        {
            optionalSlice c = consume_identifier(interp);
            toEdit->params[currentVar] = c.value;
            currentVar++;
            consume(",", interp);
        }
        consume("{", interp);
        skipCurlyBraces(effects, interp);
        return true;
    }
    // This allows the rest of the program to know that we need to return out of a fucntion
    else if (!effects && equals(id.value, "return"))
    {
        globalReturnValue = expression(false, interp);
        returned = true;
        return false;
    }
    else if (equals(id.value, "if"))
    {
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
            char const *temp = interp->current;
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
            char const *temp = interp->current;
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
        return true;
    }
    else if (equals(id.value, "while"))
    {
        char const *reeval = interp->current;
        uint64_t v = expression(effects, interp);
        char const *commands = interp->current;
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
                optionalInt x = findLocal(id.value);
                if (x.hasValue)
                {
                    insertLocal(id.value, v);
                    return true;
                }
                else if (find(id.value).hasValue)
                {
                    insert(id.value, v);
                }
                else
                {
                    insertLocal(id.value, v);
                }
            }
            return true;
        }
        // Run a function
        else if (findFunction(id.value) != NULL)
        {
            runFunction(effects, interp, id);
            globalReturnValue = 0;
            return true;
        }
        else
        {
            fail(interp);
        }
    }
    return false;
}

void statements(bool effects, Interpreter *interp)
{
    while (statement(effects, interp));
}

void run(Interpreter *interp)
{
    statements(true, interp);
    end_or_fail(interp);
}

// code to run a function
void runFunction(bool effects, Interpreter *interp, optionalSlice id)
{
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
    char const *oldLocation = interp->current;
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
}

int main(int argc, const char *const *const argv)
{

    if (argc != 2)
    {
        fprintf(stderr, "usage: %s <file name>\n", argv[0]);
        exit(1);
    }

    // open the file
    int fd = open(argv[1], O_RDONLY);
    if (fd < 0)
    {
        perror("open");
        exit(1);
    }

    // determine its size (std::filesystem::get_size?)
    struct stat file_stats;
    int rc = fstat(fd, &file_stats);
    if (rc != 0)
    {
        perror("fstat");
        exit(1);
    }

    // map the file in my address space
    char const *prog = (char const *)mmap(
        0,
        file_stats.st_size,
        PROT_READ,
        MAP_PRIVATE,
        fd,
        0);
    if (prog == MAP_FAILED)
    {
        perror("mmap");
        exit(1);
    }

    Interpreter x = newInterp(prog);

    run(&x);

    puts("    .data");
    puts("format: .byte '%', 'd', 10, 0");
    puts("    .text");
    puts("    .global main");
    puts("main:");
    puts("    mov $0,%rax");
    puts("    lea format(%rip),%rdi");
    puts("    mov $42,%rsi");
    puts("    .extern printf");
    puts("    call printf");
    puts("    mov $0,%rax");
    puts("    ret");

    return 0;
}

// vim: tabstop=4 shiftwidth=2 expandtab
