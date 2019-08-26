#ifndef NCURSESCLASS__H
#define NCURSESCLASS__H

#include <string>
#include <ncurses.h>
#include <unistd.h>
#include "SysInfo.h"
#include "ProcessContainer.h"


class NcursesClass {
	private:
		ProcessContainer procs;
		SysInfo sys;

		char* getCString(std::string str);
		void writeSysInfoToConsole(WINDOW* sys_win);
		void getProcessListToConsole(WINDOW* win);
	
	public:
		NcursesClass(ProcessContainer procs, SysInfo sys);
		void printMain();
};

#endif