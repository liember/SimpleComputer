#include "SimpleComputer.hpp"

int main()
{
  SimpleComputer Computer;

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
