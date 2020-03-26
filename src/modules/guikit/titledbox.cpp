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
    Window()->bc->PrintBox(PosX(), PosY(), PosX() + width, PosY() + height);
    if ((int)title.length() > width)
    {
        Window()->term->GotoXY(PosX(), PosY());
    }
    else
    {
        Window()->term->GotoXY(PosX() + (width / 2 - title.length() / 2), PosY());
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