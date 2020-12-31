#ifndef large_uint_hpp
#define large_uint_hpp

class _sha2
{
	private:
		static const unsigned int h[8];
		static const unsigned int k[64];
		unsigned int word[16];
		unsigned int extended_word[64];
};

#endif