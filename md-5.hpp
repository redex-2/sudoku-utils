#ifndef md5_hpp
#define md5_hpp

#include "types.hpp"
#include "hash.hpp"
#include <sstream>

class _md5:protected _hash
{
	private:
		uint32 hash[4];
		uint32 block_size = 512;
		std::stringstream sstring;
		uint64 out_len;
		uint32** data;
		
		uint32 F(uint32, uint32, uint32);
		uint32 G(uint32, uint32, uint32);
		uint32 H(uint32, uint32, uint32);
		uint32 I(uint32, uint32, uint32);
		void init(void);

	public:
		std::string create(char*, uint64);

};

#endif