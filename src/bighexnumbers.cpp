#include "guikit.hpp"

#include <sstream>

using namespace gui_kit;

constexpr char bigchar_plus[64] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 1, 1, 0, 0, 0,
    0, 0, 0, 1, 1, 0, 0, 0,
    0, 1, 1, 1, 1, 1, 1, 0,
    0, 1, 1, 1, 1, 1, 1, 0,
    0, 0, 0, 1, 1, 0, 0, 0,
    0, 0, 0, 1, 1, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0};

constexpr char bigchar_0[64] = {
    0, 0, 1, 1, 1, 1, 0, 0,
    0, 1, 0, 0, 0, 0, 1, 0,
    1, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 1,
    0, 1, 0, 0, 0, 0, 1, 0,
    0, 0, 1, 1, 1, 1, 0, 0};

constexpr char bigchar_1[64] = {
    0, 0, 0, 0, 0, 1, 1, 0,
    0, 0, 0, 0, 1, 0, 1, 0,
    0, 0, 0, 1, 0, 0, 1, 0,
    0, 0, 0, 0, 0, 0, 1, 0,
    0, 0, 0, 0, 0, 0, 1, 0,
    0, 0, 0, 0, 0, 0, 1, 0,
    0, 0, 0, 0, 0, 0, 1, 0,
    0, 0, 0, 0, 0, 0, 1, 0};

constexpr char bigchar_2[64] = {
    0, 0, 0, 1, 1, 1, 0, 0,
    0, 0, 1, 0, 0, 0, 1, 0,
    0, 1, 0, 0, 0, 0, 1, 0,
    0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 0, 1, 0, 0, 0,
    0, 0, 0, 1, 0, 0, 0, 0,
    0, 0, 1, 0, 0, 0, 0, 0,
    0, 1, 1, 1, 1, 1, 1, 0};

constexpr char bigchar_3[64] = {
    0, 0, 1, 1, 1, 1, 1, 0,
    0, 0, 0, 0, 0, 0, 1, 0,
    0, 0, 0, 0, 0, 0, 1, 0,
    0, 0, 0, 1, 1, 1, 1, 0,
    0, 0, 0, 0, 0, 0, 1, 0,
    0, 0, 0, 0, 0, 0, 1, 0,
    0, 0, 0, 0, 0, 0, 1, 0,
    0, 0, 1, 1, 1, 1, 1, 0};

constexpr char bigchar_4[64] = {
    0, 0, 1, 0, 0, 0, 1, 0,
    0, 0, 1, 0, 0, 0, 1, 0,
    0, 0, 1, 0, 0, 0, 1, 0,
    0, 0, 1, 1, 1, 1, 1, 0,
    0, 0, 0, 0, 0, 0, 1, 0,
    0, 0, 0, 0, 0, 0, 1, 0,
    0, 0, 0, 0, 0, 0, 1, 0,
    0, 0, 0, 0, 0, 0, 1, 0};

constexpr char bigchar_5[64] = {
    0, 0, 1, 1, 1, 1, 1, 0,
    0, 0, 1, 0, 0, 0, 0, 0,
    0, 0, 1, 0, 0, 0, 0, 0,
    0, 0, 1, 1, 1, 1, 1, 0,
    0, 0, 0, 0, 0, 0, 1, 0,
    0, 0, 0, 0, 0, 0, 1, 0,
    0, 0, 0, 0, 0, 0, 1, 0,
    0, 0, 1, 1, 1, 1, 1, 0};

constexpr char bigchar_6[64] = {
    0, 0, 1, 1, 1, 1, 1, 0,
    0, 0, 1, 0, 0, 0, 0, 0,
    0, 0, 1, 0, 0, 0, 0, 0,
    0, 0, 1, 1, 1, 1, 1, 0,
    0, 0, 1, 0, 0, 0, 1, 0,
    0, 0, 1, 0, 0, 0, 1, 0,
    0, 0, 1, 0, 0, 0, 1, 0,
    0, 0, 1, 1, 1, 1, 1, 0};

constexpr char bigchar_7[64] = {
    0, 0, 1, 1, 1, 1, 1, 0,
    0, 0, 0, 0, 0, 0, 1, 0,
    0, 0, 0, 0, 0, 0, 1, 0,
    0, 0, 0, 0, 0, 0, 1, 0,
    0, 0, 0, 0, 0, 0, 1, 0,
    0, 0, 0, 0, 0, 0, 1, 0,
    0, 0, 0, 0, 0, 0, 1, 0,
    0, 0, 0, 0, 0, 0, 1, 0};

constexpr char bigchar_8[64] = {
    0, 0, 1, 1, 1, 1, 1, 0,
    0, 0, 1, 0, 0, 0, 1, 0,
    0, 0, 1, 0, 0, 0, 1, 0,
    0, 0, 1, 1, 1, 1, 1, 0,
    0, 0, 1, 0, 0, 0, 1, 0,
    0, 0, 1, 0, 0, 0, 1, 0,
    0, 0, 1, 0, 0, 0, 1, 0,
    0, 0, 1, 1, 1, 1, 1, 0};

constexpr char bigchar_9[64] = {
    0, 0, 1, 1, 1, 1, 1, 0,
    0, 0, 1, 0, 0, 0, 1, 0,
    0, 0, 1, 0, 0, 0, 1, 0,
    0, 0, 1, 1, 1, 1, 1, 0,
    0, 0, 0, 0, 0, 0, 1, 0,
    0, 0, 0, 0, 0, 0, 1, 0,
    0, 0, 0, 0, 0, 0, 1, 0,
    0, 0, 1, 1, 1, 1, 1, 0};

