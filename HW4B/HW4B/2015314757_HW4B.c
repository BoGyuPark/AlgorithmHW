#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct MyStruct
{
	int priority;
	char name[20];
}Info;

void DFS(int i);
int matrix[100][100] = { 0, };
int visited[100], count = 0;

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
	Info info[100];
	
	char *ptr = strtok(inputString, "/");
	int i = 0;
	while (ptr != NULL)
	{
		info[i].priority = 1;
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
		if (indegree == count)
			printf("Stupid David!\n");

	}
	
	for (int x = 0; x < pos; x++) {
		DFS(V[x]);
	}


}

void DFS(int i)
{
	int j;
	visited[i] = 1;
	int distance = 0;
	printf(" %d->", i + 1);
	for (j = 0; j < count; j++)
	{
		if (matrix[i][j] == 1 && visited[j] == 0)
			DFS(j);
	}
}