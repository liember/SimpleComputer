#include "myTerm.hpp"
#include <iostream>

int myTerm::SetFgColor(enum colors color)
{
	switch (color)
	{
	case black:
		std::cout << "\E[30m";
		break;
	case red:
		std::cout << "\E[31m";
		break;
	case green:
		std::cout << "\E[32m";
		break;
	case brown:
		std::cout << "\E[33m";
		break;
	case blue:
		std::cout << "\E[34m";
		break;
	case magenta:
		std::cout << "\E[35m";
		break;
	case cyan:
		std::cout << "\E[36m";
		break;
	case light_blue:
		std::cout << "\E[37m";
		break;
	case defaul:
		std::cout << "\E[39m";
		break;
	default:
		return -1;
	}
	return 0;
}
