// global1.c
#include <stdio.h>
#include <pthread.h>
#include "LZW.h"
#include "oku_conv.h"

pthread_mutex_t myMutex;

void *thread1(void *param)
{	
	pthread_mutex_lock(&myMutex);
    meh();
    pthread_mutex_unlock(&myMutex);
}


void *thread2(void *param)
{
   	lzwio();
}


int main()
{
    pthread_t p1, p2;
    pthread_mutex_init(&myMutex,0);
    pthread_create(&p1, NULL, thread1, NULL);
    pthread_create(&p2, NULL, thread2, NULL);
	
    // join waits for the threads to finish
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
    pthread_mutex_destroy(&myMutex);
    return 0;
}
