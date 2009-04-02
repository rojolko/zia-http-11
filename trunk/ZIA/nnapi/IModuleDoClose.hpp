#ifndef __IMODULEDOCLOSE_HPP__
# define __IMODULEDOCLOSE_HPP__

namespace				zia
{
	/**
	* Heriter de cette interface permet de remplacer le close sur le socket
	*/
	class				IModuleDoClose
	{
		public:
			/**
			* cette methode est appelee a la place du close par default sur le socket
			* @param une reference sur une IModuleClient (voir son utilisation)
			*/
			virtual bool	doClose(IModuleClient &) = 0;
	};
}

# endif // !__IMODULEDOCLOSE_HPP__

//
// END OF FILE
//
