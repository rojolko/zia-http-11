#ifndef __IMODULE_HPP__
# define __IMODULE_HPP__

#if defined(_WIN32) || defined(WIN32)
# define ZIA_EXPORT __declspec(dllexport)
#else
# define ZIA_EXPORT
#endif

//
// INCLUDES
//
#include "IModuleRequest.hpp"
#include "IModuleResponse.hpp"
#include "IModuleConfig.hpp"
#include "IModuleClient.hpp"
#include "IModuleOnSend.hpp"
#include "IModuleDoSend.hpp"
#include "IModuleOnRead.hpp"
#include "IModuleDoRead.hpp"
#include "IModuleSpecificPort.hpp"
#include "IModuleSpecificExtension.hpp"
#include "IModuleOnAccept.hpp"
#include "IModuleOnClose.hpp"
#include "IModuleDoClose.hpp"
#include "IModuleDoExec.hpp"

//
// NAMESPACE
//
namespace					zia
{
	/**
	*  Interface base du module.
	*/
	class					IModule
	{
		public:
			virtual			~IModule() {}
			/**
			*  Permet l'identification du module.
			*  @return Le nom du module.
			*/
			virtual std::string	getName(void) const = 0;
			/**
			*  Methode appelee lors du chargement du module.
			*  @param La configuration du serveur.
			*  @return true si le module est loader correctement.
			*/
			virtual bool		OnLoad(IModuleConfig *conf) = 0;
			/**
			*  Methode appelee lors du déchargement du module.
			*/
			virtual void		OnUnload(void) = 0;
	};
}

//
// EXTERN C
//
extern "C"
{
	/**
	*  Cette fonction cree une instance du module.
	*  @return Une instance du module.
	*/
	ZIA_EXPORT zia::IModule			*createInstance(void);
}

#endif //! __IMODULE_HPP__

//
// END OF FILE
//
