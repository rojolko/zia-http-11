#include "Thread.h"

// Constructeur
Thread::Thread() : tExec(false) { }

// Destructeur

Thread::~Thread()
{
	if (tExec)
	{
	#ifdef WIN32
		int resultat;
		resultat = CloseHandle( _handle );
		if( resultat == 0 )
			std::cout << std::endl << "Erreur avec CloseHandle()! Error = " << GetLastError() << "." << std::endl;
	#else
	pthread_detach( _handle );
	#endif
	}
}

// Methodes


// Initialisation des Threads

HANDLE Thread::tStart(void *f, void *param)
{
	if (!this->tExec)
	{
#ifdef WIN32
	_handle = (HANDLE)_beginthreadex(NULL, 0, (unsigned int(__stdcall*)(void*))f, (LPVOID)param, 0, &_identThreadW32);
	
	// exception
	if (!_handle)	
		std::cout << "Probleme au beginthreadex" << std::endl;
	return (_handle);
#else
	 int valeur = pthread_create( &_handle, 0, ThreadLauncher, this );
	 if( valeur != 0 )
	 std::cout << std::endl << "Erreur avec pthread_create()!" << std::endl;
#endif 
	}
}	


