#include "MenuFrame.hpp"

void printMenu(int xOffset, int yOffset, int width, int height,
    int color, int term, vector<string> menuList){
    for (int i = 0; i < menuList.size(); i++){
        printFrame(xOffset, yOffset + i*(height + term +2), width, height, color, menuList[i]);
    }
}
