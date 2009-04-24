#include "DynamicObject.h"

DynamicObject::DynamicObject()
{

}

DynamicObject::~DynamicObject()
{
	if (this->_hinstLib != NULL)
	  {
#if defined(WIN32) || defined(WIN64)
	    FreeLibrary(this->_hinstLib);
#else
	    dlclose(this->_hinstLib);
#endif
	  }
}

zia::IModule*	DynamicObject::getInstanceFromModule(LPCTSTR dllName)
{
#if defined(WIN32) || defined(WIN64)
  this->_hinstLib = LoadLibraryEx(dllName, NULL, NULL);
  if (this->_hinstLib != NULL)
    {
      this->_procAdd = (MYPROC) GetProcAddress(this->_hinstLib, DO_INSTANTIATOR);
      if (this->_procAdd != NULL)
	{
	  return this->_procAdd();
	}
    }
#else
  this->_hinstLib = dlopen(dllName, RTLD_NOW); // RTLD_LAZY ou RTLD_NOW
  if (this->_hinstLib != NULL)
    {
      printf("dlopen (%s) succeed\n", dllName);
      this->_procAdd = dlsym(this->_hinstLib, DO_INSTANTIATOR);
      if (this->_procAdd)
	{
	  return (zia::IModule *)this->_procAdd;
	}
    }
  else // affichage erreur, a retirer...
    {
      printf("error dlopen(%s): %s\n", dllName, dlerror());
    }

#endif
  return NULL;
}
