#include "Thread.h"
#include <iostream>


void functest()
{
	std::cout << "ca passe" << std::endl;

 _endthreadex(0);

}


void	ThreadExample()
{
	HANDLE h;
	Thread *t = new Thread();

	std::cout << "WTF" << std::endl;
	try
	  {
		h = t->tStart(functest);
	  }
	catch(char say[])
	  {
	  std::cout << "Exception :" << say << std::endl;
      std::cout << "Program Termination." << std::endl;
      }
}