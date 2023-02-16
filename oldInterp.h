//This is the exact same as the interpreter from p2 used only for cases where we can employ the technique of constant folding

#pragma once
#include "cslice.h"
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

typedef struct Interpreter
{
    char *program;
    char *current;
} Interpreter;

uint64_t Iexpression(bool effects, Interpreter *interp);
bool consume(char *str, Interpreter *interp);
optionalInt consume_literal(Interpreter *interp);

uint64_t Ie1(bool effects, Interpreter *interp)
{
    if (consume("(", interp))
    {
        uint64_t v = Iexpression(effects, interp);
        consume(")", interp);
        return v;
    }
    optionalInt v = consume_literal(interp);
    if (v.hasValue)
    {
        return v.value;
    }
    return 0;
}

// ++ -- unary+ unary- ... (Right)
uint64_t Ie2(bool effects, Interpreter *interp)
{
    uint64_t counter = 0;

    while (consume("!", interp))
    {
        counter++;
    }
    if (counter == 0)
        return Ie1(effects, interp);
    else if (counter % 2 == 0)
    {
        return !!Ie1(effects, interp);
    }
    else
        return !Ie1(effects, interp);
}

// * / % (Left)
uint64_t Ie3(bool effects, Interpreter *interp)
{
    uint64_t v = Ie2(effects, interp);

    while (true)
    {
        if (consume("*", interp))
        {
            v = v * Ie2(effects, interp);
        }
        else if (consume("/", interp))
        {
            uint64_t right = Ie2(effects, interp);
            v = (right == 0) ? 0 : v / right;
        }
        else if (consume("%", interp))
        {
            uint64_t right = Ie2(effects, interp);
            v = (right == 0) ? 0 : v % right;
        }
        else
        {
            return v;
        }
    }
}

// (Left) + -
uint64_t Ie4(bool effects, Interpreter *interp)
{
    uint64_t v = Ie3(effects, interp);

    while (true)
    {
        if (consume("+", interp))
        {
            v = v + Ie3(effects, interp);
        }
        else if (consume("-", interp))
        {
            v = v - Ie3(effects, interp);
        }
        else
        {
            return v;
        }
    }
}

// << >>
uint64_t Ie5(bool effects, Interpreter *interp)
{
    return Ie4(effects, interp);
}

// < <= > >=
uint64_t Ie6(bool effects, Interpreter *interp)
{
    uint64_t v = Ie5(effects, interp);

    while (true)
    {
        if (consume("<=", interp))
        {
            v = (v <= Ie5(effects, interp));
        }
        else if (consume("<", interp))
        {
            v = (v < Ie5(effects, interp));
        }
        else if (consume(">=", interp))
        {
            v = (v >= Ie5(effects, interp));
        }
        else if (consume(">", interp))
        {
            v = (v > Ie5(effects, interp));
        }
        else
        {
            return v;
        }
    }
}

// == !=
uint64_t Ie7(bool effects, Interpreter *interp)
{

    uint64_t v = Ie6(effects, interp);

    while (true)
    {
        if (consume("==", interp))
        {
            v = (v == Ie6(effects, interp));
        }
        else if (consume("!=", interp))
        {
            v = (v != Ie6(effects, interp));
        }
        else
        {
            return v;
        }
    }
}

// (left) &
uint64_t Ie8(bool effects, Interpreter *interp)
{
    return Ie7(effects, interp);
}

// ^
uint64_t Ie9(bool effects, Interpreter *interp)
{
    return Ie8(effects, interp);
}

// |
uint64_t Ie10(bool effects, Interpreter *interp)
{
    return Ie9(effects, interp);
}

// &&
uint64_t Ie11(bool effects, Interpreter *interp)
{

    uint64_t v = Ie10(effects, interp);

    while (true)
    {
        if (consume("&&", interp))
        {
            v = (Ie10(effects, interp) && v);
        }
        else
        {
            return v;
        }
    }
}

// ||
uint64_t Ie12(bool effects, Interpreter *interp)
{
    uint64_t v = Ie11(effects, interp);

    while (true)
    {
        if (consume("||", interp))
        {
            v = (Ie11(effects, interp) || v);
        }
        else
        {
            return v;
        }
    }
}

// (right with special treatment for middle expression) ?:
uint64_t Ie13(bool effects, Interpreter *interp)
{
    return Ie12(effects, interp);
}

// = += -= ...
uint64_t Ie14(bool effects, Interpreter *interp)
{
    return Ie13(effects, interp);
}

// ,
uint64_t Ie15(bool effects, Interpreter *interp)
{
    return Ie14(effects, interp);
}

uint64_t Iexpression(bool effects, Interpreter *interp)
{
    return Ie15(effects, interp);
}