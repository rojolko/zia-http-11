//
// INCLUDES
//
#include "IModule.hpp"
#include "ban.hpp"

namespace zia
{
	BanModule::BanModule(void)
	{
	}

	BanModule::~BanModule(void)
	{ 
	}

	bool			BanModule::OnLoad(IModuleConfig *conf)
	{
		this->_conf = conf;
		return true;
	}

	void			BanModule::OnUnload(void)
	{
	}

	std::string		BanModule::getName(void) const
	{
		return ("mod_ban");
	}

	bool			BanModule::onAccept(IModuleClient &client)
	{
		std::cout << "Module zia_ban : onAccept client sock #" << client.getSocket() << " port : " << client.getPort() << std::endl;
		if (0/*bannir le client*/)
			return (false);
		return (true);
	}
}

zia::IModule		*createInstance(void)
{
	return (new zia::BanModule());
}

#if defined(_WIN32) || defined(_WIN64) || defined(WIN32) || defined(WIN64)
BOOL APIENTRY	DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
		default:
			break;
	}
	return (TRUE);
}

#endif //! WIN_32 || WIN_64

//
// END OF FILE
//
