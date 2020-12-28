#include "des.hpp"
#include <string>
#include <cmath>
#include <bitset>
#include <iostream>

void des::split (unsigned long long in, unsigned int *left, unsigned int *right )
{
	*left=in>>32;
	*right=in&0xFFFFFFFF;
}

void des::split_key (unsigned long long in, unsigned int *left, unsigned int *right )
{
	*left = in>>28;
	*right = in&0xFFFFFFF;
}

void des::gen_key_array(unsigned long long key, unsigned long long keys[16])
{
	split_key(first_key_permutation(key), &leftKey, &rightKey);
	for (j = 0; j < 16; j++)
	{
		if (j == 0 || j == 1 || j == 8 || j == 15) 
		{
			leftKey<<=1;
			rightKey<<=1;
		}
		else 
		{
			leftKey<<=2;
			rightKey<<=2;
		}
		leftKey |= leftKey >>28&3;
		rightKey|= rightKey>>28&3;
		leftKey &= 0x0FFFFFFF;
		rightKey&= 0x0FFFFFFF;
	
		key56 = (unsigned long long)rightKey | (unsigned long long)leftKey<<28;
		keys[j] = second_key_permutation(key56);
	}
}

unsigned int des::sBox (unsigned long long input) {
	temp = 0;
	for (i = 0; i < 48; i += 6) {
		row = (input>>(42-i)&1)  | ((input>>(47-i))&1)<<1;	
		col = (input>>((43-i)))&0xF;
		
		if( i == 0 )
			temp |= (s1[row][col]<<28);
		else if( i == 6 )
			temp |= (s2[row][col]<<24);
		else if( i == 12 )
			temp |= (s3[row][col]<<20);
		else if( i == 18 )
			temp |= (s4[row][col]<<16);
		else if( i == 24 )
			temp |= (s5[row][col]<<12);
		else if( i == 30 )
			temp |= (s6[row][col]<<8);
		else if( i == 36 )
			temp |= (s7[row][col]<<4);
		else if( i == 42 )
			temp |= (s8[row][col]);
	}
	return temp;
}

unsigned long long des::first_permutation( unsigned long long in )
{
	temp = 0;
	for(i = 0; i < 64; i++)
	{
		temp|=((in>>(64-first_permutation_table[63-i]))&1)<<i;
	}
	return temp;
}

unsigned long long des::final_permutation( unsigned long long in )
{
	temp = 0;
	for(i = 0; i < 64; i++)
	{
		temp|=((in>>(64-final_permutation_table[63-i]))&1)<<i;
	}
	return temp;
}

unsigned long long des::expand_permutation( unsigned int in )
{
	temp = 0;
	for(i = 0; i < 48; i++)
	{
		temp|=(((unsigned long long)in>>(expanding_permutation_table[i]-1))&1)<<i;
	}
	return temp;
}

unsigned int des::p_permutation( unsigned int in )
{
	temp = 0;
	for(i = 0; i < 32; i++)
	{
		temp|=((in>>(32-p_permutation_table[31-i]))&1)<<i;
	}
	return temp;
}

unsigned long long des::first_key_permutation( unsigned long long in )
{
	temp = 0;
	for(i = 0; i < 56; i++)
	{
		temp|=((in>>(64-first_key_permutation_table[55-i]))&1)<<i;
	}
	return temp;
}


unsigned long long des::second_key_permutation( unsigned long long in )
{
	temp = 0;
	for(i = 0; i < 48; i++)
	{
		temp|=((in>>(56-second_key_permutation_table[47-i]))&1)<<i;
	}
	return temp;
}


unsigned long long des::encrypt (unsigned long long in, unsigned long long key)
{
	gen_key_array(key, keys);
	split(first_permutation(in), &left, &right);
	for (j = 0; j < 16; j++)
	{
		temp_right = (p_permutation(sBox(expand_permutation(right)^keys[j])))^left;
		if(j!=15)
		{
			left=right;
			right=temp_right;
		}
		else
		{
			left=temp_right;
		}
	}
	return final_permutation(((unsigned long long)left<<32)|right);
}

