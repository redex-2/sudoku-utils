#ifndef toml_hpp
#define toml_hpp

#include "types.hpp"
#include <sstream>
#include <algorithm>
#include <fstream>
#include <string>
#include <iostream>
//#include <codecvt>

class _toml
{
	private:
		std::fstream tomlfile;
		std::string file = "";
		bool is_setting_up = 0;
		std::string s="";
		std::string k="";
		//uint16 type = 0;

		bool eos(std::string data);

	public:
		_toml(void);
		_toml(std::string filename);
		int setup(std::string filename);
		//bool section_list(std::string *);
		bool section(std::string section);
		bool section(void);
		//bool key_list(std::string *);
		bool key(std::string key);

		std::string get(void);

		int64 get_int(void);
		bool get_int(int64& result);

		uint64 get_uint(void);
		bool get_uint(uint64 &result);

		bool get_bit(void);
		bool get_bit(bool &result);

		//bool edit(std::string section, std::string key, std::string data);
};

#endif
