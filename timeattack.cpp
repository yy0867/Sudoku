#include "timeattack.hpp"

#define TIME_ROW 35
#define TIME_COL 3

using namespace std;

void measure_time(pid_t pid, double time) {
    int count = 0;
    for (double i = time; i >= 0; i -= 0.01) {
        gotoxy(TIME_ROW, TIME_COL);
        cout << i << "..." << endl;

        fflush(stdout);
        usleep(10000); // 0.01sec
    }
    cout << "Time Over!" << endl;

    kill(pid, SIGINT);
}
