#include "SimpleComputer.hpp"

int main()
{
  mySimpleComputer::SimpleComputer Computer;
  Computer.Init(false);
  while (Computer.isRun())
    Computer.Process();
  Computer.End();

  return 0;
}
