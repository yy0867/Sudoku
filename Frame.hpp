#ifndef __FRAME_HPP__
#define __FRAME_HPP__

#include <string>
#include "Sudoku.hpp"

using namespace std;

void printFrame(int x, int y, int width, int height, string multiColor, string rowEdge, string columnEdge);
void printFrame(int x, int y, int width, int height, int color);
void printFrameCursor(int x, int y, int width, int height, int color);

#endif
