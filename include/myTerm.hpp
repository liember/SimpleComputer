#pragma once

#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>

class myTerm
{
public:
	enum colors
	{
		black,
		red,
		green,
		brown,
		blue,
		magenta,
		cyan,
		light_blue,
		defaul = 9
	};

	int rows;
	int cols;

private:
	int GetScreenSize();

public:
	int ClrScr();
	int GotoXY(int x, int y);
	int SetFgColor(enum colors color);
	int SetBgColor(enum colors color);

	int GetScreenSizeX();
	int GetScreenSizeY();
	myTerm();
};
