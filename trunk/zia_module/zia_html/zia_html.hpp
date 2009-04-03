#ifndef _HTMLMODULE_HPP_
#define _HTMLMODULE_HPP_

//
// INCLUDES
//
#include <string>

namespace zia
{
	class							HtmlModule : public IModule
	{
		public:
			HtmlModule(void);
			virtual ~HtmlModule(void);
			virtual std::string				getName(void) const;
			virtual bool					OnLoad(IModuleConfig *conf);
			virtual void					OnUnload(void);
		private:
			IModuleConfig					*_conf;
	};
}

#endif