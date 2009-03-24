#include "Client.h"

Client::Client(SOCKET sock, sockaddr srcInf, SOCKADDR_IN srcInfIn)
{
	this->_status = CONNECT;
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

void	Client::setStatus(enum CL_STAT value)
{
	this->_status = value;
}

void	Client::process()
{
	int		readRet;
	//C'est moche I know :D
	this->_request = new Request(this->_sock);

	if (this->_status != IDLE && this->_status != CLOSE)
	{
		if (this->_status == FETCH)
		{
			std::cout << "Client with IP:" << this->getIp() << " on socket #" << this->_sock << " is FETCHING" << std::endl;
			//Launch Read on the client's socket
			this->_status = this->_request->processRequest();
			// readRet = recv(this->_sock, this->_readBuff, CL_BUFF_SIZE - 1, 0);
			// this->_readBuff[readRet] = '\0';
			std::cout << "ReadRet -> [" << this->_request->getRetVal() << "]" << std::endl;
			// if (readRet > 0)
			//	this->_status = PROCESS;
			// else
			// {
			// 	std::cout << WSAGetLastError() << std::endl;
			// 	std::cout << "Client with IP:" << this->getIp() << " closed connection on socket #" << this->_sock << std::endl;
			// 	this->_status = CLOSE;
			// }
		}
		if (this->_status == PROCESS)
		{
			// std::cout << "Request from IP:" << this->getIp() << " -> [" << this->_readBuff << "]." << std::endl;
			std::cout << "Request from IP:" << this->getIp() << " -> [" << this->_request->getRequest() << "]." << std::endl;
			//Build and send the response to the client
			this->_status = IDLE;
		}
		if (this->_status == CLOSE)
		{
			std::cout << WSAGetLastError() << std::endl;
			std::cout << "Client with IP:" << this->getIp() << " closed connection on socket #" << this->_sock << std::endl;
		}
	}
	delete this->_request;
}

bool Client::toKill()
{
	if (this->_status == CLOSE /* || timeout exceed */ )
		return true;
	else
		return false;
}