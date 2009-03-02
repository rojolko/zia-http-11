#pragma once

class Thread
{
	// Variables
private:

	bool	tExec;

	#ifdef WIN32
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
	HANDLE	tStart(void *, void *);
	void		tStop();
};
