#include "ProcessParser.h"
#include "Util.h"
#include "Constants.h"

// get process command
std::string ProcessParser::getCmd(std::string pid) {
  std::ifstream cmdStatusFile = Util::getStream(Path::basePath() + pid + Path::statusPath());
  std::vector<std::string> values = Util::getValues(cmdStatusFile, "Name:");
  std::string result = values[1];

  return result;
}

// get the list of process PID running
std::vector<std::string> ProcessParser::getPidList() {
  std::vector<std::string> vPidList;

  DIR *dirPtr = NULL;
  dirPtr = opendir(Path::basePath().c_str());
  if(dirPtr == NULL) {
    throw std::runtime_error("Cannot open directory: " + Path::basePath());
  }

  struct dirent *entryPtr = NULL;
  while((entryPtr = readdir(dirPtr))) {
    if(entryPtr == NULL) {
      throw std::runtime_error("entryPtr could not be initialised correctly");
    }
    
    if(Util::isNumber(entryPtr->d_name))
      vPidList.push_back(entryPtr->d_name);
  }
  
  closedir(dirPtr);

  return vPidList;
}

std::string ProcessParser::getVmSize(std::string pid) {
  std::ifstream statusFile = Util::getStream(Path::basePath() + pid + Path::statusPath());
  string str;
  while(statusFile>>str) {
    if(str.substr(0, 6) == "VmData") { 
      statusFile>>str;
      return std::to_string(stof(str) / float(1024));
    }
  } 

  return "";
}

std::string ProcessParser::getCpuPercent(std::string pid) {
  std::ifstream statFile = Util::getStream(Path::basePath() + pid + "/" + Path::statPath());
  std::vector<string> values = Util::getValues(statFile);
  float uTime = stof(ProcessParser::getProcUpTime(pid));
  float sTime = stof(values[14]);
  float cuTime = stof(values[15]);
  float csTime = stof(values[16]);
  float startTime = stof(values[21]);
  float upTime = ProcessParser::getSysUpTime();
  float freq = sysconf(_SC_CLK_TCK);
  float totalTime = uTime + sTime + cuTime +csTime;
  float seconds = upTime - (startTime / freq);
  float result = 100.0 * ((totalTime / freq) / seconds);

  return std::to_string(result);
}

long int ProcessParser::getSysUpTime() {
  std::ifstream upTimeFile = Util::getStream(Path::basePath() + Path::upTimePath());
  std::vector<string> values = Util::getValues(upTimeFile);
  long int result = stoi(values[0]);

  return result;
}

std::string ProcessParser::getProcUpTime(std::string pid) {
  std::ifstream statFile = Util::getStream(Path::basePath() + pid + "/" + Path::statPath());
  std::vector<string> values = Util::getValues(statFile);
  float result = stof(values[23]) / sysconf(_SC_CLK_TCK);

  return  std::to_string(result);
}

std::string ProcessParser::getProcUser(std::string pid) {
  //get user id from /proc/[pid]/status
  std::ifstream stream = Util::getStream(Path::basePath() + pid + Path::statusPath());
  std::vector<string> values = Util::getValues(stream, "Uid:");
  //get user name from /etc/passwd
  stream = Util::getStream("/etc/passwd");
  values = Util::getValues(stream, "x:" + values[1]);
  std::string result = values[0].substr(0, values[0].find(':'));

  return result;
}

short int ProcessParser::getNumberOfCores() {
  std::ifstream cpuInfoFile = Util::getStream(Path::basePath() + Path::cpuInfo());
  std::vector<string> values = Util::getValues(cpuInfoFile, "cpu cores");
  int result = stoi(values[3]);

  return result;
}

std::vector<std::string> ProcessParser::getSysCpuPercent(std::string coreNumber) {
  std::ifstream statFile = Util::getStream(Path::basePath() + Path::statPath());
  std::vector<std::string> values = Util::getValues(statFile, "cpu"+coreNumber);

  return values;
}

