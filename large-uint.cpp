#include <iostream>
#include "large-uint.hpp"

large_uint::large_uint(uint16  bits)
{ 
	length = (bits + 31) / 32; 
	value = new uint32 [length]; 
	for (uint16 i = 0; i < length; i++) value[i]=0;
}

large_uint::large_uint(const large_uint &n) 
{ 
	length = n.length;
	value = new uint32 [length]; 
	for (uint16 i = 0; i < length; i++) value[i] = n.value[i]; 
} 

large_uint::~large_uint()
{
	delete [] value;
}

void large_uint::change_length(uint16 n)
{
	if(n==length)
	{
		return;
	}
	else if(n>length)
	{
		value = new uint32 [n-length]; 
		for (uint16 i = length-1; i < n; i++)
		{
			value[i] = 0;
		}
		length=n;
	}
	else
	{
		uint32 *copy_of_value = new uint32[length];
		for (uint16 i = 0; i < length; i++)
		{
			copy_of_value[i] = value[i];
		}
		delete [] value;
		value = new uint32 [n]; 
		for (uint16 i = 0; i < length; i++)
		{
			value[i]=copy_of_value[i];
		}
		delete [] copy_of_value;
	}
}

int large_uint::comp(const large_uint &n) const
{
	uint16 i;
	if (length > n.length)
	{
		for (i = length-1; i >= n.length; i--)
		{
			if (value[i] != 0)
			{
				return 1;
			}
		}
	}
	else if (n.length > length)
	{
		for (i = n.length-1; i >= length; i--)
		{
			if (n.value[i] != 0)
			{
				return -1;
			}
		}
	}
	else
	{
		i = length-1;
	}
	while (1)
	{
		if (value[i] > n.value[i])
		{
			return 1;
		}
		if (value[i] < n.value[i])
		{
			return -1;
		}
		if (i == 0)
		{
			return 0;
		}
		i--;
	}
}

int large_uint::comp(uint32 n) const
{
	for (uint16 i = length-1; i >= 1; i--)
	{
		if (value[i] != 0)
		{
			return 1;
		}
	}
	return value[0] > n ? 1 : value[0] < n ? -1 : 0;
}


bool large_uint::zero(void) const
{
	for (uint16 i = 0; i < length; i++)
	{
		if (value[i] != 0)
		{
			return false;
		}
	}
	return true;
}

uint16 large_uint::get_length(void)
{
	uint16 temp=0;
	for(int i = length-1; i >= 0; i--)
	{
		if(value[i]==0)
		{
			temp++;
		}
		else
		{
			break;
		}
	}
	return length-temp;
}

uint16 large_uint::get_length(const large_uint &n)
{
	uint16 temp=0;
	for(int i = n.length-1; i >= 0; i--)
	{
		if(n.value[i]==0)
			temp++;
		else
		{
			break;
		}
	}
	return n.length-temp;
}

uint32 large_uint::div(uint32 n)
{
	if(n==0) throw;
	uint16 i = length;
	uint32 rem = 0;
	while (i-- != 0)
	{
		uint64 divnd = (uint64) rem << 32 | (uint64) value[i];
		value[i] = divnd / n;
		rem = divnd % n;
	}
	return rem;
}

large_uint large_uint::div(const large_uint &divisor)
{ 
	if (divisor.zero())
		throw;
	
	large_uint remainder(length);
	large_uint dividend(*this);
	
	remainder = 0; 
	*this = 0;
	
	uint16 i = dividend.length; 
	while (i-- != 0)
	{ 
		uint16 bit = 32;
		while (bit-- != 0) 
		{ 
			remainder = (remainder<<1)|(dividend.value[i] >> bit & 1); 
			if (divisor <= remainder) 
			{ 
				*this = (*this<<1)|1; 
				remainder -= divisor; 
			}
			else 
			{
				*this = (*this<<1);
			}
		}
	}
	return remainder;
} 

