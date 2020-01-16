#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)
#define SWAP(x,y,t) ((t)=(x),(x)=(y),(y)=(t))

struct element {
	int key;
};

void adjust(element[], int, int);
void heapsort(element [], int);
element *addheap(element[], int,int);
void heapprint(element [], int);

int main()
{
	int cond,key,n=0;
	element root[100] = { NULL };

	while (1)
	{
		printf("[1]���� [2]���� [3]���� [4]��� [5]����\n");
		scanf("%d", &cond);

		if (cond == 1) {
			printf("���� �Է��ϼ���.\n");
			scanf("%d", &key);
			addheap(root, key, ++n);
		}
		else if (cond == 2) {

		}
		else if (cond == 3) {

		}
		else if (cond == 4) {
			heapprint(root, n);
		}
		else if (cond == 5)
			break;
		else
		{
			printf("�߸��� Ű �Է�.\n");
			exit(1);
		}
	}
	
}

element *addheap(element list[], int key, int n)
{

	list[n].key = key;
	//adjust(list,n,n);
	heapsort(list, n);

	return list;
}

void heapprint(element list[], int n)
{
	int i;
	for (i=1; i <= n; i++)
	{
		printf("%d ", (list[i].key));
	}
	printf("\n");
}
void adjust(element list[], int root, int n)
{
	int child, rootkey;
	element temp; 
	temp = list[root]; //temp�� (n/2 = ������ ����� �θ�)�� �ּҸ� �� 
	rootkey = list[root].key; // rootkey��  n/2�� ���� ��
	child = 2 * root; // child = ���� �ڽ�
	while (child <= n)//���� �ڽ��� n���� �۰ų� ������ �ݺ��� ����
	{
		//������ �ڽ��� �����Ҷ�, �����ڽ� ���� ������ �ڽ� ������ ������ ���������� �̵�
		if ((child < n) && (list[child].key < list[child + 1].key))
			child++;
		//�θ��� ���� �ڽ��� ������ ũ�� ��������
		if (rootkey > list[child].key)
			break;
		//�θ� �ڽĺ��� ���� ������, �θ� �ڽİ��� �־��ְ�,
		//Ȥ�� �ڽ��� �� �ֳ� Ȯ��(child*=2;)
		else
		{
			list[child / 2] = list[child];
			child *= 2;
		}
	}
	
	list[child / 2] = temp;
}

void heapsort(element list[], int n)
{
	int i, j;
	element temp;

	for (i = n / 2; i > 0; i--)
		adjust(list, i, n);
	for (i = n - 1; i > 0; i--)
		SWAP(list[1], list[i + 1], temp);
	adjust(list, 1, i);
}
