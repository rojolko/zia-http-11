#include "Response.h"

Response::Response(void)
{
	_bufReady = false;
}

Response::~Response(void)
{

}

void	Response::bufAdd(const char *str)
{
	this->_response.insert(this->_response.length(), str, strlen(str));
}

std::string	Response::getBuf()
{
	return this->_response;
}

void	Response::setBufReady(const bool br)
{
	this->_bufReady = br;
}

bool	Response::getBufReady()
{
	return this->_bufReady;
}