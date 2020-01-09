#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>



struct node {
	char *name;
	struct node *link;
};
int getname(char *);
struct node *addlist(struct node *, char *);
struct node *invert(struct node *);
char *namecopy(char *);
void listprint(struct node *);

int main()
{
	struct node *root;
	char name[80];
	root = NULL;
	while (getname(name) != EOF)
		root = addlist(root, name);
	listprint(root);
	//invert
	root = invert(root);
	printf("-----invert-----\n");
	listprint(root);
	return 0;
}

int getname(char *pname)
{
	int i = 0;	char c;
	while (((c = getchar()) != '\n') && c != EOF)
		*(pname + i++) = c;
	if (c == '\n')
		*(pname + i) = '\0';
	if (c == EOF)
		*pname = EOF;
	return *pname;
}

struct node *addlist(struct node *p, char *w)
{
	if (p == NULL)
	{
		p = (struct node *)malloc(sizeof(struct node));
		p->name = namecopy(w);
		p->link = NULL;
	}
	else
		p->link = addlist(p->link, w);
	return p;
}

struct node *invert(struct node *lead)
{
	struct node *middle, *trail;
	middle = NULL;

	while (lead)
	{
		trail = middle;
		middle = lead;
		lead = lead->link;
		middle->link = trail;
	}
	return middle;
}

char *namecopy(char *s)
{
	char *p;
	p = (char *)malloc(strlen(s) + 1);
	strcpy(p, s);

	return p;
}

void listprint(struct node *p)
{
	while (p != NULL)
	{
		printf("%s\n", p->name);
		p = p->link;
	}
}
