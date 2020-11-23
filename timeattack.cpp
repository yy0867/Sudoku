#include "timeattack.hpp"

#define TIME_ROW 35
#define TIME_COL 3

using namespace std;

void measure_time(int time) {
    for (int i = time; i >= 0; i--) {
        gotoxy(TIME_ROW, TIME_COL);
        cout << i << "..." << endl;
        fflush(stdout);
        sleep(1);
    }
    cout << "Time Over!" << endl;

    kill(getppid(), SIGINT);
}
