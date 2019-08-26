#include "../test/TestConstants.h"
#include "../test/TestUtil.h"
#include "../test/TestProcessParser.h"
#include "../test/TestSysInfo.h"
#include "../test/TestProcess.h"
#include "../test/TestProcessContainer.h"

#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <vector>
#include <ncurses.h>
#include <time.h>
#include <sstream>
#include <iomanip>
#include "NcursesClass.h"


int main() {
  // testConstants();
  //testUtil();
  // testProcessParser();
  // testSysInfo();
  // testProcess();
  // testProcessContainer();

  //Object which contains list of current processes, Container for Process Class
  ProcessContainer procs;
  // Object which containts relevant methods and attributes regarding system details
  SysInfo sys;
  //string s = writeToConsole(sys);
  NcursesClass ncurses(procs, sys);
  ncurses.printMain();

  return 0;  
}



