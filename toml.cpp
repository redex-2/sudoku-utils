#include "toml.hpp"


_toml::_toml(void)
{
	return;
}

_toml::_toml(std::string filename) 
{
	is_setting_up = 1;
	file = filename;
	return;
}

int _toml::setup(std::string filename)
{
	is_setting_up = 1;
	file = filename;
	return 1;
}

bool _toml::section(std::string section)
{
	return true;
}

bool _toml::section(void)
{
	return true;
}

bool _toml::key(std::string key)
{
	return true;
}

bool _toml::get(std::string& data)
{
	return true;
}