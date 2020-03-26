#include "guikit.hpp"

using namespace gui_kit;

VOS *base_parameters::vos = nullptr;

void base_parameters::SetVOS(VOS *out)
{
    base_parameters::vos = out;
}

void base_parameters::SetBgColor(myTerm::colors c)
{
    bgcolor = c;
}

void base_parameters::SetFgColor(myTerm::colors c)
{
    fgcolor = c;
}

void base_parameters::SetPos(int new_x, int new_y)
{
    x = new_x;
    y = new_y;
}

myTerm::colors base_parameters::FgColor()
{
    return fgcolor;
}

myTerm::colors base_parameters::BgColor()
{
    return bgcolor;
}

int base_parameters::PosX()
{
    return x;
}

int base_parameters::PosY()
{
    return y;
}

VOS *base_parameters::Window()
{
    return base_parameters::vos;
}