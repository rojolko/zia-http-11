#include "DynamicObject.h"
#include <iostream>

DynamicObject::DynamicObject()
{

}

DynamicObject::~DynamicObject()
{
	if (this->_hinstLib != NULL)
		FreeLibrary(this->_hinstLib);
}

zia::IModule*	DynamicObject::getInstanceFromModule(LPCTSTR dllName)
{
	this->_hinstLib = LoadLibrary(dllName);
	if (this->_hinstLib != NULL)
	{
		this->_procAdd = (MYPROC) GetProcAddress(this->_hinstLib, DO_INSTANTIATOR);
		if (this->_procAdd != NULL)
		{
			return this->_procAdd();
		}
	}
	return NULL;
}