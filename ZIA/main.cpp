#include "ConnectionManager.h"
#include <iostream>
#include <Windows.h>
#include "IModule.hpp"
#include "DynamicObject.h"

int	main(int ac, char *av[])
{
	ConnectionManager	*cm;
	DynamicObject		dObj;
	zia::IModule		*test;

	test = dObj.getInstanceFromModule(TEXT("zia_html.dll"));
	if (test)
	{
		std::cout << test->getName() << std::endl;
		delete test;
	}

	std::cout << "ZIA server Startup..." << std::endl;
	try
	{
		cm = new ConnectionManager(8080);
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
