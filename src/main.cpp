#include "SimpleComputer.hpp"

int main()
{
  myspc::SimpleComputer Computer;

  Computer.Init();

  while (Computer.IsRunning())
  {
    Computer.DrawUI();
    Computer.InputHandle();
    Computer.Process();
  }

  Computer.Save();

  return 0;
}
