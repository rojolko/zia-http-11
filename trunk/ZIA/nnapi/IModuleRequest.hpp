#ifndef __IMODULEREQUEST_HPP__
# define __IMODULEREQUEST_HPP__

//
// INCLUDES
//
#include <map>
#include <string>

namespace									zia
{
	/**
	*  Interface d'une requete.
	*/
	class									IModuleRequest
	{
		public:
			virtual							~IModuleRequest() {}
			/**
			*  Methode qui modifie la methode de la requete (GET, POST, ...)
			*/
			virtual void						setMethod(const std::string&) = 0;
			/**
			*  Methode qui renvoie la methode de la requete (GET, POST, ...)
			*  @return la methode
			*/
			virtual const std::string&				getMethod(void) const = 0;
			/**
			*  Methode qui modifie l'URI
			*/
			virtual void						setURI(const std::string&) = 0;
			/**
			*  Methode qui renvoie l'URI
			*  @return l'URI
			*/
			virtual const std::string&				getURI(void) const = 0;
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
			*  Methode qui modifie les "headers" de la requete (Content-Length, ...)
			*/
			virtual void						setHeaders(const std::map<std::string, std::string>&) = 0;
			/**
			*  Methode qui modifie les "headers" de la requete (Content-Length, ...)
			*/
			virtual void						setHeader(const std::string &, const std::string &) = 0;
			/**
			*  Methode qui renvoie les "headers" de la requete (Content-Length, ...)
			*  @return une std::map des "headers"
			*/
			virtual const std::map<std::string, std::string>&	getHeaders(void) const = 0;
			/**
			*  Methode qui modifie le coeur de la requete (body)
			*/
			virtual void						setContent(const std::string&) = 0;
			/**
			*  Methode qui renvoi le coeur de la requete (body)
			*  @return le coeur de la requete
			*/
			virtual const std::string&				getContent(void) const = 0;
	};
}

# endif // !__IMODULEREQUEST_HPP__

//
// END OF FILE
//
