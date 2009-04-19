#ifndef _DYNAMICOBJECT_H_
#define _DYNAMICOBJECT_H_

#include <string>
#include <Windows.h>

#include "IModule.hpp"

#define DO_INSTANTIATOR "createInstance"

extern "C"
{
	typedef zia::IModule* (__cdecl *MYPROC)(); 
}

class DynamicObject
{
private:
	HINSTANCE		_hinstLib; 
	MYPROC			_procAdd; 
public:
	DynamicObject();
	~DynamicObject();

	zia::IModule	*getInstanceFromModule(LPCTSTR);
};

#endif
