#ifndef md5_hpp
#define md5_hpp

#include "types.hpp"
#include "hash.hpp"
#include <sstream>

class _md5:protected _hash
{
	private:
		uint16 i;
		uint32** data;
		uint32 hash[4];
		uint32 working[6];
		uint32 word[16];
		uint32 block_size = 512;
		uint64 out_len, j;
		static const uint32 k[64];
		static const uint16 s[64];
		std::stringstream sstring;
		
		uint32 rotate(uint32, uint16);
		uint32 permutation(uint32);
		uint32 F(uint32, uint32, uint32);
		uint32 G(uint32, uint32, uint32);
		uint32 H(uint32, uint32, uint32);
		uint32 I(uint32, uint32, uint32);
		void init(void);
		void rewriting(void);

	public:
		std::string create(char*, uint64);

};

#endif