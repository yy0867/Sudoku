#include "Frame.hpp"

void printFrameInGameMenu() {
    printFrame(30, -5, 18, 1, 94);         // Time box
    printFrame(30, 0, 18, 1, 94, "RESET"); // reset function box
    printFrame(30, 5, 18, 1, 94, "SAVE");  // save function box
    printFrame(30, 10, 18, 1, 94, "MENU"); // return to menu function box
}
