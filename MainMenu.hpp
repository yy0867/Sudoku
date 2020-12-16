#ifndef __MAIN_MENU_HPP__
#define __MAIN_MENU_HPP__

#include "MenuFrame.hpp"
#include <sys/ioctl.h>
#include "ConsoleCursor.hpp"

#define MENU_WIDTH 20
#define MENU_HEIGHT 3
#define MENU_TERM 2
#define MENU_NUMBER 3
#define MENU_COLOR CUSTOM_FONT_COLOR
#define MENU_CURSOR_COLOR CUSTOM_FONT_COLOR

enum class SelectedMenu {NEW_START, LOAD_SAVE, EXIT};
enum SelectedSaveSlot {SLOT_0, SLOT_1, SLOT_2};

void printMainMenu(int xOffset, int yOffset);
void printSaveSlot(int xOffset, int yOffset);
SelectedMenu printMainMenu();

#endif
