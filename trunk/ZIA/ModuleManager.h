#ifndef _MODULEMANAGER_H_
#define _MODULEMANAGER_H_

#include <list>
#include <iostream>
#include <Windows.h>

#include "IModule.hpp"
#include "ModuleInfo.h"
#include "DynamicObject.h"

class ModuleManager
{
private:
	static	ModuleManager*							_singleton;

	std::map<zia::IModule*, ModuleInfo*>			_moduleList;
	std::map<zia::IModule*, ModuleInfo*>::iterator	_it;

public:
	ModuleManager();
	~ModuleManager();
	static ModuleManager*							getInstance();
	static void										killInstance();

	void											LoadModule(LPCTSTR);

	const std::map<zia::IModule*, ModuleInfo*>		getModuleList(void) const;

	void											dumpLoadedModule(void);
};

#endif