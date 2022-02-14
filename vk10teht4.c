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
	int file1;
	int file2;
	//check that has all of the fields 
	if(argc > 3){

		switch (pid = fork()) {
		case -1:
		      	perror("Error in fork\n");
			exit(1);
			break;
		case 0:
			//check if '-' in stdin
			//handle stdin
		      	if (strcmp(argv[1],"-")!=0){
		      		file1 = open(argv[1],O_RDONLY);
		      		//open worked
		      		if (file1 < 0){
		      			perror("file1 open()");
		      			exit(1);
		      		}
		      		//dup2() check
		      	
		      		if (dup2(file1, STDIN_FILENO) < 0){
		      			perror("file1 dub2()");
		      			close(file1);
			      		exit(1);
		      		
		      		}
		      		//closing the file
		      		close(file1);
		      	
		      	}else{
		      		//still had to use stdin if no file
		      		dup(STDIN_FILENO);
		      		//close(STDIN_FILENO);
		      		
		      	}
		      	//check if '-' in stdout
		      	//handle stdout
		      	if (strcmp(argv[2],"-")!=0) {
		      		file2 = open(argv[2],O_WRONLY);
		      		//open worked
		      		if (file2 < 0){
		      			perror("file2 open()");
		      			exit(1);
		      		}
		      		//dup2() check
		      		if(dup2(file2,STDOUT_FILENO)< 0){
		      			perror("file2 dub2()");
			      		close(file2);
			      		exit(1);
		      		
		      		}
		      		//closing the file
		      		close(file2);
		      	
		      	} else{
		      		//still had to use stdout if no file
		      		dup(STDOUT_FILENO);
		      		//close(STDOUT_FILENO);
		      	}
		        
		        //run command
		        if (execvp(argv[3], argv+3) == -1){
		        	perror("execvp");
		      		exit(1);
		        
		        }
		        break;
		default:
		        //the parent waits for the child to end execution 
		        printf("Child %d was born, waiting in parent...\n", pid);
		        if (wait(&status) == -1){
		        	perror("wait");
		      		exit(1);
		        }
		  	printf("Child done, status: 0x%X\n", status);
			break;
		}
	}else{
		printf("usage:<./program> <file-for-stdin> <file-for-stdout> <command> [arguments]\n");
		exit(1);
	
	}
	
	return 0;
}


