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

	//N과 C 값 읽기
	scanf("%d %d", &N, &C);
	getchar();

	//한줄 입력받기
	fgets(inputString, strlen(inputString), stdin);

	//String 끝에 \n 제거하기
	inputString[strlen(inputString) - 1] = '\0';

	/*len = strlen(inputString);
	printf("strtok 사용시 \n");*/

	// '/'로 구분하여 각 구조체에 Name넣고 초기값 priority = 1 로 세팅

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

	////각 Name이 제대로 입력되었나 체크
	//for (int j = 0; j < count; j++) {
	//	printf("%s\n", info[j].name);
	//}

	// C번 입력받는다. -> adjacency Matrix를 세팅한다.
	while (C) {
		char tempString[40] = { 0, };
		fgets(tempString, 40, stdin);
		tempString[strlen(tempString) - 1] = '\0';

		// '/' 기준으로 앞의 temp1을 뒤에 temp2를 대입한다.
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

	//Matrix 확인을 위한 print
	for (int b = 0; b < count; b++) {
		for (int d = 0; d < count; d++) {
			printf("%d ", matrix[b][d]);
		}
		printf("\n");
	}

	//indegree가 0인 경우를 찾는다.
	//모든 V가 indegree가 0이면 cycle이 생기므로 Stupid David! 출력한다.
	int indegree = 0;
	//V배열은 indegree가 0인 열의 인덱스를 저장한다. 초기값 -1로 세팅한다.
	int V[100];
	for (int q = 0; q < 100; q++)
		V[q] = -1;


	int pos = 0;
	for (int b = 0; b < count; b++) {
		int sum = 0;
		queue[b] = -1;
		for (int d = 0; d < count; d++) {
			//각 col의 요소의 합이 indegree 값이다.
			sum += matrix[d][b];
		}
		if (sum == 0) {
			V[pos] = b;
			pos++;
			printf("matrix %d 열은 indegree가 0이다\n", b);
		}
		else {
			indegree++;
		}

		//cycle이 생기는 경우
		if (indegree == count) {
			printf("Stupid David!\n");
			return 0;
		}

	}

	for (int x = 0; x < pos; x++) {
		BFS(V[x]);
	}

	// info배열 lexicographically order 정렬
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

	// info배열을 distance 오름차순으로 정렬
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
	visited[v] = 1; // 정점 v를 방문했다고 표시
	//printf("%d에서 시작\n", v);

	queue[rear++] = v; // 큐에 v를 삽입하고 후단을 1 증가시킴

	while (front < rear) // 후단이 전단과 같거나 작으면 루프 탈출
	{
		// 큐의 첫번째에 있는 데이터를 제외하고 제외된 값을 가져오며, 전단 1 증가
		v = queue[front++];
		for (i = 0; i < count; i++)
		{
			// 정점 v와 정점 i가 만나고, 정점 i를 방문하지 않은 상태일 경우
			if (matrix[v][i] == 1)
			{
				visited[i] = 1; // 정점 i를 방문했다고 표시
				if (info[i].distance < info[v].distance + 1) {
					info[i].parent = v;
					info[i].distance = info[v].distance + 1;
				}
				//printf("%d에서 %d로 이동\n", v, i);
				queue[rear++] = i; // 큐에 i를 삽입하고 후단을 1 증가시킴
			}
		}
	}
}