void large_uint::add (const large_uint &n)
{
	uint64 carry = 0;
	for (uint16 i = 0; i < length; i++)
	{
		uint64 sum = (uint64)value[i] + (i < n.length ? n.value[i] : 0) + carry;
		value[i] = sum;
		carry = sum >> 32;
	}
}

void large_uint::add (const uint32 &n)
{
	uint64 sum = (uint64)value[0] + n;
	value[0] = sum;
	uint64 carry = sum >> 32;
	for (uint16 i = 1; i < length; i++)
	{
		sum = (uint64)value[i] + carry;
		value[i] = sum;
		carry = sum >> 32;
	}
}


void large_uint::sub (const large_uint &n)
{
	uint32 borrow = 0;
	for (uint16 i = 0; i < length; i++)
	{
		uint32 subtrahend = (i < n.length ? n.value[i] : 0) + borrow;
		borrow = (uint32)(value[i]) < subtrahend;
		value[i] -= subtrahend;
	}
}

void large_uint::sub (const uint32 &n)
{
	if (value[0] >= n)
		value[0] -= n;
	else
	{
		uint32 subtrahend = n;
		uint32 borrow = (uint32)(value[0]) < subtrahend;
		value[0] -= subtrahend;
		for (uint16 i = 1; i < length; i++)
		{
			subtrahend = borrow;
			borrow = (uint32)(value[i]) < subtrahend;
			value[i] -= subtrahend;
		}
	}
}


void large_uint::multi (const large_uint &n)
{
	uint16 i;
	uint32 *copy_of_value = new uint32[length];
	
	for (i = 0; i < length; i++)
	{
		copy_of_value[i] = value[i];
		value[i] = 0;
	}
	
	for (i = 0; i < length; i++)
	{
		uint16 j;
		for (j = 0; j < n.length; j++)
		{
			uint64 product = (uint64)copy_of_value[i] * n.value[j];
			uint16 k = i + j;
			while (product != 0)
			{
				product += value[k];
				value[k] = product;
				product >>= 32;
				k++;
			}
		}
	}
	delete [] copy_of_value;
}

void large_uint::multi (const uint32 &n)
{
	uint16 i;
	uint64 product = 0;
	for (i = 0; i < length; i++)
	{
		product += (uint64)n * value[i];
		value[i] = product;
		product >>= 32;
	}
}


large_uint large_uint::pow(large_uint &exponent, large_uint &modulus)
{
	large_uint r((32 * this->get_length()) * (32*exponent.get_length()) );
	r = 1;
	bool one = true;
	uint16 i = exponent.length;
	while (i-- != 0)
	{
		uint32 bit = 1 << 31;
		do
		{
			if (!one)
			{
				large_uint n(r);
				r *= n;
				r %= modulus;
			}
			if (exponent.value[i] & bit)
			{
				r *= *this;
				r %= modulus;
				one = false;
			}
			bit >>= 1;
		} while (bit != 0);
	}
	return r;
}

large_uint large_uint::pow(large_uint &exponent)
{
	large_uint r((32 * this->get_length()) * (32*exponent.get_length()) );
	r = 1;
	
	large_uint i(exponent.length);
	
	for(i = 0; i < exponent; i++)
	{
		r *= *this;
	}
	return r;
}

large_uint large_uint::sqrt(void) //return floor value of this sqrt
{ 
    if (*this == 0 || *this == 1) return *this;
	
    large_uint i = 1;
	large_uint result = 1; 
    while (result <= *this) 
    { 
		i++; 
		result = i * i; 
    } 
    return i - 1; 
} 

void large_uint::dump() const
{
	uint32 i;
	std::cout<<std::hex<<"0x ";
	std::streamsize w = std::cout.width( 8 );
	for (i = 0; i < length; i++)
	{
		std::cout.fill( '0' );
		std::cout<<value[length-1-i]<<" ";
	}
	std::cout.width( w );
	std::cout<<std::dec<<std::endl;
}

void large_uint::left_shift (const large_uint &n)
{
	if(get_length(n)>1)
	{
		left_shift(0xFFFFFFFF);
	}
	else
	{
		left_shift(n.value[0]);
	}
}


