#include "Sudoku.cpp"
#include "timeattack.cpp"
#include "getkey.cpp"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <sys/types.h>
#include <termios.h>
#include <unistd.h>

using namespace std;

bool exit_flag = false;

void signalHandler(int signum);

int main() {
    srand(time(NULL));
    system("clear");

    signal(SIGINT, signalHandler);

    Sudoku sud;
    sud.printBoard();
    pid_t pid = 0;
    double time = 100;

    if (pid = fork()) {
        measure_time(getpid(), time);
    }

    while (1) {
        sud.moveCursor();
    }
    return 0;
}

void signalHandler(int signum) {
    if (signum == SIGINT) {
        system("clear");
        cout << "Exit!" << endl;
        exit(1); // change exit to UI
    }
}
