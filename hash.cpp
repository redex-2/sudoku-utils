#include "hash.hpp"
#include <iostream>

void _hash::split_message(const char *message, uint64 len, uint32** &out, uint64 &out_len, uint16 block_size)
{
	block_size=(block_size+31)/32;
	out = new uint32*[block_size];
	out_len = ((len+40)/(block_size*4))+1;
	
	for (uint16 i = 0; i < block_size; i++ )
	{
		out[i]=new uint32[((len+40)/(block_size*4))+1];
	}
	
	
	uint64 i=0;
	if(len>3)
	{
		for (i = 0; i < len-3; i+=4 )
		{
			out[i/4%block_size][i/(block_size*4)]=(uint32)message[i]<<24|message[i+1]<<16|message[i+2]<<8|message[i+3];
		}
	}
	
	
	if(len%4 ==1)
	{
		
		out[(i+1)/4%block_size][(i+1)/(block_size*4)]=(uint32)message[i]<<24|1<<23;
	}
	else if(len%4 == 2)
	{
		out[(i+1)/4%block_size][(i+1)/(block_size*4)]=(uint32)message[i]<<24|(uint32)message[i+1]<<16|1<<15;
	}
	else if(len%4 == 3)
	{
		out[(i+1)/4%block_size][(i+1)/(block_size*4)]=(uint32)message[i]<<24|(uint32)message[i+1]<<16|(uint32)message[i+2]<<8|1<<7;
	}
	else
	{
		out[(i+1)/4%block_size][(i+1)/(block_size*4)]=1<<31;
	}
	
	i+=4;
	
	while( (i/4%block_size) != (block_size-2) ) 
	{
		i+=4;
		out[i/4%block_size][i/(block_size*4)]=0;
	}
	len*=8;
	out[(i)/4%block_size][(i)/(block_size*4)]=len>>32;
	out[(i+4)/4%block_size][(i+1)/(block_size*4)]=len;
	
	out_len = i/(block_size*4)+1;
}