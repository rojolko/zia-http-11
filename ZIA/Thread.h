#pragma once

#if defined(WIN32) || defined(WIN64)

#include <process.h> 
#include <Windows.h>
#include <iostream>

#else

# include <pthread.h>
# include <unistd.h>

#endif

class Thread
{
	// Variables
private:

	bool	tExec;

#if defined(WIN32) || defined(WIN64)
	HANDLE _handle;
	unsigned int _identThreadW32;
#else
	pthread_t _handle;
	static void * ThreadLauncher();
#endif 
	
	
public:
	// Constructeur
	Thread();

	// Destructeur
	~Thread();

	// Methods
#if defined(WIN32) || defined(WIN64)
	HANDLE	tStart(void (*f)());
#else
	pthread_t tStart(void*,void*);
#endif
	void	tStop();
};
