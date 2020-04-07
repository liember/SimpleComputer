#include "guikit.hpp"

using namespace gui_kit;

void untitled_box::Move(int new_x, int new_y)
{
    SetPos(new_x, new_y);
}

void untitled_box::Resize(int new_width, int new_height)
{
    width = new_width;
    height = new_height;
}

void untitled_box::Draw()
{
    terminal.term.PrintBox(PosX(), PosY(), PosX() + width, PosY() + height);
}

untitled_box::untitled_box(int w, int h, int _x, int _y)
{
    SetPos(_x, _y);
    width = w;
    height = h;
}