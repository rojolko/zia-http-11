#ifndef __IMODULECLIENT_HPP__
# define __IMODULECLIENT_HPP__

namespace					zia
{
	/**
	* Permet d'obtenir le socket et le port courant
	*/
	class					IModuleClient
	{
		public:
			virtual			~IModuleClient() {}
			/**
			* @return le socket courant 
			*/
			virtual int		getSocket() const = 0;
			/**
			* @return le port d'ecoute courant
			*/
			virtual unsigned short	getPort() const = 0;
	};
}

# endif // !__IMODULECLIENT_HPP__

//
// END OF FILE
//

