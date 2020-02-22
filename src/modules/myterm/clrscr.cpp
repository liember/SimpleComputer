#include "myTerm.hpp"

int myTerm::ClrScr()
{
	printf("\E[H\E[2J");
	return 0;
}
