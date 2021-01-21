/* CS 211 PA1: bst
 * Created for: psp116
 */

#include <stdio.h>
#include <stdlib.h>

struct node{
	int data;
	struct node *left;
	struct node *right;
};
struct node *root = NULL;
void add(int d){
	struct node *new = (struct node*)malloc(sizeof(struct node));
	new->data = d;
	new->left = NULL;
	new->right = NULL;
	if(root == NULL){
		root = new;
		printf("inserted\n");
	}
	else{
		struct node *temp = root;
		while(1 > 0){
			if(d < temp->data){
				if(temp->left!=NULL)
					temp = temp->left;
				else{
					temp->left = new;
					printf("inserted\n");
					break;
				}
			}
			else if(d > temp->data){
				if(temp->right != NULL)
					temp = temp->right;
				else{
					temp->right = new;
					printf("inserted\n");
					break;
				}
			}
			else{
				printf("not inserted\n");
				break;
			}
		}
	}
}
int search(int n)
{
	struct node *temp = root;
	if(temp != NULL){
	while(1>0)
	{
		if(n>temp->data)
		{
			if(temp->right != NULL)
				temp = temp->right;
			else
			{
				return 0;
				break;
			}
		}
		else if(n<temp->data)
		{
			if(temp->left != NULL)
				temp = temp->left;
			else
			{
				return 0;
				break;
			}
		}
		else
		{
			return 1;
			break;
		}
	}
	}
	else
		return 0;
}
void delete(int n){
	struct node *temp = root;
	struct node *delete;
	int ori = -1;
	if(search(n) == 1){
		if(temp->data == n){
			ori = 0;
			delete = root;
		}
		else{
			while(1 > 0){
				if(n > temp->data)
				{
					if(temp->right->data == n)
					{
						delete = temp;
						ori = 1;
						break;
					}
					else
					{
						if(temp->right != NULL)
							temp = temp->right;
						else
							break;
					}
				}
				else if(n < temp->data)
				{
					if(temp->left->data == n)
					{
						delete = temp;
						ori = 2;
						break;
					}
					else
					{
						if(temp->left != NULL)
							temp = temp->left;
						else
							break;
					}
				}
			}
		}
		if(ori == 0)
		{
			if(delete->left == NULL && delete->right == NULL)
				root = NULL;
			else if(delete->left == NULL)
				root = delete->right;
			else if(delete->right == NULL)
				root = delete->left;
			else{
				temp = delete->left;
				while(temp->right->right != NULL)
					temp = temp->right;
				root->data = temp->right->data;
				temp->right = NULL;
			}
			printf("deleted\n");
		}
		else if(ori == 1)
		{
			if(delete->right->left == NULL && delete->right->right == NULL)
				delete->right = NULL;
			else if(delete->right->left == NULL)
				delete->right = delete->right->right;
			else if(delete->right->right == NULL)
				delete->right = delete->right->left;
			else{
				temp = delete->right->left;
				while(temp->right->right != NULL)
					temp = temp->right;
				delete->right->data = temp->right->data;
				temp->right = NULL;
			}
			printf("deleted\n");
		}
		else if(ori == 2)
		{
			if(delete->left->left == NULL && delete->left->right == NULL)
				delete->left = NULL;
			else if(delete->left->left == NULL)
				delete->left = delete->left->right;
			else if(delete->left->right == NULL)
				delete->left = delete->left->left;
			else{
				temp = delete->left->left;
				while(temp->right->right != NULL)
					temp = temp->right;
				delete->left->data = temp->right->data;
				temp->right = NULL;
			}
			printf("deleted\n");
		}
		else
		{
			printf("absent\n");
		}
	}
	else
		printf("absent\n");		
}

void display(struct node *temp){
	if(temp!=NULL)
	{
		printf("(");
		display(temp->left);
		printf("%d", temp->data);
		display(temp->right);
		printf(")");
	}
	
}
int main(int argc, char **argv)
{
	char ch;
	int d;
	while(scanf("%c ", &ch)!=EOF)
	{
		if(ch == 'p'){
			display(root);
			printf("\n");
			continue;
		}
		scanf("%d", &d);
		if(ch == 'i')
			add(d);
		if(ch == 'd')
			delete(d);
		if(ch == 's'){
			if(search(d) == 1)
				printf("present\n");
			else
				printf("absent\n");
		}
	}
		
}

