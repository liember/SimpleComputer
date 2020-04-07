#include "guikit.hpp"

using namespace gui_kit;

base_parameters::base_parameters()
{
    SetBgColor(terminal::colors::defaul);
    SetFgColor(terminal::colors::defaul);
    SetPos(0, 0);
}

void base_parameters::SetBgColor(terminal::colors c)
{
    bgcolor = c;
}

void base_parameters::SetFgColor(terminal::colors c)
{
    fgcolor = c;
}

void base_parameters::SetPos(int new_x, int new_y)
{
    x = new_x;
    y = new_y;
}

terminal::colors base_parameters::FgColor()
{
    return fgcolor;
}

terminal::colors base_parameters::BgColor()
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
