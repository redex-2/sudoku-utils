#include <iostream>
#include <string>
#include "des.hpp"
#include "diffie-hellman.hpp"
#include "rsa.hpp"

_des des;

int main()
{
	std::cout<<std::hex<<des.encrypt(0x0123456789ABCDEF, 0x133457799BBCDFF1)<<std::endl;
	std::cout<<std::hex<<des.decrypt(des.encrypt(0x0123456789ABCDEF, 0x133457799BBCDFF1), 0x133457799BBCDFF1)<<std::endl;
	return 0;
}