#ifndef __IMODULEONREAD_HPP__
# define __IMODULEONREAD_HPP__

namespace				zia
{
	/**
	* Heriter de cette interface permet de traiter la requete apres lecture.
	*/
	class				IModuleOnRead
	{
		public:
			virtual							~IModuleOnRead() {}
			/**
			*  Methode appelee pour traiter la requete apres lecture
			*  @param la requete
			*/
			virtual void	onRead(IModuleRequest &) = 0;
	};
}

# endif // !__IMODULEONREAD_HPP__

//
// END OF FILE
//
