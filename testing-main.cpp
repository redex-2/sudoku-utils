#include <iostream>
#include <string>
#include "des.hpp"
#include "diffie-hellman.hpp"
#include "rsa.hpp"

des test;

int main()
{
	std::cout<<std::hex<<test.encrypt(0x0123456789ABCDEF, 0x133457799BBCDFF1)<<std::endl;
	std::cout<<std::hex<<test.decrypt(test.encrypt(0x0123456789ABCDEF, 0x133457799BBCDFF1), 0x133457799BBCDFF1)<<std::endl;
	//std::cout<<std::hex<<test.encrypt(0x123456ABCD132536, 0xAABB09182736CCDD)<<std::endl;
	return 0;
}