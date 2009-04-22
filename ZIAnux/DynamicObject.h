#ifndef _DYNAMICOBJECT_H_
#define _DYNAMICOBJECT_H_

#include <string>
#include "IModule.hpp"

/// WIN
#if defined(WIN32) || defined(WIN64)
# include <Windows.h>
extern "C"
{
	typedef zia::IModule* (__cdecl *MYPROC)(); 
}

/// *NIX
#else
# include <dlfcn.h>
# define HINSTANCE	void*
# define MYPROC		void*
# define LPCTSTR	const char*
#endif

#define DO_INSTANTIATOR "createInstance"

class DynamicObject
{
 private:
  HINSTANCE		_hinstLib; 
  MYPROC		_procAdd; 
  
 public:
  DynamicObject();
  ~DynamicObject();
  
  zia::IModule		*getInstanceFromModule(LPCTSTR dllName);
};

#endif
