#ifndef __FRAME_HPP__
#define __FRAME_HPP__

#include <string>
#include "Sudoku.hpp"

using namespace std;

void printFrame(int x, int y, int width, int height, string multiColor, string rowEdge, string columnEdge, string leftTopCorner, string rightTopCorner, string letfBottomCorner, string rightBottomCorner);
void printFrame(int x, int y, int width, int height, string multiColor, string rowEdge, string columnEdge);
void printFrame(int x, int y, int width, int height, int color);
void printFrame(int x, int y, int width, int height, int color, string label);
void printFrameCursor(int x, int y, int width, int height, int color);
void removeFrameCursor(int x, int y, int width, int height);

#endif
