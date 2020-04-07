#include "guikit.hpp"

using namespace gui_kit;

void titled_box::Move(int new_x, int new_y)
{
    SetPos(new_x, new_y);
}

void titled_box::Resize(int new_width, int new_height)
{
    width = new_width;
    height = new_height;
}

void titled_box::Draw()
{
    terminal.term.PrintBox(PosX(), PosY(), PosX() + width, PosY() + height);
    if ((int)title.length() > width)
    {
        terminal.term.GotoXY(PosX(), PosY());
    }
    else
    {
        terminal.term.GotoXY(PosX() + (width / 2 - title.length() / 2), PosY());
    }
    std::cout << " " << title << " ";
}

titled_box::titled_box(int w, int h, int _x, int _y, std::string _title)
{
    SetPos(_x, _y);
    width = w;
    height = h;
    title = _title;
}