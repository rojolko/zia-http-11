//
// INCLUDES
//
#include "zia_html.hpp"

namespace zia
{
	HtmlModule::HtmlModule(void)
	{
		std::cout << "zia html module : instancied :P" << std::endl;
	}

	HtmlModule::~HtmlModule(void)
	{
		std::cout << "zia html module : destroyed :D" << std::endl;
	}

	bool			HtmlModule::OnLoad(IModuleConfig *conf)
	{
		this->_conf = conf;
		return true;
	}

	void			HtmlModule::OnUnload(void)
	{
	}

	std::string		HtmlModule::getName(void) const
	{
		return ("mod_html");
	}
	int		HtmlModule::doRead(zia::IModuleClient &cl, void *buf, unsigned int size)
	{
		return 1;
	}
	void	HtmlModule::getExtensions(std::list<std::string> &extList)
	{
		std::string	ext;

		ext = "php";
		extList.push_back(ext);
	}
}


zia::IModule		*createInstance(void)
{
	return (new zia::HtmlModule());
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
