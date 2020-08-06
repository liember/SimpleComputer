#include "user_interaction.hpp"
#include "mem_intern.hpp"

#include <string>
#include <sstream>
#include <iomanip>

using namespace user_interaction;

int16_t GraphicalInterface::output_buf = 00;

GraphicalInterface::GraphicalInterface() : box_memory(61, 11, 1, 1, "Memory"),
                                           box_accamulator(25, 2, 63, 1, "Accumulator"),
                                           box_instruction_counter(25, 2, 63, 4, "Instruction Counter"),
                                           box_operation(25, 2, 63, 7, "Operation"),
                                           box_flag(25, 2, 63, 10, "Flags"),
                                           number_selector(45, 9, 1, 13),
                                           bh_selected_number(12341, 2, 14),
                                           box_help(39, 9, 49, 13),
                                           selected_mem(0),
                                           sys_draw()
{
}

void GraphicalInterface::print_flags(int x, int y, int registers)
{
    x += 6;
    sys_draw.output.term.GotoXY(x, y);
    if (registers & (1 << internal_memory::flags::overflow))
        std::cout << "O";
    else
        printf(" ");

    sys_draw.output.term.GotoXY(x + 3, y);
    if (registers & (1 << internal_memory::flags::command))
        std::cout << "E";
    else
        printf(" ");

    sys_draw.output.term.GotoXY(x + 6, y);
    if (registers & (1 << internal_memory::flags::interrupt))
        printf("V");
    else
        printf(" ");

    sys_draw.output.term.GotoXY(x + 9, y);
    if (registers & (1 << internal_memory::flags::out_of_mem))
        printf("M");
    else
        printf(" ");

    sys_draw.output.term.GotoXY(x + 12, y);
    if (registers & (1 << internal_memory::flags::zero_division))
        printf("Z");
    else
        printf(" ");
}

void GraphicalInterface::print_keys(int x, int y)
{
    sys_draw.output.term.GotoXY(x, y);
    printf("l  - load");
    sys_draw.output.term.GotoXY(x, y + 1);
    printf("s  - save");
    sys_draw.output.term.GotoXY(x, y + 2);
    printf("r  - run");
    sys_draw.output.term.GotoXY(x, y + 3);
    printf("t  - step");
    sys_draw.output.term.GotoXY(x, y + 4);
    printf("i  - reset");
    sys_draw.output.term.GotoXY(x, y + 5);
    printf("F5 - accumulator");
    sys_draw.output.term.GotoXY(x, y + 6);
    printf("F6 - instructionCounter");
}

void GraphicalInterface::print_memory(int x, int y, int16_t *mem, int selected, int scomand)
{
    uint16_t smem, command;
    for (int i = 0; i < 10; i++)
    {
        sys_draw.output.term.GotoXY(x, y + i);
        for (int j = 0; j < 10; j++)
        {
            smem = mem[i * 10 + j];
            command = (mem[i * 10 + j] >> 14) & 1;

            std::ostringstream ostr;
            ostr << std::hex << std::setfill('0') << std::setw(4) << (smem & 0x3fff);
            std::string s = ostr.str();

            if (command == 0)
            {
                sys_draw.output.term.SetBgColor(terminal::colors::brown);
                s.insert(s.begin(), '+');
            }
            else
            {
                sys_draw.output.term.SetBgColor(terminal::colors::magenta);
                s.insert(s.begin(), ' ');
            }

            if (i * 10 + j == selected)
            {
                sys_draw.output.term.SetBgColor(terminal::colors::green);
            }
            else if (i * 10 + j == scomand)
            {
                sys_draw.output.term.SetBgColor(terminal::colors::red);
            }
            smem = mem[i * 10 + j] & 0x3FF;
            command = (mem[i * 10 + j] >> 14) & 1;

            std::cout << ' ' << s;
        }
    }
    sys_draw.output.term.SetBgColor(terminal::colors::defaul);
}

int GraphicalInterface::Draw()
{
    box_memory.Draw();
    box_accamulator.Draw();
    box_instruction_counter.Draw();
    box_operation.Draw();
    box_flag.Draw();
    number_selector.Draw();
    // help window
    box_help.Draw();
    print_keys(50, 14);
    return 0;
}

void GraphicalInterface::PrintInfo(int registers, int acc, int inst_count, int16_t *mem)
{
    bh_selected_number.SetNumber(mem[selected_mem]);
    bh_selected_number.Draw();

    sys_draw.output.term.GotoXY(72, 2);
    printf("%0*X ", 4, acc);

    sys_draw.output.term.GotoXY(72, 5);
    printf("%0*X ", 4, inst_count);

    sys_draw.output.term.GotoXY(72, 8);
    printf("%0*X", 2, ((mem[inst_count] & 0x3fff) >> 7));
    printf(" :: %0*X ", 2, (mem[inst_count] & 0x7f));

    print_memory(2, 2, mem, selected_mem, inst_count);

    print_flags(62, 11, registers);

    sys_draw.output.term.GotoXY(1, 23);
    std::cout << "Input/Output: " << output_buf << std::endl;
}
