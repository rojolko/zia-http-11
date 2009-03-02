#pragma once
#include <Winsock2.h>

enum	CL_STAT
{
	CONNECT,
	IDLE,
	FETCH,
	PROCESS,
	CLOSE
};

class Client
{
private:
	SOCKET		_sock;
	CL_STAT		_status;
//	Request		_request;
//	Response	_response;
//	Timer			_timer;
	int*			_readQueue;
	int*			_writeQueue;
public:
	Client(SOCKET);
	~Client(void);

	void	process();
	int*	needWrite();
	int*	needRead();
	
	void	canWrite(int*);
	void	canRead(int*);
};
