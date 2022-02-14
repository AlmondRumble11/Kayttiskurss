#include <stdio.h>
#include <stdlib.h>
struct Vektori {
	int* luvut;
	int maara;
	int koko;

};


struct Vektori *alusta_vektori(struct Vektori *vec,int koko){
	
	if((vec->luvut = (int*)malloc(koko * sizeof(int))) == NULL){
		perror("Muistin varaus epäonnistui");
		exit(1);
	}
	
	vec->maara = 0;
	vec->koko = koko;
	return vec;
	

}
struct Vektori *lisaa_luku(struct Vektori *v, int uusiluku){
	int uusikoko;
	int *luvut;
	
	uusikoko = v->koko + 1;
	if((luvut = (int*)realloc(v->luvut,uusikoko * sizeof(int))) == NULL){
		perror("Muistin varaus epäonnistui");
		exit(1);
	}
	v->luvut = luvut;
	v->luvut[v->maara++] = uusiluku; 
	
	v->koko = uusikoko;
	printf("koko = %d\n",v->koko);
	printf("määrä = %d\n",v->maara);
	
	return v;

}
int main(void){
	struct Vektori *vector, vec;
	vector = &vec;
	int koko = 5;
	vector = alusta_vektori(&(*vector),koko);
	for (int i = 0; i<vector->koko;i++){
		vector->luvut[i] = i;
		vector->maara = vector->maara +1;
	}
	printf("vektori ennen uutta lukua\n");

	for (int i = 0; i<vector->koko;i++){
		printf("%d\n",vector->luvut[i]);
	}
	int uusiluku = 5;
	printf("vektori uuden luvun jälkeen\n");
	vector= lisaa_luku(&(*vector), uusiluku);
	for (int i = 0; i<vector->koko;i++){
		printf("%d\n",vector->luvut[i]);
	}
	free(vector->luvut);
	
	return 0;
}
