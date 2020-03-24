#include "myTerm.hpp"
#include <iostream>

int myTerm::SetFgColor(enum colors color)
{
	std::cout << "\E[3" << color << "m";
	return 0;
}
