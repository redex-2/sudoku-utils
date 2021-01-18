#ifndef toml_hpp
#define toml_hpp

#include "types.hpp"
#include <cstring>
#include <fstream>

class _toml
{
	private:
		std::string file = "";
		bool is_setting_up = 0;
		std::string s;
		std::string k;

	public:
		_toml(void);
		_toml(std::string filename);
		int setup(std::string filename);
		bool section_list(std::string *);
		bool section(std::string section);
		bool section(void);
		bool key_list(std::string *);
		bool key(std::string key);
		bool value_list(uint64 *);
		bool get(std::string &data);
};

#endif
