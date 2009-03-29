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

#include <map>
#include <string>

#include <iostream>
#include <sstream>

#include "cl_stat_enum.h"

#define RQ_BUFF_SIZE 512

class Request
{
	SOCKET				_sock;
	int					_retVal;
	std::ostringstream	_buffStream;

	std::string			_requestType;
	std::string			_askedPath;
	std::string			_requestVers;
	std::map<std::string, std::string>	_varList;

	void	parseRequestTypePathVers(std::string &);
	void	consumeRequest(std::string&, const size_t&);
public:
	Request(SOCKET sock);
	~Request(void);

	CL_STAT			processRequest();
	std::string		getRequest();
	int				getRetVal();

	void			parseRequest();
};

#endif