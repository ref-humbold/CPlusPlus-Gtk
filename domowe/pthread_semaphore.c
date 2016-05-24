#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

struct thread_sem
{
	int counter;
	pthread_cond_t waiting;
	pthread_mutex_t crit;
};

void thr_sem_init(struct thread_sem* semphr, int init_count)
{
 semphr->counter=init_count;
 pthread_cond_init(&semphr->waiting, NULL);
 pthread_mutex_init(&semphr->crit, NULL);
}

void thr_sem_init(struct thread_sem* semphr, int init_count)
{
 semphr->counter=init_count;
 semphr->before=0;
 pthread_cond_init(&semphr->waiting, NULL);
 pthread_mutex_init(&semphr->crit, NULL);
}

void thr_sem_wait(struct thread_sem* semphr)
{
 pthread_mutex_lock(&semphr->crit);
 semphr->counter--;
 
 	if(semphr->counter<0)
 	{
 	 pthread_cond_wait(&semphr->waiting, &semphr->crit);
 	}
 
 pthread_mutex_unlock(&semphr->crit);
}

void thr_sem_signal(struct thread_sem* semphr)
{
 pthread_mutex_lock(&semphr->crit);
 
 	if(semphr->counter<0)
 	{
 	 pthread_cond_signal(&semphr->waiting);
 	}
 	
 semphr->counter++;
 pthread_mutex_unlock(&semphr->crit);
}

int main()
{
	
	return 0;
}
