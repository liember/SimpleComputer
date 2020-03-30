
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
  //################### gui tests #####################
  gui_kit::VOS *window = new gui_kit::VOS();
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
