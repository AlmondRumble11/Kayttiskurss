#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <unistd.h>

int main (int argc, char *argv[]){
	char *sys_call ;
        if (argc > 1 ){
        	//strcat(sys_call,argv[1]);
        	
        	for (int i = 1; i<argc;i++){
        		if (i == 1){
	        		sys_call = (char *)calloc((strlen(argv[1])+2),sizeof(char));
	        		if (sys_call == NULL){
                			printf("malloc failed\n");
                			exit(1);
            			}
	        	}else{
	        		//printf("len sys_call: %ld\n",strlen(sys_call));
	        		//printf("len argv: %ld\n",strlen(argv[i]));
	        		sys_call = (char *)realloc(sys_call,(strlen(argv[i])+strlen(sys_call) + 2)*sizeof(char));
	        		if (sys_call == NULL){
                			printf("malloc failed\n");
                			exit(1);
            			}
	        	}
        		strcat(sys_call,argv[i]);
        		strcat(sys_call," ");
        		//printf("%s\n",argv[i]);
        	
        	}
        	//system call with system()
        	printf("System call with system()\n");
        	system(sys_call);
        	free(sys_call);
        	
        	printf("###################\n");
        	//system call with exec()
        	printf("System call with exec()\n");
        	execvp(argv[1], argv+1);
        	printf("###################\n");
        	
        	
        	//printf("%s\n",sys_call);

        
        }else{
        	printf("usage: <program> <system call> <additional fuction>\n");
        	exit(1);
        }
        
	
	
	
	return 0;
}


