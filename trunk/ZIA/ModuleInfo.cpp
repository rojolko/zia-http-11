#include "ModuleInfo.h"


ModuleInfo::ModuleInfo(zia::IModule* module, const char *filePath)
{
	_name = module->getName();
	_path = filePath;

	if (_heritTable[SPECIFIC_PORT] = (getAs<zia::IModuleSpecificPort>(module)))
		getAs<zia::IModuleSpecificPort>(module)->getPorts(_ports);
	if (_heritTable[SPECIFIC_EXTENSION] = (getAs<zia::IModuleSpecificExtension>(module)))
		getAs<zia::IModuleSpecificExtension>(module)->getExtensions(_exts);
	_heritTable[ON_ACCEPT] = (getAs<zia::IModuleOnAccept>(module));
	_heritTable[DO_READ] = (getAs<zia::IModuleDoRead>(module));
	_heritTable[ON_READ] = (getAs<zia::IModuleOnRead>(module));
	_heritTable[DO_EXEC] = (getAs<zia::IModuleDoExec>(module));
	_heritTable[ON_SEND] = (getAs<zia::IModuleOnSend>(module));
	_heritTable[DO_SEND] = (getAs<zia::IModuleDoSend>(module));
	_heritTable[ON_CLOSE] = (getAs<zia::IModuleOnClose>(module));
	_heritTable[DO_CLOSE] = (getAs<zia::IModuleDoClose>(module));
}

ModuleInfo::~ModuleInfo()
{

}

const bool	ModuleInfo::isModule(const short mod_type_code) const
{
	return this->_heritTable[mod_type_code];
}

const std::string	ModuleInfo::getName(void) const
{
	return _name;
}

const std::string	ModuleInfo::getPath(void) const
{
	return _path;
}

void	ModuleInfo::dumpInfo(void)
{
	std::cout << "ModuleInfo DUMP --- start" << std::endl;
	std::cout << "Module name = " << this->getName() << std::endl;
	std::cout << "Module path = " << this->getPath() << std::endl;
	std::cout << "IModuleSpecificPort = " << this->isModule(SPECIFIC_PORT) << std::endl;
	if (this->isModule(SPECIFIC_PORT))
		Tools::dumpList(this->_ports);
	std::cout << "IModuleSpecificExtension = " << this->isModule(SPECIFIC_EXTENSION) << std::endl;
	if (this->isModule(SPECIFIC_EXTENSION))
		Tools::dumpList(this->_exts);
	std::cout << "IModuleOnAccept = " << this->isModule(ON_ACCEPT) << std::endl;
	std::cout << "IModuleDoRead = " << this->isModule(DO_READ) << std::endl;
	std::cout << "IModuleOnRead = " << this->isModule(ON_READ) << std::endl;
	std::cout << "IModuleDoExec = " << this->isModule(DO_EXEC) << std::endl;
	std::cout << "IModuleOnSend = " << this->isModule(ON_SEND) << std::endl;
	std::cout << "IModuleDoSend = " << this->isModule(DO_SEND) << std::endl;
	std::cout << "IModuleOnClose = " << this->isModule(ON_CLOSE) << std::endl;
	std::cout << "IModuleDoClose = " << this->isModule(DO_CLOSE) << std::endl;
	std::cout << "ModuleInfo DUMP --- end" << std::endl;
}
	
bool				ModuleInfo::isSpecificPort(const unsigned short &port)
{
	if (Tools::isInList(this->_ports, port))
		return true;
	return false;
}

bool				ModuleInfo::isSpecificExt(const std::string &ext)
{
	if (Tools::isInList(this->_exts, ext))
		return true;
	return false;
}