#ifndef _REQUEST_H_
#define _REQUEST_H_

#if defined(WIN32) || defined(WIN64)

// WINDBLOWS
# include <Winsock2.h>

# define C_ENDL	"\r\n"
# define C_ENDL_SIZE 2

#else

// NUXSME
# include <sys/socket.h>
# define SOCKET			int

# define C_ENDL	"\n"
# define C_ENDL_SIZE 1

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

	std::string			_requestMethod;
	std::string			_askedPath;
	std::string			_requestVers;

	std::map<std::string, std::string>				_varList;
	std::map<std::string, std::string>::iterator	_varIt;

	void	parseRequestMethodParthVers(std::string &);
	void	parseVars(std::string &);
	void	consumeRequest(std::string &, const size_t &);
	bool	isValidRequest(std::string &);
public:
	Request(SOCKET sock);
	~Request(void);

	CL_STAT			processRequest();
	std::string		getRequest();
	int				getRetVal();

	void			parseRequest();
	void			dumpMPVandVars();
};

#endif