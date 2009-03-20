#include "ConnectionManager.h"
#include <iostream>

int	main(int ac, char *av[])
{
  ac = ac;
  ConnectionManager	*cm;

  std::cout << "ZIA server Startup..." << std::endl;
  try
    {
      cm = new ConnectionManager(8080);
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
