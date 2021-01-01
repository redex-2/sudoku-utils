#include "large-uint.hpp"

large_uint operator + (const uint32 &n, const large_uint &l)
{
	return l + n;
}

//large_uint operator - (const uint32&, const large_uint &){}

//large_uint operator / (const uint32&, const large_uint &){}

large_uint operator * (const uint32 &n, const large_uint &l)
{
	return l * n;
}

//large_uint operator % (const uint32&, const large_uint &){}

//large_uint operator & (const uint32&, const large_uint &){}

//large_uint operator | (const uint32&, const large_uint &){}

//large_uint operator ^ (const uint32&, const large_uint &){}

//large_uint operator << (const uint32&, const large_uint &){}

//large_uint operator >> (const uint32&, const large_uint &){}


bool operator && (const uint32 &n, const large_uint &l)
{
	return l && n;
}

bool operator || (const uint32 &n, const large_uint &l)
{
	return l || n;
}



//uint32 operator >>= (const uint32&, const large_uint &){}

//uint32 operator <<= (const uint32&, const large_uint &){}

//uint32 operator &= (const uint32&, const large_uint &){}

//uint32 operator |= (const uint32&, const large_uint &){}

//uint32 operator ^= (const uint32&, const large_uint &){}


bool operator == (const uint32  &n, const large_uint &l) 
{
	return l == n;
}

bool operator != (const uint32  &n, const large_uint &l) 
{
	return l != n;
}

bool operator > (const uint32  &n, const large_uint &l) 
{
	return l < n;
}

bool operator >= (const uint32  &n, const large_uint &l) 
{
	return l <= n;
}

bool operator < (const uint32  &n, const large_uint &l) 
{
	return l > n;
}

bool operator <= (const uint32  &n, const large_uint &l) 
{
	return l >= n;
}