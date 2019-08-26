#include "ProcessContainer.h"
#include "ProcessParser.h"

ProcessContainer::ProcessContainer() {
  ProcessContainer::refreshList();
}

void ProcessContainer::refreshList() {
  vector<string> pids = ProcessParser::getPidList();
  ProcessContainer::_list.clear();
  for(string pid : pids) {
    Process proc(pid);
    ProcessContainer::_list.push_back(proc);
  }
}

string ProcessContainer::printList() {
  string result = "";
  for(Process process : ProcessContainer::_list) {
    result += process.getProcess();
  }

  return result;
}

vector<string> ProcessContainer::getList() {
  vector<string> values;
  vector<Process>::iterator firstElement = this->_list.size() < 10 ? _list.begin() : _list.end()-10;
  for(vector<Process>::iterator it = firstElement; it != _list.end(); it++) {
    values.push_back(it->getProcess());
  }

  return values;
}
