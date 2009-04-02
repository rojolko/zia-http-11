#ifndef __IMODULEONCLOSE_HPP__
# define __IMODULEONCLOSE_HPP__

namespace				zia
{
	/**
	* Heriter de cette interface permet d'executer une fonction juste avant le close du socket
	*/
	class				IModuleOnClose
	{
		public:
			virtual							~IModuleOnClose() {}
			/**
			* Cette methode est appelee juste avant le close du socket
			* @param une interface client (cf IModuleClient)
			* @return renvoie true si l'action a bien été executé (pour debug).
			*/
			virtual bool	onClose(IModuleClient &) = 0;
	};
}

# endif // !__IMODULEONCLOSE_HPP__

//
// END OF FILE
//
