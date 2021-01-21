/* CS 211 PA1: palindrome
 * Created for: psp116
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
int main(int argc, char **argv)
{
	int i, j, len = 0;
	for(i = 1; i < argc; i++)
	{	
		len += strlen(argv[i]);
	}
	char *str = malloc(len);
	int cnt = 0, tempLen = 0;

	for(i = 1; i < argc; i++)
	{
		tempLen = strlen(argv[i]);
		for(j = 0; j < tempLen; j++)
		{
			if(isalpha(argv[i][j]))
				str[cnt++] = tolower(argv[i][j]);
		}
	}
	int start = 0, end = cnt - 1;
	cnt = 1;
	do
	{
		if(str[start++]!= str[end--])
			cnt = 0;
	
	}
	while((start == end) || (start == end -1));
	if(cnt==1)
		printf("yes\n");
	else
		printf("no\n");
}	
