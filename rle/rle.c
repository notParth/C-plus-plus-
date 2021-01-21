/* CS 211 PA1: rle
 * Created for: psp116
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int reverseNum(int num)
{
	int place = 1;
	int temp = num, newNum = 0;
	while(temp > 0)
	{
		place *= 10;
		temp /= 10;
	}
	temp = num;
	while(temp > 0)
	{
		place /= 10;
		newNum += ((temp % 10) * place );
		temp /= 10;
	}
	return newNum;
}
int main(int argc, char **argv)
{
	if(argv[1][0] != '\0')
	{
		int inptLen = strlen(argv[1]);
		char *str = malloc(inptLen * 2);
		int i = -1, len  = 0, cnt = 0;
		char temp = argv[1][0];
		while(i < inptLen)
		{
			i++;
			while(temp == argv[1][i] && i < inptLen)
			{	
				cnt++;
				i++;
			}
			if(isdigit(argv[1][i]))
			{
				len = -1;
				break;	
			}
			str[len++] = argv[1][i-1];
			if(cnt>9)
			{
				cnt = reverseNum(cnt);
				while(cnt > 0)
				{
					str[len++] ='0' + (cnt % 10);
					cnt = cnt / 10;
				}
			}
			else
				str[len++] = '0'+ cnt;
			cnt = 0;
			cnt++;
			temp = argv[1][i];
		}	
		
		if(len == -1)
			printf("error\n");
		else if(len > inptLen)
			printf("%s\n", argv[1]);
		else
		{	
			str[len] = '\0';
			printf("%s\n", str);
		}		
	}
}
