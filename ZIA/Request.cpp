#include "Request.h"


Request::Request(void)
{
	_mm = ModuleManager::getInstance();
	_moduleList = _mm->getModuleList();
	_statusCode = 0;
}

Request::Request(const SOCKET sock)
{
	_mm = ModuleManager::getInstance();
	_moduleList = _mm->getModuleList();
	_sock = sock;
	_statusCode = 0;
}

Request::~Request(void)
{
	for (this->_varIt = this->_varList.begin(); !this->_varList.empty(); this->_varIt = _varList.begin())
	{
		//		std::cout << "ConnectionManager Destructor - Erasing Var -> \"" << this->_varIt->first << "\"=\""<< this->_varIt->second << "\"" << std::endl;
		this->_varList.erase(this->_varIt->first);
	}
}

CL_STAT					Request::processRequest(zia::IModuleClient *client)
{
	char	readBuff[RQ_BUFF_SIZE];
	bool		mod_do_read;

	std::map<zia::IModule*, ModuleInfo*>::iterator	i;

	for (mod_do_read = 0, i = this->_moduleList.begin(); i != this->_moduleList.end(); ++i)
		if (i->second->isModule(DO_READ) && i->second->isSpecificPort((unsigned short)80) /* Tention, faudra tester le port reel du ConnectionManager */)
		{
			this->_retVal = getAs<zia::IModuleDoRead>(i->first)->doRead(*client, readBuff, RQ_BUFF_SIZE - 1);
			mod_do_read = true;
			std::cout << "Read Module" << std::endl;
			break; /* On utilise seulement un read et non plusieurs read */
		}

	if (!mod_do_read)
	{
		//		std::cout << "Client with IP:" << this->getIp() << " on socket #" << this->_sock << " is FETCHING" << std::endl;
		// Launch Read on the client's socket
		this->_retVal = recv(this->_sock, readBuff, RQ_BUFF_SIZE - 1, 0);
		std::cout << "Read Serveur" << std::endl;
	}
	//<IModuleDoRead>

	// peut etre a modif ...
	if (this->_retVal <= 0)
		return (CLOSE);
	readBuff[this->_retVal] = 0;
	// std::cout << "Last BuffStream : [" << this->_buffStream.str() << "]" << std::endl;
	this->_request.insert(this->_request.length(), readBuff, this->_retVal);
	// std::cout << "Current BuffStream : [" << this->_buffStream.str() << "]" << std::endl;
	return (PROCESS);
}

const std::string			Request::getRequest() const
{
	return (this->_request);
}

const int	Request::getRetVal() const
{
	return this->_retVal;
}

const short	Request::getStatusCode() const
{
	return this->_statusCode;
}

void			Request::parseRequest()
{
	//std::cout << "Flux Entrant: {" << this->_request << "}" << std::endl;
	std::cout << "Size Request = " << this->_request.length() << std::endl;
	this->_temp = this->_request;
	this->parseRequestMethodPathVers();
	if (!this->_statusCode && this->_temp.length())
		this->parseVars();
	if (!this->_statusCode)
		if (this->isValidMethod())
			if (this->isValidProtocolVersion())
				if (this->isValidHeader())
					this->parseBody();
	//this->dumpMPVandVars();
}

bool	Request::isValidMethod()
{
	int	i;

	for (i = 0; t_Methods[i] != NULL; ++i)
		if (this->_requestMethod.compare(t_Methods[i]) == 0)
			return true;
	std::cout << "Bad Request - Unsupported method." << std::endl;
	this->_statusCode = 501;
	return false;
}

bool	Request::isValidProtocolVersion()
{
	int	i;

	for (i = 0; t_Protocols[i] != NULL; ++i)
		if (this->_requestVers.compare(t_Protocols[i]) == 0)
			return true;
	std::cout << "Bad Request - Unsupported protocol." << std::endl;
	this->_statusCode = 505;
	return false;
}

bool	Request::isValidHeader()
{
	return true;
}

