#include "SimpleComputer.hpp"
#include "signal.h"

static mySimpleComputer::SimpleComputer *pc;

void RunProgram(int sig)
{
  pc->Run(0);
}

void Reset(int sig)
{
  pc->Reset(0);
}

int main()
{
  signal(SIGALRM, RunProgram);
  signal(SIGUSR1, RunProgram);
  mySimpleComputer::SimpleComputer Computer;
  pc = &Computer;
  Computer.Init();

  while (Computer.run_status)
  {
    Computer.Process();
  }

  Computer.End();

  return 0;
}
