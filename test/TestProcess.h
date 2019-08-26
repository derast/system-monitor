#include <iostream>
#include "../src/Process.h"

void testProcess() {
  Process process("1");
  std::cout<<process.getProcess()<<"\n";
}