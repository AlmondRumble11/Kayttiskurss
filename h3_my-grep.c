#include <stdio.h>
#include <string.h>
#include <stdlib.h>


//seaching the word from a file
void search_file(char *filename, char *input){
    FILE *file;
    char *buffer = NULL;
    size_t buffer_size = 0;
    int line_nro = 1;


    //open file and check that it was opened
    file = fopen(filename, "r");
    if (file == NULL){
        printf("my-grep: cannot open file\n");
        exit(1);
    }
    printf("Searching for the word %s from the file %s\n",input, filename);
    //read through the file
    while(getline(&buffer, &buffer_size, file) >= 0){
            //https://www.tutorialspoint.com/c_standard_library/c_function_strstr.htm
            //see if searched word is on the line
            if (strstr(buffer, input) != NULL){
                //printf("Word %s found on the line %d in file %s\n",input,line_count,filename);
                printf("Line %d: %s",line_nro, buffer);
            }

            line_nro++;
    }
    //free buffer and close the file
    free(buffer);
    fclose(file);
    printf("\n");

    
}

//searching the word from stdin
void read_stdin(char *input){
    char *buffer = NULL;
    size_t buffer_size = 0;
    int line_nro = 1;

    //read from stdin
    while (getline(&buffer,&buffer_size,stdin)  >= 0){

        //check if the line has the word
        if(strstr(buffer, input) != NULL){
            printf("Line %d: %s",line_nro, buffer);
        }
        line_nro++;
    }
    //free buffer
    free(buffer);
  
}


int main(int argc, char *argv[]){
    

    //check that fiels are given
    if (argc < 2){
        printf("my-grep: searchterm [file ...]\n");
        exit(1);
    }

    //has files
    if (argc > 2){
        //going through the file(s)
        for (int i = 2; i < argc; i++){
            search_file(argv[i],argv[1]);
          

        }
    //no file, only search term given  
    }else{
        read_stdin(argv[1]);
    }




    return 0;
}