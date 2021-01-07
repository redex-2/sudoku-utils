#ifndef large_uint_hpp
#define large_uint_hpp

#include <sstream>
#include "hash.hpp"
#include "types.hpp"


class _sha2:protected _hash
{
	private:
		static const uint32 k[64];
		uint32 working[15];
		uint32 word[64];
		uint32 hash[8];
		uint32** data;
		uint64 j, out_len;
		uint16 i, l;
		uint32 block_size = 512;
		std::stringstream sstring;
		
		uint32 rotate(uint32, uint16);
		void compression(void);
		void expand(void);
		
		
	public:
		std::string create(char*, uint64);
		
};

#endif