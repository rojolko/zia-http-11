#ifndef _CLIENT_H_
#define _CLIENT_H_

#if defined(WIN32) || defined(WIN64)

// WINDBLOWS
# include <Winsock2.h>

#else

// NUXSME
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <unistd.h>
# define SOCKET			int
//# define sockaddr		struct sockaddr_in *
# define SOCKADDR_IN		struct sockaddr_in

#endif

#include <string>
#include <iostream>

#include "Request.h"
#include "Response.h"
#include "cl_stat_enum.h"
#include "Timer.h"
//#define	CL_BUFF_SIZE	512

class Client
{
private:
	SOCKET		_sock;
	sockaddr	_clientSrcInf;
	SOCKADDR_IN	_clientSrcInfIn;

	CL_STAT		_status;
	Request		*_request;
	Response	*_response;
	Timer		_timer;
	int*		_readQueue;
	int*		_writeQueue;
	//	char			_readBuff[CL_BUFF_SIZE];
public:
	Client(SOCKET, sockaddr, SOCKADDR_IN);
	~Client();

	void		process();
	bool		needtoWrite();
	int*		needWrite();
	int*		needRead();

	void		canWrite(int*);
	void		canRead(int*);
	void		allocRequest();
	void		allocResponse();
	const char	*getIp();

	void		setStatus(enum CL_STAT value);
	bool		toKill();
};

#endif