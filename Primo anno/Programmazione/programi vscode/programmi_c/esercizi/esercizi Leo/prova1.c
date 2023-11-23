#include <stdio.h>
#include <stdlib.h>

int media_array ( int *i, int len  );
int triangolo(int l);



void main(){
	
	int i[5] = {1, 2, 3, 4, 5};
	int *p = i;
	int len_i = sizeof(i)/sizeof(int);
	int j = media_array( p, len_i);
	
	
	printf("%d\n",j);
	
	triangolo(8);
	
}


int media_array ( int *i, int len ) {
	int j = 0;
	
	for (int y = 0; y < len; y++ ) {
		j = j + i[y];
	}
	j = j/len;
	return j;
}
	
int triangolo(int l) {
	int count = 1;
	for (int m = 1; m <= l; m++){
		for (int n = 1; n <= m; n++){
			printf("%d ",count);
			count++;
		}
		printf("\n");
		
	}
}


