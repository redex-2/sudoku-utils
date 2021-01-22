#include "large-uint.hpp"

large_uint large_uint::rand(void)
{
	std::random_device rd;
	std::default_random_engine generator(rd());
	std::uniform_int_distribution<uint64> distribution(0, 0xFFFFFFFF);
	for (uint16 i = 0; i < length; i++)
	{
		value[i] = distribution(generator);
	}
	return *this;
}

large_uint large_uint::rand(uint32 n)
{
	std::random_device rd;
	std::default_random_engine generator(rd());
	std::uniform_int_distribution<uint64> distribution(0, 0xFFFFFFFF);
	for (uint16 i = 0; i < (n/32); i++)
	{
		value[i] = distribution(generator);
	}
	std::uniform_int_distribution<uint64> _distribution(0, 0xFFFFFFFF>>(32-(n%32)));
	value[n / 32] = _distribution(generator);
	return *this;
}