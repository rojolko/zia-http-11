#ifndef _MODULEINFO_H_
#define _MODULEINFO_H_

#include <iostream>
#include <string>

#include "IModule.hpp"
#include "mod_type_def.h"
#include "getAs.hpp"

class			ModuleInfo
{
private:
	bool				_heritTable[10];
	std::string			_name;
	std::string			_path;
public:
	ModuleInfo(zia::IModule*);
	~ModuleInfo();

	const bool			isModule(const short) const;
	const std::string	getName(void) const;
	const std::string	getPath(void) const;

	void				dumpInfo(void);
};

#endif