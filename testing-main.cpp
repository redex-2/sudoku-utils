#include <iostream>
#include <string>
#include "des.hpp"
#include "md-5.hpp"
#include "sha-2.hpp"
#include "types.hpp"
#include "database.hpp"

_des des;
_sha256 sha256;
_md5 md5;

int main()
{
	//des
	unsigned long long v0 = 0x0123456789ABCDEF;
	unsigned long long v1 = 0x85e813540f0ab405;
	unsigned long long key = 0x133457799BBCDFF1;
	
	unsigned long long v = des.encrypt(v0, key);
	
	//des test
	if(v==v1)std::cout<<"[   "<<"\033[32m"<<"OK"<<"\033[0m"<<"   ] "<<"DES encrypt\t"<<std::hex<<v<<std::endl;
	else std::cout<<"[ "<<"\033[31m"<<"FAILED"<<"\033[0m"<<" ] "<<"DES encrypt\t"<<std::hex<<v<<std::endl;
	v = des.decrypt(v1, key);
	
	if(v==v0)std::cout<<"[   "<<"\033[32m"<<"OK"<<"\033[0m"<<"   ] "<<"DES decrypt\t"<<std::hex<<v<<std::endl;
	else std::cout<<"[ "<<"\033[31m"<<"FAILED"<<"\033[0m"<<" ] "<<"DES decrypt\t"<<std::hex<<v<<std::endl;
	
	//sha256 test
	std::string sha0="8fc32d0d087d03115b7b200631109d66a60e052e434aa1609971130fa24d6d25";
	std::string sha = sha256.create((char*)"worldogjnosafworldogjnosafworldogjnosafworldogjnosafworldogjnosafworldogjnosafworldogjnosafworldogjnosaf", 104);
	if(sha==sha0)std::cout<<"[   "<<"\033[32m"<<"OK"<<"\033[0m"<<"   ] "<<"sha256\t"<<std::hex<<sha<<std::endl;
	else std::cout<<"[ "<<"\033[31m"<<"FAILED"<<"\033[0m"<<" ] "<<"sha256\t"<<std::hex<<sha<<std::endl;
	
	//md5 test
	std::string md0="9e107d9d372bb6826bd81d3542a419d6";
	std::string md = md5.create((char*)"The quick brown fox jumps over the lazy dog", 43); 
	if(md0==md)std::cout<<"[   "<<"\033[32m"<<"OK"<<"\033[0m"<<"   ] "<<"md5\t\t"<<std::hex<<md<<std::endl;
	else std::cout<<"[ "<<"\033[31m"<<"FAILED"<<"\033[0m"<<" ] "<<"md5\t\t"<<std::hex<<md<<std::endl;

	return 0;
}
