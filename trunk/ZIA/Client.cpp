#include "Client.h"

Client::Client(SOCKET sock, sockaddr srcInf, SOCKADDR_IN srcInfIn)
{
	this->_status = CONNECT;
	this->_sock = sock;
	this->_clientSrcInf = srcInf;
	this->_clientSrcInfIn = srcInfIn;
	this->_request = NULL;
	this->_response = NULL;
	this->_timer.start();
}

Client::~Client()
{
	std::cout << "Client with IP:" << this->getIp() << " closed connection after " << this->_timer.getTicks() << "ms on socket #" << this->_sock << std::endl;
	this->delRequest();
	this->delResponse();
	closesocket(this->_sock);
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

void	Client::allocResponse()
{
	if (this->_response == NULL)
		this->_response = new Response();
}

void	Client::delRequest()
{
	if (this->_request != NULL)
	{
		delete this->_request;
		this->_request = NULL;
	}
}

void	Client::delResponse()
{
	if (this->_response != NULL)
	{
		delete this->_response;
		this->_response = NULL;
	}
}

void	Client::process()
{
	if (this->_status == FETCH)
	{
		this->allocRequest();
		//		std::cout << "Client with IP:" << this->getIp() << " on socket #" << this->_sock << " is FETCHING" << std::endl;
		// Launch Read on the client's socket
		this->_status = this->_request->processRequest();
		//		std::cout << "ReadRet -> [" << this->_request->getRetVal() << "]" << std::endl;
	}
	else if (this->_status == PROCESS)
	{
		//		std::cout << "Request from IP:" << this->getIp() <</* " -> [" << this->_request->getRequest() << "]." <<*/ std::endl;
		//Build the response for the client (Review, We could need another state like "Respond")
		this->_request->parseRequest();


		///////////////////////   /!\  TEST  START  /!\    ////////////////////////

		this->allocResponse();
		//Create Status Line -> Method SP Request-URI SP HTTP-Version CRLF

		this->_response->bufAdd("HTTP/1.1 200 OK\r\n");
		this->_response->bufAdd("Content-Length: 74\r\n");
		this->_response->bufAdd("Connection: close\r\n");
		this->_response->bufAdd("Content-Type: text/html; charset=utf-8\r\n");
		this->_response->bufAdd("\r\n");
		this->_response->bufAdd("<html><img src=\"/image.prout\"\></br>\nContent fichier/image/what-else</html>");
		this->_response->setBufReady(true);

		///////////////////////   /!\  TEST  END  /!\    ////////////////////////


		//		std::cout << "Client with IP:" << this->getIp() << " go on state IDLE #" << this->_sock << std::endl;
		this->_status = IDLE;
	}
	else if (this->_status == RESPONSE)
	{
		//		std::cout << "Send to client : [" << this->_response->getBuf() << "]" << std::endl;
		/*std::cout << "Send return = [" << */send(this->_sock, this->_response->getBuf().c_str(), this->_response->getBuf().size(), 0)/* << "]" << std::endl*/;

		this->delRequest();
		this->delResponse();
		//Depend of Connection Header and server conf
		this->_status = IDLE;//
	}
	else if (this->_status == CLOSE)
	{
		std::cout << "To close ->#" << this->_sock << std::endl;
	}
	else if (this->_status == IDLE)
	{
		//std::cout << "Client with IP:" << this->getIp() << " is IDLE after " << this->_timer.getTicks() << "ms on socket #" << this->_sock << std::endl;
	}

}

bool Client::toKill()
{
	if (this->_status == CLOSE /* || timeout exceed */ )
		return true;
	else
		return false;
}

bool	Client::needtoWrite()
{
	if (this->_response == NULL)
		return false;
	return this->_response->getBufReady();
}