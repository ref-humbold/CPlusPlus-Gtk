#ifndef PTHREAD_SEMAPHORE_H
#define PTHREAD_SEMAPHORE_H

#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>

struct pthread_semaphore
{
    int counter;
    pthread_cond_t waiting;
    pthread_mutex_t crit;
};

void sem_init(struct pthread_semaphore * semaphore, int init_count);

void sem_wait(struct pthread_semaphore * semaphore);

void sem_signal(struct pthread_semaphore * semaphore);

#endif
