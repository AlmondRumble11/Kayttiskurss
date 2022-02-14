#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//source: https://www.tutorialspoint.com/c_standard_library/c_function_getenv.htm
//how getenv() works
//https://stackoverflow.com/questions/9628645/use-printf-to-format-floats-without-decimal-places-if-only-trailing-0s
//float without decimals

int main(int argc, char *argv[]){
	//double so can handle large numbers
	double sum = 0; 
	double mult = 1;
	
	//if no operator
	if (getenv("OPERATOR") == NULL){
		printf("No OPERATIOR given\n");
		exit(1);
	}
	//if values
	if (argc > 1){
		//if add
		if (strcmp(getenv("OPERATOR"),"add") == 0){
			printf("Add operator\n");
			//go through all the numbers
			for(int i = 1; i < argc; i++){
				sum += atof(argv[i]);
				//printf("%f\n",sum);
			
			}
			printf("Sum of all the commandline parameters: %g\n", sum);
		//if multiplication
		}else if (strcmp(getenv("OPERATOR"),"multiplication") == 0){
			printf("Multiplication operator\n");
			//go through all the numbers
			for(int i = 1; i < argc; i++){
				mult *= atof(argv[i]);
				//printf("%f\n",mult);
			
			}
			
			printf("Multiplication of all the commandline parameters: %g\n", mult);
		}else{
			printf("usage: export OPERATOR=<add> or <multiplication>\n");
		}
	}else{
		printf("No arguments give\n");
	}
	
	return 0;
}
