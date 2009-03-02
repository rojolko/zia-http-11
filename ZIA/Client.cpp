#include "Client.h"

Client::Client(SOCKET sock, sockaddr srcInf, SOCKADDR_IN srcInfIn)
{
	this->_sock = sock;
	this->_clientSrcInf = srcInf;
	this->_clientSrcInfIn = srcInfIn;
}

Client::~Client(void)
{

}

const char	*Client::getIp()
{
	return (inet_ntoa((in_addr)this->_clientSrcInfIn.sin_addr));
}