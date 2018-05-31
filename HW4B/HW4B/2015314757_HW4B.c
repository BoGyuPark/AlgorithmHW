#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 100  

typedef struct MyStruct
{
	int parent;
	int distance;
	char name[20];
}Info;

void BFS(int v);
int rear, front;
int matrix[MAX][MAX] = { 0, };
int visited[MAX], count = 0;
int queue[MAX];

Info info[100];

main()
{
	int N = 0, C = 0;		// 1<= N <100 , 1<= C < 1000 , 1<= length of animal name < 20
	char inputString[2000];
	int len = 0;

	//N�� C �� �б�
	scanf("%d %d", &N, &C);
	getchar();

	//���� �Է¹ޱ�
	fgets(inputString, strlen(inputString), stdin);

	//String ���� \n �����ϱ�
	inputString[strlen(inputString) - 1] = '\0';

	/*len = strlen(inputString);
	printf("strtok ���� \n");*/

	// '/'�� �����Ͽ� �� ����ü�� Name�ְ� �ʱⰪ priority = 1 �� ����

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

	////�� Name�� ����� �ԷµǾ��� üũ
	//for (int j = 0; j < count; j++) {
	//	printf("%s\n", info[j].name);
	//}

	// C�� �Է¹޴´�. -> adjacency Matrix�� �����Ѵ�.
	while (C) {
		char tempString[40] = { 0, };
		fgets(tempString, 40, stdin);
		tempString[strlen(tempString) - 1] = '\0';

		// '/' �������� ���� temp1�� �ڿ� temp2�� �����Ѵ�.
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

	//Matrix Ȯ���� ���� print
	for (int b = 0; b < count; b++) {
		for (int d = 0; d < count; d++) {
			printf("%d ", matrix[b][d]);
		}
		printf("\n");
	}

	//indegree�� 0�� ��츦 ã�´�.
	//��� V�� indegree�� 0�̸� cycle�� ����Ƿ� Stupid David! ����Ѵ�.
	int indegree = 0;
	//V�迭�� indegree�� 0�� ���� �ε����� �����Ѵ�. �ʱⰪ -1�� �����Ѵ�.
	int V[100];
	for (int q = 0; q < 100; q++)
		V[q] = -1;


	int pos = 0;
	for (int b = 0; b < count; b++) {
		int sum = 0;
		queue[b] = -1;
		for (int d = 0; d < count; d++) {
			//�� col�� ����� ���� indegree ���̴�.
			sum += matrix[d][b];
		}
		if (sum == 0) {
			V[pos] = b;
			pos++;
			printf("matrix %d ���� indegree�� 0�̴�\n", b);
		}
		else {
			indegree++;
		}

		//cycle�� ����� ���
		if (indegree == count) {
			printf("Stupid David!\n");
			return 0;
		}

	}

	for (int x = 0; x < pos; x++) {
		BFS(V[x]);
	}

	// info�迭 lexicographically order ����
	for (int w = 0; w < count - 1; ++w) 
	{
		for (int e = w + 1; e < count; ++e) 
		{
			if (strcmp(info[w].name, info[e].name) > 0)
			{
				Info temp;
				temp = info[w];
				info[w] = info[e];
				info[e] = temp;
				
			}
		}
	}

	// info�迭�� distance ������������ ����
	for (int w = 0; w < count - 1; ++w)
	{
		for (int e = w + 1; e < count; ++e)
		{
			if (info[w].distance>info[e].distance)
			{
				Info temp;
				temp = info[w];
				info[w] = info[e];
				info[e] = temp;

			}
		}
	}
	



	for (int i = 0; i < count; i++) {
		printf("%d %s\n", info[i].distance, info[i].name);
	}


}

void BFS(int v)
{
	int i;
	visited[v] = 1; // ���� v�� �湮�ߴٰ� ǥ��
	//printf("%d���� ����\n", v);

	queue[rear++] = v; // ť�� v�� �����ϰ� �Ĵ��� 1 ������Ŵ

	while (front < rear) // �Ĵ��� ���ܰ� ���ų� ������ ���� Ż��
	{
		// ť�� ù��°�� �ִ� �����͸� �����ϰ� ���ܵ� ���� ��������, ���� 1 ����
		v = queue[front++];
		for (i = 0; i < count; i++)
		{
			// ���� v�� ���� i�� ������, ���� i�� �湮���� ���� ������ ���
			if (matrix[v][i] == 1)
			{
				visited[i] = 1; // ���� i�� �湮�ߴٰ� ǥ��
				if (info[i].distance < info[v].distance + 1) {
					info[i].parent = v;
					info[i].distance = info[v].distance + 1;
				}
				//printf("%d���� %d�� �̵�\n", v, i);
				queue[rear++] = i; // ť�� i�� �����ϰ� �Ĵ��� 1 ������Ŵ
			}
		}
	}
}