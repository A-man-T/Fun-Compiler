#pragma once
#include <stdint.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

// A slice represents an immutable substring.
// Assumptions:
//      * the underlying string outlives the slice
//      * the underlying string is long enough
//      * the underlying string can be represented with single byte
//        characters (e.g. ASCII)
//
//      Slice representing "cde"
//          +---+---+
//          | o | 3 |
//          +-|-+---+
//            |
//            v
//       ...abcdefg...
//
// This class is intended as a light-weight wrapper around pointer and length
// and should be passed around by value.
//
typedef struct Slice
{
  char const *start; // where does the string start in memory?
                     // The 2 uses of 'const' express different ideas:
                     //    * the first says that we can't change the
                     //      character we point to
                     //    * the second says that we can't change the
                     //      place we point to
  size_t len;        // How many characters in the string
} Slice;

// Constructors
inline Slice new_Slice(char const *const s, size_t const l)
{
  Slice sl = {s, l};
  return sl;
}

inline Slice new_Slice1(char const *const start, char const *const end)
{
  Slice sl = {start, end - start};
  return sl;
}

// Compares a Slice to a pointer
bool equals(Slice slice, char const *p)
{
  for (size_t i = 0; i < slice.len; i++)
  {
    if (p[i] != slice.start[i])
      return false;
  }
  return p[slice.len] == 0;
}

// Compares two Slices
bool equalsSlice(Slice slice, Slice other)
{
  if (slice.len != other.len)
    return false;
  for (size_t i = 0; i < slice.len; i++)
  {
    if (other.start[i] != slice.start[i])
      return false;
  }
  return true;
}

// Checks if the character is a Slice is an identifier
bool is_identifier(Slice slice)
{
  if (slice.len == 0)
    return 0;
  if (isalpha(slice.start[0]) == 0)
    return false;
  for (size_t i = 1; i < slice.len; i++)
    if (isalnum(slice.start[i]) == 0)
      return false;
  return true;
}

void print(Slice slice)
{
  for (size_t i = 0; i < slice.len; i++)
  {
    printf("%c", slice.start[i]);
  }
}

// hash for a slice, not used in this interpretation
size_t hash(Slice key)
{
  // djb2
  size_t out = 5381;
  for (size_t i = 0; i < key.len; i++)
  {
    char const c = key.start[i];
    out = out * 33 + c;
  }
  return out;
}

// vim: ts=4 sw=2 et
