#ifndef _MODULEMANAGER_H_
#define _MODULEMANAGER_H_

#include <list>
#include <iostream>
#include <string>
#include <sstream>
#include <Windows.h>

#include "IModule.hpp"
#include "ModuleInfo.h"
#include "DynamicObject.h"
#include "Config.h"

class ModuleManager
{
private:
	static	ModuleManager*							_singleton;

	DynamicObject*									_loader;

	std::map<zia::IModule*, ModuleInfo*>			_moduleList;
	std::map<zia::IModule*, ModuleInfo*>::iterator	_it;

public:
	ModuleManager();
	~ModuleManager();
	static ModuleManager*							getInstance();
	static void										killInstance();

	void											LoadModule(LPCTSTR, Config&);

	std::map<zia::IModule*, ModuleInfo*>			getModuleList(void);

	void											dumpLoadedModule(void);
};

#endif