float ProcessParser::getSysActiveCpuTime(std::vector<std::string> values) {
  return (
    stof(values[(int)CPUStates::S_USER]) + stof(values[(int)CPUStates::S_NICE]) + stof(values[(int)CPUStates::S_SYSTEM]) + 
    stof(values[(int)CPUStates::S_IRQ]) + stof(values[(int)CPUStates::S_SOFTIRQ]) + stof(values[(int)CPUStates::S_STEAL]) + 
    stof(values[(int)CPUStates::S_GUEST]) + stof(values[(int)CPUStates::S_GUEST_NICE])
  );
}

float ProcessParser::getSysIdleCpuTime(std::vector<std::string> values) {
  return (
    stof(values[(int)CPUStates::S_IDLE]) + stof(values[(int)CPUStates::S_IOWAIT])
  );
}

std::string ProcessParser::printCpuStats(std::vector<std::string> values1, std::vector<std::string> values2) {
  float activeTime = getSysActiveCpuTime(values2) - getSysActiveCpuTime(values1);
  float idleTime = getSysIdleCpuTime(values2) - getSysIdleCpuTime(values1);
  float totalTime = activeTime + idleTime;
  float result = 100.0 * (activeTime / totalTime);

  return std::to_string(result);
}

float ProcessParser::getSysRamPercent() {
  std::string memAvailableLabel = "MemTotal:";
  std::string memFreeLabel = "MemFree:";
  std::string buffersLabel = "Buffers:";
  int result;
  std::ifstream memInfoFile = Util::getStream(Path::basePath() + Path::memInfoPath());
  float totalMem = 0; 
  float freeMem = 0;
  float buffers = 0;
  std::vector<std::string> values;
  std::string line;
  while(getline(memInfoFile, line)) {
    if(totalMem != 0 && freeMem != 0) {
      break;
    }
    if(line.compare(0, memAvailableLabel.size(), memAvailableLabel) == 0) {
      std::istringstream buf(line);
      std::istream_iterator<string> beg(buf), end;
      values = std::vector<string>(beg, end);
      totalMem = stof(values[1]);
    }
    if(line.compare(0, memFreeLabel.size(), memFreeLabel) == 0) {
      std::istringstream buf(line);
      std::istream_iterator<string> beg(buf), end;
      values = std::vector<string>(beg, end);
      freeMem = stof(values[1]);
    }
    if(line.compare(0, buffersLabel.size(), buffersLabel) == 0) {
      std::istringstream buf(line);
      std::istream_iterator<string> beg(buf), end;
      values = std::vector<string>(beg, end);
      buffers = stof(values[1]);
    }
  }

  return float(100.0*(1-(freeMem/(totalMem-buffers))));
}

std::string ProcessParser::getSysKernelVersion() {
  std::ifstream versionFile = Util::getStream(Path::basePath() + Path::versionPath());
  std::vector<string> values = Util::getValues(versionFile, "Linux version ");

  return values[2];
}

std::string ProcessParser::getOsName() {
  std::ifstream osReleaseFile = Util::getStream(Path::osReleasePath());
  std::string valueToFind = "PRETTY_NAME=";
  std::vector<string> values = Util::getValues(osReleaseFile, valueToFind);
  std::string result = values[0].substr(valueToFind.length()+1, values[0].length()) + " " + values[1] + " " +
    values[2].substr(0, values[2].length()-1);

  return result;
}

int ProcessParser::getTotalThreads() {
  std::ifstream file;
  std::vector<std::string> values;
  int totalThreads = 0;
  for(std::string pid : ProcessParser::getPidList()) {
    file = Util::getStream(Path::basePath() + pid + Path::statusPath());
    values = Util::getValues(file, "Threads:");
    totalThreads += stoi(values[1]);
    file.close();
    values.clear();
  }

  return totalThreads;
}

int ProcessParser::getTotalNumberOfProcesses() {
  std::ifstream statFile = Util::getStream(Path::basePath() + Path::statPath());
  std::vector<std::string> values = Util::getValues(statFile, "processes");
  int result = stoi(values[1]);

  return result;
}

int ProcessParser::getNumberOfRunningProcesses() {
  std::ifstream statFile = Util::getStream(Path::basePath() + Path::statPath());
  std::vector<std::string> values = Util::getValues(statFile, "procs_running");
  int result = stoi(values[1]);

  return result;
}