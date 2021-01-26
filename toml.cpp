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

bool _toml::eos(std::string data)
{
	uint32 pos = data.find_first_not_of(" \t\r\n");
	if (pos != -1 && data[pos] != '#')
	{
		k.clear();
		return false;
	}
	return true;
}

bool _toml::section(std::string section)
{
	if (!is_setting_up) return false;
	tomlfile.open(file, std::ios::in);
	if (tomlfile.good())
	{
		std::stringstream sstream;
		std::string temp = "";
		s = "";
		while (std::getline(tomlfile, temp))
		{
			temp.erase(std::remove(temp.begin(), temp.end(), ' '), temp.end());
			temp.erase(std::remove(temp.begin(), temp.end(), '\t'), temp.end());
			if (temp == "["+section+"]" || temp == "["+section+"]"+'\r')
				break;
		}
		while (std::getline(tomlfile, temp))
		{
			uint32 pos = temp.find_first_not_of(" \t\r\n");
			if (pos != 0xFFFFFFFF && temp[pos] != '#')
			{
				if (temp[pos] == '[')
				{
					tomlfile.close();
					s = sstream.str();
					return true;
				}
				sstream << temp << std::endl;
			}
		}
		tomlfile.close();
	}
	return false;
}

bool _toml::section(void)
{
	tomlfile.open(file, std::ios::in);
	if (tomlfile.good())
	{
		std::stringstream sstream;
		std::string temp = "";
		s = "";
		while (std::getline(tomlfile, temp))
		{
			uint32 pos = temp.find_first_not_of(" \t\r\n");
			if (pos != 0xFFFFFFFF && temp[pos] != '#')
			{
				if (temp[pos] == '[')
				{
					tomlfile.close();
					s = sstream.str();
					return true;
				}
				sstream << temp << std::endl;
			}
		}
		tomlfile.close();
	}
	return false;
}

