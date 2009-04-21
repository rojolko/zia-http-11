#include "Tools.h"

std::string	Tools::intToString(const int &value)
{
	std::stringstream	nb;

	nb << value;
	return nb.str();
}

