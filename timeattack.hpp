#ifndef __TIMEATTACK_HPP__
#define __TIMEATTACK_HPP__

#include "Sudoku.hpp"
#include <signal.h>
#include <unistd.h>

void measure_time(pid_t pid, double time);

#endif