#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXLEN 1024
struct List{
	char *input;
	struct List *next;
	struct List *prev;


};
typedef struct List list;

int read_lines(list **head, FILE *stream){
	char input[MAXLEN];
	list *temp;
	
	while (fgets(input, MAXLEN, stream) != NULL) {
		
		if (*head == NULL) {
			if ((*head = temp = malloc(sizeof(list))) == NULL) {
				fprintf(stderr, "ERROR: could not allocate memory\n");
				return -1;
			}
			temp->prev = temp->next = NULL;
		} else {
			if ( (temp = malloc(sizeof(list))) == NULL) {
				fprintf(stderr, "ERROR: could not allocate memory\n");
				return -1;
			}

			/* Here you should insert the lines that link the list correctly */
			
			//go to last node of the real list
			list *end = *head;
			while(end->next != NULL){
         			end = end->next;
         		}
         		//former last node's next is current node-> new last node
		      	end->next=temp;
		      	//current nodes prev node is the former end node
		      	temp->prev = end;
			//(*head)->next = NULL;
			//*head = temp;
			

		}
		
		if ( (temp->input = malloc(strlen(input) + 1)) == NULL) {
			fprintf(stderr, "ERROR: could not allocate memory\n");
			return -1;
		}
		
		strcpy(temp->input, input);
		
	}
	//printf("%s",temp->input);
	return 0;
}


void print_lines(list *head, FILE *stream){
	list *temp;
	
	/* Here you should implement a loop that prints the lines in reverse order. 	*/
	/* First you need to follow the links from the first node to the last node.	*/ 
	
	
	temp = head;
	//printf("%s\n",temp->input);
	if (head != NULL){
		//to last node
		while(temp->next != NULL){
			//printf("%s",temp->input);
			temp = temp->next;
		}	
		//then printing backwards
		//from last node to first
		printf("\nYour input backwards:\n");
		while(temp != NULL){
			fprintf(stream,"%s",temp->input);
			temp = temp->prev;
		
		}
	}

}

void delete_lines(list *head){
	list *temp;
	temp = head;
	while (temp != NULL) {
		head = temp->next;
		free(temp->input);
		free(temp);
		temp = head;
	}
}

int main(void){
	
	list * head = NULL;
	
	if (read_lines(&head, stdin) == -1){
		exit(1);
	}
	print_lines(head, stdout);
	delete_lines(head);
	return 0;
}
