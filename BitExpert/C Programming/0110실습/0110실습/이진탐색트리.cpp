#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)
/*
if(deleted->left)
{
if(deleted == parent) // ���� subtree���� ����
	parent->left = move->left;
else
	parent->right = move->left;
}
else if(deleted->right) // ������ subtree���� ����

//�� ���� ��ܸ� ��� �����ϰ��

else//�ܸ���� ������ ���

*/
struct tnode {
	int item;
	struct tnode *left;
	struct tnode *right;
};

struct tnode *addtree(struct tnode *, int);
void deletetree(struct tnode **, int);
void treeprint(struct tnode *);

int main()
{
	struct tnode *root;
	int cond, num;
	root = NULL;

	while (1)
	{
		printf("[1 : ����   2 : ����   3 : ���   4 : ����]\n");
		scanf("%d", &cond);
		if (cond == 1)
		{
			printf("Add Number\n");
			scanf("%d", &num);
			root = addtree(root, num);
		}
		else if (cond == 2)
		{
			printf("Delete Number\n");
			scanf("%d", &num);
			deletetree(&root, num);
		}
		else if (cond == 3)
			treeprint(root);
		else if (cond == 4)
			break;
		else
		{
			printf("Wrong Input\n");
			exit(1);
		}
	}
	return 0;
}

struct tnode *addtree(struct tnode *p, int num)
{
	if (p == NULL)
	{
		p = (struct tnode *)malloc(sizeof(struct tnode));
		p->item = num;
		p->left = p->right = NULL;
	}
	else if (num == p->item)
		printf("�����ϴ� ���� �Դϴ�.\n");
	else if (num < p->item)
		p->left = addtree(p->left, num);
	else
		p->right = addtree(p->right, num);

	return p;
}

void treeprint(struct tnode *p)
{
	if (p != NULL)
	{
		treeprint(p->left);
		printf("%d\n", p->item);
		treeprint(p->right);
	}
}

void deletetree(struct tnode **p, int num)
{
	
	tnode* parent = *p;
	//tnode* move = ((*p)->item > num) ? (*p)->left : (*p)->right;
	tnode* move = (*p)->right;
	tnode* deleted;


	do
	{
		if (move->item == num)
			break;

		parent = move;
		move = (parent->item > num) ? parent->left : parent->right; 		
	}while (move != NULL);

	if (move == NULL)
	{
		printf("������ ��尡 �����ϴ�.");
		return;
	}
	
	
	deleted = move; 

	parent = deleted;
	move = parent->left ? parent->left : parent;

	while (move->right != NULL)

	{
		parent = move;
		move = move->right;
	}
	
	if (deleted->left)
	{
		if (deleted == parent)
			parent->left = move->left;
		else
			parent->right = move->left;
	}
	else if (deleted->right)
	{
		if (parent->left == move)
			parent->left = NULL;
		else
			parent->right = NULL;
	}
	else
	{
		if (parent->item > num)
			parent->left = NULL;
		else
			parent->right = NULL;
	}
	
	deleted->item = move->item;

	deleted = move;

	delete deleted;
	deleted = NULL;
}