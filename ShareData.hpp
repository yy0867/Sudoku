#ifndef __SHAREDATA_HPP__
#define __SHAREDATA_HPP__

#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>

key_t shmkey;
int shmid;

void shm_init();
double *shm_attach();
void shm_detach(double *addr);

#endif
