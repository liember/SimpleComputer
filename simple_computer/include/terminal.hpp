#pragma once

#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include <string>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>

namespace terminal
{
    namespace
    {
        inline constexpr char BOXCHAR_REC = 'a';
        inline constexpr char *const BOXCHAR_BR = (char *)"j";
        inline constexpr char *const BOXCHAR_BL = (char *)"m";
        inline constexpr char *const BOXCHAR_TR = (char *)"k";
        inline constexpr char *const BOXCHAR_TL = (char *)"l";
        inline constexpr char *const BOXCHAR_VERT = (char *)"x";
        inline constexpr char *const BOXCHAR_HOR = (char *)"q";
    } // namespace

    enum colors
    {
        black,
        red,
        green,
        brown,
        blue,
        magenta,
        cyan,
        light_blue,
        defaul = 9
    };

    namespace comands
    {
        // returns size of termmianl frame
        int GetScreenSize(int &w, int &h);

        void ClrScreen();

        // unsafe move
        void GotoXY(int x, int y);

        // colors
        void SetFgColor(enum colors color);
        void SetBgColor(enum colors color);

        // prints string using additional code table
        void PrintExtended(char *str);
    } // namespace comands

    class BigChar
    {
    private:
        int SetBigCharPos(int *big, int x, int y, int value);
        int GetBigCharPos(int *big, int x, int y, int *value);

        int *big;

    public:
        int _x;
        int _y;

        BigChar(int x_pos, int y_pos);
        // prints big char 8x8
        int PrintBigChar(enum colors fg, enum colors bg);
        // specific func for transform matrix into big char
        // char bigchar_array[64] = {}
        void ArrToBig(const char *arr);
    };

    class Box
    {
    public:
        int x1, y1, x2, y2;
        Box(int x_pos1, int y_pos1, int x_pos2, int y_pos2);
        // prints box, just box ;)
        virtual void Print();
    };

    class TitledBox : public Box
    {
    public:
        TitledBox(int x_pos1, int y_pos1, int x_pos2, int y_pos2, std::string box_title);
        std::string title;
        void Print() override;
    };

    class InputListener
    {
    public:
    private:
        char lastkey[16];
        int SwitchRegime(int regime, int vtime, int vmin, int echo, int sigint);

    public:
        int ReadKey();
        char *GetKey() { return lastkey; }
    };

} // namespace terminal