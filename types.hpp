#ifndef types_hpp
#define types_hpp

typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long long uint64;
typedef short int16;
typedef int int32;
typedef long long int64;

static_assert(sizeof(uint16) == 2, "Change type of var for uint16");
static_assert(sizeof(uint32) == 4, "Change type of var for uint32");
static_assert(sizeof(uint64) == 8, "Change type of var for uint64");
static_assert(sizeof(int16) == 2, "Change type of var for int16");
static_assert(sizeof(int32) == 4, "Change type of var for int32");
static_assert(sizeof(int64) == 8, "Change type of var for int64");

#endif
