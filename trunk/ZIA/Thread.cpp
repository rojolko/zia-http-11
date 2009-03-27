#include "Thread.h"

// Constructeur
Thread::Thread() : tExec(false) { }

// Destructeur

Thread::~Thread()
{
  if (tExec)
    {
#if defined(WIN32) || defined(WIN64)
      if(!CloseHandle( _handle ))
		std::cout << "Erreur avec CloseHandle()! Error = " << GetLastError() << "." << std::endl;
#else
      pthread_detach( _handle );
#endif
    }
}

// Methodes


// Initialisation des Threads

HANDLE Thread::tStart(void (*f)())
{
  if (!this->tExec)
    {
#if defined(WIN32) || defined(WIN64)
		_handle = (HANDLE)_beginthreadex(NULL, 0, (unsigned int(__stdcall*)(void*))f, 0, 0, &_identThreadW32);
       // exception
      if (!_handle)
		throw("Thread Creation Problem.");
      return (_handle);
#else
      int valeur = pthread_create( &_handle, 0, ThreadLauncher, this );
      if( valeur != 0 )
	{
	  std::cout << std::endl << "Erreur avec pthread_create()!" << std::endl;
	}
#endif 
    }
}
