#define   _GNU_SOURCE
#include<stdio.h>
#include <stdlib.h>
#include<string.h>


int main(void){
	char *buffer;
	size_t len=0;
	
	
	
	while(getline(&buffer, &len, stdin) != -1){
		printf("buffer = %s\n", buffer);
		if(strstr(buffer,"\n")){
			break;
		}
	
	
	
	}
	
}
