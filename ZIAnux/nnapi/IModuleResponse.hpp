#ifndef __IMODULERESPONSE_HPP__
# define __IMODULERESPONSE_HPP__

//
// INCLUDES
//
#include <map>
#include <string>

namespace									zia
{
	/**
	*  Interface d'une reponse.
	*/
	class									IModuleResponse
	{
		public:
			virtual							~IModuleResponse() {}
			/**
			*  Methode qui modifie la version du protocole (1.0, 1.1)
			*/
			virtual void						setVersion(const std::string&) = 0;
			/**
			*  Methode qui renvoie la version du protocole (1.0, 1.1)
			*  @return la version du protocole
			*/
			virtual const std::string&				getVersion(void) const = 0;
			/**
			*  Methode qui modifie les "headers" de la reponse (Content-Length, ...)
			*/
			virtual void						setHeaders(const std::map<std::string, std::string>&) = 0;
			/**
			*  Methode qui modifie les "headers" de la reponse (Content-Length, ...)
			*/
			virtual void						setHeader(const std::string &, const std::string &) = 0;
			/**
			*  Methode qui renvoie les "headers" de la reponse (Content-Length, ...)
			*  @return une std::map des "headers"
			*/
			virtual const std::map<std::string, std::string>&	getHeaders(void) const = 0;
			/**
			*  Methode qui modifie le coeur de la reponse (body)
			*  Voir aussi setFilePath qui est une alternative au stockage en RAM.
			*/
			virtual void						setContent(const std::string&) = 0;
			/**
			*  Methode qui renvoi le coeur de la reponse (body)
			*  @return le coeur de la reponse
			*/
			virtual const std::string&				getContent(void) const = 0;
			/**
			*  Methode qui modifie le code de retour de la reponse
			*/
			virtual void						setCode(short) = 0;
			/**
			*  Methode qui renvoie le code de retour de la reponse
			*  @return le code de retour de la reponse
			*/
			virtual short						getCode(void) const = 0;
			/**
			*  Methode qui modifie le message de la reponse
			*/
			virtual void						setMessage(const std::string&) = 0;
			/**
			*  Methode qui renvoie le message de la reponse
			*  @return le message de la reponse
			*/
			virtual const std::string&			getMessage(void) const = 0;
			/**
			*  Cette fonction est une alternative au stockage du content en RAM.
			*  Il est possible de stocker le contenu dans un fichier (ou autre chose).
			*  Attention: Soit vous utilisez "setFilePath" ou "setContent" mais pas les deux :)
			*/
			virtual void						setFilePath(const std::string&) = 0;

			/**
			*  Methode qui renvoie le chemin du fichier de la reponse (cf : setFilePath)
			*  @return le chemin de fichier de la reponse
			*/
			virtual const std::string&			getFilePath(void) const = 0;

			/**
			*  Methode qui dit si le fichier (cf: setFilePath) est temporaire.
			*  En vue d'une eventuelle suppression apres traitement.
			*/
			virtual void						isTmpFile(bool) = 0;
			/**
			*  Methode qui renvoie si le fichier est temporaire.
			*  En vue d'une eventuelle suppression apres traitement.
			*  @return true si le fichier est temporaire.
			*/
			virtual bool						isTmpFile(void) const = 0;
	};
}

# endif // !__IMODULERESPONSE_HPP__

//
// END OF FILE
//
