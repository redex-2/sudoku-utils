#include "database.hpp"

void database::setup(std::string db_name, std::string db_user, std::string db_pass, uint32 db_port, std::string db_addr)
{
	//postgresql://[user[:password]@][netloc][:port][,...][/dbname]
	conndata="postgresql://";
	conndata+=db_user;
	conndata+=":";
	conndata+=db_pass;
	conndata+="@";
	conndata+=db_addr;
	conndata+="?port=";
	conndata+=db_port;
	conndata+="&dbname=";
	conndata+=db_name;
}

int database::connect(void)
{
	conn = PQconnectdb(conndata.c_str());
	if (PQstatus(conn) != CONNECTION_OK)
	{
		PQfinish(conn);
		return -1;
	}
	return 1;
}

void database::close(void)
{
	PQclear(res);
	PQfinish(conn);
}