#include <iostream>
#include <string>
#include "des.hpp"
#include "md-5.hpp"
#include "sha-2.hpp"
#include "types.hpp"

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
	if(v==v1)std::cout<<"encryption ok!\t"<<std::hex<<v<<std::endl;
	else std::cout<<"encryption not work!\t"<<std::hex<<v<<std::endl;
	v = des.decrypt(v1, key);
	
	if(v==v0)std::cout<<"decryption ok!\t"<<std::hex<<v<<std::endl;
	else std::cout<<"decryption not work!\t"<<std::hex<<v<<std::endl;
	
	std::string sha0="8fc32d0d087d03115b7b200631109d66a60e052e434aa1609971130fa24d6d25";
	std::string sha = sha256.create((char*)"worldogjnosafworldogjnosafworldogjnosafworldogjnosafworldogjnosafworldogjnosafworldogjnosafworldogjnosaf", 104);
	if(sha==sha0)std::cout<<"sha256 ok!\t"<<std::hex<<sha<<std::endl;
	else std::cout<<"sha256 not work!\t"<<std::hex<<sha<<std::endl;
	
	std::string md0="9e107d9d372bb6826bd81d3542a419d6";
	std::string md = md5.create((char*)"The quick brown fox jumps over the lazy dog", 43); 
	if(md0==md)std::cout<<"md5 ok!\t"<<std::hex<<md<<std::endl;
	else std::cout<<"md5 not work!\t"<<std::hex<<md<<std::endl;

	return 0;
}