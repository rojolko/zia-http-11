#include "Client.h"

Client::Client(SOCKET sock, sockaddr srcInf, SOCKADDR_IN srcInfIn)
{
	//<IModuleOnAccept>
	_mm = ModuleManager::getInstance();
	_moduleList = _mm->getModuleList();
	_status = CONNECT;
	_sock = sock;
	_clientSrcInf = srcInf;
	_clientSrcInfIn = srcInfIn;
	_request = NULL;
	_response = NULL;

	_sendRet = 0;

	_doOnAccept();
	_timer.start();
}

Client::~Client()
{
	bool		mod_on_close = false;
	bool		mod_do_close = false;
	std::map<zia::IModule*, ModuleInfo*>::iterator	i;

	this->delRequest();
	this->delResponse();

	//<IModuleOnClose>
	for (i = this->_moduleList.begin(); i != this->_moduleList.end(); ++i)
		if (i->second->isModule(ON_CLOSE))
		{
			getAs<zia::IModuleOnClose>(i->first)->onClose(*this);
			mod_on_close = true;
		}
	if (!mod_on_close)
	{
		;
	}

	//<IModuleDoClose>
	for (i = this->_moduleList.begin(); i != this->_moduleList.end(); ++i)
		if (i->second->isModule(DO_CLOSE))
		{
			getAs<zia::IModuleDoClose>(i->first)->doClose(*this);
			mod_do_close = true;
		}
	if (!mod_do_close)
	{
		std::cout << "Client with IP:" << this->getIp() << " closed connection after " << this->_timer.getTicks() << "ms on socket #" << this->_sock << std::endl;
		closesocket(this->_sock);
	}
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
	return this->_response->isReady();
}

void	Client::process()
{
	if (this->_status == FETCH)
		this->_doRead();
	else if (this->_status == PROCESS && this->_timer.getTicks() > WAIT_FOR_MORE)
	{
		this->_doOnRead();
		this->_doExec();
		std::cout << "-------------- OnSend -------------" << std::endl;
		this->_doOnSend();
	}
	else if (this->_status == RESPONSE)
	{
		std::cout << "-------------- DoSend -------------" << std::endl;
		this->_doSend();
	}
}

void		Client::_doOnAccept()
{
	bool		mod_on_accept = false;
	std::map<zia::IModule*, ModuleInfo*>::iterator	i;

	for (i = this->_moduleList.begin(); i != this->_moduleList.end(); ++i)
		if (i->second->isModule(ON_ACCEPT))
		{
			getAs<zia::IModuleOnAccept>(i->first)->onAccept(*this);
			mod_on_accept = true;
		}
	if (!mod_on_accept)
	{
		;
	}
}

void		Client::_doRead()
{
	this->allocRequest();

	bool		mod_do_read = false;
	std::map<zia::IModule*, ModuleInfo*>::iterator	i;

	void*		mod_void = 0;
	int			mod_int = 0;

	this->allocResponse();

	for (i = this->_moduleList.begin(); i != this->_moduleList.end(); ++i)
		if (i->second->isModule(DO_READ))
		{
			getAs<zia::IModuleDoRead>(i->first)->doRead(*this, mod_void, mod_int);
			mod_do_read = true;
		}

	if (!mod_do_read)
	{
		//		std::cout << "Client with IP:" << this->getIp() << " on socket #" << this->_sock << " is FETCHING" << std::endl;
		// Launch Read on the client's socket
		this->_status = this->_request->processRequest();
		//std::cout << "ReadRet -> [" << this->_request->getRetVal() << "]" << std::endl;
		this->_timer.start();
	}
}

void		Client::_doOnRead()
{
	bool		mod_on_read = false;
	std::map<zia::IModule*, ModuleInfo*>::iterator	i;

	this->allocResponse();

	for (i = this->_moduleList.begin(); i != this->_moduleList.end(); ++i)
		if (i->second->isModule(ON_READ))
		{
			getAs<zia::IModuleOnRead>(i->first)->onRead(*this->_request);
			mod_on_read = true;
		}

	if (!mod_on_read)
	{
		this->_request->parseRequest();
	}
	std::cout << "do On Read !!!!" << std::endl;
}

