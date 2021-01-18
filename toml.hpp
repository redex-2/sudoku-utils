#ifndef toml_hpp
#define toml_hpp

#include <cstring>
#include <fstream>

class _toml
{
	private:
		std::string file = "";
		bool is_setting_up = 0;
		std::string temp;

	public:
		_toml(void);
		_toml(std::string filename);
		int setup(std::string filename);
		bool section(std::string section);
		bool section(void);
		bool key(std::string key);
		bool get(std::string &data);
};

#endif