unsigned long long des::decrypt (unsigned long long in, unsigned long long key)
{
	gen_key_array(key, keys);
	split(first_permutation(in), &left, &right);
	for (j = 0; j < 16; j++)
	{
		temp_right = (p_permutation(sBox(expand_permutation(right)^keys[15-j])))^left;
		if(j!=15)
		{
			left=right;
			right=temp_right;
		}
		else
		{
			left=temp_right;
		}
	}
	return final_permutation(((unsigned long long)left<<32)|right);
}

const short des::first_permutation_table[64]=
{
	58, 50, 42, 34, 26, 18, 10,  2, 60, 52, 44, 36, 28, 20, 12,  4,
	62, 54, 46, 38, 30, 22, 14,  6, 64, 56, 48, 40, 32, 24, 16,  8,
	57, 49, 41, 33, 25, 17,  9,  1, 59, 51, 43, 35, 27, 19, 11,  3,
	61, 53, 45, 37, 29, 21, 13,  5, 63, 55, 47, 39, 31, 23, 15,  7
};

const short des::final_permutation_table[64]=
{
	40,  8, 48, 16, 56, 24, 64, 32, 39,  7, 47, 15, 55, 23, 63, 31,
	38,  6, 46, 14, 54, 22, 62, 30, 37,  5, 45, 13, 53, 21, 61, 29,
	36,  4, 44, 12, 52, 20, 60, 28, 35,  3, 43, 11, 51, 19, 59, 27,
	34,  2, 42, 10, 50, 18, 58, 26, 33,  1, 41,  9, 49, 17, 57, 25
};

const short des::expanding_permutation_table[48]=
{
	32,  1,  2,  3,  4,  5,  4,  5,  6,  7,  8,  9,
	 8,  9, 10, 11, 12, 13, 12, 13, 14, 15, 16, 17,
	16, 17, 18, 19, 20, 21, 20, 21, 22, 23, 24, 25,
	24, 25, 26, 27, 28, 29, 28, 29, 30, 31, 32, 01
};


const short des::first_key_permutation_table[56]=
{
	57, 49, 41, 33, 25, 17,  9,  1, 58, 50, 42, 34, 26, 18, 
	10,  2, 59, 51, 43, 35, 27, 19, 11,  3, 60, 52, 44, 36, 
	
	63, 55, 47, 39, 31, 23, 15,  7, 62, 54, 46, 38, 30, 22, 
	14,  6, 61, 53, 45, 37, 29, 21, 13,  5, 28, 20, 12,  4
};

const short des::second_key_permutation_table[48]=
{
	14, 17, 11, 24,  1,  5, 
	 3, 28, 15,  6, 21, 10, 
	23, 19, 12,  4, 26,  8, 
	16,  7, 27, 20, 13,  2, 
	41, 52, 31, 37, 47, 55, 
	30, 40, 51, 45, 33, 48, 
	44, 49, 39, 56, 34, 53, 
	46, 42, 50, 36, 29, 32
};

const short des::p_permutation_table[32]=
{
	16,  7, 20, 21, 29, 12, 28, 17,
	 1, 15, 23, 26,  5, 18, 31, 10,
	 2,  8, 24, 14, 32, 27,  3,  9,
	19, 13, 30,  6, 22, 11,  4, 25
};



const short des::s1[4][16]=
{
	14,  4, 13,  1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7,
	 0, 15,  7,  4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8,
	 4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0,
	15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13
};

const short des::s2[4][16]=
{
	15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10,
	 3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5,
	 0, 14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3,  2, 15,
	13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9
};

const short des::s3[4][16]=
{
	10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8,
	13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1,
	13,  6,  4,  9,  8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14,  7,
	 1, 10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12
};

const short des::s4[4][16]=
{
	 7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15,
	13,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9,
	10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4,
	 3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14
};

const short des::s5[4][16]=
{
	 2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9,
	14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6,
	 4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14,
	11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3
};

const short des::s6[4][16]=
{
	12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11,
	10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8,
	 9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6,
	 4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13
};

const short des::s7[4][16]=
{
	 4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1,
	13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6,
	 1,  4, 11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9,  2,
	 6, 11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12
};

const short des::s8[4][16]=
{
	13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7,
	 1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2,
	 7, 11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8,
	 2,  1, 14,  7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11
};