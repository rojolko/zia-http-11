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

#include "IModule.hpp"
#include "cl_stat_enum.h"

#define RQ_BUFF_SIZE 1000000

#define C_ENDL	"\r\n"
#define C_ENDL_SIZE 2

class Request : public zia::IModuleRequest
{
private:
	SOCKET				_sock;
	int					_retVal;
	std::string			_request;
	std::string			_temp;

	std::string			_requestMethod;
	std::string			_askedPath;
	std::string			_requestVers;
	std::string			_body;
	unsigned int		_statusCode;

	std::map<std::string, std::string>				_varList;
	std::map<std::string, std::string>::iterator	_varIt;

	void		parseRequestMethodPathVers();
	void		parseVars();
	void		parseBody();
	void		consumeRequest(const size_t &);
	const int	countInRequest(const std::string &);

	bool		isValidRequest();
public:
	Request(void);
	Request(SOCKET sock);
	~Request(void);

	CL_STAT				processRequest();
	std::string			getRequest();
	int					getRetVal();

	void				parseRequest();
	void				dumpMPVandVars();
	const std::string&	getVersion(void) const;
	const std::string&	getMethod(void) const;
	const std::string&	getURI(void) const;
	const std::map<std::string, std::string>&	getHeaders(void) const;
	const std::string&	getContent(void) const;
	void				setMethod(const std::string&);
	void				setURI(const std::string&);
	void				setVersion(const std::string&);
	void				setHeader(const std::string&, const std::string&);
	void				setHeaders(const std::map<std::string, std::string>&);
	void				setContent(const std::string&);
};

#endif