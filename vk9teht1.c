#include <stdio.h>
#include <stdlib.h>
#include "vk9teht1.h"




int main(int argc, char *argv[]){
	int num1;
	int num2;
	
	//2 additional arguments given
	if (argc == 3){
	
		//str to int. If conversion not number --> 0
		num1 = atoi(argv[1]);
		num2 = atoi(argv[2]);
		
		//function call
		sum_values(num1, num2);
	
	}else {
	
		printf("usage: <number1> <number2>\n");
		printf("output: sum of <number1> <number2>\n");
	}

	return 0;
}
