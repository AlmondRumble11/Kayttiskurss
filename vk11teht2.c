#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<sys/wait.h>

//https://tldp.org/LDP/lpg/node11.html
//how pipes work

int main(int argc, char *argv[]){
	int pipes[2]; 
	int pid;
	int status;	
	
	//has command
	if (argc < 2){
		printf("usage: <program> <commands>\n");
		exit(1);
	
	}
	//https://www.geeksforgeeks.org/c-program-demonstrate-fork-and-pipe/
	//how to use pipes
	if (pipe(pipes) == -1){
		perror("pipe");
		exit(1);
	}
	switch(pid = fork()){
	
		case -1:
			perror("Fork");
			exit(1);
			break;
		case 0://child process
			printf("Child %d was born, running it\n",pid);
			//close the input end
			close(pipes[0]);
			/*for (int i=1; i<argc; i++) {
				strcat(command,argv[i]);
				strcat(command," ");
			}*/
			
			//send the output stream to output
			if (dup2(pipes[1],STDOUT_FILENO) < 0){
				perror("dub2");
				exit(1);
			
			}
			//run command
			if (execvp(argv[1],argv+1) == -1){
				perror("execvp");			
				exit(1);
			
			}
			//close the output end
			close(pipes[1]);
			break;
			
			
		default://parent
			printf("Child %d was born, waiting in child\n",pid);
			if(wait(&status) == -1){
				perror("wait");
				exit(1);
			}
			printf("Child done, status %d\n",status);
			
			/*had to add this so i could use stdin
			i had one error message( puts (ioputs.c:35) at strlen) for the commented out while read and i had no idea where it came from
			so i just now redirect the pipe to stdin and read it from there using fgets. 
			*/
			if (dup2(pipes[0],STDIN_FILENO) < 0){
				perror("dub2");
				exit(1);
			} 
			//close the outout end
			close(pipes[1]);
			
			
			//buffer
			char buffer[256];
			printf("Printing the child output\n");
			
			//read the read pipe
			int counter = 0;
			while(fgets(buffer,sizeof(buffer),stdin)){
			//while(read(pipes[0], buffer, sizeof(buffer)) > 0){
				counter++;
				printf("%s",buffer);
				
			}
			//close input end
			close(pipes[0]);
		
			break;
	}
	return 0;
}
