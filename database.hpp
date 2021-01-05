#ifndef database_hpp
#define database_hpp

#include <libpq-fe.h>
#include <string>
#include "../sudoku-utils/types.hpp"

class database
{
	private:
		PGconn *conn;
		std::string db_name;
		std::string db_user;
		std::string db_pass;
		uint32      db_port;
		std::string db_addr;
	public:
		void setup(std::string db_name, std::string db_user, std::string db_pass, uint32 db_port, std::string db_addr);
		int connect();
		
		
		int close();
};

#endif