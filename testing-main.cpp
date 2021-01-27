#include <iostream>
#include <string>
#include "des.hpp"
#include "md-5.hpp"
#include "sha-2.hpp"
#include "types.hpp"
#include "prime.hpp"
#include "large-uint.hpp"
#include "toml.hpp"
#ifdef DATABASE
#include "database.hpp"
#endif

_des des;
_sha256 sha256;
_md5 md5;
_prime prime;
large_uint number(128);
_toml toml("config.toml");

int main()
{
	bool ok = 1;

	//des
	unsigned long long v0 = 0x0123456789ABCDEF;
	unsigned long long v1 = 0x85e813540f0ab405;
	unsigned long long key = 0x133457799BBCDFF1;

	unsigned long long v = des.encrypt(v0, key);

	//des test
	if (v == v1)std::cout << "[   " << "\033[32m" << "OK" << "\033[0m" << "   ] " << "DES encrypt\t" << std::hex << v << std::endl;
	else {std::cout << "[ " << "\033[31m" << "FAILED" << "\033[0m" << " ] " << "DES encrypt\t" << std::hex << v << std::endl; ok = 0;}
	v = des.decrypt(v1, key);
	
	if(v==v0)std::cout<<"[   "<<"\033[32m"<<"OK"<<"\033[0m"<<"   ] "<<"DES decrypt\t"<<std::hex<<v<<std::endl;
	else {std::cout<<"[ "<<"\033[31m"<<"FAILED"<<"\033[0m"<<" ] "<<"DES decrypt\t"<<std::hex<<v<<std::endl; ok = 0; }
	
	//sha256 test
	std::string sha0="8fc32d0d087d03115b7b200631109d66a60e052e434aa1609971130fa24d6d25";
	std::string sha = sha256.create((char*)"worldogjnosafworldogjnosafworldogjnosafworldogjnosafworldogjnosafworldogjnosafworldogjnosafworldogjnosaf", 104);
	if(sha==sha0)std::cout<<"[   "<<"\033[32m"<<"OK"<<"\033[0m"<<"   ] "<<"sha256\t"<<std::hex<<sha<<std::endl;
	else {std::cout<<"[ "<<"\033[31m"<<"FAILED"<<"\033[0m"<<" ] "<<"sha256\t"<<std::hex<<sha<<std::endl; ok = 0; }
	
	//md5 test
	std::string md0="9e107d9d372bb6826bd81d3542a419d6";
	std::string md = md5.create((char*)"The quick brown fox jumps over the lazy dog", 43); 
	if(md0==md)std::cout<<"[   "<<"\033[32m"<<"OK"<<"\033[0m"<<"   ] "<<"md5\t\t"<<std::hex<<md<<std::endl;
	else { std::cout << "[ " << "\033[31m" << "FAILED" << "\033[0m" << " ] " << "md5\t\t" << std::hex << md << std::endl; ok = 0; }

	std::cout<<std::endl;
	
	//prime
	prime.method(0);
	if(prime.check(11))std::cout<<"[   "<<"\033[32m"<<"OK"<<"\033[0m"<<"   ] "<<"prime standard\t"<<std::dec<<11<<std::endl;
	else {std::cout<<"[ "<<"\033[31m"<<"FAILED"<<"\033[0m"<<" ] "<<"prime standard\t"<<std::dec<<11<<std::endl; ok = 0;}
	if(!prime.check(28))std::cout<<"[   "<<"\033[32m"<<"OK"<<"\033[0m"<<"   ] "<<"prime standard\t"<<std::dec<<28<<std::endl;
	else {std::cout<<"[ "<<"\033[31m"<<"FAILED"<<"\033[0m"<<" ] "<<"prime standard\t"<<std::dec<<28<<std::endl; ok = 0;}
	if(prime.check(67))std::cout<<"[   "<<"\033[32m"<<"OK"<<"\033[0m"<<"   ] "<<"prime standard\t"<<std::dec<<67<<std::endl;
	else {std::cout<<"[ "<<"\033[31m"<<"FAILED"<<"\033[0m"<<" ] "<<"prime standard\t"<<std::dec<<67<<std::endl; ok = 0;}
	if(!prime.check(100))std::cout<<"[   "<<"\033[32m"<<"OK"<<"\033[0m"<<"   ] "<<"prime standard\t"<<std::dec<<100<<std::endl;
	else {std::cout<<"[ "<<"\033[31m"<<"FAILED"<<"\033[0m"<<" ] "<<"prime standard\t"<<std::dec<<100<<std::endl; ok = 0; }
	
	prime.method(1);
	if(prime.check(11))std::cout<<"[   "<<"\033[32m"<<"OK"<<"\033[0m"<<"   ] "<<"prime miller\t\t"<<std::dec<<11<<std::endl;
	else {std::cout<<"[ "<<"\033[31m"<<"FAILED"<<"\033[0m"<<" ] "<<"prime miller\t\t"<<std::dec<<11<<std::endl; ok = 0;}
	if(!prime.check(28))std::cout<<"[   "<<"\033[32m"<<"OK"<<"\033[0m"<<"   ] "<<"prime miller\t\t"<<std::dec<<28<<std::endl;
	else {std::cout<<"[ "<<"\033[31m"<<"FAILED"<<"\033[0m"<<" ] "<<"prime miller\t\t"<<std::dec<<28<<std::endl; ok = 0;}
	if(prime.check(67))std::cout<<"[   "<<"\033[32m"<<"OK"<<"\033[0m"<<"   ] "<<"prime miller\t\t"<<std::dec<<67<<std::endl;
	else {std::cout<<"[ "<<"\033[31m"<<"FAILED"<<"\033[0m"<<" ] "<<"prime miller\t\t"<<std::dec<<67<<std::endl; ok = 0;}
	if(!prime.check(100))std::cout<<"[   "<<"\033[32m"<<"OK"<<"\033[0m"<<"   ] "<<"prime miller\t\t"<<std::dec<<100<<std::endl;
	else {std::cout<<"[ "<<"\033[31m"<<"FAILED"<<"\033[0m"<<" ] "<<"prime miller\t\t"<<std::dec<<100<<std::endl; ok = 0;}
	
	prime.method(1);
	uint16 t;
	if((v=prime.next(11))==11)std::cout<<"[   "<<"\033[32m"<<"OK"<<"\033[0m"<<"   ] "<<"prime next\t\t"<<std::dec<<v<<std::endl;
	else if((((t = prime.method(0))||1)&&prime.check(v)&&(prime.method(t)||1)))std::cout<<"[ "<<"\033[33m"<<"ACCEPT"<<"\033[0m"<<" ] "<<"prime next\t\t"<<std::dec<<v<<std::endl;
	else {std::cout<<"[ "<<"\033[31m"<<"FAILED"<<"\033[0m"<<" ] "<<"prime next\t\t"<<std::dec<<v<<std::endl; ok = 0;}
	
	if((v=prime.next(28))==29)std::cout<<"[   "<<"\033[32m"<<"OK"<<"\033[0m"<<"   ] "<<"prime next\t\t"<<std::dec<<v<<std::endl;
	else if((((t = prime.method(0))||1)&&prime.check(v)&&(prime.method(t)||1)))std::cout<<"[ "<<"\033[33m"<<"ACCEPT"<<"\033[0m"<<" ] "<<"prime next\t\t"<<std::dec<<v<<std::endl;
	else { std::cout << "[ " << "\033[31m" << "FAILED" << "\033[0m" << " ] " << "prime next\t\t" << std::dec << v << std::endl; ok = 0; }
	
	if((v=prime.next(67))==67)std::cout<<"[   "<<"\033[32m"<<"OK"<<"\033[0m"<<"   ] "<<"prime next\t\t"<<std::dec<<v<<std::endl;
	else if((((t = prime.method(0))||1)&&prime.check(v)&&(prime.method(t)||1)))std::cout<<"[ "<<"\033[33m"<<"ACCEPT"<<"\033[0m"<<" ] "<<"prime next\t\t"<<std::dec<<v<<std::endl;
	else { std::cout << "[ " << "\033[31m" << "FAILED" << "\033[0m" << " ] " << "prime next\t\t" << std::dec << v << std::endl; ok = 0; }
	
	if((v=prime.next(0b1000000000000000000000000000000000000000000000000000000000))==144115188075855881)std::cout<<"[   "<<"\033[32m"<<"OK"<<"\033[0m"<<"   ] "<<"prime next\t\t"<<std::dec<<v<<std::endl;
	else if((((t = prime.method(0))||1)&&prime.check(v)&&(prime.method(t)||1)))std::cout<<"[ "<<"\033[33m"<<"ACCEPT"<<"\033[0m"<<" ] "<<"prime next\t\t"<<std::dec<<v<<std::endl;
	else {std::cout<<"[ "<<"\033[31m"<<"FAILED"<<"\033[0m"<<" ] "<<"prime next\t\t"<<std::dec<<v<<std::endl; ok = 0;}
	
	number.rand(40);
	number.dump();
	number.rand();
	number.dump();

	//toml
	toml.section();
	toml.key("main");

	if (toml.get() == "TOML STRING WITHOUT SECTION")std::cout << "[   " << "\033[32m" << "OK" << "\033[0m" << "   ] " << "toml without section string" << std::endl;
	else { std::cout << "[ " << "\033[31m" << "FAILED" << "\033[0m" << " ] " << "toml without section string" << std::endl; ok = 0; }


	toml.section("database");

	toml.key("port");
	uint64 temp_uint64;
	if (toml.get_uint(temp_uint64) && temp_uint64 == 2147483649)std::cout << "[   " << "\033[32m" << "OK" << "\033[0m" << "   ] " << "toml section uint" << std::endl;
	else { std::cout << "[ " << "\033[31m" << "FAILED" << "\033[0m" << " ] " << "toml section uint" << std::endl; ok = 0; }

	toml.key("int");
	int64 temp_int64;
	if (toml.get_int(temp_int64) && temp_int64 == -214748364)std::cout << "[   " << "\033[32m" << "OK" << "\033[0m" << "   ] " << "toml section int" << std::endl;
	else { std::cout << "[ " << "\033[31m" << "FAILED" << "\033[0m" << " ] " << "toml section int" << std::endl; ok = 0; }

	toml.section("time");
	toml.key("time");
	if (toml.get() == "2020-01-01T07:32:00+00:00")std::cout << "[   " << "\033[32m" << "OK" << "\033[0m" << "   ] " << "toml section time" << std::endl;
	else { std::cout << "[ " << "\033[31m" << "FAILED" << "\033[0m" << " ] " << "toml section time" << std::endl; ok = 0; }
	
	toml.section("database");
	toml.key("us.er");
	if (toml.get() == "root")std::cout << "[   " << "\033[32m" << "OK" << "\033[0m" << "   ] " << "toml section string" << std::endl;
	else { std::cout << "[ " << "\033[31m" << "FAILED" << "\033[0m" << " ] " << "toml section string" << std::endl; ok = 0; }
	

	toml.section("numbers");

	toml.key("ubin");
	if (toml.get_uint(temp_uint64) && toml.get_uint() == 10)std::cout << "[   " << "\033[32m" << "OK" << "\033[0m" << "   ] " << "toml section ubin" << std::endl;
	else { std::cout << "[ " << "\033[31m" << "FAILED" << "\033[0m" << " ] " << "toml section ubin" << std::endl; ok = 0; }

	toml.key("uoct");
	if (toml.get_uint(temp_uint64) && toml.get_uint() == 102030)std::cout << "[   " << "\033[32m" << "OK" << "\033[0m" << "   ] " << "toml section uoct" << std::endl;
	else { std::cout << "[ " << "\033[31m" << "FAILED" << "\033[0m" << " ] " << "toml section uoct" << std::endl; ok = 0; }

	toml.key("uhex");
	if (toml.get_uint(temp_uint64) && toml.get_uint() == 1020)std::cout << "[   " << "\033[32m" << "OK" << "\033[0m" << "   ] " << "toml section uhex" << std::endl;
	else { std::cout << "[ " << "\033[31m" << "FAILED" << "\033[0m" << " ] " << "toml section uhex" << std::endl; ok = 0; }


	toml.key("bin");
	if (toml.get_int(temp_int64) && toml.get_int() == -10)std::cout << "[   " << "\033[32m" << "OK" << "\033[0m" << "   ] " << "toml section bin" << std::endl;
	else { std::cout << "[ " << "\033[31m" << "FAILED" << "\033[0m" << " ] " << "toml section bin" << std::endl; ok = 0; }

	toml.key("oct");
	if (toml.get_int(temp_int64) && toml.get_int() == -102030)std::cout << "[   " << "\033[32m" << "OK" << "\033[0m" << "   ] " << "toml section oct" << std::endl;
	else { std::cout << "[ " << "\033[31m" << "FAILED" << "\033[0m" << " ] " << "toml section oct" << std::endl; ok = 0; }

	toml.key("hex");
	if (toml.get_int(temp_int64) && toml.get_int() == -1020)std::cout << "[   " << "\033[32m" << "OK" << "\033[0m" << "   ] " << "toml section hex" << std::endl;
	else { std::cout << "[ " << "\033[31m" << "FAILED" << "\033[0m" << " ] " << "toml section hex" << std::endl; ok = 0; }

	toml.section("server");
	bool temp_bool;

	toml.key("ipv6");
	if (toml.get_bit(temp_bool) && toml.get_bit() == 1)std::cout << "[   " << "\033[32m" << "OK" << "\033[0m" << "   ] " << "toml section bool" << std::endl;
	else { std::cout << "[ " << "\033[31m" << "FAILED" << "\033[0m" << " ] " << "toml section bool" << std::endl; ok = 0; }

	toml.key("ipv4");
	if (toml.get_bit(temp_bool) && toml.get_bit() == 0)std::cout << "[   " << "\033[32m" << "OK" << "\033[0m" << "   ] " << "toml section bool" << std::endl;
	else { std::cout << "[ " << "\033[31m" << "FAILED" << "\033[0m" << " ] " << "toml section bool" << std::endl; ok = 0; }


	if (ok)std::cout << std::endl << std::endl << "[   " << "\033[32m" << "OK" << "\033[0m" << "   ] " << "completed\t\t" << std::endl;
	else std::cout << std::endl << std::endl << "[ " << "\033[31m" << "FAILED" << "\033[0m" << " ] " << "completed\t\t" << std::endl;
	
	return 0;
}