void large_uint::left_shift (const uint32 &n)
{
	
	uint32 *copy_of_value = new uint32[length];
	for (uint16 i = 0; i < length; i++)
	{
		copy_of_value[i] = value[i];
	}
	
	int m = n/32;
	if(m>length) m = length;
	int b = n%32;
	for(uint16 i = 0; i<m; i++)
	{
		value[i] = 0;
	}
	for(uint16 i = m; i < length; i++)
	{
		value[i]=copy_of_value[i-m];
	}
	if(b>0)
	{
		uint64 s = 0;
		uint64 l = 0;
		for(uint16 i = m; i < length; i++)
		{
			s = (uint64)value[i]<<b;
			value[i]=s|l;
			s >>= 32;
			l=s;
		}
	}
	delete [] copy_of_value;
}




	
void large_uint::right_shift (const large_uint &n)
{
	if(get_length(n)>1)
	{
		right_shift(0xFFFFFFFF);
	}
	else
	{
		right_shift(n.value[0]);
	}
}


void large_uint::right_shift (const uint32 &n)
{
	uint32 *copy_of_value = new uint32[length];
	
	for (uint16 i = 0; i < length; i++)
	{
		copy_of_value[i] = value[i];
	}
	
	uint32 m = n/32;
	if(m>length) m = length;
	uint32 b = n%32;
	int i = length-1;
	
	for(; i >= (length-m); i--)
	{
		value[i]=0;
	}
	for(; i >= 0; i--)
	{
		value[i]=copy_of_value[i+m];
	}
	
	if( b > 0 && m != length)
	{
		uint64 s = 0;
		uint64 l = 0;
		for(i = (length-m-1); i >= 0; i--)
		{
			s = ((uint64)value[i]<<32)>>b;
			value[i]=(s|l)>>32;
			s <<= 32;
			l=s;
		}
	}
	delete [] copy_of_value;
}



void large_uint::bit_and (const large_uint &n)
{
	if(length == n.length)
	{
		for (uint16 i = 0; i < length; i++)
		{
			value[i]=value[i]&n.value[i];
		}
	}
	else if(length > n.length)
	{
		uint16 i = 0;
		for (; i < length; i++)
		{
			value[i]=value[i]&n.value[i];
		}
		for (; i < n.length; i++)
		{
			value[i]=value[i]&0;
		}
	}
	else
	{
		uint16 i = 0;
		for (; i < n.length; i++)
		{
			value[i]=value[i]&n.value[i];
		}
		for (; i < length; i++)
		{
			value[i]=n.value[i]&0;
		}
	}
}

void large_uint::bit_and (const uint32 &n)
{
	value[0]&=n;
	for (uint16 i = 1; i < length; i++)
	{
		value[i]&=0;
	}
}


	
void large_uint::bit_or (const large_uint &n)
{
	if(length == n.length)
	{
		for (uint16 i = 0; i < length; i++)
		{
			value[i]=value[i]|n.value[i];
		}
	}
	else
	{
		for (uint16 i = 0; i < n.length; i++)
		{
			value[i]=value[i]|n.value[i];
		}
	}
}

void large_uint::bit_or (const uint32 &n)
{
	value[0]|=n;
}



void large_uint::bit_xor (const large_uint &n)
{
	if(length == n.length)
	{
		for (uint16 i = 0; i < length; i++)
		{
			value[i]=value[i]^n.value[i];
		}
	}
	else if(length > n.length)
	{
		uint16 i = 0;
		for (; i < length; i++)
		{
			value[i]=value[i]^n.value[i];
		}
		for (; i < n.length; i++)
		{
			value[i]=value[i]^0;
		}
	}
	else
	{
		uint16 i = 0;
		for (; i < n.length; i++)
		{
			value[i]=value[i]^n.value[i];
		}
		for (; i < length; i++)
		{
			value[i]=n.value[i]^0;
		}
	}
}

void large_uint::bit_xor (const uint32 &n)
{
	value[0]^=n;
	for (uint16 i = 1; i < length; i++)
	{
		value[i]^=0;
	}
}
