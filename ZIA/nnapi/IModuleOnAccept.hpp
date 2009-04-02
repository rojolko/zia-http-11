#ifndef __IMODULEONACCEPT_HPP__
# define __IMODULEONACCEPT_HPP__

namespace				zia
{
	/**
	*  Heriter de cette interface permet d'etre appele lors de l'evenement onAccept
	*/
	class				IModuleOnAccept
	{
		public:
			virtual							~IModuleOnAccept() {}
			/**
			*  Methode appelee lors de l'acceptation d'un nouveau client
			*  @param une interface sur le client (cf IModuleClient)
			*  @return si le client doit etre accepte ou non
			*/
			virtual bool	onAccept(IModuleClient &) = 0;
	};
}

# endif // !__IMODULEONACCEPT_HPP__

//
// END OF FILE
//
