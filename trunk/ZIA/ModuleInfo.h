#ifndef _MODULEINFO_H_
#define _MODULEINFO_H_

#include <iostream>
#include <string>

#include <TCHAR.H>

#include "IModule.hpp"
#include "mod_type_def.h"
#include "Tools.h"
#include "getAs.hpp"

typedef std::basic_string<TCHAR> tstring;

class			ModuleInfo
{
private:
	bool				_heritTable[10];

	std::string			_name;
	std::string			_path;

	std::list<unsigned short>	_ports;
	std::list<std::string>		_exts;
public:
	ModuleInfo(zia::IModule*, const char*);
	~ModuleInfo();

	const bool			isModule(const short) const;
	const std::string	getName(void) const;
	const std::string	getPath(void) const;

	void				dumpInfo(void);
	
	bool				isSpecificPort(const unsigned short &port);
	bool				isSpecificExt(const std::string &ext);
};

#endif
