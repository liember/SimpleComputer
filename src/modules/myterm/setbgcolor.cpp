#include "myTerm.hpp"
#include <iostream>

int myTerm::SetBgColor(enum colors color)
{
	std::cout << "\E[4" << color << "m";
	return 0;
}
