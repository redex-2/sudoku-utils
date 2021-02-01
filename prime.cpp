#include "prime.hpp"
#include <random>
#include <cmath>

uint64 _prime::sqrt(uint64 number)
{
	if(number == 0 || number == 1) return number;
	result = 1;
	j = 1;
	while (result <= number) 
    {
		j++;
		result = j * j;
    }
	if(result < number) j--;
    return (uint64)j;
}

uint64 _prime::power(uint64 base, uint64 exponent, uint64 mod) 
{
    result = 1;
    base = base % mod;
	
    while (exponent > 0) 
    { 
        if (exponent & 1) 
            result = (result*base)%mod; 
        exponent = exponent>>1;
        base = (base*base)%mod; 
    } 
    return result;
} 

bool _prime::miller_rabin_unit(uint32 d, uint32 number)
{
	std::random_device rd;
	std::default_random_engine generator(rd());
	std::uniform_int_distribution<uint64> distribution(2, number - 2);
	a = distribution(generator);

	x = power(a, d, number);

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

bool _prime::miller_rabin(uint32 number)
{
	if(number == 2 
		|| number == 3) return true;
	if(number%2 == 0 
		|| number < 4) return false;
		
	d = number - 1; 
    while (d%2 == 0) 
        d/=2; 
		
	for(i=0; i < k; i++)
		if (!miller_rabin_unit((uint32)d, number))
			return false;
	return true;
}

bool _prime::standard(uint64 number)
{
	if(number == 2 
		|| number == 3
		|| number == 5
		|| number == 7) return true;
	if(number%2 == 0 
		|| number < 11) return false;
	
	c = (uint64)std::sqrt(number);
	n = 3;
	while(number % n != 0)
	{
		if(n <= c)
			n+=2;
		else
			return true;
	}
	return false;
}

uint16 _prime::method(uint16 n)
{
	t=m;
	if(n>2)n=1;
	m=n;
	return t;
}

uint16 _prime::precision(uint32 p)
{
	t=k;
	k=p;
	return t;
}

uint16 _prime::check(uint64 number)
{
	if(m==0 || number >= 0xFFFFFFFF)
		return standard(number);
	else if(m==1)
		return miller_rabin((uint32)number);
	else if(m==2 && number < 0xFFFF)
		return standard(number);
	else
		return miller_rabin((uint32)number)+1;
}

uint64 _prime::next(uint64 number)
{
	if(number%2==0) number++;
	while(!check(number))
		number+=2;
	return number;
}