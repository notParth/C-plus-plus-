/* CS 211 PA4
 * Created for: psp116
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { AND, OR, NAND, NOR, XOR, NOT, PASS, DECODER, MULTIPLEXER } kind_t;
struct gate
{
	kind_t kind;
	int size;
	int *params;
};
//method to recognize gates
int gateToNum(char *input)
{
	if(strcmp(input, "AND") == 0)
		return 0;
	else if(strcmp(input, "OR") == 0)
		return 1;
	else if(strcmp(input, "NAND") == 0)
		return 2;
	else if(strcmp(input, "NOR") == 0)
		return 3;
	else if(strcmp(input, "XOR") == 0)
		return 4;
	else if(strcmp(input, "NOT") == 0)
		return 5;
	else if(strcmp(input, "PASS") == 0)
		return 6;
	else if(strcmp(input, "DECODER") == 0)
		return 7;
	else
		return 8;
}
//method to calculate 2^n
int power(int n)
{
	int total = 1;
	if(n < 30)
	{
		for(int i = 0; i < n; i++)
		{	
			total = total * 2;
		}
	}
	return total;
}
//method to find the index of "check" in string array "arr", else return -1
int index_return(char **arr, char *check, int size)
{
	for(int i = 0; i < size; i++)
		if(strcmp(arr[i], check) == 0)
			return i;
	return -1;
}
//method to turn decimal to binary and store it in an int*
void toBinary(int n, int *arr, int size)
{
	size--;
	while(n > 0)
	{
		arr[size--] = n % 2;;
		n = n / 2;
	}
	for(int i = size; i >= 0; i--)
		arr[i] = 0;
}
//method to return a decimal number converted from binary
int toDecimal(int *arr, int size)
{
	int total = 0;
	int cnt = 0;
	for(int i = size - 1; i >= 0; i--)
		total = total + ((power(cnt++) * arr[i]));
	return total;
}
int OneOrZero(char *check)
{
	if(strcmp(check, "0") == 0)
		return 0;
	else
		return 1;
}
int main(int argc, char **argv)
{
	/*
	 * input_size will store the amount of input variables
	 * output_size will store the amount of output variables
	 * temp_size will store the amount of temporary variables
	 * seq_size will store the amount of gates in the circuit
	 */
	
	int input_size;
	int output_size;
	int temp_size = 0;
	int seq_size = -1;
	
	//open input file
	FILE *circuit = fopen(argv[1], "r");
	//temporary string variable
	char temp[20];
	
	fscanf(circuit, "%s %d", temp, &input_size);
	//array to store all the variable names of the various inputs
	char **input_names = (char **)malloc(sizeof(char*) * input_size);
	for(int i = 0; i < input_size; i++)
	{
		input_names[i] = (char *)malloc(sizeof(char) * 8);
		fscanf(circuit, "%s", input_names[i]);
	}

	fscanf(circuit, "%s %d", temp, &output_size);
	//array to store all the variable names of the various outputs
	char **output_names = (char **)malloc(sizeof(char*) * output_size);
	for(int i = 0; i < output_size; i++)
	{
		output_names[i] = (char *)malloc(sizeof(char) * 8);
		fscanf(circuit, "%s", output_names[i]);
	}
	
	//array to store all the names of the various temporary variables
	char **temp_names = (char**)malloc(sizeof(char*) * 50);
	for(int i = 0; i < 50; i++)
		temp_names[i] = (char*)malloc(sizeof(char) * 8);
	
	//stores all the gates in ascending order of working
	struct gate sequence[50];

	/* Loop to find and store all the temp variables, gates and their respective type and size
	 * Encoding used as follows:
	 * If a gate utilizes an:
	 * (1) Input variable : store (index from input_arr + 100)
	 * (2) Output variable: store (index from output_arr + 200)
	 * (3) Temporary variable : store (index from temp_arr + 300)
	 * and store in *params in the respective gate/struct
	 */
	while(!feof(circuit))
	{
		seq_size++;
		fscanf(circuit, "%s", temp);
		sequence[seq_size].kind = gateToNum(temp);
		int gate_type = sequence[seq_size].kind;

		if(gate_type == 7 || gate_type == 8)
		{
			fscanf(circuit, "%d", &sequence[seq_size].size);
			//number of inputs for a type 7 or 8 gate
			int size = sequence[seq_size].size;
			//2^size
			int powSize = power(size);
			//total number of general parameters associated with the gate
			int calc_size = size + powSize;
			if(gate_type == 8)
			{
				//+1 for output
				calc_size++;
				sequence[seq_size].params = (int *)malloc(sizeof(int) * calc_size);
				for(int i = 0; i < powSize + size; i++)
				{
					//joined the part to deal with selectors and input
					fscanf(circuit, "%s", temp);
					int input_index = index_return(input_names, temp, input_size);
					int temp_index = index_return(temp_names, temp, temp_size);

					if(input_index != -1)
						sequence[seq_size].params[i] = input_index + 100;
					else if(temp_index != -1)
						sequence[seq_size].params[i] = temp_index + 300;
					else
						sequence[seq_size].params[i] = OneOrZero(temp);
				}	
				fscanf(circuit, "%s", temp);
				int output_index = index_return(output_names, temp, output_size);
				int temp_index = index_return(temp_names, temp, temp_size);
				if(output_index != -1)
					sequence[seq_size].params[size + powSize] = output_index + 200;
				else if(temp_index != -1)
					sequence[seq_size].params[size + powSize] = temp_index + 300;
				else
				{
					strcpy(temp_names[temp_size], temp);
					sequence[seq_size].params[size + powSize] = (temp_size++) + 300;
				}
			}
			else
			{
				sequence[seq_size].params = (int *)malloc(sizeof(int) * calc_size);
				for(int i = 0; i < size; i++)
				{
					fscanf(circuit, "%s", temp);
					int input_index = index_return(input_names, temp, input_size);
					int temp_index = index_return(temp_names, temp, temp_size);
					if(input_index != -1)
						sequence[seq_size].params[i] = input_index + 100;
					else
						sequence[seq_size].params[i] = temp_index + 300;
				}
				for(int i = size; i < size + powSize; i++)
				{
					fscanf(circuit, "%s", temp);
					int output_index = index_return(output_names, temp, output_size);
					int temp_index = index_return(temp_names, temp, temp_size);
					if(output_index != -1)
						sequence[seq_size].params[i] = output_index + 200;
					else if(temp_index != -1)
						sequence[seq_size].params[i] = temp_index + 300;
					else if(strcmp(temp, "-") == 0)
						sequence[seq_size].params[i] = 999;
					else
					{
						strcpy(temp_names[temp_size], temp);
						sequence[seq_size].params[i] = (temp_size++) + 300;
					}

				}
			}
		}
		//NOt and PASS gate
		else if(gate_type == 5 || gate_type == 6)
		{
			sequence[seq_size].size = 2;
			sequence[seq_size].params = (int *)malloc(sizeof(int) * 2);
			for(int i = 0; i < 2; i++)
			{
				fscanf(circuit, "%s", temp);
				int input_index = index_return(input_names, temp, input_size);
				int output_index = index_return(output_names, temp, output_size);
				int temp_index = index_return(temp_names, temp, temp_size);

				if(input_index != -1)
					sequence[seq_size].params[i] = input_index + 100;
				else if(output_index != -1)
					sequence[seq_size].params[i] = output_index + 200;
				else if(temp_index != -1)
					sequence[seq_size].params[i] = temp_index + 300;
				else
				{
					strcpy(temp_names[temp_size], temp);
					sequence[seq_size].params[i] = (temp_size++) + 300;
				}
			}

		}
		//AND, OR, NOR, NAND and XOR gate
		else
		{
			sequence[seq_size].size = 3;
			sequence[seq_size].params = (int *)malloc(sizeof(int) * 3);
			for(int i = 0; i < 3; i++)
			{
				fscanf(circuit, "%s", temp);
				int input_index = index_return(input_names, temp, input_size);
				int output_index = index_return(output_names, temp, output_size);
				int temp_index = index_return(temp_names, temp, temp_size);

				if(input_index != -1)
					sequence[seq_size].params[i] = input_index + 100;
				else if(output_index != -1)
					sequence[seq_size].params[i] = output_index + 200;
				else if(temp_index != -1)
					sequence[seq_size].params[i] = temp_index + 300;
				else if((strcmp(temp, "0") == 0) || (strcmp(temp, "1") == 0))
					sequence[seq_size].params[i] = OneOrZero(temp);
				else
				{
					strcpy(temp_names[temp_size], temp);
					sequence[seq_size].params[i] = (temp_size++) + 300;
				}
			}
		}
	}
	
	
	int *input_arr = (int *)malloc(sizeof(int) * input_size);
	int *output_arr = (int *)malloc(sizeof(int) * output_size);
	int *temp_arr = (int *)malloc(sizeof(int) * temp_size);

	int rows = power(input_size);
	for(int i = 0; i < rows; i++)
	{
		toBinary(i, input_arr, input_size);
		for(int j = 0; j < seq_size; j++)
		{
			struct gate currentGate = sequence[j];
			//MULTIPLEXER
			if(currentGate.kind == 8)
			{
				int size = currentGate.size;
				int powSize = power(size);
				int *mul_temp = (int *)malloc(sizeof(int) * size);
				//loop to store all the selectors in mul_temp array
				for(int k = powSize; k < powSize + size; k++)
				{
					int input_mul_temp = currentGate.params[k];
					if(input_mul_temp < 200)
						mul_temp[k - powSize] = input_arr[input_mul_temp - 100];
					else
						 mul_temp[k - powSize] = temp_arr[input_mul_temp - 300];
				}
				//converting the selectors into decimal to figure out which input to choose
				int selected_index = toDecimal(mul_temp, size);
				int selected_input = currentGate.params[selected_index];
				int output_data;
				if(selected_input < 2)
					output_data = selected_input;
				else if(selected_input < 200)
					output_data = input_arr[selected_input - 100];
				else 
					output_data = temp_arr[selected_input - 300];
				int output_dest = currentGate.params[size + powSize];
				if(output_dest < 300)
					output_arr[output_dest - 200] = output_data;
				else
					temp_arr[output_dest - 300] = output_data;
				//free(mul_temp);
			}
			//DECODER
			else if(currentGate.kind == 7)
			{
				int size = currentGate.size;
				int powSize = power(size);
				int *dec_temp = (int *)malloc(sizeof(int) * size);
				//loop to store the input
				for(int k = 0; k < size; k++)
				{
					int input_dec_temp = currentGate.params[k];
					if(input_dec_temp < 200)
						dec_temp[k] = input_arr[input_dec_temp - 100];
					else
						dec_temp[k] = temp_arr[input_dec_temp - 300];
				}
				//index of output to make "1"
				int selected_output = size + toDecimal(dec_temp, size);
				//iterating through outputs to make them 1 or 0 accordingly
				for(int k = size; k < size + powSize; k++)
				{
					int current_output = currentGate.params[k];
					if(current_output < 300)
					{
						if(selected_output == k)
							output_arr[current_output - 200] = 1;
						else
							output_arr[current_output - 200] = 0;
					}
					else if(current_output < 400)
					{
						if(selected_output == k)
							temp_arr[current_output - 300] = 1;
						else
							temp_arr[current_output - 300] = 0;
					}
					else
					{	
					}
				}
				//free(dec_temp);
			}
			//PASS gate
			else if(currentGate.kind == 6)
			{
				int input_data = temp_arr[currentGate.params[0] - 300];
				output_arr[currentGate.params[1] - 200] = input_data;
			}
			//NOT gate
			else if(currentGate.kind == 5)
			{
				int input = currentGate.params[0];
				int input_data, output_data;
				if(input < 200)
					input_data = input_arr[input - 100];
				else
					input_data = temp_arr[input - 300];
				if(input_data == 1)
					output_data = 0;
				else
					output_data = 1;
				int output = currentGate.params[1];
				if(output < 300)
					output_arr[output - 200] = output_data;
				else
					temp_arr[output - 300] = output_data;
			}
			else
			{
				int *input_data = (int *)malloc(sizeof(int) * 3);
				int output_data;
				for(int k = 0; k < 2; k++)
				{
					int input_temp = currentGate.params[k];
					if(input_temp < 2)
						input_data[k] = input_temp;
					else if(input_temp < 200)
						input_data[k] = input_arr[input_temp - 100];
					else
						input_data[k] = temp_arr[input_temp - 300];
				}
				if(currentGate.kind == 4)
				{
					if(input_data[0] == input_data[1])
						output_data = 0;
					else
						output_data = 1;
				}
				else if(currentGate.kind == 3)
				{
					if(input_data[0] == 1 || input_data[1] == 1)
						output_data = 0;
					else
						output_data = 1;
				}
				else if(currentGate.kind == 2)
				{
					if(input_data[0] == 1 && input_data[1] ==1)
						output_data = 0;
					else
						output_data = 1;
				}
				else if(currentGate.kind == 1)
				{
					if(input_data[0] == 1 || input_data[1] == 1)
						output_data = 1;
					else
						output_data = 0;
				}
				else
				{
					if(input_data[0] == 1 && input_data[1] == 1)
						output_data = 1;
					else
						output_data = 0;
				}
				int selected_output = currentGate.params[2];
				if(selected_output < 300)
					output_arr[selected_output - 200] = output_data;
				else
					temp_arr[selected_output - 300] = output_data;
				//free(input_data);
			}
		}
		for(int k = 0; k < input_size; k++)
			printf("%d ", input_arr[k]);
		printf("|");
		for(int k = 0; k < output_size; k++)
			printf(" %d", output_arr[k]);
		printf("\n");
	}

}
