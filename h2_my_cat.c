#include <stdio.h>
#include <string.h>
#include <stdlib.h>


//printing the contents
void print_file_contents(char file[]){

   FILE *filename; 
   char *buffer; 
   char *line; //extra line 
   size_t buffer_len; //buffer length
  
    //opening the file and checking it worked
   filename = fopen(file, "r");
   if (filename == NULL){
        printf("my-cat: cannot open file\n");
        perror("fopen:");
        exit(1);
   }

    //allocate starting memory
   buffer = malloc(254*sizeof(char));
   if(buffer == NULL){
    	perror("malloc");
   	exit(1);
   }
   
   //in case if line too long for the buffer
   buffer_len = sizeof(buffer);
   line = calloc(buffer_len,sizeof(char));
   if(line == NULL){
    	perror("calloc");
    	exit(1);
    }
    
    
    //reading the file and inputing it to the user
   printf("Printing the file: %s\n",file);
   while(fgets(buffer, sizeof(buffer), filename) != NULL){

            //if line too long --> allocate more memory           
           if (buffer_len - strlen(line) < sizeof(buffer)){
          	buffer_len *= 2;
            	line = realloc(line,buffer_len);
           	if (line == NULL){
            		perror("realloc");
            		free(line);
            		exit(1);
            	}    	
            	
           }
            
            //add to buffer
           strcat(line, buffer);
	   //print line
	   printf("%s",buffer);
    }

   printf("\n");
   //close the file and free memory
   fclose(filename);
   free(buffer);
   free(line);
}


int main(int argc, char *argv[]){
    
    //char *filename;

    //check that enough
    if (argc < 2){
        printf("No file(s) given. Exiting the program...\n");
        exit(0);
    }

    //going through the files and printing the contents
    for (int i = 1; i < argc; i++){
      	//filename = (char *)malloc(strlen(argv[i])*sizeof(char));
        //strcpy(filename,argv[i]);
        print_file_contents(argv[i]);
        //free(filename);
    }
    return 0;
}
