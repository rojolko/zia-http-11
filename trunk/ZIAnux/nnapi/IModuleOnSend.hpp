#ifndef __IMODULEONSEND_HPP__
# define __IMODULEONSEND_HPP__

//
// INCLUDES
//
#include <string>

namespace				zia
{
	/**
	* Heriter de cette interface permet de traiter le flux avant envoie.
	*/
	class				IModuleOnSend
	{
		public:
			virtual							~IModuleOnSend() {}
			/**
			*  Methode appelee pour traiter le flux avant envoie
			*  @param la reponse
			*/
			virtual void	onSend(IModuleResponse &) = 0;
	};
}

# endif // !__IMODULEONSEND_HPP__

//
// END OF FILE
//
