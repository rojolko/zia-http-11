#if defined(WIN32) || defined(WIN64)
# include <Windows.h>
#endif

#include "ConnectionManager.h"
#include <iostream>
#include "IModule.hpp"
#include "DynamicObject.h"
#include "ModuleManager.h"

int	main(int ac, char *av[])
{
	ConnectionManager	*cm;
	ModuleManager		*mm;
	zia::IModule		*test;
	Config				cfg;

	//std::cout.setstate(std::ios::failbit); /* Pour desactiver les sorties */
	cfg.setInfo("www-dir", "./");
	cfg.setInfo("tmp-dir", "./");
	cfg.setInfo("homepage", "index.bf");
	cfg.setInfo("homepage", "index.php");
	cfg.dump();

	mm = ModuleManager::getInstance();

//	mm->LoadModule("mod_bf.dll", cfg);
//	mm->LoadModule("zia_html.dll", cfg);
//	mm->LoadModule("zia_ban.dll", cfg);
//	mm->LoadModule("mod_test1.dll", cfg);

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
