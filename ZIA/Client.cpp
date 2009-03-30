#include "Client.h"

Client::Client(SOCKET sock, sockaddr srcInf, SOCKADDR_IN srcInfIn)
{
	this->_status = CONNECT;
	this->_sock = sock;
	this->_clientSrcInf = srcInf;
	this->_clientSrcInfIn = srcInfIn;
	this->_request = NULL;
}

Client::~Client(void)
{
	if (this->_request != NULL)
		delete this->_request;
}

const char	*Client::getIp()
{
	return (inet_ntoa((in_addr)this->_clientSrcInfIn.sin_addr));
}

void	Client::setStatus(enum CL_STAT value)
{
	this->_status = value;
}

void	Client::allocRequest()
{
	if (this->_request == NULL)
		this->_request = new Request(this->_sock);
}

void	Client::process()
{

	if (this->_status != IDLE && this->_status != CLOSE)
	{
		if (this->_status == FETCH)
		{
			this->allocRequest();
			std::cout << "Client with IP:" << this->getIp() << " on socket #" << this->_sock << " is FETCHING" << std::endl;
			// Launch Read on the client's socket
			this->_status = this->_request->processRequest();
			std::cout << "ReadRet -> [" << this->_request->getRetVal() << "]" << std::endl;
		}
		else if (this->_status == PROCESS)
		{
			std::cout << "Request from IP:" << this->getIp() <</* " -> [" << this->_request->getRequest() << "]." <<*/ std::endl;
			//Build the response for the client (Review, We could need another state like "Respond")
			this->_request->parseRequest();
			this->_status = IDLE;
		} 
		else if (this->_status == CLOSE)
		{
#if defined(WIN32) || defined(WIN64)
			std::cout << "Client closed connection with error : " << WSAGetLastError() << std::endl;
#else
			perror("Client closed connection with error : ");
#endif
			std::cout << "Client with IP:" << this->getIp() << " closed connection on socket #" << this->_sock << std::endl;
		}
		if (this->_status == IDLE)
			;
	}
}

bool Client::toKill()
{
	if (this->_status == CLOSE /* || timeout exceed */ )
		return true;
	else
		return false;
}