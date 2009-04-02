#ifndef __IMODULEDOEXEC_HPP__
# define __IMODULEDOEXEC_HPP__

//
// INCLUDES
//
#include <string>

namespace				zia
{
	/**
	* Heriter de cette interface permet de repondre soi-meme a la requete
	*/
	class				IModuleDoExec
	{
		public:
			/**
			*  Cette methode est appele a la place de l'execution par default des requetes
			*  @param une interface sur la requete (cf IModuleRequest)
			*  @param une interface sur le client (cf IModuleClient)
			*  @param une interface sur le send (cf IModuleDoSend)
			*  @return un boleen (true si l'execution s'est bien passee)
			*/
			virtual bool	doExec(IModuleRequest &, IModuleClient &, IModuleResponse &) = 0;
	};
}

# endif // !__IMODULEDOEXEC_HPP__

//
// END OF FILE
//
