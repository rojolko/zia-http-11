#include "ModuleInfo.h"


ModuleInfo::ModuleInfo(zia::IModule* module, const char *filePath)
{
	_name = module->getName();
	_path = filePath;

	_heritTable[SPECIFIC_PORT] = (getAs<zia::IModuleSpecificPort>(module));
	_heritTable[SPECIFIC_EXTENSION] = (getAs<zia::IModuleSpecificExtension>(module));
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
	std::cout << "IModuleSpecificExtension = " << this->isModule(SPECIFIC_EXTENSION) << std::endl;
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
