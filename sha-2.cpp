#include "sha-2.hpp"

uint32 _sha2::rotate(uint32 data, uint16 num)
{
	return ((uint64)data<<32)>>num|(data>>num);
}

void _sha2::expand(void)
{
	for(i=16; i < 64; i++)
	{
		working[9] = rotate(word[i-15], 7) ^  rotate(word[i-15], 18) ^  (word[i-15] >> 3);
		working[10] = rotate(word[i-2], 17) ^  rotate(word[i-2], 19) ^  (word[i-2] >> 10);
		word[i] = word[i-16] +  working[9] +  word[i-7] +  working[10];
	}
}

void _sha2::compression(void)
{
	working[0] = hash[0]; 
	working[1] = hash[1]; 
	working[2] = hash[2]; 
	working[3] = hash[3]; 
	working[4] = hash[4]; 
	working[5] = hash[5]; 
	working[6] = hash[6]; 
	working[7] = hash[7];
	for(i=0; i < 64 ;i++)
	{
		working[10] = rotate(working[4], 6) ^ rotate(working[4], 11) ^ rotate(working[4], 25);
		working[11] = (working[4] & working[5]) ^ ((~working[4]) & working[6]);
		working[13] = working[7] + working[10] + working[11] + k[i] + word[i];
		working[9] = rotate(working[0], 2) ^ rotate(working[0], 13) ^ rotate(working[0], 22);
		working[12] = (working[0] & working[1]) ^ (working[0] & working[2]) ^ (working[1] & working[2]);
		working[14] = working[9] + working[12];
		working[7] = working[6];
		working[6] = working[5];
		working[5] = working[4];
		working[4] = working[3] + working[13];
		working[3] = working[2];
		working[2] = working[1];
		working[1] = working[0];
		working[0] = working[13] + working[14];
	}
	hash[0] += working[0];
	hash[1] += working[1];
	hash[2] += working[2];
	hash[3] += working[3];
	hash[4] += working[4];
	hash[5] += working[5];
	hash[6] += working[6];
	hash[7] += working[7];
}

std::string _sha2::create(char *message, uint64 len)
{
	sstring.str(std::string());
	
	hash[0] = 0x6a09e667; 
	hash[1] = 0xbb67ae85; 
	hash[2] = 0x3c6ef372; 
	hash[3] = 0xa54ff53a; 
	hash[4] = 0x510e527f; 
	hash[5] = 0x9b05688c; 
	hash[6] = 0x1f83d9ab; 
	hash[7] = 0x5be0cd19;
	
	_hash::split_message(message, len, data, out_len, block_size);
	
	for(j = 0; j < out_len; j++)
	{
		for(l = 0; l < 16; l++)
		{
			word[l]=*(*(data+l)+j);
		}
		expand();
		compression();
	}
	
	for (j = 0; j < 8; j++)
	{
		sstring.width( 8 );
		sstring.fill( '0' );
		sstring<<std::hex<<hash[j];
	}
	return sstring.str();
}

const uint32 _sha2::k[64]=
{
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
	0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
	0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
	0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
	0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
	0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
	0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
	0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};