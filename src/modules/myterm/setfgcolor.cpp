#include "myTerm.hpp"

int myTerm::SetFgColor(enum colors color)
{
	switch (color)
	{
	case black:
		printf("\E[30m");
		break;
	case red:
		printf("\E[31m");
		break;
	case green:
		printf("\E[32m");
		break;
	case brown:
		printf("\E[33m");
		break;
	case blue:
		printf("\E[34m");
		break;
	case magenta:
		printf("\E[35m");
		break;
	case cyan:
		printf("\E[36m");
		break;
	case light_blue:
		printf("\E[37m");
		break;
	case defaul:
		printf("\E[39m");
		break;
	default:
		return -1;
	}
	return 0;
}
