#ifndef _RESPONSE_H_
#define _RESPONSE_H_

#include <string>
#include <iostream>
#include <sstream>
#include <map>

#include "Tools.h"
#include "globals.h"
#include "IModule.hpp"

t_statcde t_SatusCode[];

class					Response : public zia::IModuleResponse
{
private:
	std::string							_buf;
	bool										_isTmpFile;
	bool										_isReady;
	bool										_headersDone;
	short										_statusCode;
	std::string									_content;
	std::string									_version;
	std::string									_message;
	std::string									_filePath;
	std::string									_requestMethod;
	std::map<std::string, std::string>			_headers;
	std::map<std::string, std::string>::iterator	_headersIt;
public:
	Response(const std::string& str);
	~Response(void);
	const std::string&			getBuf(void) const;
	void										buildBuf(void);
	void										setVersion(const std::string&);
	const std::string&							getVersion(void) const;
	void										setHeaders(const std::map<std::string, std::string>&);
	void										setHeader(const std::string &, const std::string &);
	const std::map<std::string, std::string>&	getHeaders(void) const;
	void										setContent(const std::string&);
	const std::string&							getContent(void) const;
	void										setCode(short);
	short										getCode(void) const;
	void										setMessage(const std::string&);
	const std::string&							getMessage(void) const;
	const std::string&							getMethod(void) const;
	void										setFilePath(const std::string&);
	const std::string&							getFilePath(void) const;
	void										isReady(bool);
	bool										isReady(void) const;
	void										isTmpFile(bool);
	bool										isTmpFile(void) const;
};

#endif