#include <stdio.h>
#include <stdlib.h>

int main(void){
	int *data;
	int maara = 100;
	
	if((data = (int*)malloc(maara * sizeof(int))) == NULL){
		perror("Muistin varaus epäonnistui");
		exit(1);
	}
	
	//int *temp;
	for (int i = 0; i<maara;i++){
		data[i] = i;
	}
	//temp = &data[50];
	/*for (int i = 0; i<maara;i++){
		printf("%d. luku = %d\n",i,data[i]);
	}*/
	//printf("%d\n",*temp);
	//free(temp);
	free(data);
	printf("%d\n",data[50]);
	return 0;
}
