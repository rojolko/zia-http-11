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
	this->_bufStream << str;
}

std::string	Response::getBuf()
{
	return this->_bufStream.str();
}

void	Response::setBufReady(const bool br)
{
	this->_bufReady = br;
}

bool	Response::getBufReady()
{
	return this->_bufReady;
}