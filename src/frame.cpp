#include "SimpleComputer.hpp"

int main()
{
  myspc::SimpleComputer Computer;

  Computer.Init();

  while (Computer.IsRunning())
  {
    Computer.DrawUI();
    Computer.Process();
  }

  Computer.End();

  return 0;
}
