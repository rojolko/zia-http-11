#include "Client.h"

Client::Client(SOCKET sock, sockaddr srcInf, SOCKADDR_IN srcInfIn)
{
	//<IModuleOnAccept>
	this->_doOnAccept();
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
	//<IModuleOnClose>

	//<IModuleDoClose>
	closesocket(this->_sock);
}

// IModuleClient

int		Client::getSocket() const
{
	return (int)this->_sock;
}

unsigned short	Client::getPort() const
{
	return this->_clientSrcInfIn.sin_port;
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
	return this->_response->isTmpFile();
}

void	Client::process()
{
	if (this->_status == FETCH)
		this->_doRead();
	else if (this->_status == PROCESS)
		this->_doExec();
	else if (this->_status == RESPONSE)
		this->_doSend();
}

void		Client::_doOnAccept()
{

}

void		Client::_doRead()
{
	this->allocRequest();
	//		std::cout << "Client with IP:" << this->getIp() << " on socket #" << this->_sock << " is FETCHING" << std::endl;
	// Launch Read on the client's socket
	this->_status = this->_request->processRequest();
	std::cout << "ReadRet -> [" << this->_request->getRetVal() << "]" << std::endl;
}

void		Client::_doOnRead()
{

}

void		Client::_doExec()
{
	//Build the response for the client (Review, We could need another state like "Respond")
	this->_request->parseRequest();
	//<IModuleOnRead>

	///////////////////////   /!\  TEST  START  /!\    ////////////////////////

	this->allocResponse();
	//Create Status Line -> Method SP Request-URI SP HTTP-Version CRLF

	this->_response->setVersion("HTTP/1.1");
	this->_response->setCode(200);

	this->_response->setHeader("Content-Length", "74");
	//this->_response->setHeader("Connection", "close");
	this->_response->setHeader("Content-Type", "text/html; charset=utf-8");

	this->_response->setContent("<html><img src=\"/image.prout\"\></br>\nContent fichier/image/what-else</html>");

	this->_response->buildMessage();

	// a remplacer !
	/*/!\*/		this->_response->isTmpFile(true); /*/!\*/

	///////////////////////   /!\  TEST  END  /!\    ////////////////////////
	this->_status = IDLE;
}


void		Client::_doOnSend()
{

}

void		Client::_doSend()
{
	//		std::cout << "Send to client : [" << this->_response->getBuf() << "]" << std::endl;
	/*std::cout << "Send return = [" << */
	send(this->_sock, this->_response->getMessage().c_str(), this->_response->getMessage().size(), 0)
		/* << "]" << std::endl*/;

	this->delRequest();
	this->delResponse();
	//Depend of Connection Header and server conf
	this->_status = IDLE;//
}


