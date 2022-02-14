#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct lines{
    char *line;
    struct lines *next;
};
typedef struct lines lines;

void tyhjennys(lines **start){
	lines *ptr = *start;
	while (ptr != NULL){
		*start = ptr->next;
		free(ptr->line); //free the char array
		free(ptr);
		ptr = *start;
	}
	
}
void print_original_files(lines *pA){
    lines *temp = pA;
    while(temp != NULL){
        printf("%s", temp->line); 
        temp = temp->next; 
    }
    printf("\n");
}

void open_file(lines **start,char *filename){
    FILE * input_file;
    
    char *buffer;
    size_t buffer_size = 1024;
    lines *new_line;

    buffer = (char*)malloc(buffer_size * sizeof(char));
    if (buffer == NULL){
        perror("malloc");
        exit(1);
    }


    //open file and check if opening worked
    input_file = fopen(filename, "r");
    if (input_file == NULL){
        printf("Eroor opening file: %s\n",filename);
        exit(1);
    }

    
    


    //going through the file andadding to linked list
    while(getline(&buffer,&buffer_size,input_file)  != -1){

        //aalocating memory for new list item
        if((new_line = (lines *)malloc(sizeof(lines))) == NULL){
            printf("malloc failed\n");
            exit(1);	
        }
        //allocating memory for the new line
        new_line->line = (char* )malloc((strlen(buffer)+1)*sizeof(char));
        if (new_line->line == NULL){
                printf("malloc failed\n");
                exit(1);
        }
        //saving value 
        strcpy(new_line->line, buffer);
        new_line->next = NULL;
        //printf("buffer: %s\n",buffer);
        //printf("new_line data: %s\n",new_line->line);
      

        //move the pointer to rigth spot
        if (*start == NULL){
            *start = new_line;
        }else{
            lines *last = *start;
            while(last->next != NULL){
                last = last->next;
            }
            last->next = new_line;
        }
    }

    //free buffer and close the file
    free(buffer);
    fclose(input_file);
}
void compress_file(lines *start){
    
    lines *temp;
    temp = start;
    int char_count;
    int line_lenght = 0;
    int first_char;
    int next_char;
    char_count = 1;

  
    
    while(temp != NULL){
        //printf("%s", temp->line); 
        first_char = temp->line[0];
        //printf("%d ", temp->line[0]);
        line_lenght = strlen(temp->line);
        //for(int i = 1; i < line_lenght; i++){
        for(int i = 1; temp->line[i] != '\0'; i++){
            //printf("%d ", temp->line[i]);
            next_char = temp->line[i];
            
            if (first_char == next_char) {
                char_count++;
            }else{
               
                    //printf("%d%c ",char_count, first_char);
                    //printf("%d ",next_char);
                    

                    //fwrite(&f, sizeof(f), 1, stdout);

                    //fprintf(stdout,"%d%c",char_count, first_char);
                    char character = first_char;
                    int *count_pointer;
                    count_pointer = &char_count;
                    //printf("%d ",char_count);
                    
                    fwrite(&count_pointer,4,1,stdout);
                    fwrite(&character,sizeof(character),1,stdout);
                    
                    first_char = next_char;
                    char_count = 1;
                    //printf("\n");
                
            }

        }
        //printf("\n");

        temp = temp->next; 
    }
    

    

    

}

int main(int argc, char *argv[]){


    lines *start = NULL;
    if (argc < 2){
        printf("my-zip: file1 [file2 ...]\n");
        exit(1);
    }

    //going throught the files
    for(int i = 1; i<argc; i++){
        open_file(&start, argv[i]);
        compress_file(start);
    }
    //print_original_files(start);

    tyhjennys(&start);



    return 0;
}