#ifndef __MAIN_TITLE_HPP__
#define __MAIN_TITLE_HPP__

#include <stdlib.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include "ConsoleCursor.hpp"
#include <sys/ioctl.h>

void printTitle(int xPadding, int yPadding, const string path);
int getLargestWidth(const string path);
void printBlinkingComment(int x, int y, int color, const string comment);
void printTitle();
void printTitle(const string path, const string ment);
void printGameOver();
void printGameClear();
void printPause();

using namespace std;

#endif
