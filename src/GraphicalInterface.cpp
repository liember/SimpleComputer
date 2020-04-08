#include "user_interaction.hpp"
#include "mem_intern.hpp"

using namespace user_interaction;

GraphicalInterface::GraphicalInterface() : sys_draw(),
                                           box_memory(60, 11, 1, 1, "Memory"),
                                           box_accamulator(25, 2, 62, 1, "Accumulator"),
                                           box_instruction_counter(25, 2, 62, 4, "Instruction Counter"),
                                           box_operation(25, 2, 62, 7, "Operation"),
                                           box_flag(25, 2, 62, 10, "Flags"),
                                           number_selector(45, 9, 1, 13),
                                           bh_selected_number(12341, 2, 14),
                                           box_help(39, 9, 48, 13),
                                           selected_mem(0)
{
}

void GraphicalInterface::print_flags(int x, int y, int registers)
{
    x += 6;
    sys_draw.output().term.GotoXY(x, y);
    if (registers & (1 << FLAG_OVERFLOW))
        std::cout << "O";
    else
        printf(" ");

    sys_draw.output().term.GotoXY(x + 3, y);
    if (registers & (1 << FLAG_COMMAND))
        std::cout << "E";
    else
        printf(" ");

    sys_draw.output().term.GotoXY(x + 6, y);
    if (registers & (1 << FLAG_INTERRUPT))
        printf("V");
    else
        printf(" ");

    sys_draw.output().term.GotoXY(x + 9, y);
    if (registers & (1 << FLAG_OUTMEM))
        printf("M");
    else
        printf(" ");

    sys_draw.output().term.GotoXY(x + 12, y);
    if (registers & (1 << FLAG_DIVISION))
        printf("Z");
    else
        printf(" ");
}

void GraphicalInterface::print_keys(int x, int y)
{
    sys_draw.output().term.GotoXY(x, y);
    printf("l  - load");
    sys_draw.output().term.GotoXY(x, y + 1);
    printf("s  - save");
    sys_draw.output().term.GotoXY(x, y + 2);
    printf("r  - run");
    sys_draw.output().term.GotoXY(x, y + 3);
    printf("t  - step");
    sys_draw.output().term.GotoXY(x, y + 4);
    printf("i  - reset");
    sys_draw.output().term.GotoXY(x, y + 5);
    printf("F5 - accumulator");
    sys_draw.output().term.GotoXY(x, y + 6);
    printf("F6 - instructionCounter");
}

void GraphicalInterface::print_memory(int x, int y, uint16_t *mem, int selected)
{
    int i, j;
    int smem, command;

    for (i = 0; i < 10; i++)
    {
        sys_draw.output().term.GotoXY(x, y + i);
        for (j = 0; j < 9; j++)
        {
            smem = mem[i * 10 + j] & 0x3FF;
            command = (mem[i * 10 + j] >> 14) & 1;
            if (command == 0)
            {
                sys_draw.output().term.SetBgColor(terminal::colors::brown);
                std::cout << "+";
            }
            else
            {
                sys_draw.output().term.SetBgColor(terminal::colors::magenta);
                std::cout << " ";
            }

            if (i * 10 + j == selected)
            {
                sys_draw.output().term.SetBgColor(terminal::colors::green);
            }
            else if (i * 10 + j == selected)
            {
                sys_draw.output().term.SetBgColor(terminal::colors::red);
            }
            printf("%0*X ", 4, smem);
        }
        smem = mem[i * 10 + j] & 0x3FF;
        command = (mem[i * 10 + j] >> 14) & 1;
        if (command == 0)
            printf("+");
        else
            printf(" ");
        printf("%0*X", 4, smem);
    }
    sys_draw.output().term.SetBgColor(terminal::colors::defaul);
}

int GraphicalInterface::Draw()
{
    box_memory.Draw();

    box_accamulator.Draw();
    sys_draw.output().term.GotoXY(72, 2);

    box_instruction_counter.Draw();
    sys_draw.output().term.GotoXY(72, 5);

    box_operation.Draw();
    sys_draw.output().term.GotoXY(72, 8);

    box_flag.Draw();

    number_selector.Draw();
    // help window
    box_help.Draw();
    print_keys(50, 14);

    sys_draw.output().term.GotoXY(1, 23);
    std::cout << "Input/Output: " << std::endl;
    return 0;
}

void GraphicalInterface::PrintInfo(int registers, int acc, int inst_count, uint16_t *mem)
{
    bh_selected_number.SetNumber(mem[selected_mem]);
    bh_selected_number.Draw();
    printf("%0*X ", 4, mem[inst_count]);
    print_memory(2, 2, mem, selected_mem);
    print_flags(62, 11, registers);
    printf("%0*X ", 4, inst_count);
    printf("%0*X ", 4, acc);
}
