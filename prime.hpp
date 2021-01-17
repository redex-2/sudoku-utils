#ifndef prime_hpp
#define prime_hpp

#include "types.hpp"
#include "large-uint.hpp"

class _prime
{
	private:
		large_uint x=large_uint(128);
		large_uint result=large_uint(128);
		large_uint i=large_uint(256);
		uint16 t, m = 2;//0=standard 1-miller_rabin 2-auto
		uint32 k = 100;
		uint64 d, a;//, i, x, result;
		uint64 sqrt(uint64);
		large_uint power(uint64 base, uint64 exponent, uint64 mod);
		bool miller_rabin(uint64);
		bool standard(uint64);
	public:
		uint16 precision(uint32);
		uint16 method(uint16);
		uint16 check(uint64);
		uint64 next(uint64);
};

#endif