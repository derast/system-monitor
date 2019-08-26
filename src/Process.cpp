#include "Process.h"
#include "ProcessParser.h"
  
Process::Process() {
  
}

Process::Process(string pid) {
  Process::pid = pid;
  Process::user = ProcessParser::getProcUser(pid);
  Process::memory = ProcessParser::getVmSize(pid);
  Process::cmd = ProcessParser::getCmd(pid);
  Process::upTime = ProcessParser::getProcUpTime(pid);
  Process::cpu = ProcessParser::getCpuPercent(pid);
}

// Process::Process(ProcessInterpreter pi) {

// }

string Process::getPid() const {
  return Process::pid;
}

std::string Process::getUser() const {
  return Process::user;
}

std::string Process::getCmd() const {
  return Process::cmd;
}

string Process::getCpu() const {
  return Process::cpu;
}

string Process::getMemory() const {
  return Process::memory;
}

std::string Process::getUpTime() const {
  return Process::upTime;
}

void Process::setPid(string pid) {
  Process::pid = pid;
}

void Process::setUser(std::string user) {
  Process::user = user;
}

void Process::setCmd(std::string cmd) {
  Process::cmd = cmd;
}

void Process::setCpu(string cpu) {
  Process::cpu = cpu;
}

void Process::setMemory(string memory) {
  Process::memory = memory;
}

void Process::setUpTime(std::string upTime) {
  Process::upTime = upTime;
}

string Process::getProcess() {
  Process::memory = ProcessParser::getVmSize(pid);
  Process::upTime = ProcessParser::getProcUpTime(pid);
  Process::cpu = ProcessParser::getCpuPercent(pid);
  string blankSpaces = "   ";
  string processStr = Process::pid + blankSpaces + 
    blankSpaces + Process::user + blankSpaces + 
    blankSpaces + Process::memory.substr(0,5) + blankSpaces +
    blankSpaces + Process::cpu.substr(0,5) + blankSpaces +
    blankSpaces + Process::upTime.substr(0,5) + blankSpaces +
    blankSpaces + Process::cmd.substr(0,30) + blankSpaces +
    "...";

  return processStr;
}