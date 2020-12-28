#include <iostream>
#include <string>
#include "des.hpp"
#include "diffie-hellman.hpp"
#include "rsa.hpp"

_des des;

int main()
{
	unsigned long long v0 = 0x0123456789ABCDEF;
	unsigned long long v1 = 0x85e813540f0ab405;
	unsigned long long key = 0x133457799BBCDFF1;
	
	unsigned long long v = des.encrypt(v0, key);
	if(v==v1)std::cout<<"encryption ok!\t"<<std::hex<<v<<std::endl;
	else std::cout<<"encryption not work!\t"<<std::hex<<v<<std::endl;
	v = des.decrypt(v1, key);
	if(v==v0)std::cout<<"decryption ok!\t"<<std::hex<<v<<std::endl;
	else std::cout<<"decryption not work!\t"<<std::hex<<v<<std::endl;
	return 0;
}