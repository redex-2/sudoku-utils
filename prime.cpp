#include "prime.hpp"

uint64 _prime::sqrt(uint64 &number)
{
	if(number == 0 || number == 1) return number;
	uint64 result = 1;
	uint64 i = 1;
	while (result <= number) 
    { 
		i++; 
		result = i * i; 
    } 
    return i - 1; 
}

bool _prime::miller_rabin(uint64 &)
{
	
}

bool _prime::standard(uint64 &number)
{
	if(number == 2 
		|| number == 3
		|| number == 5
		|| number == 7) return true;
	if(number%2 == 0 
		|| number < 11) return false;
	
	uint64 c = sqrt(number);
	while(number % c != 0)
	{
		if(c > 3)
		{
			c-=2;
		}
		else
		{
			return true;
		}
	}
	return false;
}

void _prime::method(uint16)
{
	
}

void _prime::precision(uint64)
{
	
}

uint16 _prime::check(uint64 number)
{
	return standard(number);
}

uint64 _prime::next(uint64)
{
	
}