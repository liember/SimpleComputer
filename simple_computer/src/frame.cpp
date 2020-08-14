#include "SimpleComputer.hpp"

int main()
{
  mySimpleComputer::SimpleComputer Computer;
  Computer.Init(true);
  while (Computer.isRun())
  {
    Computer.Display();
    Computer.Process();
  }
  Computer.End();

  return 0;
}
