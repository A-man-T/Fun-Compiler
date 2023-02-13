#pragma once

#include <stdint.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include "cslice.h"

// The optional structs are written to replace optional<Generic> in C++

typedef struct optionalSlice
{

    bool hasValue;

    Slice value;

} optionalSlice;