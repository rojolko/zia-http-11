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

#define RQ_BUFF_SIZE 1000000

#define C_ENDL	"\r\n"
#define C_ENDL_SIZE 2

class Request
{
	SOCKET				_sock;
	int					_retVal;
	std::ostringstream	_bufStream;
	std::string			_temp;

	std::string			_requestMethod;
	std::string			_askedPath;
	std::string			_requestVers;
	unsigned int		_statusCode;

	std::map<std::string, std::string>				_varList;
	std::map<std::string, std::string>::iterator	_varIt;

	void		parseRequestMethodPathVers();
	void		parseVars();

	void		consumeRequest(const size_t &);
	const int	countInRequest(const std::string &);

	bool		isValidRequest();
public:
	Request(SOCKET sock);
	~Request(void);

	CL_STAT			processRequest();
	std::string		getRequest();
	int				getRetVal();

	void			parseRequest();
	void			dumpMPVandVars();
	const std::string	&getVers();
	const std::string	&getMethod();
	const std::string	&getPath();
};

#endif