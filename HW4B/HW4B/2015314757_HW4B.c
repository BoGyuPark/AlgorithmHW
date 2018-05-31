#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 101

typedef struct MyStruct
{
	int parent;
	int distance;
	char name[20];
}Info;

void BFS(int v);
int rear, front, count = 0;
int matrix[MAX][MAX] = { 0, };
int queue[MAX];

Info info[MAX];

main()
{
	// 1<= N <100 , 1<= C < 1000 , 1<= length of animal name < 20
	int N = 0, C = 0;		
	char inputString[2000];
	int len = 0;

	//scan N,C 
	scanf("%d %d", &N, &C);
	getchar();

	//Get oneline
	fgets(inputString, strlen(inputString), stdin);

	//Remove \n at the end of a String
	inputString[strlen(inputString) - 1] = '\0';

	// input'Name' for each structure separated by '/', and initialize distance and parent values.
	char *ptr = strtok(inputString, "/");
	int i = 0;
	while (ptr != NULL)
	{
		info[i].distance = 1;
		info[i].parent = -1;
		strcpy(info[i].name, ptr);
		//printf("%s\n", ptr);
		ptr = strtok(NULL, "/");
		count++; i++;
	}

	// Input C times and set adjacency Matrix
	while (C) {
		char tempString[40] = { 0, };
		fgets(tempString, 40, stdin);
		tempString[strlen(tempString) - 1] = '\0';

		//After dividing by slash, assign the first part to temp1 and the second part to temp2.
		char *pptr = strtok(tempString, "/");
		char temp1[20], temp2[20];
		strcpy(temp1, pptr);
		pptr = strtok(NULL, "/");
		strcpy(temp2, pptr);
		int row = 0, col = 0;

		for (int j = 0; j < count; j++) {
			if (!strcmp(temp1, info[j].name)) {
				row = j;
			}
			if (!strcmp(temp2, info[j].name))
				col = j;
		}
		matrix[row][col] = 1;
		C--;
	}

	
	//The V array stores the index of the column with indegree = 0. The initial value is set to - 1.
	int V[MAX];
	for (int q = 0; q < MAX; q++)
		V[q] = -1;

	//Finds if indegree is zero.
	//If all V's have an indegree greater than 1, a cycle will occur, so print "Stupid David!".
	int indegree = 0;
	int pos = 0;
	for (int b = 0; b < count; b++) {
		int indegreeSum = 0;
		queue[b] = -1;
		for (int d = 0; d < count; d++) {
			//The sum of the elements in each column is indegreeSum.
			indegreeSum += matrix[d][b];
		}
		if (indegreeSum == 0) {
			V[pos] = b;
			pos++;
		}
		else {
			indegree++;
		}

		//When a cycle occurs
		if (indegree == count) {
			printf("Stupid David!\n");
			return 0;
		}
	}

	//Apply a vertex with indegree = 0 to the BFS function.
	for (int x = 0; x < pos; x++) {
		BFS(V[x]);
	}

	Info temp;
	//Sort the info array lexicographically.
	for (int i = count - 1; i>0; i--)
	{
		for (int j = 0; j < i; j++)
		{
			if (strcmp(info[j].name, info[j+1].name) > 0)
			{
				temp = info[j];
				info[j] = info[j+1];
				info[j+1] = temp;
			}
		}
	}

	//Sort the info array in ascending distance order.(Bubble Sort, stable)
	for (int i = count - 1; i>0; i--)
	{
		for (int j = 0; j < i; j++)
		{
			if (info[j].distance>info[j+1].distance)
			{
				temp = info[j];
				info[j] = info[j+1];
				info[j+1] = temp;
			}
		}
	}
	
	//Print output
	for (int i = 0; i < count; i++) {
		printf("%d %s\n", info[i].distance, info[i].name);
	}


}

void BFS(int v)
{
	int i;
	queue[rear++] = v; 

	while (front < rear) 
	{
		v = queue[front++];
		for (i = 0; i < count; i++)
		{
			//Regardless of the vertex you visited, run it and choose the larger distance of vertex
			if (matrix[v][i] == 1)
			{
				if (info[i].distance < info[v].distance + 1) {
					info[i].parent = v;
					info[i].distance = info[v].distance + 1;
				}
				queue[rear++] = i; 
			}
		}
	}
}