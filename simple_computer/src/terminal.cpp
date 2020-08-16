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

Box::Box(int x_pos1, int y_pos1, int x_pos2, int y_pos2)
{
	x1 = x_pos1;
	x2 = x_pos2;
	y1 = y_pos1;
	y2 = y_pos2;
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

TitledBox::TitledBox(int x_pos1, int y_pos1, int x_pos2, int y_pos2, std::string box_title) : Box(x_pos1, y_pos1, x_pos2, y_pos2)
{
	title = box_title;
}

void TitledBox::Print()
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
	comands::GotoXY(x1, y1);
	std::cout << title;
}

int InputListener::SwitchRegime(int regime, int vtime, int vmin, int echo, int sigint)
{
	struct termios options;

	if (tcgetattr(STDIN_FILENO, &options) != 0)
		return -1;
	if (regime == 1)
		options.c_lflag |= ICANON;
	else if (regime == 0)
		options.c_lflag &= ~ICANON;
	else
		return -1;
	if (regime == 0)
	{
		options.c_cc[VTIME] = vtime;
		options.c_cc[VMIN] = vmin;
		if (echo == 1)
			options.c_lflag |= ECHO;
		else if (echo == 0)
			options.c_lflag &= ~ECHO;
		else
			return -1;
		if (sigint == 1)
			options.c_lflag |= ISIG;
		else if (sigint == 0)
			options.c_lflag &= ~ISIG;
		else
			return -1;
	}
	if (tcsetattr(STDIN_FILENO, TCSANOW, &options) != 0)
		return -1;

	return 0;
}

int InputListener::ReadKey()
{
	struct termios orig_options;
	int num_read;

	if (tcgetattr(STDIN_FILENO, &orig_options) != 0)
		return -1;
	if (SwitchRegime(0, 0, 1, 0, 1) != 0)
		return -1;
	num_read = read(STDIN_FILENO, lastkey, 15);
	if (num_read < 0)
		return -1;
	lastkey[num_read] = '\0';
	if (tcsetattr(STDIN_FILENO, TCSANOW, &orig_options) != 0)
		return -1;

	return 0;
}