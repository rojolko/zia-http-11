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
		std::string	www;
		conf->getInfo("www-dir", www);

		std::cout << "Load Success : " << www << std::endl;
		return true;
	}

	void			HtmlModule::OnUnload(void)
	{
	}

	std::string		HtmlModule::getName(void) const
	{
		return ("mod_html");
	}
/*	int		HtmlModule::doRead(IModuleClient &cl, void *buf, unsigned int size)
	{
		return 1;
	}
*/	void	HtmlModule::getExtensions(std::list<std::string> &extList)
	{
		std::string	ext;

		ext = "php";
		extList.push_back(ext);
	}
	bool	HtmlModule::onAccept(IModuleClient &cl)
	{
		std::cout << "Module zia_html : onAccept client sock #" << cl.getSocket() << " port : " << cl.getPort() << std::endl;
		return true;
	}
	bool	HtmlModule::doExec(IModuleRequest &request, IModuleClient &client, IModuleResponse &response)
	{
		response.setVersion("HTTP/1.1");
		response.setCode(200);

		response.setHeader("Content-Length", "74");
		//response.setHeader("Connection", "close");
		response.setHeader("Content-Type", "text/html; charset=utf-8");

		response.setContent("<html><img src=\"/image.prout\"\></br>\nContent fichier/image/what-else</html>");
	
		return true;
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