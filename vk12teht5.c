#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NTHREAD 10

int result = 0;
int thread_num = -1;
pthread_mutex_t mt = PTHREAD_MUTEX_INITIALIZER;

void * increment(void * par) {
	pthread_mutex_lock(&mt); //lock so only one thread can add to result
	thread_num++;
	printf("Securing lock for thread %d\n",thread_num);
        int i;
        for (i = 0; i< *(int *)par; i++) {
                result++;
                //printf("result %d\n",result);
        }
        printf("Unlocking lock from thread %d\n",thread_num);
        pthread_mutex_unlock(&mt); //unlocking the lock so other thread can add to result
        
}

//source how loks work: https://www.geeksforgeeks.org/mutex-lock-for-linux-thread-synchronization/

int main() {
        pthread_t tid[NTHREAD];
        int i;
        int num = 10000;

        for (i = 0; i<NTHREAD; i++) {
                printf("Creating thread %d\n",i);
                pthread_create(& tid[i], NULL, increment, (void *)&num);
        }
        for (i = 0; i< NTHREAD; i++){
       	 pthread_join(tid[i], NULL);
        }
	

	
        printf("Value %d\n", result);
        
        pthread_mutex_destroy(&mt);

}

