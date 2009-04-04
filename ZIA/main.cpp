#include "ConnectionManager.h"
#include <iostream>
#include <Windows.h>
#include "IModule.hpp"
#include "DynamicObject.h"
#include "ModuleManager.h"

int	main(int ac, char *av[])
{
	ConnectionManager	*cm;
	ModuleManager		*mm;
	zia::IModule		*test;
	Config				cfg;
	cfg.setInfo("Super", "RienDuTout");
	mm = ModuleManager::getInstance();

	mm->LoadModule(TEXT("zia_html.dll"));
//	mm->LoadModule(TEXT("mod_test1.dll"));
//	mm->LoadModule(TEXT("mod_bf.dll"));

	mm->dumpLoadedModule();

	std::cout << "ZIA server Startup..." << std::endl;
	try
	{
		cm = new ConnectionManager(8080, cfg);
		//ThreadExample();
		while (1)
		{
			cm->fillFdSet();
			cm->doSelect();
			cm->fdProcess();
		}
	}
	catch(char const say[])
	{
		std::cout << av[0] << ": " << say << std::endl;
		std::cout << "Program Termination." << std::endl;
		exit(-1);
	}
}
