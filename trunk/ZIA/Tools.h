#ifndef _TOOLS_H_
#define _TOOLS_H_

#include <sstream>
#include <list>

namespace	Tools
{
	std::string intToString(const int& value);
	template<typename T>
	void		dumpList(std::list<T> &list)
	{
		int	i;

		std::list<T>::iterator	it;

		for (i = 1, it = list.begin(); it != list.end(); ++it, ++i)
			std::cout << "	" << i << "- " << *it << std::endl;
	}
	template<typename T, typename S>
	bool		isInList(std::list<T> &list, S value)
	{
		std::list<T>::iterator	it;

		for (it = list.begin(); it != list.end(); ++it)
			if (*it == value)
				return true;
		return false;
	}
}
#endif