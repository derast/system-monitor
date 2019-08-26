#ifndef UTIL__H
#define UTIL__H

#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <iterator>

class Util {
  public:
    static std::string convertToTime(long int inputSeconds);
    static std::string getProgressBar(std::string percent);
    static std::ifstream getStream(std::string path);
    static bool isNumber(const char *cStr);    
    static std::vector<std::string> getValues(std::ifstream &stream, std::string valueToFind="");
};

#endif