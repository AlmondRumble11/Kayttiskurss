#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include<sys/wait.h>


static int number; //for child to contunue from same value as main

void count_to_zero(int *number){
	
	
	while(*number >= 1){
		
		//printf("num = %d\n",*number);
		
		printf("%d. seconds left\n",*number);
		sleep(1);
		*number = *number - 1;
	}
	
}


void interuption_handler(int sig_numl){
	
	signal(SIGINT, interuption_handler);
	int pid;
	
	pid = fork();
	
	if (pid < 0){
		perror("Fork");
		exit(1);
	}else if (pid == 0){
		number = number -1; //so it does not start form the last value as sleep is after the message
		count_to_zero(&number); //continue the counting from the same number
	
	}else{
		
		wait(0); //wait for the child
		exit(0); //when child finnished exit 
	}
}


int main(void){
	
	
	
	
	printf("Give a number from which counting to zero: ");
	scanf("%d",&number);
	signal(SIGINT, interuption_handler);
	count_to_zero(&number);

	return 0;

}
