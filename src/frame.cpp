#include "SimpleComputer.hpp"

int main()
{
  myspc::SimpleComputer Computer;

  Computer.Init();

  while (Computer.run_status)
  {
    Computer.DrawUI();
    Computer.Process();
  }

  Computer.End();

  return 0;
}
