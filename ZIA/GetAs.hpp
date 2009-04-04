#ifndef _GETAS_HPP_
#define _GETAS_HPP_

template<typename T>
T			*getAs(zia::IModule* inst)
{
	return (dynamic_cast<T *>(inst));
}

#endif