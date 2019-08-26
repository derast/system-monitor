#include "SysInfo.h"
#include "ProcessParser.h"
#include "Util.h"

SysInfo::SysInfo() {
  SysInfo::getOtherCores(ProcessParser::getNumberOfCores());
  SysInfo::setLastCpuMeasures();
  SysInfo::setAttributes();
  SysInfo::osName = ProcessParser::getOsName();
  SysInfo::kernelVer = ProcessParser::getSysKernelVersion();
}

void SysInfo::setAttributes() {
  SysInfo::memPercent = ProcessParser::getSysRamPercent();
  SysInfo::upTime = ProcessParser::getSysUpTime();
  SysInfo::totalProc = ProcessParser::getTotalNumberOfProcesses();
  SysInfo::runningProc = ProcessParser::getNumberOfRunningProcesses();
  SysInfo::threads = ProcessParser::getTotalThreads();
  SysInfo::currentCpuStats = ProcessParser::getSysCpuPercent();
  SysInfo::cpuPercent = ProcessParser::printCpuStats(SysInfo::lastCpuStats, SysInfo::currentCpuStats);
  SysInfo::lastCpuStats = SysInfo::currentCpuStats;
  SysInfo::setCpuCoresStats();
}

void SysInfo::setLastCpuMeasures() {
  SysInfo::lastCpuStats = ProcessParser::getSysCpuPercent();
}

string SysInfo::getMemPercent() const {
  return std::to_string(SysInfo::memPercent);
}

long SysInfo::getUpTime() const {
  return SysInfo::upTime;
}

string SysInfo::getThreads() const {
  return std::to_string(SysInfo::threads);
}

string SysInfo::getTotalProc() const {
  return std::to_string(SysInfo::totalProc);
}

string SysInfo::getRunningProc() const {
  return std::to_string(SysInfo::runningProc);
}

string SysInfo::getKernelVersion() const {
  return SysInfo::kernelVer;
}

string SysInfo::getOsName() const {
  return SysInfo::osName;
}

string SysInfo::getCpuPercent() const {
  return SysInfo::cpuPercent;
}

void SysInfo::getOtherCores(int _size) {
  SysInfo::coresStats = vector<string>();
  SysInfo::coresStats.resize(_size);
  SysInfo::lastCpuCoresStats = vector<vector<string>>();
  SysInfo::currentCpuCoresStats = vector<vector<string>>();
  SysInfo::currentCpuCoresStats.resize(_size);
  for(int i=0; i<_size; i++) {
    SysInfo::lastCpuCoresStats.push_back(ProcessParser::getSysCpuPercent(std::to_string(i)));
  }
}

void SysInfo::setCpuCoresStats() {
  // Getting data from files (previous data is required)
  for(int i=0; i<SysInfo::currentCpuCoresStats.size(); i++) {
    vector<string> sysCpuPercent = ProcessParser::getSysCpuPercent(std::to_string(i));
    SysInfo::currentCpuCoresStats[i] = sysCpuPercent;
    SysInfo::coresStats[i] = ProcessParser::printCpuStats(SysInfo::lastCpuCoresStats[i], sysCpuPercent);
  }
  SysInfo::lastCpuCoresStats = SysInfo::currentCpuCoresStats;
}

vector<string> SysInfo::getCoresStats() const {
  vector<string> result = vector<string>();
  for(int i=0; i<SysInfo::coresStats.size(); i++) {
    string temp = "cpu" + std::to_string(i) + ": ";
    float check = stof(SysInfo::coresStats[i]);
    if(!check || SysInfo::coresStats[i] == "nan") {
      return vector<string>();
    }
    temp += Util::getProgressBar(SysInfo::coresStats[i]);
    result.push_back(temp);
  }

  return result;
}