void	Request::parseRequestMethodPathVers()
{
	//Primary Cut of the HttpRequest to get informations from Status-Line.
	size_t	first_endl;
	size_t	next_space;
	size_t	to_use;
	size_t	elem_size;
	int		i;
	for (i = 0, elem_size = 0; 1; ++i)
	{
		next_space = this->_temp.find_first_of(" ");
		first_endl = this->_temp.find_first_of(C_ENDL);
		if (elem_size == 1 || this->_temp.length() == 0)
			break;
		if (next_space > first_endl && first_endl != std::string::npos)
		{
			if (i < 2)
			{
				std::cout << "Bad Request - Wrong Satus-Line Synthax. Case 1 : Too few words." << std::endl;
				//std::cout << "	Request Content - [" << this->_temp << "]." << std::endl;
				this->_statusCode = 400;
				break;
			}
			elem_size = 1;
			to_use = first_endl;
		}
		else
		{
			elem_size = 0;
			to_use = next_space;
		}
		if (i == 0)
			this->_requestMethod = this->_temp.substr(0, to_use);
		else if (i == 1)
			this->_askedPath = this->_temp.substr(0, to_use);
		else if (i == 2)
			this->_requestVers = this->_temp.substr(0, to_use);
		else if (i == 3 && this->_temp.length())
		{	
			std::cout << "Bad Request - Wrong Status-Line Synthax. Case 2 : Too many words." << std::endl;
			//std::cout << "	Request Content - [" << this->_temp << "]." << std::endl;
			this->_statusCode = 400;
			break;
		}
		this->consumeRequest(to_use + elem_size);
	}
}

void	Request::parseVars()
{
	size_t	first_endl;
	size_t	next_doubledot;
	std::string tmpVar;
	std::string tmpVal;

	while (1)
	{
		if (!(this->_temp.find_first_of(":") < this->_temp.find_first_of(C_ENDL) && this->_temp.find_first_of(C_ENDL) != std::string::npos))
		{
			std::cout << "Bad Request Bad Syntax for headers-[" << this->_temp << "]" << std::endl;
			this->_statusCode = 400;
			break;
		}
		next_doubledot = this->_temp.find_first_of(":");
		tmpVar = this->_temp.substr(0, next_doubledot);
		consumeRequest(next_doubledot + 1);
		first_endl = this->_temp.find_first_of(C_ENDL);
		tmpVal = this->_temp.substr(0, first_endl);
		consumeRequest(first_endl + (C_ENDL_SIZE - 1));
		this->_varList.insert(std::pair<std::string, std::string>(tmpVar, tmpVal));
		if (!this->_temp.find_first_of(C_ENDL))
			break;
	}
}

void	Request::parseBody()
{
	if (this->_temp.length() > 0 && this->_temp.compare(C_ENDL))
	{
		if (this->_temp.find(C_ENDL) == 0)
			this->_temp = this->_temp.substr(2, this->_temp.length() - 2);
		this->setContent(this->_temp);
	}
	std::cout << "Content Set - Content Size = " << this->_body.length() << " bytes." << std::endl;
}

void	Request::consumeRequest(const size_t& idx)
{
	if (this->_temp.length() > idx)
		this->_temp = this->_temp.substr(idx + 1, this->_temp.length() - idx);
	else
		this->_temp = "";
}

const int	Request::countInRequest(const std::string &str)
{
	int	i;
	size_t	last;

	for (i = 0, last = 0; (last = this->_temp.find(str, last + (last ? str.length() : 0))) != std::string::npos; ++i);
	return i;
}

void	Request::dumpMPVandVars()
{
	std::cout << "Method =[" << this->_requestMethod << "]" << std::endl;
	std::cout << "Path =[" << this->_askedPath << "]" << std::endl;
	std::cout << "Vers =[" << this->_requestVers << "]" << std::endl;

	std::cout << "Request Vars Dump :" << std::endl;
	for (this->_varIt = this->_varList.begin(); this->_varIt != this->_varList.end(); ++this->_varIt)
		std::cout << "	[" << this->_varIt->first << "]=[" << this->_varIt->second << "]" << std::endl;
}

const std::map<std::string, std::string>&	Request::getHeaders(void) const
{
	return this->_varList;
}

const std::string&	Request::getContent(void) const
{
	return this->_body;
}

void	Request::setMethod(const std::string &str)
{
	this->_requestMethod = str;
}

void	Request::setURI(const std::string &str)
{
	this->_askedPath = str;
}

void	Request::setVersion(const std::string &str)
{
	this->_requestVers = str;
}

void	Request::setHeaders(const std::map<std::string, std::string> &hmap)
{
	this->_varList = hmap;
}

void	Request::setContent(const std::string &str)
{
	this->_body = str;
}

void	Request::setHeader(const std::string& key, const std::string &value)
{
	if (this->_varList.find(key) != this->_varList.end())
		this->_varList.erase(key);
	this->_varList.insert(std::pair<std::string, std::string>(key, value));
}

const std::string&	Request::getVersion(void) const
{
	return this->_requestVers;
}

const std::string&	Request::getMethod(void) const
{
	return this->_requestMethod;
}

const std::string&	Request::getURI(void) const
{
	return this->_askedPath;
}
