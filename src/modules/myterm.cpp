#include "myTerm.hpp"
#include <iostream>

int myTerm::SetFgColor(enum colors color)
{
	std::cout << "\E[3" << color << "m";
	return 0;
}

int myTerm::SetBgColor(enum colors color)
{
	std::cout << "\E[4" << color << "m";
	return 0;
}

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

int myTerm::GetScreenSizeX()
{
	return cols;
}

int myTerm::GetScreenSizeY()
{
	return rows;
}

void myTerm::SetScreenSize(int r, int c)
{
	rows = r;
	cols = c;
}
myTerm::myTerm()
{
	GetScreenSize();
}
int myTerm::GotoXY(int x, int y)
{
	if ((y < rows) && (x < cols) && (x >= 0) && (y >= 0))
	{
		std::cout << "\E[" << y << ";" << x << "H";
		return 0;
	}
	else
		return -1;
}

int myTerm::ClrScr()
{
	std::cout << "\E[H\E[2J";
	return 0;
}
