
#include "memory.hpp"
#include "registers.hpp"
#include "interpreter.hpp"

#include "myTerm.hpp"

#include "myBigChars.hpp"

#include "SimpleComputer.hpp"
#include "guikit.hpp"

#include <iostream>
#include <stdio.h>

using namespace std;

int main()
{
  //################### lab 1 #####################
  int value;
  //int command = 33, operand = 9;
  const char *input_file = "input_data.bin";
  const char *output_file = "output_data.bin";

  Memory sc_memory;

  // test 1
  sc_memory.Init();
  sc_memory.Show();

  // test 2
  sc_memory.Set(101, 1);
  sc_memory.Show();

  // test 3
  sc_memory.Set(0, 1);
  sc_memory.Set(2, 1);
  sc_memory.Set(27, 1);
  sc_memory.Show();

  // test 4
  sc_memory.Get(23, &value);
  cout << "Value: " << value << endl;
  sc_memory.Get(27, &value);
  cout << "Value: " << value << endl;

  // test 5
  sc_memory.Save(output_file);

  // test 6
  sc_memory.Load(input_file);
  sc_memory.Show();

  // test 7
  Registers::Init();
  Registers::Set(TOO_FULL, 1);
  Registers::Get(TOO_FULL, &value);
  cout << "Register \"TOO_FULL\" is:" << value << endl;

  // test 8
  interpreter sc_command;
  int val = 0;
  if (sc_command.Encode(READ, 10, &val))
    return 1;
  cout << "Value: " << val << endl;

  // test 9
  if (sc_command.Encode(READ, 1234, &val))
    cout << "Value: " << val << endl;

  // test 10
  if (sc_command.Encode(123, 10, &val))
    cout << "Value: " << val << endl;

  //test 11
  int command = 0, operand = 0;
  if (sc_command.Decode(val, &command, &operand))
    cout << "Command: " << command << endl;
  cout << "Operand: " << operand << endl;

  //test 12
  val = 0x000002FF;
  sc_command.Decode(val, &command, &operand);

  //test 13
  val = 0x0000C2FF;
  sc_command.Decode(val, &command, &operand);

  //################### lab 2 #####################
  myTerm term;
  //test 1
  term.ClrScr();

  //test 2
  term.SetFgColor(myTerm::colors::red);
  term.GotoXY(120, 10);
  std::cout << " Hello world" << std::endl;

  // test 3
  term.SetFgColor(myTerm::colors::defaul);
  term.SetBgColor(myTerm::colors::defaul);
  std::cout << " Hello world " << std::endl;

  //################### lab 3 #####################
  myBigChars bc(&term);

  char bigchar_0[64] = {
      0, 0, 1, 1, 1, 1, 0, 0,
      0, 1, 0, 0, 0, 0, 1, 0,
      1, 0, 0, 0, 0, 0, 0, 1,
      1, 0, 0, 0, 0, 0, 0, 1,
      1, 0, 0, 0, 0, 0, 0, 1,
      1, 0, 0, 0, 0, 0, 0, 1,
      0, 1, 0, 0, 0, 0, 1, 0,
      0, 0, 1, 1, 1, 1, 0, 0};

  bc.PrintBox(1, 1, 80, 10);

  int *zero = bc.ArrToBig(bigchar_0);
  bc.PrintBigChar(zero, 2, 2, myTerm::colors::defaul, myTerm::colors::defaul);
  bc.PrintBigChar(zero, 11, 2, myTerm::colors::defaul, myTerm::colors::defaul);
  bc.PrintBigChar(zero, 20, 2, myTerm::colors::defaul, myTerm::colors::defaul);
  bc.PrintBigChar(zero, 29, 2, myTerm::colors::defaul, myTerm::colors::defaul);
  bc.PrintBigChar(zero, 38, 2, myTerm::colors::defaul, myTerm::colors::defaul);
  bc.PrintBigChar(zero, 47, 2, myTerm::colors::defaul, myTerm::colors::defaul);
  bc.PrintBigChar(zero, 56, 2, myTerm::colors::defaul, myTerm::colors::defaul);
  bc.PrintBigChar(zero, 65, 2, myTerm::colors::defaul, myTerm::colors::defaul);

  int ret1 = bc.PrintBox(-1, 1, 8, 8);
  int ret2 = bc.PrintBox(1, 10000, 10, 10);
  cout << endl
       << endl
       << "PrintBox returned 1:" << ret1 << " 2:" << ret2 << endl;

  //################### gui tests #####################
  gui_kit::VOS *window = new gui_kit::VOS(&term, &bc);
  gui_kit::base_parameters::SetVOS(window);

  gui_kit::titled_box box(20, 5, 1, 1, "hello");
  gui_kit::untitled_box ubox(20, 5, 22, 1);
  gui_kit::big_hex_bumbers bignum(1234, 1, 8);

  window->SetSize(50, 100);
  window->ClrScr();
  bignum.Draw();

  window->GoToLastRow();

  return 0;
}
