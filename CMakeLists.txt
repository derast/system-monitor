cmake_minimum_required(VERSION 2.8.9)
project(system_monitor)
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})
add_executable(
  monitor.bin 
  src/Monitor.cpp 
  src/Constants.cpp 
  src/Util.cpp 
  src/ProcessParser.cpp
  src/SysInfo.cpp
  src/Process.cpp
  src/ProcessContainer.cpp
  src/NcursesClass.cpp
)
target_link_libraries(monitor.bin ${CURSES_LIBRARIES})
