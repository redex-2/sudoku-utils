#ifndef prime_hpp
#define prime_hpp

#include "types.hpp"

class _prime
{
	private:
		uint16 t, m = 2;//0=standard 1-miller_rabin 2-auto
		uint32 k = 100;
		uint64 result, j, d, a, i, x, n, c;
		uint64 sqrt(uint64);
		uint64 power(uint64 base, uint64 exponent, uint64 mod);
		bool miller_rabin(uint32);
		bool miller_rabin_unit(uint32, uint32);
		bool standard(uint64);
	public:
		uint16 precision(uint32);
		uint16 method(uint16);
		uint16 check(uint64);
		uint64 next(uint64);
};

#endif