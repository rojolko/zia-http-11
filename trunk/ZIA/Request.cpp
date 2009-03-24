#include "Request.h"

Request::Request(SOCKET sock)
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
	this->_retVal = recv(this->_sock, this->_readBuff, RQ_BUFF_SIZE - 1, 0);
	// peut etre a modif ...
	if (this->_retVal <= 0)
		return (CLOSE);
	this->_readBuff[this->_retVal] = 0;
	this->_buffStream << this->_readBuff;
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