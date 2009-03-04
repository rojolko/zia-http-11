#pragma once

#include <Winsock2.h>

#include <string>
#include <iostream>

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
	sockaddr	_clientSrcInf;
	SOCKADDR_IN	_clientSrcInfIn;

	CL_STAT		_status;
//	Request		_request;
//	Response	_response;
//	Timer			_timer;
	int*			_readQueue;
	int*			_writeQueue;
	char			_readBuff[1024];
public:
	Client(SOCKET, sockaddr, SOCKADDR_IN);
	~Client(void);

	void	process();
	int*	needWrite();
	int*	needRead();
	
	void	canWrite(int*);
	void	canRead(int*);

	const char	*getIp();

	void	setStatus(enum CL_STAT value);
	bool	toKill();
};
