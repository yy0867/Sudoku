#include "Frame.hpp"
#include "ConsoleCursor.hpp"
#include <cmath>

void printFrame(int x, int y, int width, int height, string multiColor, string rowEdge, string columnEdge, string leftTopCorner, string rightTopCorner, string letfBottomCorner, string rightBottomCorner) {
    int xOffset, yOffset;
    printColorCursor(X_PADDING + x, y + Y_PADDING, multiColor, leftTopCorner);
    for (xOffset = 1; xOffset <= width; xOffset++){
        printColorCursor(X_PADDING + x + xOffset, y + Y_PADDING, multiColor, rowEdge);
    }
    printColorCursor(X_PADDING + x + xOffset, y + Y_PADDING, multiColor, rightTopCorner);
    for (yOffset = 1; yOffset <= height; yOffset++){
        printColorCursor(X_PADDING + x, Y_PADDING + y + yOffset, multiColor, columnEdge);
        printColorCursor(X_PADDING + x + xOffset, Y_PADDING + y + yOffset, multiColor, columnEdge);
    }
    printColorCursor(X_PADDING + x, Y_PADDING + y + yOffset, multiColor, letfBottomCorner);
    for (xOffset = 1; xOffset <= width; xOffset++){
        printColorCursor(X_PADDING + x + xOffset, Y_PADDING + y + yOffset, multiColor, rowEdge);
    }
    printColorCursor(X_PADDING + x + xOffset, Y_PADDING + y + yOffset, multiColor, rightBottomCorner);
}

void printFrame(int x, int y, int width, int height, string multiColor, string rowEdge, string columnEdge) {
    printFrame(x, y, width, height, multiColor, rowEdge, columnEdge,
    "┏", "┓", "┗", "┛");
}

void printFrame(int x, int y, int width, int height, int color) {
    printFrame(x, y, width, height, to_string(color),  "━", "┃");
}

void printFrame(int x, int y, int width, int height, int color, string label){
    printColorCursor(X_PADDING + x + width/2 - (label.size()/2) + 1, Y_PADDING + y + ceil((double)(height/2)) + 1, color, label); // +1 cause frame
    printFrame(x, y, width, height, color);
}

void printFrameCursor(int x, int y, int width, int height, int color) {
    string blink = "5;"; //blink option
    printFrame(x, y, width, height, blink.append(to_string(color)), " ", " ");
}

void removeFrame(int x, int y, int width, int height){
    printFrame(x, y, width, height, to_string(DEFAULT_FONT_COLOR),
    " ", " ", " ", " ", " ", " ");
}
