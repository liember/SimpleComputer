#include "myTerm.hpp"

myTerm::myTerm()
{
    GetScreenSize();
}

int myTerm::GetScreenSizeX()
{
    return cols;
}

int myTerm::GetScreenSizeY()
{
    return rows;
}