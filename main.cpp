#include "ConsoleCursor.cpp"
#include "Frame.cpp"
#include "IngameMenu.cpp"
#include "MainMenu.cpp"
#include "MainTitle.cpp"
#include "MenuFrame.cpp"
#include "Sudoku.cpp"
#include "getkey.cpp"
#include "timeattack.cpp"
#include "UserDataManagement.cpp"

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <sys/types.h>
#include <termios.h>
#include <unistd.h>
#define PMESSAGE_ROW 35
#define PMESSAGE_COL 5

using namespace std;

const int p_key = 112; // p button value
bool exit_flag = false;

void signalHandler(int signum);
void newgame();

int main() {
    // random setting
    srand(time(NULL));
    system("clear");

    signal(SIGINT, signalHandler);
    signal(SIGTSTP, signalHandler);
    Sudoku sud;
    UserDataManagement data;

    printTitle();
    getch();
    system("clear");
    while (1) {
        switch (printMainMenu()) {
        case SelectedMenu::NEW_START: {
            system("clear");
            sud.printBoard();
            pid_t pid = 0;
            double time = 100;
            printFrameInGameMenu();

            pid = fork(); // make child process
            if (pid == 0) {
                measure_time(getppid(), time);
                // if (get_key() == p_key) {
                //     kill(pid, SIGTSTP);
                // }
            } else {
                while (1) {
                    sud.moveCursor();
                    if (sud.out == true) {
                        kill(pid, SIGKILL);
                        system("clear");
                        sud.out = false;
                        break;
                    }
                }
                if (sud.is_reset == true) {
                    newgame();
                }
            }
            break;
        }
        case SelectedMenu::LOAD_SAVE:
            data.loadData(sud, timeLeft);
            break;

        case SelectedMenu::EXIT:
            exit(0);
            break;
        }
    }
    return 0;
}

int main2() {
    // int t = system("clear");

    // cout << printMainMenu() << endl;
    return 0;
}

void signalHandler(int signum) {
    if (signum == SIGINT) {
        system("clear");
        cout << "Exit!" << endl;
        exit(1); // change exit to UI
    }
    // else if (signum == SIGTSTP) {
    //     while (get_key() != p_key) {
    //     }
    // } // pause timeattack by pushing p button
}
void newgame() {
    srand(time(NULL));
    system("clear");

    Sudoku sud;
    sud.printBoard();
    pid_t pid = 0;
    double time = 100;
    printFrameInGameMenu();

    pid = fork(); // make child process
    if (pid == 0) {
        measure_time(getppid(), time);
        // if (get_key() == p_key) {
        //     kill(pid, SIGTSTP);
        // }
    } else {
        while (1) {
            sud.moveCursor();
            if (sud.out == true) {
                kill(pid, SIGKILL);
                system("clear");
                sud.out = false;
                break;
            }
        }
        if (sud.is_reset == true) {
            newgame();
        }
    }
}
