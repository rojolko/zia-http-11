#ifndef _RESPONSE_H_
#define _RESPONSE_H_

#include <string>
#include <iostream>
#include <sstream>

class Response
{
private:
	bool				_bufReady;
	std::string			_response;
public:
	Response(void);
	~Response(void);

	bool				getBufReady();
	void				setBufReady(const bool);
	void				bufAdd(const char *);
	std::string			getBuf();
};

#endif