#include <ctime>
#include "log.hpp"

int _log::setup(std::string filename)
{
	is_setting_up=1;
	file=filename;
	return 1;
}

_log::_log(std::string filename)
{
	is_setting_up=1;
	file=filename;
	return;
}

_log::_log(void)
{
	is_setting_up = 0;
	return;
}

int _log::write(std::string msg)	//write msg to logfile with time ISO9601
{
	if(is_setting_up)
	{
		lock.lock();
		myfile.open(_log::file, std::ios::out | std::ios::app | std::ios::ate); //write on the end of file
		if(myfile.good())// if file is correct open
		{
			u = time(NULL);	//get unix time
			ptm = gmtime ( &u );// set ptm to current time
			
			myfile<<ptm->tm_year+1900;
			myfile<<"-";
			if(ptm->tm_mon+1<10)myfile<<"0";
			myfile<<ptm->tm_mon+1;
			myfile<<"-";
			if(ptm->tm_mday<10)myfile<<"0";
			myfile<<ptm->tm_mday;
			myfile<<"T";
			if(ptm->tm_hour<10)myfile<<"0";
			myfile<<ptm->tm_hour;
			myfile<<":";
			if(ptm->tm_min<10)myfile<<"0";
			myfile<<ptm->tm_min;
			myfile<<":";
			if(ptm->tm_sec<10)myfile<<"0";
			myfile<<ptm->tm_sec;
			myfile<<"+00:00\t ";
			myfile<<msg;
			myfile<<"\n";
			myfile.close();
			lock.unlock();
			return 1;
		}
		lock.unlock();
	}
	return 0;
}