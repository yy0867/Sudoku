#include "ConsoleCursor.cpp"
#include "Frame.cpp"
#include "IngameMenu.cpp"
#include "MainMenu.cpp"
#include "MainTitle.cpp"
#include "MenuFrame.cpp"
#include "Sudoku.cpp"
#include "Sync.cpp"
#include "UserDataManagement.cpp"
#include "getkey.cpp"
#include "timeattack.cpp"

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
    // signal(SIGTSTP, signalHandler);
    Sudoku sud;
    UserDataManagement data;

    // create Semaphore
    if (creat_sem() == -1) {
        perror("semaphore create error!");
        exit(0);
    }

    printTitle();
    getch();
    system("clear");
    while (1) {
        SelectedMenu sel;
        if (sud.resetflag == true) {
            sel = SelectedMenu::NEW_START;
            sud = Sudoku();
        } else {
            sel = printMainMenu();
        }
        switch (sel) {
        case SelectedMenu::NEW_START: {
            sud.resetflag = false;
            system("clear");
            sud.printBoard();
            pid_t pid = 0;
            double time = 100;
            printFrameInGameMenu();

            pid = fork(); // make child process
            if (pid == 0) {
                setTimePid(getpid());
                measure_time(getppid(), time);
            } else {
                setTimePid(pid);
                while (1) {
                    sud.moveCursor();
                    if (sud.endflag == true) {
                        kill(pid, SIGKILL);
                        system("clear");
                        sud.endflag = false;
                        break;
                    }
                }
            }
            break;
        }
        case SelectedMenu::LOAD_SAVE:
            data.loadData(sud, timeLeft);
            break;

        case SelectedMenu::EXIT:
            destroy_sem();
            system("clear");
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
    //      while (get_key() != p_key) {
    //      }
    // } // pause timeattack by pushing p button
}
// void newgame() {
//     srand(time(NULL));
//     system("clear");

//     Sudoku sud;
//     sud.printBoard();
//     pid_t pid = 0;
//     double time = 100;
//     printFrameInGameMenu();

//     pid = fork(); // make child process
//     if (pid == 0) {
//         measure_time(getppid(), time);
//         // if (get_key() == p_key) {
//         //     kill(pid, SIGTSTP);
//         // }
//     } else {
//         while (1) {
//             sud.moveCursor();
//             if (sud.out == true) {
//                 kill(pid, SIGKILL);
//                 system("clear");
//                 sud.out = false;
//                 break;
//             }
//         }
//         if (sud.is_reset == true) {
//             newgame();
//         }
//     }
// }
