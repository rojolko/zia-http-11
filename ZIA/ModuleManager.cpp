#include "ModuleManager.h"

ModuleManager *ModuleManager::_singleton = NULL;

ModuleManager::ModuleManager()
{
	_loader = new DynamicObject();
}

ModuleManager::~ModuleManager()
{

}

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

void	ModuleManager::LoadModule(const char* modulePath, Config &cfg)
{
	zia::IModule*	tmp;
	wchar_t			tmp_fname[256];
	//tstring	ts(modulePath);

/*	std::wostringstream	wos;
	std::wstring			ws;

	wos << modulePath;
	ws = wos.str();
*/	
//	this->_loader = new DynamicObject();
	mbstowcs(tmp_fname, modulePath, 256);
	tmp = this->_loader->getInstanceFromModule((LPCTSTR)tmp_fname);
	if (tmp)
	{
		tmp->OnLoad(&cfg);
		this->_moduleList.insert(std::pair<zia::IModule*, ModuleInfo*>(tmp, new ModuleInfo(tmp, modulePath)));
	}
	else
		std::cout << "Module File could not be loaded :" << modulePath << std::endl;
}

void	ModuleManager::dumpLoadedModule(void)
{
	for (this->_it = this->_moduleList.begin(); this->_it != this->_moduleList.end(); ++this->_it)
		this->_it->second->dumpInfo();
}

std::map<zia::IModule*, ModuleInfo*>	ModuleManager::getModuleList(void)
{
	return this->_moduleList;
}