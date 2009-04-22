#include "Config.h"

Config::Config(void)
{

}

Config::~Config(void)
{

}

bool	Config::getInfo(const std::string &key, std::string &result)
{
	if ((this->_varIt = this->_varList.find(key)) != this->_varList.end())
	{
		result = this->_varIt->second;
		return true;
	}
	else
		return false;
}

bool	Config::setInfo(const std::string &key, const std::string &value)
{
	if (key.compare("ip") && key.compare("port"))
	{
		if (this->_varList.find(key) != this->_varList.end())
			this->_varList.erase(key);
		this->_varList.insert(std::pair<std::string, std::string>(key, value));
		return true;
	}
	return false;
}

void	Config::dump()
{
	std::cout << "Config::dump() :" << std::endl;
	for (this->_varIt = this->_varList.begin(); this->_varIt != this->_varList.end(); ++this->_varIt)
		std::cout << "		-[" << this->_varIt->first << "] =[" << this->_varIt->second << "]" << std::endl; 
}

void	Config::setIp(const std::string& ip)
{
	if (this->_varList.find("ip") != this->_varList.end())
			this->_varList.erase("ip");
	this->_varList.insert(std::pair<std::string, std::string>("ip", ip));
}

void	Config::setPort(const std::string& port)
{
	if (this->_varList.find("port") != this->_varList.end())
			this->_varList.erase("port");
	this->_varList.insert(std::pair<std::string, std::string>("port", port));
}
