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
			virtual							~IModuleDoExec() {}
			/**
			*  Cette methode est appele entre OnRead et OnSend
			*  Elle permet par exemple d'executer un script CGI puis de generer une reponse.
			*  Attention : il n'y a plus de DoSend a faire. La reponse suit le chemin classique
			*              de l'execution ( DoExec -> OnSend -> DoSend )
			*  @param une interface sur la requete (cf IModuleRequest)
			*  @param une interface sur le client (cf IModuleClient)
			*  @param une interface sur la reponse a remplir (cf IModuleResponse)
			*  @return un boleen (true si l'execution s'est bien passee)
			*/
			virtual bool	doExec(IModuleRequest &, IModuleClient &, IModuleResponse &) = 0;
	};
}

# endif // !__IMODULEDOEXEC_HPP__

//
// END OF FILE
//
