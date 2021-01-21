/* CS 211 PA1: list
 * Created for: psp116
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

struct node{
	int data;
	struct node *next;
};
struct node head;
int size = 0;
void order()
{
	struct node *temp;
	temp = &head;
	int tem;
	for(int j = 1; j < size; j++)
	{
		temp = &head;
		for(int i = 1; i < size; i++)
		{
			if((temp->data)	> (temp->next->data))
			{
				tem = temp->data;
				temp->data = temp->next->data;
				temp->next->data = tem;	
			}
			temp = (temp->next);
		}
	}
}
void display()
{
	struct node *temp;
	temp = &head;
	printf("%d :", size);
	if(size >= 1)
		printf(" %d", temp->data);
	for(int i = 1; i < size; i++)
	{
	//	printf(" ");
		temp = (temp->next);
		printf(" %d", (temp->data));
	}
	printf("\n");	
}
void add(int d)
{
	struct node *new = (struct node*)malloc(sizeof(struct node));
	new->data = d;
	new->next = NULL;
	int cnt = 0;
	if(size == 0)
	{
		head = *new;
		size++;
	}
	else
	{
		struct node *temp;
		temp = &head;
		if(temp->data == d)
			cnt = -1;
		for(int i = 1; i < size; i++)
		{
			if(temp->data == d)
				cnt = -1;
			temp = (temp->next);
		}
		if(cnt != -1)
		{
			temp->next = new;
			size++;
		}
	}
	order();
	display();
}
void delete(int n)
{
	struct node *temp;
	temp = &head;
	if(temp->data == n)
	{
		if(temp->next != NULL)
			head = *(temp->next);
		size--;
	}
	else
	{
		for(int i = 1; i < size; i++)
		{
			if(temp->next->data == n)
			{
				if(i == size -1)
					temp->next = NULL;
				else
					temp->next = temp->next->next;
				
				size--;
			}
			temp= temp->next;
		}
	}
	order();
	display();
}	
int main(int argc, char **argv)
{
	char ch;
	int num;
	while((scanf("%c %d", &ch, &num)) != EOF){
		if(ch == 'i')
			add(num);
		if(ch == 'd')
			delete(num);
	}	
}
