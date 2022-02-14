#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
void temp_file_function();

static char *get_temp(){
	static char temp[20] = "/tmp/tempfileXXXXXX";
	return temp;
}
void handle_sigint(int sig){
	printf("Unlinking file %s\n",get_temp());
	//atexit(temp_file_function);
	unlink(get_temp());
	exit(1);

}

void temp_file_function(){
	FILE *fd;
	int file = -1;
	char text[20] = "text to file\n";
	char buffer[20];
	time_t start_time;
	time_t end_time;
	int counter;
	
	
	//create temp file
	//https://stackoverflow.com/questions/12008243/how-to-get-a-temporary-file-name 
	file = mkstemp(get_temp());
	unlink(get_temp());
	printf("%s\n",get_temp());
	if (file < 1){
		printf("Failed to create temporary file. Exiting...\n");
		exit(1);
	}
	
	
	/*first attenpt 
	tempfile https://www.geeksforgeeks.org/tmpfile-function-c/ 
	file = tmpfile();
	
	if (file == NULL){
		printf("Failed to create temporary file. Exiting...\n");
		exit(1);
	}
	printf("Temporary file created\n");*/
	
	
	
	//https://stackoverflow.com/questions/15110642/how-to-fdopen-as-open-with-the-same-mode-and-flags
	//opening the temp file
	fd = fdopen(file, "w+");
	if (fd == NULL){
		printf("Failed to open temporary file. Exiting...\n");
		exit(1);
	
	}
	//start time
	start_time = time(NULL);
	end_time = 30 + start_time;
	printf("Adding text to file for 30s. Starting time is: %s\n",ctime(&start_time));
	//write lines to file for 30s

	
	//https://stackoverflow.com/questions/21181162/how-do-i-stop-a-while-loop-after-a-certain-time-in-c 
	while(start_time < end_time){
	
		//write after every 1s
		sleep(1);
		start_time = time(NULL);
		fprintf(fd,"%s",text); //write to file
		printf("Time now: %s\n",ctime(&start_time));
		
	
	}
	
	printf("Written text to file for 30s. End time is: %s\n",ctime(&end_time));
	printf("Printing the contents of temp file\n");
	

	
	counter = 1;
	//back to front
	fseek(fd, 0, SEEK_SET);
	//https://www.ibm.com/support/knowledgecenter/en/ssw_ibm_i_73/rtref/fdopen.htm
	
	
	//https://stackoverflow.com/questions/15697783/how-does-fread-know-when-the-file-is-over-in-c
	//how fread works
	//printing contents
	while (fread(buffer,1, strlen(text), fd) == strlen(text)){
		printf("%d. %s",counter, buffer);
		counter ++;
	}

	//closing the file
	
	fclose(fd);
}

int main(void){
	//https://www.youtube.com/watch?v=ZRS-5I9-Bac
	//how atexit works
	//temp_file_function();
	signal(SIGINT, handle_sigint);
	if ( atexit(temp_file_function) != 0){
		printf("Failed to register temp_file_function as the termination function\n");
	}
	return 0;
}
