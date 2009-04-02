#ifndef __IMODULEDOREAD_HPP__
# define __IMODULEDOREAD_HPP__

//
// INCLUDES
//
#include <string>

namespace				zia
{
	/**
	*  Interface permettant de remplacer la lecture sur le socket client
	*/
	class				IModuleDoRead
	{
		public:
			virtual							~IModuleDoRead() {}
			/**
			*  Methode appelee pour lire sur le socket client
			*  @param informations du client
			*  @param buffer
			*  @param taille du buffer
			*  @return le nombre d'octects lus
			*/
			virtual int	doRead(IModuleClient &, void *, unsigned int) = 0;
	};
}

# endif // !__IMODULEDOREAD_HPP__

//
// END OF FILE
//
