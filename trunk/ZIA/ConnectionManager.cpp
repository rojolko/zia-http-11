#include "ConnectionManager.h"

ConnectionManager::ConnectionManager(const int port)
{
	this->cmInitWSA();
	this->cmSetSocket();
	this->cmBind(port);
	this->cmListen();
	std::cout << "Socket #" << this->_sock << " OK ! Listening on port " << port << "." << std::endl;
}

ConnectionManager::~ConnectionManager(void)
{
	WSACleanup();
	for (this->_clientIt = this->_clientList.begin(); !this->_clientList.empty(); this->_clientIt = _clientList.begin())
	{
		std::cout << "ConnectionManager Destructor - Erasing Client -> " << this->_clientIt->first << "-"<< this->_clientIt->second->getIp() << std::endl;
		delete this->_clientList[this->_clientIt->first];
		this->_clientList.erase(this->_clientIt->first);
	}
	std::cout << "ConnectionManager Destroyed." << std::endl;
}

void		ConnectionManager::cmInitWSA()
{
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
}

void		ConnectionManager::cmSetSocket()
{
	this->_sock = socket(AF_INET, SOCK_STREAM, NULL);
	if (this->_sock == INVALID_SOCKET)
	{
		std::cout << "Couldn't create socket with error : " << WSAGetLastError() << std::endl;
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
		printf("Couldn't listen on port %d with error : %d, WSA error %d.\n", port, err, WSAGetLastError());
		throw("Bind failed.");
	}
}

void ConnectionManager::cmListen()
{
	if (listen(this->_sock, 100) == SOCKET_ERROR)
	{
		closesocket(this->_sock);
		WSACleanup();
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
		//Fill with Clients foreach blablablah ... 

	//Write Part
		//Fill with Clients foreach blablablah ...
}

void		ConnectionManager::doSelect()
{
	select(NULL, &this->_read, &this->_write, NULL, NULL);
}

void		ConnectionManager::fdProcess()
{
	//Read Part
		//Main Socket for connection attempts
	if (FD_ISSET(this->_sock, &this->_read))
		this->cmNewClient();
	//Write Part

}

void		ConnectionManager::cmNewClient()
{
	SOCKET			clientSocket;
	sockaddr		clientSrcInf;
	int				sizeofClientSrcInf;
	SOCKADDR_IN		clientSrcInfBis;
//EN CONSTRUCTION  --- a dynamiser avec la liste
	sizeofClientSrcInf = sizeof(clientSrcInf);
	clientSocket = accept(this->_sock, &clientSrcInf, &sizeofClientSrcInf);
	sizeofClientSrcInf = sizeof(clientSrcInfBis);
	getpeername(clientSocket, (SOCKADDR *)&clientSrcInfBis, &sizeofClientSrcInf);
	if(clientSocket == INVALID_SOCKET)
		std::cout << "Couldn't accept TCP session with error : " << WSAGetLastError() << std::endl;
	else
	{
		//On instancie un nouveau client et c'est parti pour le mettre dans la map/liste
		this->allocNewClientInList(clientSocket, clientSrcInf, clientSrcInfBis);
		std::cout << "New TCP Connection OK, from " << inet_ntoa((in_addr)clientSrcInfBis.sin_addr);
		std::cout << std::endl;
	}
}

void		ConnectionManager::allocNewClientInList(SOCKET sock, sockaddr srcInf, SOCKADDR_IN srcInfIn)
{
	Client *newClient;

	newClient = new Client(sock, srcInf, srcInfIn);
	this->_clientIt = this->_clientList.end();
	this->_clientList.insert(std::pair<SOCKET, Client*>(sock, newClient));
	this->dumpClientsData();
}

void	ConnectionManager::dumpClientsData()
{
	std::cout << "ConnectionManagerDump :" << std::endl;
	for (this->_clientIt = this->_clientList.begin(); this->_clientIt != this->_clientList.end(); ++this->_clientIt)
		std::cout << "	" << this->_clientIt->first << "-"<< this->_clientIt->second->getIp() << std::endl;
}