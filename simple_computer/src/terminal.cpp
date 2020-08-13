#include "terminal.hpp"
#include <iostream>

using namespace terminal;

void comands::PrintExtended(char *str)
{
	printf("\E(0%s\E(B", str);
}

void comands::SetFgColor(enum colors color)
{
	std::cout << "\E[3" << color << "m";
}

void comands::SetBgColor(enum colors color)
{
	std::cout << "\E[4" << color << "m";
}

int comands::GetScreenSize(int &w, int &h)
{
	struct winsize win;
	if (!ioctl(STDOUT_FILENO, TIOCGWINSZ, &win))
	{
		h = win.ws_row;
		w = win.ws_col;
		return 0;
	}
	else
		return -1;
}

void comands::GotoXY(int x, int y)
{
	std::cout << "\E[" << y << ";" << x << "H";
}

void comands::ClrScreen()
{
	std::cout << "\E[H\E[2J";
}

void BigChar::ArrToBig(const char *arr)
{
	big = new int[2];
	int i;
	int x, y;

	for (i = 0; i < 64; i++)
	{
		x = i % 8;
		y = i / 8;
		SetBigCharPos(big, x, y, arr[i]);
	}
}
int BigChar::GetBigCharPos(int *big, int x, int y, int *value)
{
	int pos;

	if ((x < 0) || (y < 0) || (x > 7) || (y > 7))
		return -1;
	if (y <= 3)
		pos = 0;
	else
		pos = 1;
	y = y % 4;
	*value = (big[pos] >> (y * 8 + x)) & 1;

	return 0;
}

int BigChar::SetBigCharPos(int *big, int x, int y, int value)
{
	int pos;

	if ((x < 0) || (y < 0) || (x > 7) || (y > 7) || (value < 0) || (value > 1))
		return -1;
	if (y <= 3)
		pos = 0;
	else
		pos = 1;
	y = y % 4;
	if (value == 0)
		big[pos] &= ~(1 << (y * 8 + x));
	else
		big[pos] |= 1 << (y * 8 + x);

	return 0;
}
int BigChar::PrintBigChar(enum colors fg, enum colors bg)
{
	int pos, bit;
	int i, j;
	char row[9];

	row[8] = '\0';
	comands::SetFgColor(fg);
	comands::SetBgColor(bg);
	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 8; j++)
		{
			pos = i >> 2;
			bit = (big[pos] >> ((i % 4) * 8 + j)) & 1;
			if (bit == 0)
				row[j] = ' ';
			else
				row[j] = BOXCHAR_REC;
		}
		comands::GotoXY(_x, _y + i);
		comands::PrintExtended(row);
	}
	comands::SetFgColor(colors::defaul);
	comands::SetBgColor(colors::defaul);
	return 0;
}

void Box::Print()
{
	if (x1 > x2)
	{
		std::swap(x1, x2);
	}
	if (y1 > y2)
	{
		std::swap(x1, x2);
	}
	comands::GotoXY(x1, y1);
	comands::PrintExtended(BOXCHAR_TL);
	for (int i = x1 + 1; i < x2; i++)
		comands::PrintExtended(BOXCHAR_HOR);
	comands::PrintExtended(BOXCHAR_TR);
	for (int i = y1 + 1; i < y2; i++)
	{
		comands::GotoXY(x1, i);
		comands::PrintExtended(BOXCHAR_VERT);
		comands::GotoXY(x2, i);
		comands::PrintExtended(BOXCHAR_VERT);
	}
	comands::GotoXY(x1, y2);
	comands::PrintExtended(BOXCHAR_BL);
	for (int i = x1 + 1; i < x2; i++)
		comands::PrintExtended(BOXCHAR_HOR);
	comands::PrintExtended(BOXCHAR_BR);
}
