#include "myTerm.hpp"
#include <iostream>

int myTerm::GotoXY(int x, int y)
{
	int rows, cols;
	if ((y < rows) && (x < cols) && (x >= 0) && (y >= 0))
	{
		std::cout << "\E[" << y << ";" << x << "H";
		return 0;
	}
	else
		return -1;
}
