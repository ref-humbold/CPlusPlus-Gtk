#include "pthreadsem.h"

void sem_init(struct pthread_semaphore * semaphore, int init_count)
{
    semaphore->counter = init_count;
    pthread_cond_init(&semaphore->waiting, NULL);
    pthread_mutex_init(&semaphore->crit, NULL);
}

void sem_wait(struct pthread_semaphore * semaphore)
{
    pthread_mutex_lock(&semaphore->crit);
    semaphore->counter--;

    if(semaphore->counter < 0)
        pthread_cond_wait(&semaphore->waiting, &semaphore->crit);

    pthread_mutex_unlock(&semaphore->crit);
}

void sem_signal(struct pthread_semaphore * semaphore)
{
    pthread_mutex_lock(&semaphore->crit);

    if(semaphore->counter < 0)
        pthread_cond_signal(&semaphore->waiting);

    semaphore->counter++;
    pthread_mutex_unlock(&semaphore->crit);
}
