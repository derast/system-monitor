#ifndef SYSINFO__H
#define SYSINFO__H

#include <vector>
#include <string>

using std::vector;
using std::string;

class SysInfo {
  private:
    vector<string> lastCpuStats;
    vector<string> currentCpuStats;
    vector<string> coresStats;
    vector<vector<string>> lastCpuCoresStats;
    vector<vector<string>> currentCpuCoresStats;
    string cpuPercent;
    float memPercent;
    string osName;
    string kernelVer;
    long upTime;
    int totalProc;
    int runningProc;
    int threads;

  public:
    SysInfo();
    void setAttributes();
    void setLastCpuMeasures();
    string getMemPercent() const;
    long getUpTime() const;
    string getThreads() const;
    string getTotalProc() const;
    string getRunningProc() const;
    string getKernelVersion() const;
    string getOsName() const;
    string getCpuPercent() const;
    void getOtherCores(int _size);
    void setCpuCoresStats();
    vector<string> getCoresStats() const;
};

#endif