#ifndef __BAN_HPP__
# define __BAN_HPP__

//
// INCLUDES
//

#include <Windows.h>
#include <iostream>
#include <string>

namespace zia
{
	class							BanModule : public IModule,
												public IModuleOnAccept
	{
		public:
			BanModule(void);
			virtual ~BanModule(void);
			virtual std::string				getName(void) const;
			virtual bool					OnLoad(IModuleConfig *conf);
			virtual void					OnUnload(void);
			virtual bool					onAccept(IModuleClient &);

		private:
			IModuleConfig					*_conf;
	};
}

#endif //! __BAN_HPP__

//
// END OF FILE
//
