#include "md-5.hpp"

uint32 _md5::F(uint32 B, uint32 C, uint32 D)
{
	return (B&C)|(~B&D);
}

uint32 _md5::G(uint32 B, uint32 C, uint32 D)
{
	return (B&D)|(C&~D);
}

uint32 _md5::H(uint32 B, uint32 C, uint32 D)
{
	return B^C^D;
}

uint32 _md5::I(uint32 B, uint32 C, uint32 D)
{
	return C^(B|~D);
}

void _md5::init(void)
{
	hash[0] = 0x01234567;
	hash[1] = 0x89abcdef;
	hash[2] = 0xfedcba98;
	hash[3] = 0x76543210;
}

std::string _md5::create(char *message, uint64 len)
{
	sstring.str(std::string());
	_hash::split_message(message, len, data, out_len, block_size);
	return sstring.str();
}