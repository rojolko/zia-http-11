#ifndef __IMODULEDOSEND_HPP__
# define __IMODULEDOSEND_HPP__

//
// INCLUDES
//
#include <string>
#include "IModuleClient.hpp"

namespace zia
{
	/**
	*  Interface permettant de remplacer l'ecriture sur le socket client
	*/
	class				IModuleDoSend
	{
		public:
			virtual							~IModuleDoSend() {}
			/**
			*  Methode appelee pour ecrire sur le socket client
			*  @param informations du client
			*  @param buffer
			*  @param taille du buffer
			*  @return le nombre d'octects envoyes
			*/
			virtual int	doSend(IModuleClient &, const void *, unsigned int)  = 0;
	};
}

# endif // !__IMODULEDOSEND_HPP__

//
// END OF FILE
//
