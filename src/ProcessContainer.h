#ifndef PROCESSCONTAINER__H
#define PROCESSCONTAINER__H

#include <string>
#include <vector>
#include "Process.h"

using std::string;
using std::vector;

class ProcessContainer {
  private:
    vector<Process> _list;

  public:
    ProcessContainer();
    void refreshList();
    string printList();
    vector<string> getList();
};

#endif