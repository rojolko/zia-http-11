#pragma once

#include <winsock2.h>
#include <list>
#include <string>
#include <iostream>

class ConnectionManager
{
private:
	SOCKET						_sock;
	SOCKADDR_IN					_src_inf;
	WSADATA						_wsaData;
	fd_set						_read;
	fd_set						_write;
//	std::list<Client>			_clientList;

	void		cmInitWSA();
	void		cmSetSocket();
	void		cmBind(const int port);
	void		cmListen();
	void		cmNewClient();

public:
	ConnectionManager(const int port);
	~ConnectionManager(void);

	void		fillFdSet();
	void		doSelect();
	void		fdProcess();
	
};
