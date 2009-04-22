#include "Tools.h"

std::string	Tools::intToString(const int &value)
{
	std::stringstream	nb;

	nb << value;
	return nb.str();
}

std::string Tools::charToString(const char* str)
{
	std::stringstream desc;

	desc << str;
	return desc.str();
}

