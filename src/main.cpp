
#include "memory.hpp"
#include "interpreter.hpp"
#include "guikit.hpp"
#include "myReadkey.hpp"

#include <iostream>

using namespace std;

memory::Registers *rg = new memory::Registers();
memory::Memory *sc_mem = new memory::Memory(rg);

terminal::VOS *window = new terminal::VOS();

void print_flags(int x, int y)
{
  window->term->GotoXY(x, y);
  if (rg->Flag() & (1 << FLAG_OVERFLOW))
    cout << "O";
  else
    printf(" ");
  if (rg->Flag() & (1 << FLAG_COMMAND))
    cout << "E";
  else
    printf(" ");
  if (rg->Flag() & (1 << FLAG_INTERRUPT))
    printf("V");
  else
    printf(" ");
  if (rg->Flag() & (1 << FLAG_OUTMEM))
    printf("M");
  else
    printf(" ");
  if (rg->Flag() & (1 << FLAG_DIVISION))
    printf("Z");
  else
    printf(" ");
}

void print_keys(int x, int y)
{
  window->term->GotoXY(x, y);
  printf("l  - load");
  window->term->GotoXY(x, y + 1);
  printf("s  - save");
  window->term->GotoXY(x, y + 2);
  printf("r  - run");
  window->term->GotoXY(x, y + 3);
  printf("t  - step");
  window->term->GotoXY(x, y + 4);
  printf("i  - reset");
  window->term->GotoXY(x, y + 5);
  printf("F5 - accumulator");
  window->term->GotoXY(x, y + 6);
  printf("F6 - instructionCounter");
}

void print_memory(int x, int y)
{
  int i, j;
  int smem, command;

  for (i = 0; i < 10; i++)
  {
    window->term->GotoXY(x, y + i);
    for (j = 0; j < 9; j++)
    {
      smem = memory::Memory::mem[i * 10 + j] & 0x3FF;
      command = (memory::Memory::mem[i * 10 + j] >> 14) & 1;
      if (command == 0)
        printf("+");
      else
        printf(" ");
      printf("%0*X ", 4, smem);
    }
    smem = memory::Memory::mem[i * 10 + j] & 0x3FF;
    command = (memory::Memory::mem[i * 10 + j] >> 14) & 1;
    if (command == 0)
      printf("+");
    else
      printf(" ");
    printf("%0*X", 4, smem);
  }
}

int main()
{
  gui_kit::base_parameters::SetVOS(window);
  window->SetSize(500, 100);
  window->ClrScr();

  sc_mem->Init();

  print_memory(2, 2);

  gui_kit::titled_box box_mem(60, 11, 1, 1, "Memory");

  gui_kit::titled_box box_acc(25, 2, 62, 1, "Accumulator");
  gui_kit::titled_box box_ins(25, 2, 62, 4, "Instruction Counter");
  gui_kit::titled_box box_ope(25, 2, 62, 7, "Operation");
  gui_kit::titled_box box_fla(25, 2, 62, 10, "Flags");

  gui_kit::untitled_box selector(45, 9, 1, 13);
  gui_kit::big_hex_bumbers selected_number(12341, 2, 14);

  gui_kit::untitled_box help(39, 9, 48, 13);

  myReadkey *keyboard = new myReadkey();

  box_mem.Draw();
  box_acc.Draw();
  box_ins.Draw();
  box_ope.Draw();
  box_fla.Draw();
  selector.Draw();

  selected_number.Draw();

  // help window
  help.Draw();
  print_keys(50, 14);
  window->term->GotoXY(0, 22);
  cout << endl;

  keyboard->ReadKey();

  return 0;
}
