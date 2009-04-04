#include "Request.h"
#include "globals.h"

Request::Request(void)
{
	_statusCode = 0;
}

Request::Request(const SOCKET sock)
{
	_sock = sock;
	_statusCode = 0;
}

Request::~Request(void)
{
	for (this->_varIt = this->_varList.begin(); !this->_varList.empty(); this->_varIt = _varList.begin())
	{
		//		std::cout << "ConnectionManager Destructor - Erasing Var -> \"" << this->_varIt->first << "\"=\""<< this->_varIt->second << "\"" << std::endl;
		this->_varList.erase(this->_varIt->first);
	}
}

const CL_STAT					Request::processRequest()
{
	char	readBuff[RQ_BUFF_SIZE];

	this->_retVal = recv(this->_sock, readBuff, RQ_BUFF_SIZE - 1, 0);
	//<IModuleDoRead>

	// peut etre a modif ...
	if (this->_retVal <= 0)
		return (CLOSE);
	readBuff[this->_retVal] = 0;
	// std::cout << "Last BuffStream : [" << this->_buffStream.str() << "]" << std::endl;
	this->_request.insert(this->_request.length(), readBuff, this->_retVal);
	// std::cout << "Current BuffStream : [" << this->_buffStream.str() << "]" << std::endl;
	return (PROCESS);
}

const std::string			Request::getRequest() const
{
	return (this->_request);
}

const int	Request::getRetVal() const
{
	return this->_retVal;
}

const short	Request::getStatusCode() const
{
	return this->_statusCode;
}

void			Request::parseRequest()
{
	//std::cout << "Flux Entrant: {" << this->_request << "}" << std::endl;
	std::cout << "Size Request = " << this->_request.length() << std::endl;
	this->_temp = this->_request;
	if (this->isValidRequest())
	{
		this->parseRequestMethodPathVers();
		this->parseVars();
		this->dumpMPVandVars();
	}
	else
		std::cout << "Bad request" << std::endl;
}

const bool	Request::isValidRequest()
{
	int	i;

	for (i = 0; t_Methods[i] != NULL; ++i)
		if (this->_temp.find(t_Methods[i]) == 0)
			return true;
	this->_statusCode = 501;
	std::cout << "Bad Request - Method not found." << std::endl;
	return false;
}

void	Request::parseRequestMethodPathVers()
{
	//Primary Cut of the HttpRequest to get informations from Status-Line.
	size_t	first_endl;
	size_t	next_space;

	next_space = this->_temp.find_first_of(" ");
	this->_requestMethod = this->_temp.substr(0, next_space);
	this->consumeRequest(next_space);
	next_space = this->_temp.find_first_of(" ");
	this->_askedPath = this->_temp.substr(0, next_space);
	this->consumeRequest(next_space);
	first_endl = this->_temp.find_first_of(C_ENDL);
	this->_requestVers = this->_temp.substr(0, first_endl);
	this->consumeRequest(first_endl + (C_ENDL_SIZE - 1));
}

void	Request::parseVars()
{
	size_t	first_endl;
	size_t	next_doubledot;
	std::string tmpVar;
	std::string tmpVal;

	while (1)
	{
		if (!(this->_temp.find_first_of(":") < this->_temp.find_first_of(C_ENDL) && this->_temp.find_first_of(C_ENDL) != std::string::npos))
		{
			std::cout << "Bad Request Bad Syntax for headers-[" << this->_temp << "]" << std::endl;
			this->_statusCode = 400;
			break;
		}
		next_doubledot = this->_temp.find_first_of(":");
		tmpVar = this->_temp.substr(0, next_doubledot);
		std::cout << "tmpVar = [" << tmpVar << "]" << std::endl;
		consumeRequest(next_doubledot + 1);
		first_endl = this->_temp.find_first_of(C_ENDL);
		tmpVal = this->_temp.substr(0, first_endl);
		consumeRequest(first_endl + (C_ENDL_SIZE - 1));
		this->_varList.insert(std::pair<std::string, std::string>(tmpVar, tmpVal));
		if (!this->_temp.find_first_of(C_ENDL))
			break;
	}
}

void	Request::consumeRequest(const size_t& idx)
{
	if (this->_temp.compare("") != 0)
		this->_temp = this->_temp.substr(idx + 1, this->_temp.length() - idx);
}

const int	Request::countInRequest(const std::string &str)
{
	int	i;
	size_t	last;

	for (i = 0, last = 0; (last = this->_temp.find(str, last + (last ? str.length() : 0))) != std::string::npos; ++i);
	return i;
}

void	Request::dumpMPVandVars()
{
	std::cout << "Method =[" << this->_requestMethod << "]" << std::endl;
	std::cout << "Path =[" << this->_askedPath << "]" << std::endl;
	std::cout << "Vers =[" << this->_requestVers << "]" << std::endl;

	std::cout << "Request Vars Dump :" << std::endl;
	for (this->_varIt = this->_varList.begin(); this->_varIt != this->_varList.end(); ++this->_varIt)
		std::cout << "	[" << this->_varIt->first << "]=[" << this->_varIt->second << "]" << std::endl;
}

const std::map<std::string, std::string>&	Request::getHeaders(void) const
{
	return this->_varList;
}

const std::string&	Request::getContent(void) const
{
	return this->_body;
}

void	Request::setMethod(const std::string &str)
{
	this->_requestMethod = str;
}

void	Request::setURI(const std::string &str)
{
	this->_askedPath = str;
}

void	Request::setVersion(const std::string &str)
{
	this->_requestVers = str;
}

void	Request::setHeaders(const std::map<std::string, std::string> &hmap)
{
	this->_varList = hmap;
}

void	Request::setContent(const std::string &str)
{
	this->_body = str;
}

void	Request::setHeader(const std::string& key, const std::string &value)
{
	this->_varList.insert(std::pair<std::string, std::string>(key, value));
}

const std::string&	Request::getVersion(void) const
{
	return this->_requestVers;
}

const std::string&	Request::getMethod(void) const
{
	return this->_requestMethod;
}

const std::string&	Request::getURI(void) const
{
	return this->_askedPath;
}
