#pragma once

#include <map>
#include <string>
#include <iostream>

#include "IModule.hpp"


class Config :	public zia::IModuleConfig
{
private:
	std::map<std::string, std::string>				_varList;
	std::map<std::string, std::string>::iterator	_varIt;
public:
	Config(void);
	~Config(void);

	void	dump();
	bool	getInfo(const std::string &key, std::string &result);
	bool	setInfo(const std::string &key, const std::string &value);
	void	setIp(const std::string&);
	void	setPort(const std::string&);
};
