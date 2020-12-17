#ifndef log_hpp
#define log_hpp

#include <string>
class _log 
{
	private:
	std::string file="";
	bool is_setting_up=0;
	public:
	_log(std::string filename);
	_log(void);
	int setup(std::string filename);
	int write(std::string msg);
};

#endif