bool _toml::key(std::string key)
{
	if (!is_setting_up) return false;
	if (s != "")
	{
		std::stringstream sstream(s);
		std::string temp;
		bool multiline_basic_string = 0;
		bool multiline_literal_string = 0;
		uint64 multiline_array = 0;
		while (std::getline(sstream, temp))
		{
			uint32 pos = temp.find_first_of("=");
			if (pos != -1)
			{
				std::string key_str = temp;
				key_str.erase(pos);
				key_str.erase(std::remove(key_str.begin(), key_str.end(), ' '), key_str.end());
				key_str.erase(std::remove(key_str.begin(), key_str.end(), '\t'), key_str.end());
				if (key == key_str)
				{
					k.clear();
					//TODO:key in ' or "
					std::string key_data = temp;
					key_data.erase(0, pos + 1);
					uint32 first_char = key_data.find_first_not_of(" \t\r\n");
					uint32 last_char = key_data.find_last_not_of(" \t\r\n");
					key_data.erase(last_char+1, key_data.length());
					key_data.erase(0, first_char);
					
					//array test
					if (key_data[0] == '[')
					{
						//find end of array
						//TODO
						multiline_array = 1;
					}
					//bool test
					else if (key_data.length() >= 4 && key_data[0] == 't' && key_data[1] == 'r' && key_data[2] == 'u' && key_data[3] == 'e')
					{
						temp = key_data;
						temp.erase(0, 4);
						k.clear();
						k += "true";
						return eos(temp);
					}
					else if (key_data.length() >= 5 && key_data[0] == 'f' && key_data[1] == 'a' && key_data[2] == 'l' && key_data[3] == 's' && key_data[4] == 'e')
					{
						temp = key_data;
						temp.erase(0, 5);
						k.clear();
						k += "false";
						return eos(temp);
					}
					else if (key_data.length() >= 3 && key_data[0] == 'i' && key_data[1] == 'n' && key_data[2] == 'f')
					{
						temp = key_data;
						temp.erase(0, 3);
						k.clear();
						k += "inf";
						return eos(temp);
					}
					//nan
					else if (key_data.length() >= 3 && key_data[0] == 'n' && key_data[1] == 'a' && key_data[2] == 'n')
					{
						temp = key_data;
						temp.erase(0, 3);
						k.clear();
						k += "nan";
						return eos(temp);
					}
					//first char is number
					else if (key_data[0] >= '0' && key_data[0] <= '9' || key_data[0] == '+' || key_data[0] == '-')
					{
						//inf test
						if (key_data.length() >= 4 && (key_data[1] == 'i' && key_data[2] == 'n' && key_data[3] == 'f'))
						{
							if (key_data[0] == '-')
							{
								temp = key_data;
								temp.erase(0, 4);
								k.clear();
								k += "-inf";
								return eos(temp);
							}
							else if (key_data[0] == '+')
							{
								temp = key_data;
								temp.erase(0, 4);
								k.clear();
								k += "+inf";
								return eos(temp);
							}
							else
							{
								k.clear();
								return false;
							}
						}
						//+/-nan
						else if (key_data.length() >= 4 && (key_data[1] == 'n' && key_data[2] == 'a' && key_data[3] == 'n'))
						{
							if (key_data[0] == '-')
							{
								temp = key_data;
								temp.erase(0, 4);
								k.clear();
								k += "-nan";
								return eos(temp);
							}
							else if (key_data[0] == '+')
							{
								temp = key_data;
								temp.erase(0, 4);
								k.clear();
								k += "+nan";
								return eos(temp);
							}
							else
							{
								k.clear();
								return false;
							}
						}
						//date/datetime test
						else if (key_data[4] == '-' && key_data[7] == '-')
						{
							uint32 i = 0;
							while (key_data.length() >= i &&  key_data[i] >= '0' && key_data[i] <= '9')
							{
								k += key_data[i];
								i++;
								if (i == 4 || i == 7)
								{
									k += key_data[i];
									i++;
								}
								if (i == 10 && (key_data[i] == 'T' || key_data[i] == ' ') && key_data[i + 1] >= '0' && key_data[i + 1] <= '9')
								{
									k += key_data[i];
									i++;
								}
								if ((i == 13 || i == 16) && key_data[i] == ':')
								{
									k += key_data[i];
									i++;
								}
								if (i == 19 && key_data[i] == '.' && key_data[i + 1] >= '0' && key_data[i + 1] <= '9')
								{
									k += key_data[i];
									i++;
								}
								if (i >= 19 && (key_data[i] == '-' || key_data[i] == '+') && key_data[i + 1] >= '0' && key_data[i + 1] <= '9')
								{
									k += key_data[i];
									i++;
								}
								if (i >= 22 && key_data[i] == ':' && key_data[i + 1] >= '0' && key_data[i + 1] <= '9')
								{
									k += key_data[i];
									i++;
								}

							}
							if (key_data[i] == 'Z')
							{
								k += key_data[i];
								i++;
							}
							temp = key_data;
							temp.erase(0, i);
							return eos(temp);
						}
						//time test
						else if (key_data[2] == ':' && key_data[5] == ':')
						{
							uint32 i = 0;
							while (key_data.length() >= i && key_data[i] >= '0' && key_data[i] <= '9')
							{
								k += key_data[i];
								i++;
								if (i == 2 || i == 5)
								{
									k += key_data[i];
									i++;
								}
								if (i == 8 && key_data[i] == '.' && key_data[i + 1] >= '0' && key_data[i + 1] <= '9')
								{
									k += key_data[i];
									i++;
								}
							}
							temp = key_data;
							temp.erase(0, i);
							return eos(temp);
						}
						//binary
						else if (key_data.length() >= 3 && key_data[0] == '0' && key_data[1] == 'b')
						{
							uint32 i = 2;
							while (key_data.length() >= i && (key_data[i] >= '0' && key_data[i] <= '1' || key_data[i] == '_'))
							{
								k += key_data[i];
								i++;
							}
							temp = key_data;
							temp.erase(0, i);
							return eos(temp);
						}
						//octal
						else if (key_data.length() >= 3 && key_data[0] == '0' && key_data[1] == 'o')
						{
							uint32 i = 2;
							while (key_data.length() >= i && (key_data[i] >= '0' && key_data[i] <= '7' || key_data[i] == '_'))
							{
								k += key_data[i];
								i++;
							}
							temp = key_data;
							temp.erase(0, i);
							return eos(temp);
						}
						//hexadecinal
						else if (key_data.length() >= 3 && key_data[0] == '0' && key_data[1] == 'x')
						{
							uint32 i = 2;
							while (key_data.length() >= i && (key_data[i] >= '0' && key_data[i] <= '9' || key_data[i] >= 'a' && key_data[i] <= 'f' || key_data[i] >= 'A' && key_data[i] <= 'F' || key_data[i] == '_'))
							{
								k += key_data[i];
								i++;
							}
							temp = key_data;
							temp.erase(0, i);
							return eos(temp);
						}
						//-binary
						else if (key_data.length() >= 4 && key_data[0] == '-' && key_data[1] == '0' && key_data[2] == 'b')
						{
							uint32 i = 3;
							while (key_data.length() >= i && (key_data[i] >= '0' && key_data[i] <= '1' || key_data[i] == '_'))
							{
								k += key_data[i];
								i++;
							}
							temp = key_data;
							temp.erase(0, i);
							return eos(temp);
						}
						//-octal
						else if (key_data.length() >= 4 && key_data[0] == '-' && key_data[1] == '0' && key_data[2] == 'o')
						{
							uint32 i = 3;
							while (key_data[i] >= '0' && key_data[i] <= '7' || key_data[i] == '_')
							{
								k += key_data[i];
								i++;
							}
							temp = key_data;
							temp.erase(0, i);
							return eos(temp);
						}
						//-hexadecinal
						else if (key_data.length() >= 4 && key_data[0] == '-' && key_data[1] == '0' && key_data[2] == 'x')
						{
							uint32 i = 3;
							while (key_data[i] >= '0' && key_data[i] <= '9' || key_data[i] >= 'a' && key_data[i] <= 'f' || key_data[i] >= 'A' && key_data[i] <= 'F' || key_data[i] == '_')
							{
								k += key_data[i];
								i++;
							}
							temp = key_data;
							temp.erase(0, i);
							return eos(temp);
						}
						else
						{
							uint32 i = 0;
							if (key_data[0] == '+')
							{
								k += '+';
								i++;
							}
							else if (key_data[0] == '-')
							{
								k += '-';
								i++;
							}


							while (key_data.length() >= i && key_data[i] >= 0x30 && key_data[i] <= 0x39 || key_data[i] == '_')
							{
								k += key_data[i];
								i++;
							}
							if (key_data.length() == i || key_data[i] == ' ' || key_data[i] == '\t' || key_data[i] == '\n' || key_data[i] == '\r')
							{
								//int 
								temp = key_data;
								temp.erase(0, i);
								return eos(temp);
							}
							else if (key_data[i] == '.')
							{
								//float
								while (key_data.length() >= i && (key_data[i] >= '0' && key_data[i] <= '9' || key_data[i] == '_'))
								{
									k += key_data[i];
									i++;
								}
								if (key_data.length() == i || key_data[i] == ' ' || key_data[i] == '\t' || key_data[i] == '\n' || key_data[i] == '\r')
								{
									//float 3.14
									temp = key_data;
									temp.erase(0, i);
									return eos(temp);
								}
								else if (key_data[i] == 'E' || key_data[i] == 'e')
								{
									//float 3.14e+20
									k += key_data[i];
									i++;
									if(key_data[i] >= '0' && key_data[i] <= '9' || key_data[i] == '+' || key_data[i] == '-')
										k += key_data[i];
									while (key_data.length() >= i && key_data[i] >= '0' && key_data[i] <= '0')
									{
										k += key_data[i];
										i++;
									}
									temp = key_data;
									temp.erase(0, i);
									return eos(temp);
								}
							}
							else if (key_data[i] == 'E' || key_data[i] == 'e')
							{
								//int 15e426
								k += key_data[i];
								i++;
								if (key_data[i] >= '0' && key_data[i] <= '9' || key_data[i] == '+' || key_data[i] == '-')
									k += key_data[i];
								while (key_data.length() >= i && key_data[i] >= '0' && key_data[i] <= '9')
								{
									k += key_data[i];
									i++;
								}
								temp = key_data;
								temp.erase(0, i);
								return eos(temp);
							}
							else
							{
								k.clear();
								return false;
							}
						}
					}
					//string test
					else if (key_data[0] == '"')
					{
						key_data.erase(0, 1);
						if (key_data[0] == '"' && key_data[1] == '"')
						{
							multiline_basic_string = 1;
							//change multiline to single line
							//TODO
							//TODO:multiline in '''
						}
						else
						{
							uint32 i = 0;
							bool c = 0;
							while(1)
							{
								if (i > key_data.length())
								{
									return false;
								}
								if (key_data[i] == '\\')
								{
									c = !c;
								}
								else if (key_data[i] == '"' && c == 0)
								{
									temp = key_data;
									temp.erase(0, i+1);
									return eos(temp);
								}
								else if(c)
								{
									c = 0;
									if (key_data[i] == 'b') k += '\b';
									else if (key_data[i] == 't') k += '\t';
									else if (key_data[i] == 'n') k += '\n';
									else if (key_data[i] == 'f') k += '\f';
									else if (key_data[i] == 'r') k += '\r';
									else if (key_data[i] == '"') k += '"';
									else if (key_data[i] == '\\') k += '\\';
									else if (key_data[i] == 'u') k += "\\u";
									else if (key_data[i] == 'U') k += "\\U";
									else k += key_data[i];
								}
								else
								{
									k += key_data[i];
								}
								i++;
							}
						}
					}
					else if (key_data[0] == '\'')
					{
						key_data.erase(0, 1);
						if (key_data[0] == '\'' && key_data[1] == '\'')
						{
							multiline_literal_string = 1;
							//change multiline to single line
							//TODO
							//TODO:multiline in '''
						}
						else
						{
							uint32 i = 0;
							while(1)
							{
								if (i > key_data.length())
								{
									return false;
								}
								else if (key_data[i] == '\'')
								{
									temp = key_data;
									temp.erase(0, i+1);
									return eos(temp);
								}
								else
								{
									k += key_data[i];
								}
								i++;
							}
						}
					}
					else
						return false;
				}
			}
		}
	}
	return false;
}

