#include <stdio.h>
#pragma warning(disable:4996)
#define MAX_VERTICES 6

int cost[][MAX_VERTICES] =
{ {0,50,10,1000,45,1000},
{1000,0,15,1000,10,1000},
{20,1000,0,15,1000,1000},
{1000,20,1000,0,35,1000},
{1000,1000,1000,30,0,1000},
{1000,1000,1000,3,1000,0} };

int distance[MAX_VERTICES];
short int found[MAX_VERTICES];
int n = MAX_VERTICES;

void shortestpath(int ,int);
int choose(int[], int, short int[]);
void printpath(int, int);

int main()
{
	int start, destination;
	printf("Input start point and destination point : ");
	scanf("%d %d", &start, &destination);
	if (start > MAX_VERTICES || destination > MAX_VERTICES)
		printf("Length error\n");
	
	else
	{
		printpath(start,destination);
	}
		
	return 0;
}

void printpath(int start, int destination)
{
	int i;
	int result=0;

	shortestpath(start, destination);

	/*for (i = 0; i <= destination; i++)
	{
		if (found[i] == true)
		{
			result += distance[i];
			printf("%d ", i);
		}	
	}
	printf("%d\n", result);*/
	printf("%d에서 %d까지의 최단거리 %d", start, destination, distance[destination]);
}

void shortestpath(int v, int destination)
{
	int i, u, w;
	for (i = 0; i < n +1; i++) {
		found[i] = false;
		distance[i] = cost[v][i];
	}

	found[v] = true;
	distance[v] = 0;

	for (i = 0; i < n - 2 ; i++) {
		u = choose(distance, n, found);

		found[u] = true;
	

		for (w = 0; w < n + 1 ; w++)
			if (!found[w])
				if (distance[u] + cost[u][w] < distance[w])
					distance[w] = distance[u] + cost[u][w];
	}
}

int choose(int distance[], int n, short int found[]) 
{
	int i, min, minpos;
	min = 9999;
	minpos = -1;

	for (i = 0; i < n + 1 ; i++) {
		if (distance[i] < min && !found[i]) {
			min = distance[i];
			minpos = i;
			printf("%d ", minpos);
		}
	}
	return minpos;
}

