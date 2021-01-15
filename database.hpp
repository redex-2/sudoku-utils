#ifndef database_hpp
#define database_hpp

#include <libpq-fe.h>
#include <string>
#include "types.hpp"

class database
{
	private:
		#ifdef POSTGRES
		PGconn *conn;
		PGresult *res = NULL;
		std::string conndata = "";
		#endif
		
	public:
		void setup(std::string db_name, std::string db_user, std::string db_pass, uint32 db_port, std::string db_addr);
		int connect(void);
		
		void close(void);
};

#endif