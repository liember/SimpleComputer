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
    int PrintA(char *str);

public:
    myBigChars(myTerm *t);

    int PrintBox(int x1, int y1, int x2, int y2);
    int PrintBigChar(int *big, int x, int y, enum myTerm::colors fg, enum myTerm::colors bg);

    int SetBigCharPos(int *big, int x, int y, int value);
    int GetBigCharPos(int *big, int x, int y, int *value);

    int Write(int fd, int *big, int count);
    int Read(int fd, int *big, int need_count, int *count);

    // specific func for transform array into big char
    // char bigchar_array[64] = {}
    int *arr_to_big(char *arr);
};
