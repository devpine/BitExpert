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
		printf("[1]삽입 [2]삭제 [3]변경 [4]출력 [5]종료\n");
		scanf("%d", &cond);

		if (cond == 1) {
			printf("값을 입력하세요.\n");
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
			printf("잘못된 키 입력.\n");
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
	temp = list[root]; //temp에 (n/2 = 마지막 노드의 부모)의 주소를 줌 
	rootkey = list[root].key; // rootkey에  n/2의 값을 줌
	child = 2 * root; // child = 왼쪽 자식
	while (child <= n)//왼쪽 자식이 n보다 작거나 같으면 반복문 실행
	{
		//오른쪽 자식이 존재할때, 왼쪽자식 값이 오른쪽 자식 값보다 작으면 오른쪽으로 이동
		if ((child < n) && (list[child].key < list[child + 1].key))
			child++;
		//부모의 값이 자식의 값보다 크면 빠져나옴
		if (rootkey > list[child].key)
			break;
		//부모가 자식보다 값이 작으면, 부모에 자식값을 넣어주고,
		//혹시 자식이 더 있나 확인(child*=2;)
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
