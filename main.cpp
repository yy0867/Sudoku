#include "ConsoleCursor.cpp"
#include "Frame.cpp"
#include "MainTitle.cpp"
#include "Sudoku.cpp"
#include "getkey.cpp"
#include "timeattack.cpp"
#include "MenuFrame.cpp"
#include "MainMenu.cpp"

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
void printFrameInGameMenu();
void MoveCursorToInGameMenu();
void printFrameCursorInGameMenu();

int main() {
    // random setting
    srand(time(NULL));
    system("clear");

    signal(SIGINT, signalHandler);
    signal(SIGTSTP, signalHandler);
    Sudoku sud;
    printTitle();
    getch();
    system("clear");

    switch (printMainMenu()){
    case SelectedMenu::NEW_START:{
        system("clear");
        sud.printBoard();
        pid_t pid = 0;
        double time = 100;
        printFrameInGameMenu();

        pid = fork(); // make child process
        if (pid == 0) {
            measure_time(getpid(), time);
            if (get_key() == p_key) {
                kill(pid, SIGTSTP);
            }
        } else {
            while (1) {
                sud.moveCursor();
                // MoveCursorToInGameMenu();
            }
            break;
        }
    }
    case SelectedMenu::LOAD_SAVE:
        cout << endl;
        break;

    case SelectedMenu::EXIT:
        cout << endl;
        break;
    }

    return 0;
}

int main2() {
    //int t = system("clear");

    //cout << printMainMenu() << endl;
}


void signalHandler(int signum) {
    if (signum == SIGINT) {
        system("clear");
        cout << "Exit!" << endl;
        exit(1); // change exit to UI
    } else if (signum == SIGTSTP) {
        while (get_key() != p_key) {
        }
    } // pause timeattack by pushing p button
}

void printFrameInGameMenu() {
    printFrame(30, -5, 18, 1, 94);         // Time box
    printFrame(30, 0, 18, 1, 94, "RESET"); // reset function box
    printFrame(30, 5, 18, 1, 94, "SAVE");  // save function box
    printFrame(30, 10, 18, 1, 94, "MENU"); // return to menu function box
}

// void MoveCursorToInGameMenu() {
//     if (get_key() == KEY_RIGHT) {
//         printFrameCursorInGameMenu();
//     }
// }

// void printFrameCursorInGameMenu() {
//     printFrameCursor(29, -1, 20, 3, 94);
//     while (1) {
//         int getkey = get_key();
//         if (getkey==KEY_UP)
//             printFrameCursor(29, -1, 20, 3, 94);
//     }
// }
