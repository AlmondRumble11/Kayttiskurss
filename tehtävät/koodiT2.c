#include <stdio.h>
#include <stdlib.h>

int main(void){
	int *data;
	int maara = 100;
	
	if((data = (int*)malloc(maara * sizeof(int))) == NULL){
		perror("Muistin varaus epäonnistui");
		exit(1);
	}
	data[100] = 0;
	//printf("%d\n",data[100]);
	
	/*for (int i = 0; i<=maara;i++){
		printf("%d. luku = %d\n",i,data[i]);
	}*/

	//free(data);
	return 0;
}
