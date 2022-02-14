#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <unistd.h>
#include <sys/wait.h>



int main (int argc, char *argv[]){
	int pid;
	int status;
	
	switch (pid = fork()) {
        case -1:       /* error in fork */
        	printf("Error in fork\n");
        	exit(1);
        	break;
      
        case 0:               /* child process */
            printf("Child %d was born, running child...\n", pid);
            if (execvp(argv[1], argv+1) == -1) {
               perror("execvp");
               exit(1);
            }
           exit(pid);
           break;
        default:              /* parent process */
           printf("Child %d was born, waiting in parent...\n", pid);
           if (wait(&status) == -1) {
              perror("wait");
              exit(1);
           }
          
          printf("Child done, status: %d\n", status);
          
          break;
       }
	
	
	
	return 0;
}


