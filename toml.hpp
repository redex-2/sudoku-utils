#ifndef toml_hpp
#define toml_hpp

#include "types.hpp"
#include <sstream>
#include <algorithm>
#include <fstream>
//#include <codecvt>

/*
//      | 1 5 | 1 4 | 1 3 | 1 2 | 1 1 | 1 0 |  9  |  8  |  7  |  6  |  5  |  4  |  3  |  2  |  1  |  0  |
//      | TYPE|TYPE | TYPE|TYPE |  X  |  X  |  X  |  X  |  X  |  X  |  X  |  X  |  X  |  X  |  X  |  X  |
//UNDEF |  0  |  0  |  0  |  0  |  X  |  X  |  X  |  X  |  X  |  X  |  X  |  X  |  X  |  X  |  X  |  X  |
//number|  0  |  0  |  0  |  1  |  -  |  +  |  _  |FLOAT| BIN | OCT | DEC | HEX | EXP |  X  |  X  |  X  |
//spec	|  0  |  0  |  1  |  0  |  -  |  +  | INF | NAN |BOOL |  X  |  X  |  X  |  X  |  X  |  X  |  X  |
//str   |  0  |  1  |  0  |  0  |  0  |SINGL|MULTI|BASIC| LIT |  X  |  X  |  X  |  X  |  X  |  X  |  X  |
//array |  0  |  1  |  0  |  0  |  1  |SINGL|MULTI|  X  |  X  |  X  |  X  |  X  |  X  |  X  |  X  |  X  |
//time  |  1  |  0  |  0  |  0  |TIME | DATE| OFF |USE T|FLOAT|  X  |  X  |  X  |  X  |  X  |  X  |  X  |
*/

#define TOML_UNDEFINED					0

//types
#define TOML_NUMBER						(1<<12)
#define TOML_SPECIAL					(1<<13)
#define TOML_ARRAY						(1<<14)
#define TOML_TIME						(1<<15)

//number
#define TOML_NUMBER_NEGATIVE			(1<<11)
#define TOML_NUMBER_POSITIVE			(1<<10)
#define TOML_NUMBER_UNDERSCORE			(1<<9)
#define TOML_NUMBER_FLOATING			(1<<8)
#define TOML_NUMBER_BINARY				(1<<7)
#define TOML_NUMBER_OCTAL				(1<<6)
#define TOML_NUMBER_DECIMAL				(1<<5)
#define TOML_NUMBER_HEXADECIMAL			(1<<4)
#define TOML_NUMBER_EXPONENT			(1<<3)

//special
#define TOML_SPECIAL_NEGATIVE			(1<<11)
#define TOML_SPECIAL_POSITIVE			(1<<10)
#define TOML_SPECIAL_INFINITY			(1<<9)
#define TOML_SPECIAL_NOT_A_NUMBER		(1<<8)
#define TOML_SPECIAL_BOOL				(1<<7)

//array and string
#define TOML_ARRAY_STRING				(0)
#define TOML_ARRAY_ARRAY				(1<<11)
#define TOML_ARRAY_ARRAY_SINGLE_LINE	(1<<9)
#define TOML_ARRAY_STRING_SINGLE_LINE	(1<<9)
#define TOML_ARRAY_ARRAY_MULTI_LINE		(1<<8)
#define TOML_ARRAY_STRING_MULTI_LINE	(1<<8)
#define TOML_ARRAY_STRING_BASIC			(1<<7)
#define TOML_ARRAY_STRING_LITERAL		(1<<6)

//time
#define TOML_TIME_TIME					(1<<11)
#define TOML_TIME_DATE					(1<<10)
#define TOML_TIME_DATETIME				(TOML_TIME_TIME|TOML_TIME_DATE)
#define TOML_TIME_OFFSET				(1<<9)
#define TOML_TIME_USE_T_SEPARATOR		(1<<8)
#define TOML_TIME_FLOATING_SECOND		(1<<7)



class _toml
{
	private:
		std::fstream tomlfile;
		std::string file = "";
		bool is_setting_up = 0;
		std::string s="";
		std::string k="";
		uint32 type = TOML_UNDEFINED;
		
		bool eos(std::string data, uint32 i);

	public:
		_toml(void);
		_toml(std::string filename);
		int setup(std::string filename);
		//bool section_list(std::string *);
		bool section(std::string section);
		bool section(void);
		//bool table(std::string key);
		//bool key_list(std::string *);
		bool key(std::string key);

		uint16 get_type(void);

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
