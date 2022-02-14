#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>


int count = 0; //propably using locks would have been better but for this tasks using ticket works

void * first(void * par){
	
	
    	sleep(1);
	
   	fputs("The quick brown fox jumped ", stdout);
   	count = 1;
    	return NULL;
}

void *second(void * par){
	
	while(1){
		if(count == 1){break;}
	}

	sleep(1);

	fputs("high up in the air\n",stdout);
	

	return NULL;


}


int main(void){
	pthread_t fid, sid;
	

    	if (pthread_create(&fid, NULL, first, NULL) != 0) {
       	perror("pthread_create");
        	exit(1);
	}
	if (pthread_create(&sid, NULL, second, NULL) != 0) {
       	perror("pthread_create");
        	exit(1);
	}
    

	
	
	if (pthread_join(sid,NULL) != 0){
		perror("pthread_join");
        	exit(1);
	}
	
	if (pthread_join(fid,NULL) != 0){
		perror("pthread_join");
        	exit(1);
	
	}
	


    	return 0;
	

}
