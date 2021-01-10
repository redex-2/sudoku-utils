#ifndef types
#define types

typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long long uint64;

static_assert(sizeof(uint16) == 2, "Change type of var for uint16");
static_assert(sizeof(uint32) == 4, "Change type of var for uint32");
static_assert(sizeof(uint64) == 8, "Change type of var for uint64");

#endif
