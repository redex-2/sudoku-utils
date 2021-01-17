#ifndef prime_hpp
#define prime_hpp

#include "types.hpp"

class _prime
{
	private:
		uint16 m = 2;//0=standard 1-miller_rabin 2-auto
		uint32 k = 100;
		uint64 result, i, d, a, x;
		uint64 sqrt(uint64);
		uint64 power(uint64 base, uint64 exponent, uint64 mod);
		bool miller_rabin(uint32 &);
		bool standard(uint32 &);
	public:
		void precision(uint32);
		void method(uint16);
		uint16 check(uint32);
		uint32 next(uint32);
};

#endif