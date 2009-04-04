#include "ModuleManager.h"

ModuleManager *ModuleManager::_singleton = NULL;

ModuleManager *ModuleManager::getInstance()
{
	if (ModuleManager::_singleton == NULL)
	{
		ModuleManager::_singleton =  new ModuleManager;
		std::cout << "ModuleManager - Initialisation Succeed !" << std::endl;
	}
	return (ModuleManager::_singleton);
}

void	ModuleManager::killInstance()
{
	if (NULL != _singleton)
	{
		delete ModuleManager::_singleton;
		ModuleManager::_singleton = NULL;
		std::cout << "ModuleManager - Termination Succeed !" << std::endl;
	}
}

void	ModuleManager::LoadModule(LPCTSTR modulePath)
{
	DynamicObject	loader;
	zia::IModule*	tmp;
	ModuleInfo*		mi;

	tmp = loader.getInstanceFromModule(modulePath);
	if (tmp)
		this->_moduleList.insert(std::pair<zia::IModule*, ModuleInfo*>(tmp, new ModuleInfo(tmp)));
}

void	ModuleManager::dumpLoadedModule(void)
{
	for (this->_it = this->_moduleList.begin(); this->_it != this->_moduleList.end(); ++this->_it)
		this->_it->second->dumpInfo();
}

const std::map<zia::IModule*, ModuleInfo*>	ModuleManager::getModuleList(void) const
{
	return this->_moduleList;
}