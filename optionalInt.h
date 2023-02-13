#pragma once
#include <stdint.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

// The optional structs are written to replace optional<Generic> in C++

typedef struct optionalInt
{

    bool hasValue;

    uint64_t value;

} optionalInt;