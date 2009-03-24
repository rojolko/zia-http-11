#ifndef _REQUEST_H_
#define _REQUEST_H_

#if defined(WIN32) || defined(WIN64)

// WINDBLOWS
# include <Winsock2.h>

#else

// NUXSME
# include <sys/socket.h>
# define SOCKET			int

#endif

#include <iostream>
#include <sstream>

#include "cl_stat_enum.h"

#define RQ_BUFF_SIZE 512

class Request
{
	SOCKET				_sock;
	int					_retVal;
	std::ostringstream	_buffStream;
public:
	Request(SOCKET sock);
	~Request(void);

	CL_STAT			processRequest();
	std::string		getRequest();
	int				getRetVal();
};

#endif