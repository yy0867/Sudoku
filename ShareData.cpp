#include "ShareData.hpp"
#include <stddef.h>

void shm_init() {
    shmkey = ftok("usr/bin/", 1);
    shmid = shmget(shmkey, sizeof(double), IPC_CREAT | 0600);
}

double *shm_attach() { return (double *)shmat(shmid, NULL, 0); }

void shm_detach(double *addr) { shmdt(addr); }
