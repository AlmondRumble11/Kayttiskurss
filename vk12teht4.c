#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <unistd.h>

/* declare as volatile to make sure the compiler does not optimize the variables to fixed values */
volatile double result=0.0;
volatile long long j=1;
/*int check = -1;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond1  = PTHREAD_COND_INITIALIZER;
pthread_mutex_t lock2 = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond2  = PTHREAD_COND_INITIALIZER;
/*
//source for timer: https://cboard.cprogramming.com/c-programming/90175-how-build-timer-counts-seconds-elapsed.html

/* approximation of pi/4 by Leibniz' series */
void * compute(void * par) {
	
    	pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS,NULL);
    
    	//while (j>=0) {      /* stop if j overflows */
        	
        	//printf("j = %lld\n",j);
//	for(int i = 1; i<= j; i++){
        	//printf("check in thread %d\n",check);
        time_t start, end;
	double time_spent;
   	int i = 1;
   	time(&start);
  	while(time_spent < j){      	  
        	//sleep(1);
	    	//check = 1
	    	time(&end);
		if (i % 2 > 0){
		
			result = result - (1.0/(2.0*(double)i+1.0));
		}else{
			result = result + (1.0/(2.0*(double)i+1.0));
		}
		time_spent = difftime(end,start);
		//printf("%f\n",time_spent);
		i++;
		//printf("result in thread = %f\n",result);
		usleep(100);   /* add this little delay just because the computation is
                        otherwise so fast that you get a good approximation in 1 second */
     
               
		
	}
   
		
        	 
    
    	pthread_exit(NULL);
    	return NULL;
}

int main(int argc, char ** argv)
{
    	pthread_t cid;
   	int sec=10,c=0;;
	time_t start, end;
	double time_spent;
	
   	if (argc==2){
   	     sec=atoi(argv[1]);
		
	}
	
	result = 1.0;
	j = sec;
   	if ( pthread_create(&cid, NULL, compute, NULL) != 0){
   			perror("pthread_create");
        		exit(1);
   	}
    	printf("Computing values for %d seconds\n",sec);
    	check = 0;
    	time(&start);
    	while (time_spent < sec) {
		
		time(&end);
        	printf("%d. result is %f * 4 = %f\n",sec,result, result * 4);
		
		time_spent = difftime(end,start);
		
		if (time_spent > 1){
			sec--;
			time_spent = 0;
			time(&start);
		}
		usleep(100); 
        	
    	}
 	pthread_cancel(cid);

	
	if(pthread_join(cid, NULL) != 0){
    		perror("pthread_join");
		exit(1);
	}  
	   	
	return 0;
}