std::string _toml::get(void)
{
	if (!is_setting_up) return "NULL";
	//std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> conv;
	//return conv.to_bytes(k);
	return k;
}



int64 _toml::get_int(void)
{
	if (!is_setting_up) return 0;
	uint64 temp;
	try
	{
		temp = stoll(k);
	}
	catch (...)
	{
		temp = 0;
	}
	return temp;
}

bool _toml::get_int(int64& result)
{
	if (!is_setting_up) return 0;
	try
	{
		result = stoll(k);
	}
	catch (...)
	{
		result = 0;
		return false;
	}
	return true;
}



uint64 _toml::get_uint(void)
{
	if (!is_setting_up) return 0;
	uint64 temp;
	try
	{
		temp = stoll(k);
	}
	catch (...)
	{
		temp = 0;
	}
	return temp;
}

bool _toml::get_uint(uint64 &result)
{
	if (!is_setting_up) return 0;
	try
	{
		result = stoll(k);
	}
	catch (...)
	{
		result = 0;
		return false;
	}
	return true;
}



bool _toml::get_bit(void)
{
	if (k == "true")
		return true;
	else if (k == "false")
		return false;
	else
		return false;
}

bool _toml::get_bit(bool& result)
{
	if (k == "true")
	{
		result = true;
		return true;
	}
	else if (k == "false")
	{
		result = false;
		return true;
	}
	else
	{
		result = false;
		return false;
	}
}