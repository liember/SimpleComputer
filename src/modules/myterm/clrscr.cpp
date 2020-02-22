#include "myTerm.hpp"
#include <iostream>

int myTerm::ClrScr()
{
	std::cout << "\E[H\E[2J";
	return 0;
}
