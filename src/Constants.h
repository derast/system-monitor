#ifndef PATH__H
#define PATH__H

#include <iostream>
#include <string>

using namespace std;

enum class CPUStates: int {
  S_USER = 1,
  S_NICE,
  S_SYSTEM,
  S_IDLE,
  S_IOWAIT,
  S_IRQ,
  S_SOFTIRQ,
  S_STEAL,
  S_GUEST,
  S_GUEST_NICE  
};

class Path {
  public:
    static string basePath();
    static string cmdPath();
    static string statusPath();
    static string statPath();
    static string upTimePath();
    static string memInfoPath();
    static string versionPath();
    static string cpuInfo();
    static string osReleasePath();
};

#endif