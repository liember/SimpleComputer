#include "myTerm.hpp"
#include <iostream>

int myTerm::SetBgColor(enum colors color)
{
	switch (color)
	{
	case black:
		std::cout << "\E[40m";
		break;
	case red:
		std::cout << "\E[41m";
		break;
	case green:
		std::cout << "\E[42m";
		break;
	case brown:
		std::cout << "\E[43m";
		break;
	case blue:
		std::cout << "\E[44m";
		break;
	case magenta:
		std::cout << "\E[45m";
		break;
	case cyan:
		std::cout << "\E[46m";
		break;
	case light_blue:
		std::cout << "\E[47m";
		break;
	case defaul:
		std::cout << "\E[49m";
		break;
	default:
		return -1;
	}
	return 0;
}
