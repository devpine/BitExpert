#define MAX 50
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#pragma warning(disable:4996)

struct node {
	int key;
	 node *link;
};

struct node *addlist( node *, int);
void listprint( node *);
node *sort(node *);
int count = 0;

int main()
{
	node *root;
	int num[MAX];
	int i=0;

	root = NULL;

	while (scanf("%d", num + i++))
	{
		if (num[i - 1] == 0)
			break;
		root = addlist(root, num[i-1]);
		count++;
	}
	listprint(sort(root));
	return 0;
}

node *sort(node *p)
{
	int i, j;
	node **arr, *temp;
	arr = (node**)malloc(count * sizeof(node*));

	if (count <= 0) {
		printf("arr empty\n");
		return 0;
	}

	for (i = 0; i < count; i++) {
		arr[i] = p;
		p = p->link;
	}
	for (i = 0; i < count - 1; i++)
	{
		for (j = i + 1; j < count; j++)
		{
			if (arr[i]->key <= arr[j]->key) {
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
	}
	for (temp = arr[0], p = temp, i = 1; i < count; i++, p = p->link)
		p->link = arr[i];
		p->link = NULL;
	return *arr;
}


struct node *addlist(struct node *p, int w)
{
	if (p == NULL)
	{
		p = (struct node *)malloc(sizeof(struct node));
		p->key = w;
		p->link = NULL;
	}
	else
		p->link = addlist(p->link, w);
	return p;
}

void listprint(struct node *p)
{
	while (p != NULL)
	{
		printf("%d ", p->key);
		p = p->link;
	}
}

