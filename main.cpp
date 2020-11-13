#include "Sudoku.hpp"
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
<<<<<<< HEAD
    while (1) {
        sud.print();
        sud.cursor();
=======

=======
>>>>>>> Optimize board, number printing
        sud.printBoard();

        while (1) {
            sud.moveCursor();
>>>>>>> Optimize map, cursor printing
        }
        return 0;
    }
