#include "SimpleComputer.hpp"

int main()
{
  mySimpleComputer::SimpleComputer Computer;

  Computer.Init();

  while (Computer.run_status)
  {
    Computer.Process();
  }

  Computer.End();

  return 0;
}
