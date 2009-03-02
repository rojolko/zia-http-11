#pragma once

#include <winsock2.h>
#include <map>
#include <string>
#include <iostream>

#include "Client.h"

class ConnectionManager
{
private:
	SOCKET								_sock;
	SOCKADDR_IN							_src_inf;
	WSADATA								_wsaData;
	fd_set								_read;
	fd_set								_write;
	std::map<SOCKET, Client*>			_clientList;
	std::map<SOCKET, Client*>::iterator	_clientIt;

	void		cmInitWSA();
	void		cmSetSocket();
	void		cmBind(const int port);
	void		cmListen();
	void		cmNewClient();
	void		allocNewClientInList(SOCKET, sockaddr, SOCKADDR_IN);
	void		dumpClientsData();

public:
	ConnectionManager(const int port);
	~ConnectionManager(void);

	void		fillFdSet();
	void		doSelect();
	void		fdProcess();
	
};
