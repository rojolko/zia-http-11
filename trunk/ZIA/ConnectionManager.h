#ifndef _CONNECTIONMANAGER_H_
#define _CONNECTIONMANAGER_H_

#if defined(WIN32) || defined(WIN64)

// WINDBLOWS
#include <Winsock2.h>
#define socklen_t int
#else

// NUXSME
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <unistd.h>
# define SOCKET			int
//# define sockaddr		struct sockaddr_in *
# define SOCKADDR_IN		struct sockaddr_in
# define SOCKADDR		struct sockaddr_in
# define INVALID_SOCKET		-1
# define SOCKET_ERROR		-1

#endif

#include <map>
#include <string>
#include <iostream>

#include "Client.h"

class ConnectionManager
{
private:
	SOCKET								_sock;
	SOCKADDR_IN							_src_inf;
#if defined(WIN32) || defined(WIN64)
	WSADATA								_wsaData;
#endif
	fd_set								_read;
	fd_set								_write;
  struct timeval				_selectTime;
  int										_maxFdVal;
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

#endif