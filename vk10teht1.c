#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <sys/file.h>
#include <unistd.h>

int main (int argc, char *argv[]){
	//static struct flock lock;
        time_t t;
        int pid;
        pid = getppid();
        
        //if file not given
        if (argc != 2){
        	printf("usage: <program> <filename>\n");
        	exit(1);
        
        }
        //opening file, from the Koodia ratkaisuihin, Tasks 1
	int fd = open(argv[1], O_RDWR);
	if(fd == -1) {
                printf("Unable to open the file\n");
                exit(1);
        }
        
        //getting the exclusive lock from the Koodia ratkaisuihin, Tasks 1
	time(&t);
        printf("pid: %3d, getting exclusive lock at %s\n", pid, ctime(&t));
        if(flock(fd, LOCK_EX)==-1){
        	printf("LOCK_EX failed\n");
        	exit(1);
        }
        time(&t);
        printf("pid: %4d, exclusive locked at %s\n", pid, ctime(&t));
        sleep(10);

	//unlocking the lock from the Koodia ratkaisuihin, Tasks 1
	if (flock(fd, LOCK_UN) ==-1){
		printf("LOCK_UN failed\n");
        	exit(1);
	}
        time(&t);
        printf("pid: %4d, unlocked at %s\n", pid, ctime(&t));  

	//source: https://linux.die.net/man/2/flock 
	time(&t);
	printf("pid: %3d, getting shared lock at %s\n", pid, ctime(&t));
	if (flock(fd, LOCK_SH)==-1){
		printf("LOCK_SH failed\n");
        	exit(1);
	}
	time(&t);
        printf("pid: %4d, share locked at %s\n", pid, ctime(&t));
        sleep(10);
        time(&t);
        printf("pid: %4d, end of the program %s\n", pid, ctime(&t));  
        

	
	return 0;
}
