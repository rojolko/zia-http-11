#ifndef _REQUEST_H_
#define _REQUEST_H_

#if defined(WIN32) || defined(WIN64)

// WINDBLOWS
#include <Winsock2.h>

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
#include "ModuleInfo.h"
#include "ModuleManager.h"
#include "cl_stat_enum.h"
#include "globals.h"


#define RQ_BUFF_SIZE 2048

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
	short				_statusCode;

	std::map<std::string, std::string>				_varList;
	std::map<std::string, std::string>::iterator	_varIt;

	ModuleManager*									_mm;
	std::map<zia::IModule*, ModuleInfo*>			_moduleList;

	void		parseRequestMethodPathVers();
	void		parseVars();
	void		parseBody();
	void		parseContent();
	void		consumeRequest(const size_t &);
	const int	countInRequest(const std::string &);

	bool		isValidMethod();
	bool		isValidProtocolVersion();
	bool		isValidHeader();
public:
	Request(void);
	Request(const SOCKET sock);
	~Request(void);

	CL_STAT				processRequest(zia::IModuleClient *client);
	const std::string			getRequest() const;
	const int			getRetVal() const;
	const short			getStatusCode() const;

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