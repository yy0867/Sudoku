#include "timeattack.hpp"
#include "ShareData.hpp"
#include "Sync.hpp"

#define TIME_ROW 47
#define TIME_COL 4

using namespace std;

double timeLeft = 0;
double *shmaddr = NULL;

void measure_time(pid_t pid, double time) {
    int count = 0;
    shmaddr = shm_attach();

    for (double i = time; i >= 0; i -= 0.01) {
        *shmaddr = i;

        lock_sem();
        gotoxy(TIME_ROW, TIME_COL);
        cout << "TIME : " << i << "..." << flush;
        unlock_sem();
        timeLeft = i;

        fflush(stdout);
        usleep(10000); // 0.01sec
    }
    shm_detach(shmaddr);
    cout << "Time Over!" << endl;

    kill(pid, SIGINT);
}
