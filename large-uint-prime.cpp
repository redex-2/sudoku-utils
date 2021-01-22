#include "large-uint.hpp"

bool large_uint::prime_check_uint(large_uint d, large_uint number)
{
	large_uint x(*this);
	x.rand();
	x = x % (x - 4) + 2;

	x.pow(d, number);

	if (x == 1 || x == number - 1)
		return true;

	while (d != number - 1)
	{
		x = (x * x) % number;
		d *= 2;

		if (x == 1)return false;
		if (x == number - 1)return true;
	}
	return false;
}

bool large_uint::prime_check(void)
{
	large_uint d(*this);
	uint16 k = 100;
	if ((*this) == 2
		|| (*this) == 3) return true;
	if ((*this) % 2 == 0
		|| (*this) < 4) return false;

	d = (*this) - 1;
	while (d % 2 == 0)
		d /= 2;

	for (uint16 i = 0; i < k; i++)
		if (!prime_check_uint(d, (*this)))
			return false;
	return true;
}

large_uint large_uint::prime_next(void)
{
	if (*this % 2 == 0) (*this)++;
	while (!this->prime_check())
		*this += 2;
	return *this;
}