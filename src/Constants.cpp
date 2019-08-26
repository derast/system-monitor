#include "Constants.h"

string Path::basePath() {
  return "/proc/";
}

string Path::cmdPath() {
  return "/cmdline";
}

string Path::statusPath() {
  return "/status";
}

string Path::statPath() {
  return "stat";
}

string Path::upTimePath() {
  return "uptime";
}

string Path::memInfoPath() {
  return "meminfo";
}

string Path::versionPath() {
  return "version";
}

string Path::cpuInfo() {
  return "cpuinfo";
}

string Path::osReleasePath() {
  return "/etc/os-release";
}