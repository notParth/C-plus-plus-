/* PA2 estimate 
 * */

#include <stdio.h>
#include <stdlib.h>

void transpose(double** array, double** result, int n, int k)
{
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < k; j++)
		{
			result[j][i] = array[i][j];
		}
	}
}
void multiply(double** arrayOne, double** arrayTwo, double **result, int a, int b, int c)
{
	for(int i = 0; i < a; i++)
	{
		for(int j = 0; j < c; j++)
		{
			double total = 0;
			for(int k = 0; k < b; k++)
				total+= arrayOne[i][k] * arrayTwo[k][j];
			result[i][j] = total;
		}
	}
}
void inverse(double** array, double** result, int n)
{
	double f;
	for(int p = 0; p <= n-1; p++)
	{
		f = array[p][p];
		for(int j = 0; j < n; j++)
		{
			array[p][j] = array[p][j] / f;
			result[p][j] = result[p][j] / f;
		}
		for(int i = p+1; i < n; i++)
		{
			f = array[i][p];
			for(int j = 0; j < n; j++)
			{
				array[i][j] = array[i][j] - (array[p][j] * f);
				result[i][j] = result[i][j] - (result[p][j] * f);
			}
		}
	}
	for(int p = n-1; p > -1; p--)
	{
		for(int i = p-1; i > -1; i--)
		{
			f = array[i][p];
			for(int j = 0; j < n; j++)
			{
				array[i][j] = array[i][j] - (array[p][j] * f);
				result[i][j] = result[i][j] - (result[p][j] * f);
			}
		}
	}
}
void freeMatrix(double** array, int n)
{
	for(int i = 0; i < n; i++)
		free(array[i]);
	free(array);
}
/*
void display(double** array, int n, int k)
{
	for(int i = 0; i < n; i++)
	{
		for(int j =0; j < k; j++)
		{
			printf("%lf  ", array[i][j]);
		}
		printf("\n");
	}
}
*/
int main(int argc, char **argv)
{
	FILE* train = fopen(argv[1], "r");
	char temp[6] = "\0";
	int n, k;

	fscanf(train, "%s %d %d", temp, &k, &n);
	k++;
	double** trainX = (double**)malloc(n * sizeof(double*));
	double** trainY = (double**)malloc(n * sizeof(double*));

	for(int i = 0; i < n; i++)
	{
		trainX[i] = (double*)malloc(k * sizeof(double));
		trainY[i] = (double*)malloc(1 * sizeof(double));	
		
		trainX[i][0] = 1.0;
		for(int j = 1; j < k; j++)
		{
			fscanf(train, "%lf", &trainX[i][j]); 
		}
		fscanf(train, "%lf", &trainY[i][0]);
	}
	fclose(train);

	FILE* input = fopen(argv[2], "r");
	int n1, k1;
	
	fscanf(input, "%s %d %d", temp, &k1, &n1);
	k1++;
	double** inputX = (double**)malloc(n1 * sizeof(double*));
	double** inputY = (double**)malloc(n1 * sizeof(double*));

	for(int i = 0; i < n1; i++)
	{
		inputX[i] = (double*)malloc(k1 * sizeof(double));
		inputY[i] = (double*)malloc(1 * sizeof(double));
		
		inputX[i][0] = 1.0;
		for(int j = 1; j < k1; j++)
			fscanf(input, "%lf", &inputX[i][j]);
	}
	fclose(input);
	
	double** trainXT = (double**)malloc(k * sizeof(double*));
	double** trainMUL = (double**)malloc(k * sizeof(double*));
	double** trainMUL2 = (double**)malloc(k * sizeof(double*));
	double** trainINV = (double**)malloc(k * sizeof(double*));
	double** weights = (double**)malloc(k * sizeof(double*));
	for(int i = 0; i < k; i++)
	{
		trainXT[i] = (double*)malloc(n * sizeof(double));
		trainMUL[i] = (double*)malloc(k * sizeof(double));
		trainMUL2[i] = (double*)malloc(n * sizeof(double));
		trainINV[i] = (double*)malloc(k * sizeof(double));
		weights[i] = (double*)malloc(1 * sizeof(double));
		for(int j = 0; j < k; j++)
		{
			if(i == j)
				trainINV[i][j] = 1.0;
			else
				trainINV[i][j] = 0.0;
		}
	}
		
	transpose(trainX, trainXT, n, k);
	//	printf("TRANSPOSE\n");
	//	display(trainXT, k, n);
	multiply(trainXT, trainX, trainMUL, k, n, k);
	//	printf("\nMULTIPLYone\n");
	//	display(trainMUL, k, k);
	inverse(trainMUL, trainINV, k);
	//	printf("\nINVERSE\n");
	//	display(trainINV, k, k);
	multiply(trainINV, trainXT, trainMUL2, k, k, n);
	//	printf("\nMULTIPLYtwo\n");
	//	display(trainMUL2, k, n);	
	multiply(trainMUL2, trainY, weights, k, n, 1);
	//	printf("\nWEIGHTS\n");
	//	display(weights, k, 1);
	//	printf("\n");
	if(k == k1)
	{		
		multiply(inputX, weights, inputY, n1, k1, 1);
		for(int i = 0; i < n1; i++)
			printf("%.0lf\n", inputY[i][0]);
	}
	freeMatrix(trainX, n);
	freeMatrix(trainY, n);
	freeMatrix(trainXT, k);
	freeMatrix(trainMUL, k);
	freeMatrix(trainMUL2, k);
	freeMatrix(trainINV, k);
	freeMatrix(weights, k);
	freeMatrix(inputX, n1);
	freeMatrix(inputY, n1);
}
