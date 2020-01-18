#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable : 4996)

struct node {
	int item;
	struct node *llink;
	struct node *rlink;
};

void addq(struct node *, int);
void deleteq(struct node *);
void listprint(struct node *);

int main()
{
	struct node *head;
	int cond, item;

	head = (struct node *)malloc(sizeof(struct node)); // 더미노드
	head->llink = head->rlink = head; // 초기화

	while (1)
	{
		printf("[1:insert   2:delete   3:output   4:exit]\n");
		scanf("%d", &cond);
		if (cond == 1)
		{
			printf("Input Item\n");
			scanf("%d", &item);
			addq(head, item);
		}
		else if (cond == 2)
			deleteq(head);
		else if (cond == 3)
			listprint(head);
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

void listprint(node *head) {
	node temp = *head;

	while (temp.llink != head) {
		temp = *(temp.llink);
		printf("%d->", temp.item);
		if (temp.llink == temp.rlink) {
			break;
		}
	}
	printf("\n");
}

void addq(struct node *head, int item)
{
	node *temp = (node *)malloc(sizeof(node));
	temp->item = item;

		temp->llink = head;
		temp->rlink = head->rlink;
		head->rlink->llink = temp;
		head->rlink = temp;
		return;

}
void deleteq(node* head) {
	if (head->llink == head && head->rlink == head)
	{
		printf("큐가 비어있습니다.\n");
		return;
	}
	head->llink = head->llink->llink;
	head->llink->llink->rlink = head;
}
