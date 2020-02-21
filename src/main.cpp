#include "memory.hpp"
#include "registers.hpp"
#include "interpreter.hpp"

#include <iostream>
#include <stdio.h>

using namespace std;

int main()
{
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
  return 0;
}