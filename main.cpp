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
    while (1) {
        sud.print();
        sud.cursor();
    }

    return 0;
}
