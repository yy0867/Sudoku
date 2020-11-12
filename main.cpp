<<<<<<< HEAD
#include "Sudoku.hpp"
=======
#include "Sudoku.cpp"
>>>>>>> Optimize map, cursor printing
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <termios.h>

using namespace std;

int main() {
    srand(time(NULL));
    system("clear");

    Sudoku sud;
<<<<<<< HEAD
    while (1) {
        sud.print();
        sud.cursor();
=======

    sud.printBoard();
    while (1) {
        sud.moveCursor();
>>>>>>> Optimize map, cursor printing
    }

    return 0;
}
