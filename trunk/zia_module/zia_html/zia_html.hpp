#ifndef _HTMLMODULE_HPP_
#define _HTMLMODULE_HPP_

//
// INCLUDES
//
#include <string>
#include <Windows.h>
#include <iostream>

#include "IModule.hpp"

namespace zia
{
	class							HtmlModule :	public IModule,
													public IModuleDoRead,
													public IModuleSpecificExtension,
													public IModuleOnAccept
	{
		public:
			HtmlModule(void);
			virtual ~HtmlModule(void);
			virtual std::string				getName(void) const;
			virtual bool					OnLoad(IModuleConfig *conf);
			virtual void					OnUnload(void);
			virtual int						doRead(IModuleClient &, void *, unsigned int);
			virtual void					getExtensions(std::list<std::string> &);
			virtual bool					onAccept(IModuleClient &);
		private:
			IModuleConfig					*_conf;
	};
}

#endif