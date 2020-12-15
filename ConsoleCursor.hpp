#ifndef __CONSOLECURSOR_HPP__
#define __CONSOLECURSOR_HPP__

#include <iostream>

using namespace std;

void gotoxy(int x, int y);
void printColorCursor(int x, int y, string multiColor, const string str);
void printColorCursor(int x, int y, int color, const string str);
//void printColorCursor(int x, int y, int color, const char str);
//void printColorCursor(int x, int y, int color, const char *str);
void printColorCursor(int x, int y, int color, const int str);

#endif
