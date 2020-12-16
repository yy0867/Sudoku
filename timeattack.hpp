#ifndef __TIMEATTACK_HPP__
#define __TIMEATTACK_HPP__

#include "ConsoleCursor.hpp"
#include <signal.h>
#include <unistd.h>

void measure_time(pid_t pid, double time);
double getTimeLeft() { return timeLeft; }
pid_t getTimePid() { return getpid(); }

#endif
