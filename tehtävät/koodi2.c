#include <stdio.h>
#include <stdlib.h>

int main(void){
	int *luvut;
	int maara = 10;
	
	if((luvut = (int*)malloc(maara * sizeof(int))) == NULL){
		perror("Muistin varaus epäonnistui");
		exit(1);
	}
	
	

	
	for (int i = 0; i<maara;i++){
		luvut[i] = i;
	}
	for (int i = 0; i<maara;i++){
		printf("%d. luku = %d\n",i,luvut[i]);
	}
	//free(data);
	return 0;
}
