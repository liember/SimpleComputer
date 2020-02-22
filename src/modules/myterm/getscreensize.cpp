#include "myTerm.hpp"

int myTerm::GetScreenSize()
{
	struct winsize w;

	if (!ioctl(STDOUT_FILENO, TIOCGWINSZ, &w))
	{
		rows = w.ws_row;
		cols = w.ws_col;
		return 0;
	}
	else
		return -1;
}