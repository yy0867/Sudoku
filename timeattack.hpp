#ifndef __TIMEATTACK_HPP__
#define __TIMEATTACK_HPP__

#include "ConsoleCursor.hpp"
#include <signal.h>
#include <unistd.h>

pid_t timePid;

void measure_time(pid_t pid, double time);
double getTimeLeft();
pid_t getTimePid() { return timePid; }
void setTimePid(pid_t pid) { timePid = pid; }

#endif
