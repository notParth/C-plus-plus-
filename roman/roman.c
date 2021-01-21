/* CS 211 PA1: roman
 * Created for: psp116
 */

#include <stdio.h>
#include <stdlib.h>

void decimal_to_roman(int num)
{
	int i;
	if(num >= 900)
	{
		if(num == 900)
			printf("C");
		for (i = num; i > 0 ; i = i - 1000)
			printf("M");
	}
	else if(num>=90 && num<900)
	{
		if(num >= 500)
		{
			printf("D");
			num = num - 500;
		}
		if(num == 400)
		{
			printf("CD");
			num = 0;
		}
		if(num == 90)
			printf("X");
		for(i = num; i > 0  ; i = i -100)
			printf("C");
	}
 	else if(num>=9 && num<90)
	{
		if(num >= 50)
		{
			printf("L");
			num = num - 50;
		}
		if(num == 40)
		{
			printf("XL");
			num = 0;
		}
		if(num == 9)
			printf("I");
		for(i = num; i > 0; i = i - 10)
			printf("X");
	}
	else
	{
		if(num >= 5)
		{
			printf("V");
			num = num - 5;
		}
		if(num == 4)
		{
			printf("IV");
			num = 0;
		}
		for(i = num; i > 0; i = i - 1)
			printf("I");
	}
}
void calculate_place_number(int num, int place)
{
	int rem, temp_num = 0;
	while(num>0)
	{
		rem = num % 10;
		temp_num = rem * place;
		decimal_to_roman(temp_num);
		place = place / 10;
		num = num / 10;
	}
}

int main(int argc, char **argv)
{
	int number = atoi(argv[1]);
 	int temp_num = number;
        int num_rev = 0;
        int max_place = 1, temp_place = 0;
        while(temp_num > 0)
        {
                max_place = max_place * 10;
                temp_num = temp_num / 10;
        }
        temp_num = number;
        temp_place = max_place;
        while(temp_num > 0)
        {
		num_rev = num_rev + ((temp_num % 10)*temp_place);
		temp_num = temp_num / 10;     
		temp_place = temp_place / 10;
	}
	calculate_place_number(num_rev, max_place);   
	printf("\n");
}
