#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Node{
    char *line;
    struct Node *pNext;
   // struct Node *pPrev;
    
};
typedef struct Node node;
void print_the_list(node *pA){
    node *temp = pA;
    fprintf(stdout,"\n");
    while(temp != NULL){
        fprintf(stdout,"%s", temp->line); 
        temp = temp->pNext; 
    }
}
node *tyhjennys(node *pA){
	node *ptr = pA;
	while (ptr != NULL){
		pA = ptr->pNext;
		free(ptr);
		ptr = pA;
	}
	return pA;
}
node *reverse_linked_list(node *pA){
    node *pPrev;
    node *pNow;
    node *pNext;

    pPrev = NULL;
    pNext = NULL;
    pNow = pA;
    while(pNow != NULL){
        pNext = pNow->pNext;
        pNow->pNext = pPrev;
        pPrev = pNow;
        pNow = pNext;
    }
    return pPrev;
}


void write_to_output(node *pA, char *filename){
    FILE *output_file;
    node *ptr_start;
  
    //opening the output file
    if ((output_file = fopen(filename, "w")) == NULL){
        fprintf(stderr ,"error: cannot open file '%s'",filename);
        exit(1);	
    }
    //starting point is the start of the linked list
    ptr_start = pA;

    //writing the rows from the linked list
    while (ptr_start != NULL){
        fprintf(output_file,"%s",ptr_start->line);
        ptr_start = ptr_start->pNext;
    }
    print_the_list(pA);
    //closing the output file
    fclose(output_file);

}

node *open_input_file(node *pA, char *filename){
    
    //variables
    FILE *input_file;
    node *ptr_new = NULL;
    node *pEnd;
    //char line[100];
    char *line = malloc(1024);
    if (line == NULL){
        fprintf(stderr,"malloc failed\n");
		exit(1);
    }

    //if the linked list is empty
    if (pA == NULL){

        //opening the file
        if ((input_file = fopen(filename, "r")) == NULL){
            fprintf(stderr ,"error: cannot open file '%s'",filename);
            exit(1);	
        }
       
        //reading the file
        while (fgets(line, 1024, input_file) != NULL){
           
            //getting space
            if((ptr_new = (node *)malloc(sizeof(node))) == NULL){
			    fprintf(stderr,"malloc failed\n");
			    exit(1);	
		    }

            //saving value 
            ptr_new->line = line;
            ptr_new->pNext = NULL;
           

            line = malloc(sizeof(line));
            printf("%ld\n",strlen(line));
            if (line == NULL){
                fprintf(stderr,"malloc failed\n");
                exit(1);
            }

            //printf("%s",line);
            //printf("%s",ptr_new->line);
            
            //moving the pointer
            if (pA == NULL){
                pA = ptr_new;
                pEnd = ptr_new;
            }else{
                pEnd->pNext = ptr_new;
                pEnd = ptr_new;

            }
      
            
        }
        free(line);
        print_the_list(pA);
        fclose(input_file);
    }

    return pA;
}
void user_input(){
    char *line = NULL;
    size_t len = 0;
    

    while(getline(&line,&len,stdin) != -1){
        fprintf(stdout,"%s",line);
        }
    }
    free(line);

int main(int argc, char *argv[]) { 

    node *pA = NULL;

    if (argc == 1){
        user_input();
    }
    else if (argc == 2){
        pA = open_input_file(pA,argv[1]);

    }
    else if (argc == 3){
 

        if (strcmp(argv[1],argv[2]) != 0){
            pA = open_input_file(pA,argv[1]);
            pA = reverse_linked_list(pA);
            write_to_output(pA,argv[2]);


        }else{  //the files are the same
            fprintf(stderr ,"Input and output file must differ");
			exit(1);	

        }
    }
    
    else {
        fprintf(stdout,"usage: reverse <input> <output>");
        exit(1);
    }

    



    return 0;
}
