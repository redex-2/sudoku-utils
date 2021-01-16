#ifndef prime_hpp
#define prime_hpp

#include "types.hpp"

class _prime
{
	private:
		uint64 sqrt(uint64 &);
		bool miller_rabin(uint64 &);
		bool standard(uint64 &);
	public:
		void method(uint16);
		void precision(uint64);
		uint16 check(uint64);
		uint64 next(uint64);
};

#endif