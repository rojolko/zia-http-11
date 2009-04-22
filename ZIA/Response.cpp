#include "Response.h"


Response::Response(const std::string& str)
{
	_isTmpFile = false;
	_isReady = false;
	_statusCode = 0;
	_content = "";
	_version = "";
	_message = "";
	_buf = "";
	_filePath = "";
	_headersDone = false;
	_requestMethod = str;
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
	this->_statusCode = code;
}

short	Response::getCode(void) const
{
	return this->_statusCode;
}

void	Response::setMessage(const std::string& message)
{
	this->_message = message;
}

const std::string&	Response::getMessage(void) const
{
	return this->_message;
}

const std::string&	Response::getMethod(void) const
{
	return this->_requestMethod;
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

const std::string	&Response::getBuf(void) const
{
	return this->_buf;
}

// own

void	Response::buildBuf(void)
{
	int i;

	if (!this->_headersDone)
	{
		// status-line
		this->_buf += this->getVersion();
		this->_buf += " ";
		this->_buf += Tools::intToString((int)this->getCode());
		this->_buf += " ";
		for (i = 0; t_SatusCode[i].cde != NULL && t_SatusCode[i].cde != this->getCode(); i++);
		if (t_SatusCode[i].cde != NULL)
			this->_buf += Tools::charToString((const char*)t_SatusCode[i].str);
		this->_buf += "\r\n";

		// general-header | response-header | entity-header
		for (this->_headersIt = this->_headers.begin(); this->_headersIt != this->_headers.end(); ++this->_headersIt)
		{
			this->_buf += this->_headersIt->first;
			this->_buf += ": ";
			this->_buf += this->_headersIt->second;
			this->_buf += "\r\n";
		}
		// CRLF
		this->_buf += "\r\n";
		this->_headersDone = true;
	}

	if (this->_buf.length() < BUFSIZ)
	{
		// message-body
		if (this->_requestMethod.compare(t_Methods[3]) != 0)
		{
			if (this->getCode() >= 400)
			for (i = 0; t_SatusCode[i].cde != NULL && t_SatusCode[i].cde != this->getCode(); i++);
			{
				this->_buf += Tools::intToString((int)t_SatusCode[i].cde);		
				this->_buf += " ";
				this->_buf += Tools::charToString((const char*)t_SatusCode[i].str);			
			}
			if (!this->getContent().empty())
				this->_buf += this->getContent();
		}
	}
}
