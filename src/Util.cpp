#include "Util.h"
#include <cstring>

std::string Util::convertToTime(long int inputSeconds) {
  long minutes = inputSeconds / 60;
  long hours = minutes / 60;
  long seconds = int(inputSeconds % 60);
  minutes = int(minutes % 60);
  std::string result = std::to_string(hours) + ":" + std::to_string(minutes) + ":" + std::to_string(seconds);

  return result;
}

// constructing string for given percentage
// 50 bars is uniformly streched to 0 - 100 %
// meaning: every 2% is one bar(|)
std::string Util::getProgressBar(std::string percent) {
  std::string result = "0% ";
  int _size = 50;
  int boundaries = (stof(percent)/100)*_size;
  
  for(int i=0; i<_size; i++) {
    if(i <= boundaries) {
      result += "|";
    } else {
      result += " ";
    }
  }
  result += " " + percent.substr(0, 5) + "/100%\n";

  return result;
}

// wrapper for creating streams
std::ifstream Util::getStream(std::string path) {
  std::ifstream stream(path);
  if(!stream) {
    throw std::runtime_error("Non - existing PID");
  }

  return stream;
}

// check if const char* is a valid number
bool Util::isNumber(const char *cStr) {
  for(int i=0; i<strlen(cStr); i++) {
    if(!isdigit(cStr[i])) {
      return false;
    }
  }

  return true;
}

// return single line as vector<string>
std::vector<std::string> Util::getValues(std::ifstream &stream, std::string valueToFind) {
  std::vector<std::string>values;
  std::string line;
  while(getline(stream, line)) {
    if(valueToFind == "" || line.find(valueToFind) != std::string::npos) {
      std::stringstream ss(line);
      std::istream_iterator<std::string> beg(ss), end;
      values = std::vector<std::string>(beg, end);
    
      return values;
    }
  }

  return values;
}