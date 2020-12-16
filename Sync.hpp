#ifndef __SYNC_HPP__
#define __SYNC_HPP__

#include <semaphore.h>

sem_t semid;

int creat_sem();
int destroy_sem();
int lock_sem();
int unlock_sem();

#endif