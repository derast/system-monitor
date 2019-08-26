#ifndef PROCESS__H
#define PROCESS__H

#include <string>

using std::string;

class ProcessInterpreter;

class Process {
  private:
    string pid;
    string user;
    string cmd;
    string cpu;
    string memory;
    string upTime;
  
  public:
    Process();
    Process(string pid);
    // Process(ProcessInterpreter pi);
    string getPid() const;
    string getUser() const;
    string getCmd() const;
    string getCpu() const;
    string getMemory() const;
    string getUpTime() const;
    void setPid(string pid);
    void setUser(string user);
    void setCmd(string cmd);
    void setCpu(string cpu);
    void setMemory(string memory);
    void setUpTime(string time);
    string getProcess();
};

#endif