constexpr char bigchar_A[64] = {
    0, 0, 1, 1, 1, 1, 0, 0,
    0, 1, 0, 0, 0, 0, 1, 0,
    0, 1, 0, 0, 0, 0, 1, 0,
    0, 1, 1, 1, 1, 1, 1, 0,
    0, 1, 0, 0, 0, 0, 1, 0,
    0, 1, 0, 0, 0, 0, 1, 0,
    0, 1, 0, 0, 0, 0, 1, 0,
    0, 1, 0, 0, 0, 0, 1, 0};

constexpr char bigchar_B[64] = {
    0, 1, 1, 1, 1, 0, 0, 0,
    0, 1, 0, 0, 1, 0, 0, 0,
    0, 1, 0, 0, 1, 0, 0, 0,
    0, 1, 1, 1, 1, 1, 0, 0,
    0, 1, 0, 0, 0, 0, 1, 0,
    0, 1, 0, 0, 0, 0, 1, 0,
    0, 1, 0, 0, 0, 0, 1, 0,
    0, 1, 1, 1, 1, 1, 0, 0};

constexpr char bigchar_C[64] = {
    0, 0, 1, 1, 1, 1, 1, 0,
    0, 1, 0, 0, 0, 0, 0, 0,
    0, 1, 0, 0, 0, 0, 0, 0,
    0, 1, 0, 0, 0, 0, 0, 0,
    0, 1, 0, 0, 0, 0, 0, 0,
    0, 1, 0, 0, 0, 0, 0, 0,
    0, 1, 0, 0, 0, 0, 0, 0,
    0, 0, 1, 1, 1, 1, 1, 0};

constexpr char bigchar_D[64] = {
    0, 1, 1, 1, 1, 0, 0, 0,
    0, 1, 0, 0, 0, 1, 0, 0,
    0, 1, 0, 0, 0, 0, 1, 0,
    0, 1, 0, 0, 0, 0, 1, 0,
    0, 1, 0, 0, 0, 0, 1, 0,
    0, 1, 0, 0, 0, 0, 1, 0,
    0, 1, 0, 0, 0, 1, 0, 0,
    0, 1, 1, 1, 1, 0, 0, 0};

constexpr char bigchar_E[64] = {
    0, 1, 1, 1, 1, 1, 1, 0,
    0, 1, 0, 0, 0, 0, 0, 0,
    0, 1, 0, 0, 0, 0, 0, 0,
    0, 1, 1, 1, 1, 1, 0, 0,
    0, 1, 0, 0, 0, 0, 0, 0,
    0, 1, 0, 0, 0, 0, 0, 0,
    0, 1, 0, 0, 0, 0, 0, 0,
    0, 1, 1, 1, 1, 1, 1, 0};

constexpr char bigchar_F[64] = {
    0, 1, 1, 1, 1, 1, 1, 0,
    0, 1, 0, 0, 0, 0, 0, 0,
    0, 1, 0, 0, 0, 0, 0, 0,
    0, 1, 1, 1, 1, 0, 0, 0,
    0, 1, 0, 0, 0, 0, 0, 0,
    0, 1, 0, 0, 0, 0, 0, 0,
    0, 1, 0, 0, 0, 0, 0, 0,
    0, 1, 0, 0, 0, 0, 0, 0};

big_hex_bumbers::big_hex_bumbers(int num, int new_x, int new_y)
{
    SetPos(new_x, new_y);
    number = num;
    alf['+'] = Window()->bc->ArrToBig(bigchar_plus);
    alf['0'] = Window()->bc->ArrToBig(bigchar_0);
    alf['1'] = Window()->bc->ArrToBig(bigchar_1);
    alf['2'] = Window()->bc->ArrToBig(bigchar_2);
    alf['3'] = Window()->bc->ArrToBig(bigchar_3);
    alf['4'] = Window()->bc->ArrToBig(bigchar_4);
    alf['5'] = Window()->bc->ArrToBig(bigchar_5);
    alf['6'] = Window()->bc->ArrToBig(bigchar_6);
    alf['7'] = Window()->bc->ArrToBig(bigchar_7);
    alf['8'] = Window()->bc->ArrToBig(bigchar_8);
    alf['9'] = Window()->bc->ArrToBig(bigchar_9);
    alf['a'] = Window()->bc->ArrToBig(bigchar_A);
    alf['b'] = Window()->bc->ArrToBig(bigchar_B);
    alf['c'] = Window()->bc->ArrToBig(bigchar_C);
    alf['d'] = Window()->bc->ArrToBig(bigchar_D);
    alf['e'] = Window()->bc->ArrToBig(bigchar_E);
    alf['f'] = Window()->bc->ArrToBig(bigchar_F);
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
    ostr << std::hex << number;
    std::string s = ostr.str();
    std::cout << s << std::endl;
    Window()->bc->PrintBigChar(alf.find('+')->second, PosX(), PosY(), BgColor(), FgColor());
    for (int i = 0; i < (int)s.length(); i++)
    {
        Window()->bc->PrintBigChar(alf.find(s.c_str()[i])->second, PosX() + 9 + i * 9, PosY(), BgColor(), FgColor());
    }
}