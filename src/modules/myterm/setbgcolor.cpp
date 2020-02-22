#include "myTerm.hpp"

int myTerm::SetBgColor(enum colors color)
{
	switch (color)
	{
	case black:
		printf("\E[40m");
		break;
	case red:
		printf("\E[41m");
		break;
	case green:
		printf("\E[42m");
		break;
	case brown:
		printf("\E[43m");
		break;
	case blue:
		printf("\E[44m");
		break;
	case magenta:
		printf("\E[45m");
		break;
	case cyan:
		printf("\E[46m");
		break;
	case light_blue:
		printf("\E[47m");
		break;
	case defaul:
		printf("\E[49m");
		break;
	default:
		return -1;
	}
	return 0;
}
