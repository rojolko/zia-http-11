#ifndef __IMODULESPECIFICPORT_HPP__
# define __IMODULESPECIFICPORT_HPP__

//
// INCLUDES
//
#include <string>
#include <list>

namespace				zia
{
	/**
	*  Heriter de cette interface permet d'etre specifique a une liste de port d'ecoute.
	*  Pour chacun des ports specifies  un socket en ecoute sera cree. 
	*/
	class				IModuleSpecificPort
	{
		public:
			/**
			*  Defini les ports specifiques.
			*  @param Reference vers la liste a remplir.
			*/
			virtual void	getPorts(std::list<unsigned short> &) = 0;
	};
}

# endif // !__IMODULESPECIFICPORT_HPP__

//
// END OF FILE
//
