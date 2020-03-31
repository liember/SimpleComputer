#include "guikit.hpp"

using namespace gui_kit;

terminal::VOS *base_parameters::vos = nullptr;

base_parameters::base_parameters()
{
    SetBgColor(terminal::myTerm::colors::defaul);
    SetFgColor(terminal::myTerm::colors::defaul);
    SetPos(0, 0);
}

void base_parameters::SetVOS(terminal::VOS *out)
{
    base_parameters::vos = out;
}

void base_parameters::SetBgColor(terminal::myTerm::colors c)
{
    bgcolor = c;
}

void base_parameters::SetFgColor(terminal::myTerm::colors c)
{
    fgcolor = c;
}

void base_parameters::SetPos(int new_x, int new_y)
{
    x = new_x;
    y = new_y;
}

terminal::myTerm::colors base_parameters::FgColor()
{
    return fgcolor;
}

terminal::myTerm::colors base_parameters::BgColor()
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

terminal::VOS *base_parameters::Window()
{
    return base_parameters::vos;
}