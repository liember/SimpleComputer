#include "guikit.hpp"

#include <string>
#include <sstream>
#include <iomanip>

using namespace gui_kit;

void titled_box::Draw()
{
    output().term.PrintBox(PosX(), PosY(), PosX() + width, PosY() + height);
    if ((int)title.length() > width)
    {
        output().term.GotoXY(PosX(), PosY());
    }
    else
    {
        output().term.GotoXY(PosX() + (width / 2 - title.length() / 2), PosY());
    }
    std::cout << " " << title << " ";
}

titled_box::titled_box(int w, int h, int _x, int _y, std::string _title) : untitled_box(w, h, _x, _y)
{
    title = _title;
}

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
    output().term.PrintBox(PosX(), PosY(), PosX() + width, PosY() + height);
}

untitled_box::untitled_box(int w, int h, int _x, int _y)
{
    SetPos(_x, _y);
    width = w;
    height = h;
}

big_hex_bumbers::big_hex_bumbers(int num, int new_x, int new_y)

{

    constexpr char bc_plus[64] = {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 1, 1, 0, 0, 0,
        0, 0, 0, 1, 1, 0, 0, 0,
        0, 1, 1, 1, 1, 1, 1, 0,
        0, 1, 1, 1, 1, 1, 1, 0,
        0, 0, 0, 1, 1, 0, 0, 0,
        0, 0, 0, 1, 1, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0};

    constexpr char bc_0[64] = {
        0, 0, 1, 1, 1, 1, 0, 0,
        0, 1, 0, 0, 0, 0, 1, 0,
        1, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 1,
        0, 1, 0, 0, 0, 0, 1, 0,
        0, 0, 1, 1, 1, 1, 0, 0};

    constexpr char bc_1[64] = {
        0, 0, 0, 0, 0, 1, 1, 0,
        0, 0, 0, 0, 1, 0, 1, 0,
        0, 0, 0, 1, 0, 0, 1, 0,
        0, 0, 0, 0, 0, 0, 1, 0,
        0, 0, 0, 0, 0, 0, 1, 0,
        0, 0, 0, 0, 0, 0, 1, 0,
        0, 0, 0, 0, 0, 0, 1, 0,
        0, 0, 0, 0, 0, 0, 1, 0};

    constexpr char bc_2[64] = {
        0, 0, 0, 1, 1, 1, 0, 0,
        0, 0, 1, 0, 0, 0, 1, 0,
        0, 1, 0, 0, 0, 0, 1, 0,
        0, 0, 0, 0, 0, 1, 0, 0,
        0, 0, 0, 0, 1, 0, 0, 0,
        0, 0, 0, 1, 0, 0, 0, 0,
        0, 0, 1, 0, 0, 0, 0, 0,
        0, 1, 1, 1, 1, 1, 1, 0};

    constexpr char bc_3[64] = {
        0, 0, 1, 1, 1, 1, 1, 0,
        0, 0, 0, 0, 0, 0, 1, 0,
        0, 0, 0, 0, 0, 0, 1, 0,
        0, 0, 0, 1, 1, 1, 1, 0,
        0, 0, 0, 0, 0, 0, 1, 0,
        0, 0, 0, 0, 0, 0, 1, 0,
        0, 0, 0, 0, 0, 0, 1, 0,
        0, 0, 1, 1, 1, 1, 1, 0};

    constexpr char bc_4[64] = {
        0, 0, 1, 0, 0, 0, 1, 0,
        0, 0, 1, 0, 0, 0, 1, 0,
        0, 0, 1, 0, 0, 0, 1, 0,
        0, 0, 1, 1, 1, 1, 1, 0,
        0, 0, 0, 0, 0, 0, 1, 0,
        0, 0, 0, 0, 0, 0, 1, 0,
        0, 0, 0, 0, 0, 0, 1, 0,
        0, 0, 0, 0, 0, 0, 1, 0};

    constexpr char bc_5[64] = {
        0, 0, 1, 1, 1, 1, 1, 0,
        0, 0, 1, 0, 0, 0, 0, 0,
        0, 0, 1, 0, 0, 0, 0, 0,
        0, 0, 1, 1, 1, 1, 1, 0,
        0, 0, 0, 0, 0, 0, 1, 0,
        0, 0, 0, 0, 0, 0, 1, 0,
        0, 0, 0, 0, 0, 0, 1, 0,
        0, 0, 1, 1, 1, 1, 1, 0};

    constexpr char bc_6[64] = {
        0, 0, 1, 1, 1, 1, 1, 0,
        0, 0, 1, 0, 0, 0, 0, 0,
        0, 0, 1, 0, 0, 0, 0, 0,
        0, 0, 1, 1, 1, 1, 1, 0,
        0, 0, 1, 0, 0, 0, 1, 0,
        0, 0, 1, 0, 0, 0, 1, 0,
        0, 0, 1, 0, 0, 0, 1, 0,
        0, 0, 1, 1, 1, 1, 1, 0};

    constexpr char bc_7[64] = {
        0, 0, 1, 1, 1, 1, 1, 0,
        0, 0, 0, 0, 0, 0, 1, 0,
        0, 0, 0, 0, 0, 0, 1, 0,
        0, 0, 0, 0, 0, 0, 1, 0,
        0, 0, 0, 0, 0, 0, 1, 0,
        0, 0, 0, 0, 0, 0, 1, 0,
        0, 0, 0, 0, 0, 0, 1, 0,
        0, 0, 0, 0, 0, 0, 1, 0};

    constexpr char bc_8[64] = {
        0, 0, 1, 1, 1, 1, 1, 0,
        0, 0, 1, 0, 0, 0, 1, 0,
        0, 0, 1, 0, 0, 0, 1, 0,
        0, 0, 1, 1, 1, 1, 1, 0,
        0, 0, 1, 0, 0, 0, 1, 0,
        0, 0, 1, 0, 0, 0, 1, 0,
        0, 0, 1, 0, 0, 0, 1, 0,
        0, 0, 1, 1, 1, 1, 1, 0};

    constexpr char bc_9[64] = {
        0, 0, 1, 1, 1, 1, 1, 0,
        0, 0, 1, 0, 0, 0, 1, 0,
        0, 0, 1, 0, 0, 0, 1, 0,
        0, 0, 1, 1, 1, 1, 1, 0,
        0, 0, 0, 0, 0, 0, 1, 0,
        0, 0, 0, 0, 0, 0, 1, 0,
        0, 0, 0, 0, 0, 0, 1, 0,
        0, 0, 1, 1, 1, 1, 1, 0};

    constexpr char bc_A[64] = {
        0, 0, 1, 1, 1, 1, 0, 0,
        0, 1, 0, 0, 0, 0, 1, 0,
        0, 1, 0, 0, 0, 0, 1, 0,
        0, 1, 1, 1, 1, 1, 1, 0,
        0, 1, 0, 0, 0, 0, 1, 0,
        0, 1, 0, 0, 0, 0, 1, 0,
        0, 1, 0, 0, 0, 0, 1, 0,
        0, 1, 0, 0, 0, 0, 1, 0};

    constexpr char bc_B[64] = {
        0, 1, 1, 1, 1, 0, 0, 0,
        0, 1, 0, 0, 1, 0, 0, 0,
        0, 1, 0, 0, 1, 0, 0, 0,
        0, 1, 1, 1, 1, 1, 0, 0,
        0, 1, 0, 0, 0, 0, 1, 0,
        0, 1, 0, 0, 0, 0, 1, 0,
        0, 1, 0, 0, 0, 0, 1, 0,
        0, 1, 1, 1, 1, 1, 0, 0};

    constexpr char bc_C[64] = {
        0, 0, 1, 1, 1, 1, 1, 0,
        0, 1, 0, 0, 0, 0, 0, 0,
        0, 1, 0, 0, 0, 0, 0, 0,
        0, 1, 0, 0, 0, 0, 0, 0,
        0, 1, 0, 0, 0, 0, 0, 0,
        0, 1, 0, 0, 0, 0, 0, 0,
        0, 1, 0, 0, 0, 0, 0, 0,
        0, 0, 1, 1, 1, 1, 1, 0};

    constexpr char bc_D[64] = {
        0, 1, 1, 1, 1, 0, 0, 0,
        0, 1, 0, 0, 0, 1, 0, 0,
        0, 1, 0, 0, 0, 0, 1, 0,
        0, 1, 0, 0, 0, 0, 1, 0,
        0, 1, 0, 0, 0, 0, 1, 0,
        0, 1, 0, 0, 0, 0, 1, 0,
        0, 1, 0, 0, 0, 1, 0, 0,
        0, 1, 1, 1, 1, 0, 0, 0};

    constexpr char bc_E[64] = {
        0, 1, 1, 1, 1, 1, 1, 0,
        0, 1, 0, 0, 0, 0, 0, 0,
        0, 1, 0, 0, 0, 0, 0, 0,
        0, 1, 1, 1, 1, 1, 0, 0,
        0, 1, 0, 0, 0, 0, 0, 0,
        0, 1, 0, 0, 0, 0, 0, 0,
        0, 1, 0, 0, 0, 0, 0, 0,
        0, 1, 1, 1, 1, 1, 1, 0};

    constexpr char bc_F[64] = {
        0, 1, 1, 1, 1, 1, 1, 0,
        0, 1, 0, 0, 0, 0, 0, 0,
        0, 1, 0, 0, 0, 0, 0, 0,
        0, 1, 1, 1, 1, 0, 0, 0,
        0, 1, 0, 0, 0, 0, 0, 0,
        0, 1, 0, 0, 0, 0, 0, 0,
        0, 1, 0, 0, 0, 0, 0, 0,
        0, 1, 0, 0, 0, 0, 0, 0};

    SetPos(new_x, new_y);

    number = num;
    alf['+'] = output().term.ArrToBig(bc_plus);
    alf['0'] = output().term.ArrToBig(bc_0);
    alf['1'] = output().term.ArrToBig(bc_1);
    alf['2'] = output().term.ArrToBig(bc_2);
    alf['3'] = output().term.ArrToBig(bc_3);
    alf['4'] = output().term.ArrToBig(bc_4);
    alf['5'] = output().term.ArrToBig(bc_5);
    alf['6'] = output().term.ArrToBig(bc_6);
    alf['7'] = output().term.ArrToBig(bc_7);
    alf['8'] = output().term.ArrToBig(bc_8);
    alf['9'] = output().term.ArrToBig(bc_9);
    alf['a'] = output().term.ArrToBig(bc_A);
    alf['b'] = output().term.ArrToBig(bc_B);
    alf['c'] = output().term.ArrToBig(bc_C);
    alf['d'] = output().term.ArrToBig(bc_D);
    alf['e'] = output().term.ArrToBig(bc_E);
    alf['f'] = output().term.ArrToBig(bc_F);
}

void big_hex_bumbers::SetNumber(int new_number)
{
    number = new_number;
}

void big_hex_bumbers::Move(int new_x, int new_y)
{
    SetPos(new_x, new_y);
}

void big_hex_bumbers::Draw()
{
    std::ostringstream ostr;
    ostr << std::hex << std::setfill('0') << std::setw(4) << number;
    std::string s = ostr.str();
    if (number <= 0b100000000000000)
    {
        s.insert(s.begin(), '+');
    }
    for (int i = 0; i < (int)s.length(); i++)
    {
        output().term.PrintBigChar(alf.find(s.c_str()[i])->second, PosX() + i * 9, PosY(), BgColor(), FgColor());
    }
}

base_parameters::base_parameters()
{
    SetBgColor(terminal::colors::defaul);
    SetFgColor(terminal::colors::defaul);
    SetPos(0, 0);
}

terminal::Interface &base_parameters::output()
{
    static terminal::Interface myTerm;
    return myTerm;
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
