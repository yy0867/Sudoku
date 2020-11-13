#include "Sudoku.cpp"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <termios.h>

using namespace std;

int main() {
    srand(time(NULL));
    system("clear");

    Sudoku sud;
    sud.printBoard();

    while (1) {
        sud.moveCursor();
    }
    return 0;
}
