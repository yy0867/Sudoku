#include "Sync.hpp"

int creat_sem() { return sem_init(&semid, 1, 1); }
int destroy_sem() { return sem_destroy(&semid); }
int lock_sem() { return sem_wait(&semid); }
int unlock_sem() { return sem_post(&semid); }