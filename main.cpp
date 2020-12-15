#include "Sudoku.cpp"
#include "timeattack.cpp"
#include "getkey.cpp"
#include "ConsoleCursor.cpp"
#include "Frame.cpp"
#include "MainTitle.cpp"

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <sys/types.h>
#include <termios.h>
#include <unistd.h>

using namespace std;

const int p_key = 112;
bool exit_flag = false;

void signalHandler(int signum);

int main() {
    //random setting
    srand(time(NULL));
    system("clear");

    signal(SIGINT, signalHandler);
    signal(SIGTSTP, signalHandler);
    Sudoku sud;
    printTitle();
    getch();
    system("clear");

    sud.printBoard();
    pid_t pid = 0;
    double time = 100;

    if (pid = fork()) {
        measure_time(getpid(), time);
        if (get_key() == p_key) {
            kill(pid, SIGTSTP);
        }
    }

    while (1) {
        sud.moveCursor();
    }
    return 0;
}

int main2(){
    int t = system("clear");
    printFrame(0, 0, 15, 3, 94);
    printFrameCursor(-1, -1, 17, 5, 94);
    cout << endl;
}

void signalHandler(int signum) {
    if (signum == SIGINT) {
        system("clear");
        cout << "Exit!" << endl;
        exit(1); // change exit to UI
    } else if (signum == SIGTSTP) {
        cout << "Pause! Push p button again to continue" << endl;
        while(get_key() != p_key) {}
    } // pause timeattack by pushing p button
}
