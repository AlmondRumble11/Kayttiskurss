#include <stdio.h>
#include <stdlib.h>
#include <string.h>



void unzipping(char *filename){
    FILE *file;
    char *buffer;
    size_t buffer_size;
    size_t read_bytes;

    //opening the file
    file = fopen(filename, "rb");
    if(file == NULL){
        printf("Error opening file: %s\n",filename);
        exit(1);
    }

    //source: https://www.cplusplus.com/reference/cstdio/fread/
    //gettign the file size
    fseek(file, 0, SEEK_END);
    buffer_size = ftell(file);

    //getting back to start
    fseek(file, 0, SEEK_SET);

    //allocate mememory for the buffer
    buffer = (char*)malloc(buffer_size * sizeof(char));
    
    //rading the file
    read_bytes = fread(buffer,1, buffer_size, file);
    if(read_bytes != buffer_size){
        printf("Error when reading the file\n");
        exit(1);
    }
    printf("%s",buffer);


    fclose(file);
    free(buffer);

}


int main(int argc, char *argv[]){


    if (argc < 2){
        printf("wunzip: file1 [file2 ...]\n");
        exit(1);
    }
    for(int i = 1; i<argc; i++){
        unzipping(argv[i]);
        
    }



    return 0;
}