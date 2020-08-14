#pragma once

#include "myReadkey.hpp"
#include "terminal.hpp"

namespace mySimpleComputer
{
    namespace
    {
        inline constexpr char *l_key = (char *const) "l";
        inline constexpr char *s_key = (char *const) "s";
        inline constexpr char *r_key = (char *const) "r";
        inline constexpr char *t_key = (char *const) "t";
        inline constexpr char *i_key = (char *const) "i";
        inline constexpr char *q_key = (char *const) "q";
        inline constexpr char *f5_key = (char *const) "\033[15~";
        inline constexpr char *f6_key = (char *const) "\033[17~";
        inline constexpr char *ar_up_key = (char *const) "\033[A";
        inline constexpr char *ar_do_key = (char *const) "\033[B";
        inline constexpr char *ar_ri_key = (char *const) "\033[C";
        inline constexpr char *ar_le_key = (char *const) "\033[D";
    } // namespace

    class View
    {
    private:
        // memory
        terminal::TitledBox data;
        terminal::TitledBox command;

        // core
        terminal::TitledBox accamulator;
        terminal::TitledBox state;
        terminal::TitledBox instruction;

        terminal::TitledBox output;

        // some ui elements drawing
        void print_flags(int x, int y, int registers);
        void print_memory(int x, int y, int16_t *mem, int selected, int scomand);

    public:
        View();

        // draw boxes and states of spc,
        //but do not draw elements thats refers to memory
        int Draw();
    };

} // namespace mySimpleComputer