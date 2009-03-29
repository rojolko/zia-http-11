#include "Request.h"

Request::Request(SOCKET sock) : _buffStream()
{
	_sock = sock;
}

Request::~Request(void)
{
	for (this->_varIt = this->_varList.begin(); !this->_varList.empty(); this->_varIt = _varList.begin())
	{
	//	std::cout << "ConnectionManager Destructor - Erasing Var -> \"" << this->_varIt->first << "\"=\""<< this->_varIt->second << "\"" << std::endl;
		this->_varList.erase(this->_varIt->first);
	}
}

CL_STAT					Request::processRequest()
{
	char	readBuff[RQ_BUFF_SIZE];

	this->_retVal = recv(this->_sock, readBuff, RQ_BUFF_SIZE - 1, 0);
	// peut etre a modif ...
	if (this->_retVal <= 0)
		return (CLOSE);
	readBuff[this->_retVal] = 0;
	// std::cout << "Last BuffStream : [" << this->_buffStream.str() << "]" << std::endl;
	this->_buffStream << readBuff;
	// std::cout << "Current BuffStream : [" << this->_buffStream.str() << "]" << std::endl;
	return (PROCESS);
}

std::string			Request::getRequest()
{
	return (this->_buffStream.str());
}

int							Request::getRetVal()
{
	return this->_retVal;
}

void			Request::parseRequest()
{
	std::string	temp;

	temp = this->_buffStream.str();
	if (this->isValidRequest(temp))
	{
		this->parseRequestMethodParthVers(temp);
		this->parseVars(temp);
		this->dumpMPVandVars();
	}
	else
		std::cout << "Bad request" << std::endl;
}

bool	Request::isValidRequest(std::string &rq)
{
	int	disc;

	disc = std::string::npos;
	if (rq.find("OPTIONS") == disc &&
		rq.find("GET") == disc &&
		rq.find("HEAD") == disc &&
		rq.find("POST") == disc &&
		rq.find("PUT") == disc &&
		rq.find("DELETE") == disc &&
		rq.find("TRACE") == disc &&
		rq.find("CONNECT") == disc)
		return false;
	return true;
}

void	Request::parseRequestMethodParthVers(std::string &rq)
{
	//Primary Cut of the HttpRequest to get Request Type, Path, and Version.
	size_t	first_endl;
	size_t	next_space;

	next_space = rq.find_first_of(" ");
	this->_requestMethod = rq.substr(0, next_space);
	this->consumeRequest(rq, next_space);
	next_space = rq.find_first_of(" ");
	this->_askedPath = rq.substr(0, next_space);
	this->consumeRequest(rq, next_space);
	first_endl = rq.find_first_of(C_ENDL);
	this->_requestVers = rq.substr(0, first_endl);
	this->consumeRequest(rq, first_endl + (C_ENDL_SIZE - 1));
}

void	Request::parseVars(std::string &rq)
{
	int	process;
	size_t	first_endl;
	size_t	next_doubledot;
	std::string tmpVar;
	std::string tmpVal;

	process = 1;
	while (process)
	{
		next_doubledot = rq.find_first_of(":");
		tmpVar = rq.substr(0, next_doubledot);
		consumeRequest(rq, next_doubledot + 1);
		first_endl = rq.find_first_of(C_ENDL);
		tmpVal = rq.substr(0, first_endl);
		consumeRequest(rq, first_endl + (C_ENDL_SIZE - 1));
		this->_varList.insert(std::pair<std::string, std::string>(tmpVar, tmpVal));
		if (!rq.compare(C_ENDL))
			process = 0;
	}
}

void	Request::consumeRequest(std::string &rq, const size_t& idx)
{
	rq = rq.substr(idx + 1, rq.length() - idx);
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