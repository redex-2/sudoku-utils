#include "large-uint.hpp"

void large_uint::operator = (const large_uint &n)
{
	uint16 i;
	for (i = 0; i < length && i < n.length; i++)
	{
		value[i] = n.value[i];
	}
	for (; i < length; i++)
	{
		value[i] = 0;
	}
}

void large_uint::operator = (uint32 n)
{
	value[0] = n;
	for (uint16 i = 1; i < length; i++)
	{
		value[i] = 0;
	}
}



large_uint large_uint::operator + (const large_uint &n) const
{
	large_uint temp(*this);
	temp.add(n);
	return temp;
}

large_uint large_uint::operator + (const uint32 &n) const
{
	large_uint temp(*this);
	temp.add(n);
	return temp;
}

large_uint large_uint::operator - (const large_uint &n) const
{
	large_uint temp(*this);
	temp.sub(n);
	return temp;
}

large_uint large_uint::operator - (const uint32 &n) const
{
	large_uint temp(*this);
	temp.sub(n);
	return temp;
}

large_uint large_uint::operator * (const large_uint &n) const
{
	large_uint temp(*this);
	temp.multi(n);
	return temp;
}

large_uint large_uint::operator * (const uint32 &n) const
{
	large_uint temp(*this);
	temp.multi(n);
	return temp;
}

large_uint large_uint::operator / (const large_uint &n) const
{
	large_uint temp(*this);
	temp.div(n);
	return temp;
}

large_uint large_uint::operator / (const uint32 &n) const	//ok
{
	large_uint temp(*this);
	temp.div(n);
	return temp;
}

large_uint large_uint::operator % (const large_uint &n) const
{
	large_uint temp(*this);
	temp.div(n);
	return temp;
}

large_uint large_uint::operator % (const uint32 &n) const	//ok
{
	large_uint temp(*this);
	temp=temp.div(n);
	return temp;
}




large_uint large_uint::operator &  (const large_uint &n)
{
	large_uint temp(*this);
	temp.bit_and(n);
	return temp;
}

large_uint large_uint::operator &  (const uint32 &n)
{
	large_uint temp(*this);
	temp.bit_and(n);
	return temp;
}

large_uint large_uint::operator |  (const large_uint &n)
{
	large_uint temp(*this);
	temp.bit_or(n);
	return temp;
}

large_uint large_uint::operator |  (const uint32 &n)
{
	large_uint temp(*this);
	temp.bit_or(n);
	return temp;
}

large_uint large_uint::operator ~  ()
{
	large_uint temp(*this);
	for (uint16 i = 0; i < length; i++)
	{
		temp.value[i]=~value[i];
	}
	return temp;
}

large_uint large_uint::operator ^  (const large_uint &n)
{
	large_uint temp(*this);
	temp.bit_xor(n);
	return temp;
}

large_uint large_uint::operator ^  (const uint32 &n)
{
	large_uint temp(*this);
	temp.bit_xor(n);
	return temp;
}

large_uint large_uint::operator << (const large_uint &n)
{
	large_uint temp(*this);
	temp.left_shift(n);
	return temp;
}

large_uint large_uint::operator << (const uint64 &n)
{
	large_uint temp(*this);
	temp.left_shift(n);
	return temp;
}

large_uint large_uint::operator >> (const large_uint &n)
{
	large_uint temp(*this);
	temp.right_shift(n);
	return temp;
}

large_uint large_uint::operator >> (const uint64 &n)
{
	large_uint temp(*this);
	temp.right_shift(n);
	return temp;
}





bool large_uint::operator && (const large_uint &n) const
{
	return ( (!zero()) && (!n.zero()) );
}

bool large_uint::operator && (const uint32 &n) const
{
	return ( (!zero()) && (n >0) );
}

bool large_uint::operator || (const large_uint &n) const
{
	return ( (!zero()) || (!n.zero()) );
}

bool large_uint::operator || (const uint32 &n) const
{
	return ( (!zero()) || (n >0) );
}

bool large_uint::operator ! () const
{
	return zero();
}


uint32  large_uint::operator [] (uint16  n)
{
	return value[n];
}



large_uint::operator uint32 ()
{
	return (value[0]);
}

large_uint::operator uint64 ()
{
	return (value[0]|(uint64)value[1]<<32);
}


large_uint& large_uint::operator ++ ()
{
	add(1);
	return *this;
}

large_uint& large_uint::operator -- ()
{
	sub(1);
	return *this;
}

large_uint  large_uint::operator ++ (int)
{
	large_uint temp(*this);
	add(1);
	return temp;
}

large_uint  large_uint::operator -- (int)
{
	large_uint temp(*this);
	sub(1);
	return temp;
}




void large_uint::operator >>= (const large_uint &n)
{
	right_shift(n);
}

void large_uint::operator >>= (const uint32 &n)
{
	right_shift(n);
}

void large_uint::operator <<= (const large_uint &n)
{
	right_shift(n);
}

void large_uint::operator <<= (const uint32 &n)
{
	left_shift(n);
}

void large_uint::operator &=  (const large_uint &n)
{
	bit_and(n);
}

void large_uint::operator &=  (const uint32 &n)
{
	bit_and(n);
}

void large_uint::operator |=  (const large_uint &n)
{
	bit_or(n);
}

void large_uint::operator |=  (const uint32 &n)
{
	bit_or(n);
}

void large_uint::operator ^=  (const large_uint &n)
{
	bit_xor(n);
}

void large_uint::operator ^=  (const uint32 &n)
{
	bit_xor(n);
}



void large_uint::operator += (const large_uint &n)
{
	add(n);
}

void large_uint::operator += (uint32 n)
{
	add(n);
}

void large_uint::operator -= (const large_uint &n)
{
	sub(n);
}

void large_uint::operator -= (uint32 n)
{
	sub(n);
}

void large_uint::operator *= (const large_uint &n)
{
	multi(n);
}

void large_uint::operator *= (uint32 n)
{
	multi(n);
}

void large_uint::operator /= (const large_uint &n) 
{ 
	div(n);
}

void large_uint::operator /= (uint32 n)
{
	div(n);
}

void large_uint::operator %= (const large_uint &n) 
{ 
	*this = div(n);
} 

void large_uint::operator %= (uint32 n)
{
	*this = div(n);
}


bool large_uint::operator == (const large_uint &n) const 
{
	return comp(n) == 0;
}

bool large_uint::operator == (const uint32  &n) const 
{
	return comp(n) == 0;
}

bool large_uint::operator != (const large_uint &n) const 
{
	return comp(n) != 0;
}

bool large_uint::operator != (const uint32  &n) const 
{
	return comp(n) != 0;
}

bool large_uint::operator >  (const large_uint &n) const 
{
	return comp(n) >  0;
}

bool large_uint::operator >  (const uint32  &n) const 
{
	return comp(n) >  0;
}

bool large_uint::operator >= (const large_uint &n) const 
{
	return comp(n) >= 0;
}

bool large_uint::operator >= (const uint32  &n) const 
{
	return comp(n) >= 0;
}

bool large_uint::operator <  (const large_uint &n) const 
{
	return comp(n) <  0;
}

bool large_uint::operator <  (const uint32  &n) const 
{
	return comp(n) <  0;
}

bool large_uint::operator <= (const large_uint &n) const 
{
	return comp(n) <= 0;
}

bool large_uint::operator <= (const uint32  &n) const 
{
	return comp(n) <= 0;
}