#include "ConnectionManager.h"

ConnectionManager::ConnectionManager(const int port)
{
#if defined(WIN32) || defined(WIN64)
  this->cmInitWSA();
#endif
  this->cmSetSocket();
  this->cmBind(port);
  this->cmListen();
  this->_selectTime.tv_sec = 0;
  this->_selectTime.tv_usec = 100;
  std::cout << "Socket #" << this->_sock << " OK ! Listening on port " << port << "." << std::endl;
}

ConnectionManager::~ConnectionManager(void)
{
#if defined(WIN32) || defined(WIN64)
	WSACleanup();
#endif

  for (this->_clientIt = this->_clientList.begin(); !this->_clientList.empty(); this->_clientIt = _clientList.begin())
    {
      std::cout << "ConnectionManager Destructor - Erasing Client -> " << this->_clientIt->first << "-"<< this->_clientIt->second->getIp() << std::endl;
      delete this->_clientList[this->_clientIt->first];
      this->_clientList.erase(this->_clientIt->first);
    }
  closesocket(this->_sock);
  std::cout << "ConnectionManager Destroyed." << std::endl;
}

void		ConnectionManager::cmInitWSA()
{
#if defined(WIN32) || defined(WIN64)
  int	err;

  err = WSAStartup(MAKEWORD(2, 2), &this->_wsaData);
  if (err != 0)
    {
      printf("WSAStartup failed with error: %d\n", err);
      throw("WSA error.");
    }
  if (LOBYTE(this->_wsaData.wVersion) != 2 || HIBYTE(this->_wsaData.wVersion) != 2)
    {
      WSACleanup();
      throw("Could not find a usable version of Winsock.dll");
    }
#endif
}

void		ConnectionManager::cmSetSocket()
{
	this->_sock = socket(AF_INET, SOCK_STREAM, NULL);
  this->_maxFdVal = this->_sock;
	if (this->_sock == INVALID_SOCKET)
	{
#if defined(WIN32) || defined(WIN64)
	  std::cout << "Couldn't create socket with error : " << WSAGetLastError() << std::endl;
#else
	  perror("Couldn't create socket with error: ");
#endif
	  throw("Socket error.");
	}
}

void ConnectionManager::cmBind(const int port)
{
	int	err;

	this->_src_inf.sin_family = AF_INET;
	this->_src_inf.sin_addr.s_addr = INADDR_ANY; // Ecoute sur toutes les IP locales 
	this->_src_inf.sin_port = htons(port); // Ecoute sur le port
	
	err = bind(this->_sock,(struct sockaddr*)&this->_src_inf, sizeof(this->_src_inf));
	
	if (err != 0)
	{
#if defined(WIN32) || defined(WIN64)
	  printf("Couldn't listen on port %d with error : %d, WSA error %d.\n", port, err, WSAGetLastError());
#else
	  perror("Couldn't listen with error: ");
#endif
		throw("Bind failed.");
	}
}

void ConnectionManager::cmListen()
{
	if (listen(this->_sock, 100) == SOCKET_ERROR)
	{
#if defined(WIN32) || defined(WIN64)
	  closesocket(this->_sock);
	  WSACleanup();
#else
	  close(this->_sock);
#endif
		throw("listen error.");
	}
}

void		ConnectionManager::fillFdSet()
{
	FD_ZERO(&this->_read);
	FD_ZERO(&this->_write);
	//Read Part
	//Fill with Main socket
	FD_SET(this->_sock, &this->_read);
	//Fill with Clients
	this->_maxFdVal = this->_sock;
	for (this->_clientIt = this->_clientList.begin(); this->_clientIt != this->_clientList.end(); )
		if (!this->_clientIt->second->toKill())
		{
			this->_maxFdVal = (((this->_clientIt->first) > (this->_maxFdVal)) ? (this->_clientIt->first) : (this->_maxFdVal));
			FD_SET(this->_clientIt->first, &this->_read);
			if (this->_clientIt->second->needtoWrite() == true)
				FD_SET(this->_clientIt->first, &this->_write);
			++this->_clientIt;
		}
		else
		{
			delete this->_clientList[this->_clientIt->first];
			this->_clientList.erase(this->_clientIt++);
		}
	//Write Part
	//Fill with Clients
}

void		ConnectionManager::doSelect()
{
	select(this->_maxFdVal + 1, &this->_read, &this->_write, NULL, &this->_selectTime);
}

void		ConnectionManager::fdProcess()
{
	//Read Part
	for (this->_clientIt = this->_clientList.begin(); this->_clientIt != this->_clientList.end(); ++this->_clientIt)
	{
		if (FD_ISSET(this->_clientIt->first, &this->_read))
			this->_clientIt->second->setStatus(FETCH);
		if (FD_ISSET(this->_clientIt->first, &this->_write))
			this->_clientIt->second->setStatus(RESPONSE);
	}
  	//Main Socket for connection attempts
	if (FD_ISSET(this->_sock, &this->_read))
		this->cmNewClient();
	//Write Part

	//Launch Clients Processing
	for (this->_clientIt = this->_clientList.begin(); this->_clientIt != this->_clientList.end(); ++this->_clientIt)
		this->_clientIt->second->process();
}

void		ConnectionManager::cmNewClient()
{
	SOCKET			clientSocket;
	sockaddr		clientSrcInf;
	socklen_t		sizeofClientSrcInf;
	SOCKADDR_IN		clientSrcInfBis;

	sizeofClientSrcInf = sizeof(clientSrcInf);
	clientSocket = accept(this->_sock, &clientSrcInf, &sizeofClientSrcInf);
	sizeofClientSrcInf = sizeof(clientSrcInfBis);
	getpeername(clientSocket, (sockaddr *)&clientSrcInfBis, (socklen_t*)&sizeofClientSrcInf);
	if(clientSocket == INVALID_SOCKET)
	  {
#if defined(WIN32) || defined(WIN64)
		  std::cout << "Couldn't accept TCP session with error : " << WSAGetLastError() << std::endl;
#else
		  perror("Couldn't accept TCP session with error : ");
#endif
	  }
	else
	  {
		  //On instancie un nouveau client et c'est parti pour le mettre dans la map/liste
		  this->allocNewClientInList(clientSocket, clientSrcInf, clientSrcInfBis);
//		  std::cout << "New TCP Connection OK, from " << inet_ntoa((in_addr)clientSrcInfBis.sin_addr);
//		  std::cout << std::endl;
	  }
}

void		ConnectionManager::allocNewClientInList(SOCKET sock, sockaddr srcInf, SOCKADDR_IN srcInfIn)
{
	Client *newClient;

	newClient = new Client(sock, srcInf, srcInfIn);
	this->_clientIt = this->_clientList.end();
	this->_clientList.insert(std::pair<SOCKET, Client*>(sock, newClient));
//	this->dumpClientsData();
}

void	ConnectionManager::dumpClientsData()
{
	std::cout << "ConnectionManagerDump :" << std::endl;
	for (this->_clientIt = this->_clientList.begin(); this->_clientIt != this->_clientList.end(); ++this->_clientIt)
		std::cout << "	" << this->_clientIt->first << "-"<< this->_clientIt->second->getIp() << std::endl;
}
