#include "prime.hpp"
#include <cstdlib>
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

large_uint _prime::power(uint64 base, uint64 exponent, uint64 mod) 
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

bool _prime::miller_rabin(uint64 number)
{
	if(number == 2 
		|| number == 3) return true;
	if(number%2 == 0 
		|| number < 4) return false;
		
	d = number - 1; 
    while (d%2 == 0) 
        d/=2; 
		
	for(uint64 i=0; i < k; i++)
	{
		a = 2 + std::rand() % (number - 4); 
		x = (uint64)power(a, d, number); 
	  
		if (x == 1  || x == number-1) 
		   continue;
		   
		while (d != number-1) 
		{ 
			x = (x*x)%number; 
			d *= 2; 
	  
			if (x == 1)return false; 
			if (x == number-1)continue; 
		} 
		return false;
	}
		
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
	
	const uint64 c = std::sqrt(number);
	uint64 n = 3;
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
		return miller_rabin(number);
	else if(m==2 && number < 0xFFFF)
		return standard(number);
	else
		return miller_rabin(number)+1;
}

uint64 _prime::next(uint64 number)
{
	if(number%2==0) number++;
	while(!check(number))
		number+=2;
	return number;
}