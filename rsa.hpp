#ifndef rsa_hpp
#define rsa_hpp

#include <gmp.h>

class rsa
{
	private:
		unsigned long long length = 2048;
		unsigned long long enc_length = 512;
		mpz_t p;
		mpz_t q;
		mpz_t n;
		mpz_t euler_function_value;
		mpz_t e;
		mpz_t d;
		
		
	public:
		
		
};

#endif