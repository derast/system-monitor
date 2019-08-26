#ifndef PROCESSPARSER__H
#define PROCESSPARSER__H

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <thread>
#include <chrono>
#include <iterator>
#include <cstdlib>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cerrno>
#include <cstring>
#include <dirent.h>
#include <ctime>
#include <unistd.h>

class ProcessParser {
  public:
    static std::string getCmd(std::string pid);
    static std::vector<std::string> getPidList();
    static std::string getVmSize(std::string pid);
    static std::string getCpuPercent(std::string pid);
    static long int getSysUpTime();
    static std::string getProcUpTime(std::string pid);
    static std::string getProcUser(std::string pid);
    static short int getNumberOfCores();
    static std::vector<std::string> getSysCpuPercent(std::string coreNumber = "");
    static float getSysActiveCpuTime(std::vector<std::string> values);
    static float getSysIdleCpuTime(std::vector<std::string> values);
    static std::string printCpuStats(std::vector<std::string> values1, std::vector<std::string> values2);
    static float getSysRamPercent();
    static std::string getSysKernelVersion();
    static std::string getOsName();
    static int getTotalThreads();
    static int getTotalNumberOfProcesses();
    static int getNumberOfRunningProcesses();
};

#endif