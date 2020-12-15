#include "MainMenu.hpp"

SelectedMenu printMainMenu(){
    struct winsize console;
    int xOffset, yOffset, key, menuIndex = 0;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &console);
    xOffset = ((console.ws_col - (MENU_WIDTH + 2))/2) - X_PADDING;
    yOffset = 3 - Y_PADDING;

    printMainMenu(xOffset, yOffset);
    printFrameCursor(xOffset - 1, yOffset - 1, MENU_WIDTH + 2, MENU_HEIGHT + 2, DEFAULT_FONT_COLOR);
    while (key != KEY_ENTER){
        key = get_key();
        switch (key){
            case KEY_DOWN:
                if ((menuIndex + 1) < MENU_NUMBER){
                    removeFrame(xOffset - 1, yOffset - 1 + menuIndex*(MENU_HEIGHT + 2 + MENU_TERM),
                    MENU_WIDTH + 2, MENU_HEIGHT + 2);
                    printFrameCursor(xOffset - 1, yOffset - 1 + ++menuIndex*(MENU_HEIGHT + 2 + MENU_TERM),
                    MENU_WIDTH + 2, MENU_HEIGHT + 2, DEFAULT_FONT_COLOR);
                }
                break;

            case KEY_UP:
                if ((menuIndex - 1) >= 0){
                    removeFrame(xOffset - 1, yOffset - 1 + menuIndex*(MENU_HEIGHT + 2 + MENU_TERM),
                    MENU_WIDTH + 2, MENU_HEIGHT + 2);
                    printFrameCursor(xOffset - 1, yOffset - 1 + --menuIndex*(MENU_HEIGHT + 2 + MENU_TERM),
                    MENU_WIDTH + 2, MENU_HEIGHT + 2, DEFAULT_FONT_COLOR);
                }
                break;
        }
        gotoxy(1000, 1000);
    }
    return static_cast<SelectedMenu>(menuIndex);
}

void printMainMenu(int xOffset, int yOffset){
    vector<string> menuList = {"New Start", "Load Data", "Exit"};
    printMenu(xOffset, yOffset, MENU_WIDTH, MENU_HEIGHT, DEFAULT_FONT_COLOR, MENU_TERM, menuList);
}
