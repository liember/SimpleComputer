#pragma once

#include "myTerm.hpp"

#define BOXCHAR_REC 'a'
#define BOXCHAR_BR "j"
#define BOXCHAR_BL "m"
#define BOXCHAR_TR "k"
#define BOXCHAR_TL "l"
#define BOXCHAR_VERT "x"
#define BOXCHAR_HOR "q"

class myBigChars
{
private:
    myTerm *term;

private:
    // prints string using additional code table
    int PrintA(char *str);

    int SetBigCharPos(int *big, int x, int y, int value);
    int GetBigCharPos(int *big, int x, int y, int *value);

public:
    myBigChars(myTerm *t);

    // prints box, just box ;)
    int PrintBox(int x1, int y1, int x2, int y2);

    // prints big char 8x8
    int PrintBigChar(int *big, int x, int y, enum myTerm::colors fg, enum myTerm::colors bg);

    //write 'count' bigchars 'big' into 'fd'
    int Write(int fd, int *big, int count);
    // read bigchar from file
    int Read(int fd, int *big, int need_count, int *count);

    // specific func for transform array into big char
    // char bigchar_array[64] = {}
    int *ArrToBig(const char *arr);
};
