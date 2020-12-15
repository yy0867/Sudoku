#include "Frame.hpp"
#include "ConsoleCursor.hpp"

void printFrame(int x, int y, int width, int height, string multiColor, string rowEdge, string columnEdge) {
    int xOffset, yOffset;
    printColorCursor(X_PADDING + x, y + Y_PADDING, multiColor, "┏");
    for (xOffset = 1; xOffset <= width; xOffset++){
        printColorCursor(X_PADDING + x + xOffset, y + Y_PADDING, multiColor, rowEdge);
    }
    printColorCursor(X_PADDING + x + xOffset, y + Y_PADDING, multiColor, "┓");
    for (yOffset = 1; yOffset <= height; yOffset++){
        printColorCursor(X_PADDING + x, Y_PADDING + y + yOffset, multiColor, columnEdge);
        printColorCursor(X_PADDING + x + xOffset, Y_PADDING + y + yOffset, multiColor, columnEdge);
    }
    printColorCursor(X_PADDING + x, Y_PADDING + y + yOffset, multiColor, "┗");
    for (xOffset = 1; xOffset <= width; xOffset++){
        printColorCursor(X_PADDING + x + xOffset, Y_PADDING + y + yOffset, multiColor, rowEdge);
    }
    printColorCursor(X_PADDING + x + xOffset, Y_PADDING + y + yOffset, multiColor, "┛");
}

void printFrame(int x, int y, int width, int height, int color) {
    printFrame(x, y, width, height, to_string(color),  "━", "┃");
}

void printFrameCursor(int x, int y, int width, int height, int color) {
    string blink = "5;"; //blink option
    printFrame(x, y, width, height, blink.append(to_string(color)), " ", " ");
}
