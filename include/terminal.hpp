#pragma once

#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>

inline constexpr char BOXCHAR_REC = 'a';
inline constexpr char *const BOXCHAR_BR = (char *)"j";
inline constexpr char *const BOXCHAR_BL = (char *)"m";
inline constexpr char *const BOXCHAR_TR = (char *)"k";
inline constexpr char *const BOXCHAR_TL = (char *)"l";
inline constexpr char *const BOXCHAR_VERT = (char *)"x";
inline constexpr char *const BOXCHAR_HOR = (char *)"q";

namespace terminal
{

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

class myTerm
{
public:
    int rows;
    int cols;

public:
    int GetScreenSize();
    // sets custom terminal size
    void SetScreenSize(int r, int c);

    int ClrScreen();
    int GotoXY(int x, int y);
    int SetFgColor(enum colors color);
    int SetBgColor(enum colors color);

    int GetScreenSizeX();
    int GetScreenSizeY();
    myTerm();
};

class myBigChars : public myTerm
{
private:
    // prints string using additional code table
    int PrintA(char *str);

    int SetBigCharPos(int *big, int x, int y, int value);
    int GetBigCharPos(int *big, int x, int y, int *value);

public:
    // prints box, just box ;)
    int PrintBox(int x1, int y1, int x2, int y2);

    // prints big char 8x8
    int PrintBigChar(int *big, int x, int y, enum colors fg, enum colors bg);

    //write 'count' bigchars 'big' into 'fd'
    int Write(int fd, int *big, int count);
    // read bigchar from file
    int Read(int fd, int *big, int need_count, int *count);

    // specific func for transform array into big char
    // char bigchar_array[64] = {}
    int *ArrToBig(const char *arr);
};

//Adapter for myTerm and myBigChars modules
class Interface // visual output system
{
public:
    myBigChars term;
    void GoToLastRow();

    Interface() : term() {}
};

} // namespace terminal