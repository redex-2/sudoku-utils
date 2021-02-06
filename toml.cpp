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

bool _toml::eos(std::string data, uint32 i)
{
	data.erase(0, i);
	uint32 pos = data.find_first_not_of(" \t\r\n");
	if (pos != -1 && data[pos] != '#')
	{
		k.clear();
		type = TOML_UNDEFINED;
		return false;
	}
	return true;
}

bool _toml::section(std::string section)
{
	uint32 pos = section.find_first_not_of(" \t\r\n");
	if (pos != -1)
	{
		bool quotation = false;
		bool single = false;
		bool c = false;
		section.erase(0, pos);
		uint32 i = 0;
		if (section[i] == '"' && single == false)
		{
			quotation = 1;
			section.erase(0, 1);
			if (section.find_first_of('"') == -1) return false;
		}
		else if (i == '\'')
		{
			quotation = 1;
			single = true;
			section.erase(0, 1);
			if (section.find_first_of('\'') == -1) return false;
		}
		while (1)
		{
			if (section[i] == '"')
			{
				if (quotation && !single)
				{
					quotation = false;
					single = false;
				}
			}
			else if (i == '\'')
			{
				if (quotation && single)
				{
					quotation = false;
					single = false;
				}
			}
			else
				break;
			if (quotation)
			{
				if (i > section.length())
				{
					break;
				}
				else if (section[i] == '\\' && !c)
				{
					section.erase(i, 1);
					c = !c;
				}
				else if (section[i] == '"' && !c)
				{
					return eos(section, i + 1);
				}
				else if (c)
				{
					c = 0;
					if (section[i] == 'b') { section.insert(i, 1, '\b'); }
					else if (section[i] == 't') { section.insert(i, 1, '\t'); }
					else if (section[i] == 'n') { section.insert(i, 1, '\n'); }
					else if (section[i] == 'f') { section.insert(i, 1, '\f'); }
					else if (section[i] == 'r') { section.insert(i, 1, '\r'); }
					else if (section[i] == '"') { section.insert(i, 1, '"'); }
					else if (section[i] == '\\') { section.insert(i, 1, '\\'); }
					else if (section[i] == 'u') { section.insert(i, "\\u"); }
					else if (section[i] == 'U') { section.insert(i, "\\U"); }
					i++;
				}
				else
				{
					i++;
				}
			}
		}
	}
	else
	{
		return false;
	}
	if (!is_setting_up) return false;
	tomlfile.open(file, std::ios::in);
	if (tomlfile.good())
	{
		std::stringstream sstream;
		std::string temp = "";
		s = "";
		bool c = 0;
		while (std::getline(tomlfile, temp))
		{
			uint32 pos = temp.find_first_not_of(" \t\r\n");
			if (pos != 0xFFFFFFFF && temp[pos] == '[')
			{
				uint32 i = pos + 1;
				while (i <= temp.length())
				{
					if (temp[i] == section[i-1-pos])
					{
						i++;
					}
					else if (temp[i] == ']')
					{
						if (eos(temp, i+1))
						{
							c = 1;
							break;
						}
						else
						{
							break;
						}
					}
					else
					{
						break;
					}
				}
				if (c) break;
			}
		}
		if (!c) return false;
		while (std::getline(tomlfile, temp))//find end of section
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
		s = sstream.str();
		return true;
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
		s = sstream.str();
		return true;
	}
	return false;
}

