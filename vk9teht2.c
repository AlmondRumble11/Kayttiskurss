#include <stdio.h>

//source: https://stackoverflow.com/questions/2085302/printing-all-environment-variables-in-c-c 
//how to get environment variables to C

int main(int argc, char *argv[], char* envp[]){
	//printing the program
	printf("Program: %s\n",argv[0]);
	
	//printing the parameters
	printf("Commandline parameters:\n");
	for (int i = 1; i < argc; i++){
		printf("%s\n",argv[i]);
	}
	
	
	//printing the environment variables
	printf("All of the environment variables:\n");
	for (int j = 0; envp[j] != NULL; j++){
		printf("%s\n",envp[j]);
	}
	
	
	return 0;
}
