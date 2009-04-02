#ifndef __IMODULESPECIFICEXTENSION_HPP__
# define __IMODULESPECIFICEXTENSION_HPP__

//
// INCLUDES
//
#include <string>
#include <list>

namespace				zia
{
	/**
	*  Heriter de cette interface permet d'etre specifique a une liste d'extension de fichier.
	*/
	class				IModuleSpecificExtension
	{
		public:
			virtual							~IModuleSpecificExtension() {}
			/**
			*  Defini les extensions specifiques.
			*  @param Reference vers la liste a remplir.
			*/
			virtual void	getExtensions(std::list<std::string> &) = 0;
	};
}

# endif // !__IMODULESPECIFICEXTENSION_HPP__

//
// END OF FILE
//
