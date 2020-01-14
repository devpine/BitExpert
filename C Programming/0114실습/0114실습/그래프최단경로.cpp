#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)

#define MAX_VERTICES 6
#define TRUE 1
#define FALSE 0

int cost[][MAX_VERTICES] =
{ {0,50,10,1000,45,1000},
{1000,0,15,1000,10,1000},
{20,1000,0,15,1000,1000},
{1000,20,1000,0,35,1000},
{1000,1000,1000,30,0,1000},
{1000,1000,1000,3,1000,0} };

int distance[MAX_VERTICES];
short int found[MAX_VERTICES];
int path[MAX_VERTICES];
//int n = MAX_VERTICES;

void shortestpath(int ,int);
int choose(int[], int, short int[]);
void print_path(int, int);

int main()
{
	int start, destination;
	printf("시작점 도착점 입력 : ");
	scanf("%d %d", &start, &destination);

	shortestpath(start, MAX_VERTICES);

	printf("거리 : %d \n", distance[destination]);
	print_path(start, destination);
		
	return 0;
}

void print_path(int start, int destination)
{
	if (path[destination] != start)
		print_path(start, path[destination]);
	printf("<%d -> %d> ", path[destination], destination);

}

void shortestpath(int v, int n)
{
	int i, u, w;

	for (i = 0; i < n ; i++) {
		path[i] = v;
		found[i] = FALSE;
		distance[i] = cost[v][i];
	}

	found[v] = TRUE;
	distance[v] = TRUE;

	for (i = 0; i < n - 1 ; i++) {
		u = choose(distance, n, found);

		found[u] = true;
	

		for (w = 0; w < n  ; w++)
			if (!found[w])
				if (distance[u] + cost[u][w] < distance[w]) {
					distance[w] = distance[u] + cost[u][w];
					path[w] = u;
				}
	}
}

int choose(int distance[], int n, short int found[]) 
{
	int i, min, minpos;
	min = INT_MAX;
	minpos = -1;

	for (i = 0; i < n  ; i++) {
		if (distance[i] < min && !found[i]) {
			min = distance[i];
			minpos = i;
		}
	}
	return minpos;
}

