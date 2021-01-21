/* CS 211 PA1: mexp
 * Created for: psp116
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	FILE *input;
	input = fopen(argv[1], "r");
	
	char ch[2] = "\0";
	ch[0] = fgetc(input);

	int size = atoi(ch);
	int **a;
	a = (int **)malloc(sizeof(int *) * size);
	for(int i = 0; i < size; i++)
		a[i] = (int *)malloc(sizeof(int) * size);
	
	char t = fgetc(input);
	int cnt;
	char temp[5];
	
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			cnt = 0;
			temp[0] = '\0'; temp[1] = '\0'; temp[2] = '\0'; temp[3] = '\0'; temp[4] = '\0'; 
			t = fgetc(input);
			while(t!='\n' && t!=' '){
				temp[cnt++] = t;	
 				t = fgetc(input);
			}
			a[i][j] = atoi(temp);
			
		}
	}
	t = fgetc(input);
	temp[0] = '\0'; temp[1] = '\0'; temp[2] = '\0'; temp[3] = '\0'; temp[4] = '\0';
	cnt = 0;
	while(t != EOF){
		temp[cnt++] = t;
		t = fgetc(input);
	}
	int mulN = atoi(temp);	
	int **mul, **tempMat;
	mul = (int **)malloc(sizeof(int *) * size);
	tempMat = (int **)malloc(sizeof(int *) * size);
	for(int i = 0; i < size; i++){
		mul[i] = (int *)malloc(sizeof(int) * size);
		tempMat[i] = (int *)malloc(sizeof(int) * size);
		for(int j = 0; j < size; j++){
			mul[i][j] = a[i][j];
			tempMat[i][j] = 0;
		}
	}
	if(mulN != 0)
	{
		for(int m = 1; m < mulN; m++){
			for(int i = 0; i < size; i++){
				for(int j = 0; j < size; j++){
					int total = 0;
					for(int k = 0; k < size; k++)
						total += mul[i][k] * a[k][j];
					tempMat[i][j] = total;
				}
			}
	
			for(int x = 0; x < size; x++)
				for(int y = 0; y < size; y++)
					mul[x][y] = tempMat[x][y];
		}
	}
	else
	{
		for(int i = 0; i < size; i++)
			for(int j = 0; j < size; j++)
			{
				if(i == j)
					mul[i][j] = 1;
				else
					mul[i][j] = 0;
			}
	
	}
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			printf("%d", mul[i][j]);
			if(j != size-1)
				printf(" ");
		}
		printf("\n");
	}	
}
