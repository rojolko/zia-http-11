#include "Response.h"

Response::Response(void)
{
	_isTmpFile = false;
	_isReady = false;
	_code = 0;
	_content = "";
	_version = "";
	_message = "";
	_filePath = "";
}

Response::~Response(void)
{

}

void	Response::setVersion(const std::string& version)
{
	this->_version = version;
}

const std::string&	Response::getVersion(void) const
{
	return this->_version;
}

void	Response::setHeaders(const std::map<std::string, std::string>& headers)
{
	this->_headers = headers;
}

void	Response::setHeader(const std::string &h1, const std::string &h2)
{
	if (this->_headers.find(h1) != this->_headers.end())
			this->_headers.erase(h1);
	this->_headers.insert(std::pair<std::string, std::string>(h1, h2));
}

const std::map<std::string, std::string>&	Response::getHeaders(void) const
{
	return this->_headers;
}

void	Response::setContent(const std::string& content)
{
	this->_content = content;
}

const std::string&	Response::getContent(void) const
{
	return this->_content;
}

void	Response::setCode(short code)
{
	this->_code = code;
}

short	Response::getCode(void) const
{
	return this->_code;
}

void	Response::setMessage(const std::string& message)
{
	this->_message = message;
}

const std::string&	Response::getMessage(void) const
{
	return this->_message;
}

void	Response::setFilePath(const std::string& filePath)
{
	this->_filePath = filePath;
}

const std::string&	Response::getFilePath(void) const
{
	return this->_filePath;
}

void	Response::isTmpFile(bool isTmpFile)
{
	this->_isTmpFile = isTmpFile;
}

bool	Response::isTmpFile(void) const
{
	return this->_isTmpFile;
}

void	Response::isReady(bool isReady)
{
	this->_isReady = isReady;
}

bool	Response::isReady(void) const
{
	return this->_isReady;
}


// own

void	Response::buildMessage(void)
{
	// status-line
	this->_message += this->getVersion();
	this->_message += " ";
	//this->_message += this->getCode();
	// a remplacer 
	this->_message += "200";
	this->_message += "\r\n";

	// general-header | response-header | entity-header
	for (this->_headersIt = this->_headers.begin(); this->_headersIt != this->_headers.end(); ++this->_headersIt)
	{
		this->_message += this->_headersIt->first;
		this->_message += ": ";
		this->_message += this->_headersIt->second;
		this->_message += "\r\n";
	}

	// CRLF
	this->_message += "\r\n";

	// message-body
	if (!this->getContent().empty())
		this->_message += this->getContent();
}
