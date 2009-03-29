#include "Request.h"

Request::Request(SOCKET sock) : _buffStream()
{
	_sock = sock;
}

Request::~Request(void)
{
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
	this->parseRequestTypePathVers(temp);
	std::cout << "Type = [" << this->_requestType << "]" << std::endl;
	std::cout << "Path = [" << this->_askedPath << "]" << std::endl;
	std::cout << "[" << this->_requestVers << "]" << std::endl;
	std::cout << "rq = [" << temp << "]" << std::endl;
}

void	Request::parseRequestTypePathVers(std::string &rq)
{
	//Primary Cut of the HttpRequest to get Request Type, Path, and Version.
	size_t	first_endl;
	size_t	next_space;

	first_endl = rq.find_first_of("\n");
	next_space = rq.find_first_of(" ");
	this->_requestType = rq.substr(0, next_space);
	this->consumeRequest(rq, next_space);
	next_space = rq.find_first_of(" ");
	this->_askedPath = rq.substr(0, next_space);
	this->consumeRequest(rq, next_space);
	first_endl = rq.find_first_of("\n");
	this->_requestVers = rq.substr(0, first_endl);
	this->consumeRequest(rq, first_endl);
}

void	Request::consumeRequest(std::string &rq, const size_t& idx)
{
	rq = rq.substr(idx + 1, rq.length() - idx);
}