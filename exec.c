

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int main()
{
		//A null terminated array of character
		//pointers
		char*  args[] = { "ls", "-R", NULL };
		execv("/bin/ls",args);
	
		/*All statements are ignored after execvp() call as this whole
		process(execDemo.c) is replaced by another process (EXEC.c)
		*/
		printf("Ending-----");
	
	return 0;
}

