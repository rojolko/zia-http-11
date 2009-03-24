#include "Request.h"

Request::Request(SOCKET sock) : _buffStream()
{
	_sock = sock;
}

Request::~Request(void)
{
	// un truc a faire la ?
	// this->_buffStream
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
	if (this->_retVal == RQ_BUFF_SIZE - 1)
		return (FETCH);
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