bool _toml::key(std::string key)
{
	if (!is_setting_up) return false;
	k.clear();
	type = TOML_UNDEFINED;
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
						type = TOML_SPECIAL_BOOL | TOML_SPECIAL;
						k += "true";
						return eos(key_data, 4);
					}
					else if (key_data.length() >= 5 && key_data[0] == 'f' && key_data[1] == 'a' && key_data[2] == 'l' && key_data[3] == 's' && key_data[4] == 'e')
					{
						type = TOML_SPECIAL_BOOL | TOML_SPECIAL;
						k += "false";
						return eos(key_data, 5);
					}
					else if (key_data.length() >= 3 && key_data[0] == 'i' && key_data[1] == 'n' && key_data[2] == 'f')
					{
						type = TOML_SPECIAL_INFINITY;
						k += "inf";
						return eos(key_data, 3);
					}
					//nan
					else if (key_data.length() >= 3 && key_data[0] == 'n' && key_data[1] == 'a' && key_data[2] == 'n')
					{
						type = TOML_SPECIAL_NOT_A_NUMBER;
						k += "nan";
						return eos(key_data, 3);
					}
					//first char is number
					else if (key_data[0] >= '0' && key_data[0] <= '9' || key_data[0] == '+' || key_data[0] == '-')
					{
						//inf test
						if (key_data.length() >= 4 && (key_data[1] == 'i' && key_data[2] == 'n' && key_data[3] == 'f'))
						{
							if (key_data[0] == '-')
							{
								type = TOML_SPECIAL_INFINITY | TOML_SPECIAL_NEGATIVE;
								k += "-inf";
								return eos(key_data, 4);
							}
							else if (key_data[0] == '+')
							{
								type = TOML_SPECIAL_INFINITY | TOML_SPECIAL_POSITIVE;
								k += "+inf";
								return eos(key_data, 4);
							}
							else
							{
								return false;
							}
						}
						//+/-nan
						else if (key_data.length() >= 4 && (key_data[1] == 'n' && key_data[2] == 'a' && key_data[3] == 'n'))
						{
							if (key_data[0] == '-')
							{
								type = TOML_SPECIAL_NOT_A_NUMBER | TOML_SPECIAL_NEGATIVE;
								k += "-nan";
								return eos(key_data, 4);
							}
							else if (key_data[0] == '+')
							{
								type = TOML_SPECIAL_NOT_A_NUMBER | TOML_SPECIAL_POSITIVE;
								k += "+nan";
								return eos(key_data, 4);
							}
							else
							{
								return false;
							}
						}
						//date/datetime test
						else if (key_data[4] == '-' && key_data[7] == '-')
						{
							uint32 i = 0;
							type = TOML_TIME_DATE;
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
									type = TOML_TIME_DATETIME;
									if (key_data[i] == 'T') type |= TOML_TIME_USE_T_SEPARATOR;
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
									type |= TOML_TIME_FLOATING_SECOND;
									k += key_data[i];
									i++;
								}
								if (i >= 19 && (key_data[i] == '-' || key_data[i] == '+') && key_data[i + 1] >= '0' && key_data[i + 1] <= '9')
								{
									type |= TOML_TIME_OFFSET;
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
								type |= TOML_TIME_OFFSET;
								k += key_data[i];
								i++;
							}
							return eos(key_data, i);
						}
						//time test
						else if (key_data[2] == ':' && key_data[5] == ':')
						{
							type = TOML_TIME_TIME;
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
							return eos(key_data, i);
						}
						//binary
						else if (key_data.length() >= 3 && key_data[0] == '0' && key_data[1] == 'b')
						{
							type = TOML_NUMBER | TOML_NUMBER_BINARY;
							uint32 i = 2;
							k += "0b";
							while (key_data.length() >= i && (key_data[i] >= '0' && key_data[i] <= '1' || key_data[i] == '_'))
							{
								k += key_data[i];
								i++;
							}
							return eos(key_data, i);
						}
						//octal
						else if (key_data.length() >= 3 && key_data[0] == '0' && key_data[1] == 'o')
						{
							type = TOML_NUMBER | TOML_NUMBER_OCTAL;
							uint32 i = 2;
							k += "0o";
							while (key_data.length() >= i && (key_data[i] >= '0' && key_data[i] <= '7' || key_data[i] == '_'))
							{
								k += key_data[i];
								i++;
							}
							return eos(key_data, i);
						}
						//hexadecinal
						else if (key_data.length() >= 3 && key_data[0] == '0' && key_data[1] == 'x')
						{
							type = TOML_NUMBER | TOML_NUMBER_HEXADECIMAL;
							uint32 i = 2;
							k += "0x";
							while (key_data.length() >= i && (key_data[i] >= '0' && key_data[i] <= '9' || key_data[i] >= 'a' && key_data[i] <= 'f' || key_data[i] >= 'A' && key_data[i] <= 'F' || key_data[i] == '_'))
							{
								k += key_data[i];
								i++;
							}
							return eos(key_data, i);
						}
						//-binary
						else if (key_data.length() >= 4 && key_data[0] == '-' && key_data[1] == '0' && key_data[2] == 'b')
						{
							type = TOML_NUMBER | TOML_NUMBER_BINARY | TOML_NUMBER_NEGATIVE;
							uint32 i = 3;
							k += "-0b";
							while (key_data.length() >= i && (key_data[i] >= '0' && key_data[i] <= '1' || key_data[i] == '_'))
							{
								k += key_data[i];
								i++;
							}
							return eos(key_data, i);
						}
						//-octal
						else if (key_data.length() >= 4 && key_data[0] == '-' && key_data[1] == '0' && key_data[2] == 'o')
						{
							type = TOML_NUMBER | TOML_NUMBER_OCTAL | TOML_NUMBER_NEGATIVE;
							uint32 i = 3;
							k += "-0o";
							while (key_data[i] >= '0' && key_data[i] <= '7' || key_data[i] == '_')
							{
								k += key_data[i];
								i++;
							}
							return eos(key_data, i);
						}
						//-hexadecinal
						else if (key_data.length() >= 4 && key_data[0] == '-' && key_data[1] == '0' && key_data[2] == 'x')
						{
							type = TOML_NUMBER | TOML_NUMBER_HEXADECIMAL | TOML_NUMBER_NEGATIVE;
							uint32 i = 3;
							k += "-0x";
							while (key_data[i] >= '0' && key_data[i] <= '9' || key_data[i] >= 'a' && key_data[i] <= 'f' || key_data[i] >= 'A' && key_data[i] <= 'F' || key_data[i] == '_')
							{
								k += key_data[i];
								i++;
							}
							return eos(key_data, i);
						}
						else
						{
							type = TOML_NUMBER;
							uint32 i = 0;
							if (key_data[0] == '+')
							{
								type |= TOML_NUMBER_POSITIVE;
								k += '+';
								i++;
							}
							else if (key_data[0] == '-')
							{
								type |= TOML_NUMBER_NEGATIVE;
								k += '-';
								i++;
							}


							while (key_data.length() >= i && key_data[i] >= 0x30 && key_data[i] <= 0x39 || key_data[i] == '_')
							{
								k += key_data[i];
								i++;
							}
							if (key_data.length() >= i || key_data[i] == ' ' || key_data[i] == '\t' || key_data[i] == '\n' || key_data[i] == '\r')
							{
								//int 
								type |= TOML_NUMBER_DECIMAL;
								return eos(key_data, i);
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
									type |= TOML_NUMBER_FLOATING;
									return eos(key_data, i);
								}
								else if (key_data[i] == 'E' || key_data[i] == 'e')
								{
									//float 3.14e+20
									type |= TOML_NUMBER_FLOATING|TOML_NUMBER_EXPONENT;
									k += key_data[i];
									i++;
									if(key_data[i] >= '0' && key_data[i] <= '9' || key_data[i] == '+' || key_data[i] == '-')
										k += key_data[i];
									while (key_data.length() >= i && key_data[i] >= '0' && key_data[i] <= '0')
									{
										k += key_data[i];
										i++;
									}
									return eos(key_data, i);
								}
							}
							else if (key_data[i] == 'E' || key_data[i] == 'e')
							{
								//int 15e426
								type |= TOML_NUMBER_DECIMAL | TOML_NUMBER_EXPONENT;
								k += key_data[i];
								i++;
								if (key_data[i] >= '0' && key_data[i] <= '9' || key_data[i] == '+' || key_data[i] == '-')
									k += key_data[i];
								while (key_data.length() >= i && key_data[i] >= '0' && key_data[i] <= '9')
								{
									k += key_data[i];
									i++;
								}
								return eos(key_data, i);
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
							type = TOML_ARRAY | TOML_ARRAY_STRING | TOML_ARRAY_STRING_MULTI_LINE | TOML_ARRAY_STRING_BASIC;
							multiline_basic_string = 1;
							//change multiline to single line
							//TODO
							//TODO:multiline in '''
						}
						else
						{
							type = TOML_ARRAY | TOML_ARRAY_STRING | TOML_ARRAY_ARRAY_SINGLE_LINE | TOML_ARRAY_STRING_BASIC;
							uint32 i = 0;
							bool c = 0;
							while(1)
							{
								if (i > key_data.length())
								{
									return false;
								}
								if (key_data[i] == '\\' && !c)
								{
									c = !c;
								}
								else if (key_data[i] == '"' && !c)
								{
									return eos(key_data, i+1);
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
							type = TOML_ARRAY | TOML_ARRAY_STRING | TOML_ARRAY_STRING_MULTI_LINE | TOML_ARRAY_STRING_LITERAL;
							multiline_literal_string = 1;
							//change multiline to single line
							//TODO
							//TODO:multiline in '''
						}
						else
						{
							type = TOML_ARRAY | TOML_ARRAY_STRING | TOML_ARRAY_ARRAY_SINGLE_LINE | TOML_ARRAY_STRING_LITERAL;
							uint32 i = 0;
							while(1)
							{
								if (i > key_data.length())
								{
									return false;
								}
								else if (key_data[i] == '\'')
								{
									return eos(key_data, i+1);
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



uint16 _toml::get_type(void)
{
	return type;
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
	int64 result;
	if (get_int(result))return result;
	else return 0;
}

bool _toml::get_int(int64& result)
{
	if (!is_setting_up) return 0;
	std::string temp = k;
	try
	{
		if ((type & TOML_NUMBER) && (!(type & TOML_NUMBER_EXPONENT)))
		{
			if (type & TOML_NUMBER_BINARY)
			{
				temp.erase(temp.find_first_of('0'), 2);
				result = stoll(temp, 0, 2);
				return true;
			}
			else if (type & TOML_NUMBER_OCTAL)
			{
				temp.erase(temp.find_first_of('0'), 2);
				result = stoll(temp, 0, 8);
				return true;
			}
			else if (type & TOML_NUMBER_HEXADECIMAL)
			{
				temp.erase(temp.find_first_of('0'), 2);
				result = stoll(temp, 0, 16);
				return true;
			}
			else if (type & TOML_NUMBER_DECIMAL)
			{
				result = stoll(temp);
				return true;
			}
		}
		result = 0;
		return false;
	}
	catch (...)
	{
		result = 0;
		return false;
	}
}



uint64 _toml::get_uint(void)
{
	if (!is_setting_up) return 0;
	uint64 result;
	if (get_uint(result))return result;
	else return 0;
}

bool _toml::get_uint(uint64 &result)
{
	if (!is_setting_up) return 0;
	std::string temp = k;
	try
	{
		if ((type & TOML_NUMBER) && (!(type & TOML_NUMBER_NEGATIVE)) && (!(type & TOML_NUMBER_EXPONENT)))
		{
			if (type & TOML_NUMBER_BINARY)
			{
				temp.erase(temp.find_first_of('0'), 2);
				result = stoll(temp, 0, 2);
				return true;
			}
			else if (type & TOML_NUMBER_OCTAL)
			{
				temp.erase(temp.find_first_of('0'), 2);
				result = stoll(temp, 0, 8);
				return true;
			}
			else if (type & TOML_NUMBER_HEXADECIMAL)
			{
				temp.erase(temp.find_first_of('0'), 2);
				result = stoll(temp, 0, 16);
				return true;
			}
			else if (type & TOML_NUMBER_DECIMAL)
			{
				result = stoll(temp);
				return true;
			}
		}
		result = 0;
		return false;
	}
	catch (...)
	{
		result = 0;
		return false;
	}
}



bool _toml::get_bit(void)
{
	if (!is_setting_up) return 0;
	bool result;
	if (get_bit(result))return result;
	else return 0;
}

bool _toml::get_bit(bool& result)
{
	if (!is_setting_up) return 0;
	if ((type & TOML_SPECIAL) && (type & TOML_SPECIAL_BOOL))
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
	}
	result = false;
	return false;
}