#ifndef __IMODULECONFIG_HPP__
# define __IMODULECONFIG_HPP__

//
// INCLUDES
//
#include <string>

namespace				zia
{
	/**
	*  Class permettant de recuperer et de modifier les informations de configuration du serveur.
	*
	*  Les informations de base sont:
	*  www-dir    => repertoire www
	*  tmp-dir    => repertoire pour les fichier temporaire (upload de fichier, etc.)
	*  homepage   => fichier par defaut (index.html)
	*  port       => port du serveur (en "read only")
	*  ip         => ip du serveur (en "read only")
	*/
	class				IModuleConfig
	{
		public:
			virtual		~IModuleConfig() {}
			/**
			*  Recupere une information specifiee
			*  @param nom de l'information
			*  @param resultat
			*  @return vrai si l'information existe.
			*/
			virtual bool	getInfo(const std::string &key, std::string &result) = 0;
			/**
			*  Modifie une information specifiee.
			*  Vous pouvez utiliser cette methode pour passer des variables aux differents modules.
			*  @param nom de l'information
			*  @param valeur
			*  @return false si acces refuse.
			*/
			virtual bool	setInfo(const std::string &key, const std::string &value) = 0;
	};
}

# endif // !__IMODULECONFIG_HPP__

//
// END OF FILE
//