void		Client::_doExec()
{
	bool		mod_do_exec = false;
	std::map<zia::IModule*, ModuleInfo*>::iterator	i;

	this->allocResponse();

	for (i = this->_moduleList.begin(); i != this->_moduleList.end(); ++i)
		if (i->second->isModule(DO_EXEC))
		{
			getAs<zia::IModuleDoExec>(i->first)->doExec(*this->_request, *this, *this->_response);
			mod_do_exec = true;
		}

	if (!mod_do_exec)
	{
		//Build the response for the client (Review, We could need another state like "Respond")
		
		//<IModuleOnRead>

		///////////////////////   /!\  TEST  START  /!\    ////////////////////////

		//Create Status Line -> Method SP Request-URI SP HTTP-Version CRLF

		this->_response->setVersion("HTTP/1.1");
		this->_response->setCode(200);

		this->_response->setHeader("Content-Length", "74");
		//this->_response->setHeader("Connection", "close");
		this->_response->setHeader("Content-Type", "text/html; charset=utf-8");

		this->_response->setContent("<html><img src=\"/image.prout\"\></br>\nContent fichier/image/what-else</html>");
	}
	// a remplacer !
	/*/!\*/		this->_response->isReady(true); /*/!\*/

	///////////////////////   /!\  TEST  END  /!\    ////////////////////////
	this->_status = IDLE;
}


void		Client::_doOnSend()
{
	bool		mod_on_send = false;
	std::map<zia::IModule*, ModuleInfo*>::iterator	i;

	this->allocResponse();

	for (i = this->_moduleList.begin(); i != this->_moduleList.end(); ++i)
		if (i->second->isModule(ON_SEND))
		{
			getAs<zia::IModuleOnSend>(i->first)->onSend(*this->_response);
			mod_on_send = true;
		}

	if (!mod_on_send)
		;
//	this->_response->buildMessage();
}

void		Client::_doSend()
{
	bool		mod_do_send = false;
	std::map<zia::IModule*, ModuleInfo*>::iterator	i;
	unsigned int	mod_int;
	int				fileSize;
	char			buf[10000];
	std::string	buffer;
	int				readRet;
	int				merde = 0;

	std::ifstream	toto;

	for (i = this->_moduleList.begin(); i != this->_moduleList.end(); ++i)
		if (i->second->isModule(DO_SEND))
		{
			this->_sendRet = getAs<zia::IModuleDoSend>(i->first)->doSend(*this, (void*)this->_response->getMessage().c_str(), mod_int);
			mod_do_send = true;
			this->_status = IDLE;
		}
	if (!mod_do_send)
	{
		if (this->_response->isTmpFile())
		{
			std::cout << "opening ... : " << this->_response->getFilePath() << std::endl;
			toto.open(this->_response->getFilePath().c_str(), std::ifstream::binary);
			if (toto.fail())
				std::cout << "ERROR OPENNING : " << this->_response->getFilePath() << std::endl;
			else
				std::cout << "Open OK : " << this->_response->getFilePath() << std::endl;
			if (this->_sendRet)
				toto.seekg(this->_sendRet);
			toto.seekg(0, std::ios::end);
			fileSize = toto.tellg();
			toto.seekg(0, std::ios::beg);
			std::cout << "taille du fichier : " << fileSize << std::endl;
			this->_response->setHeader("Content-Length", Tools::intToString(fileSize));

			while (fileSize > 0)
			{
				toto.seekg(merde, std::ios::beg);
				toto.read(buf, 1000);
				readRet = toto.gcount();
				buffer.insert(merde, buf, fileSize < readRet ? fileSize : readRet);
				merde += readRet;
				fileSize -= readRet;

				std::cout << "buffer len : " << buffer.size() << " filesize = " << fileSize << std::endl;
				if (!merde)
					break;
			}
			this->_response->buildMessage();
			this->_response->setMessage(this->_response->getMessage() + buffer);

			if (toto.gcount() <= toto.tellg())
				this->_status = RESPONSE;
			this->_sendRet = send(this->_sock, this->_response->getMessage().c_str(), this->_response->getMessage().size(), 0);
			std::cout << "[" << this->_sendRet << "] have been send" << std::endl;
			if (this->_status != RESPONSE)
				this->_status = IDLE;
		}
		else
			this->_sendRet = send(this->_sock, this->_response->getMessage().c_str(), this->_response->getMessage().size(), 0);
		this->_status = IDLE;
	}
	if (this->_status == IDLE || this->_status == CLOSE)
	{
		this->delRequest();
		this->delResponse();
		this->_sendRet = 0;
	}
	//Depend of Connection Header and server conf
	this->_status = IDLE;//
}
