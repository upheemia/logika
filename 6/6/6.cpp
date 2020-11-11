#include <stdlib.h>
#include <ctime>
#include <locale.h>
#include <queue>
#include <iostream>
#include <iomanip>
#include <windows.h>

using namespace std;

typedef struct Node {
	int ver;
	struct Node* next;
} Node;

void push(Node** head, int data)
{
	Node* tmp = (Node*)malloc(sizeof(Node));
	tmp->ver = data;
	tmp->next = (*head);
	(*head) = tmp;
}

int pop(Node** head) {
	Node* prev = NULL;
	int val;
	if (head == NULL) {
		exit(-1);
	}
	prev = (*head);
	val = prev->ver;
	(*head) = (*head)->next;
	free(prev);
	return val;
}

Node* getLast(Node* head) {
	if (head == NULL) {
		return NULL;
	}
	while (head->next) {
		head = head->next;
	}
	return head;
}

void pushBack(Node* head, int value) {
	Node* last = getLast(head);
	Node* tmp = (Node*)malloc(sizeof(Node));
	tmp->ver = value;
	tmp->next = NULL;
	last->next = tmp;
}

void initializinglist(int** a, Node** head, int n)
{
	for (int i = 0; i < n; i++)
	{
		push(&head[i], i);
		for (int j = 0; j < n; j++)
		{
			if (a[i][j] == 1)
			{
				pushBack(head[i], j);
			}
		}
	}
}

void printLinkedList(const Node* head) {
	if (head) {
		cout << head->ver + 1;
		head = head->next;
	}
	while (head) {
		cout << "--->" << head->ver + 1;
		head = head->next;
	}
	printf("\n");
}

void BFS(int** a, int* visited, int n, int v)
{
	queue <int> q;
	q.push(v);
	visited[v] = 0;
	while (!q.empty())
	{
		v = q.front();
		q.pop();
		for (int i = 0; i < n; i++)
		{
			if (a[v][i] == 1 && visited[i] == -1)
			{
				q.push(i);
				visited[i] = visited[v] + 1;
			}
		}
	}
}

void BFSlist(Node** head, int* visited, int v)
{
	Node** tmp = head;
	queue <int> q;
	q.push(tmp[v]->ver);
	visited[tmp[v]->ver] = 0;
	while (!q.empty())
	{
		v = q.front();
		q.pop();
		while (tmp[v])
		{
			if (visited[tmp[v]->ver] == -1)
			{
				q.push(tmp[v]->ver);
				visited[tmp[v]->ver] = visited[v] + 1;
			}
			tmp[v] = tmp[v]->next;
		}
	}
}

void DFS(int** a, int* visited, int n, int v, const int count)
{
	visited[v] = count;
	for (int i = 0; i < n; i++)
	{
		if (a[v][i] == 1 && visited[i] == -1)
		{
			DFS(a, visited, n, i, count + 1);
		}
		if (a[v][i] == 1 && (visited[i] > count + 1))
		{
			DFS(a, visited, n, i, count + 1);
		}
	}
}

void DFSlist(Node** head, int* visited, int v, const int count)
{
	visited[v] = count;
	Node* tmp = head[v];
	while (tmp)
	{
		if (visited[tmp->ver] == -1)
			DFSlist(head, visited, tmp->ver, count + 1);
		if (visited[tmp->ver] > count + 1)
			DFSlist(head, visited, tmp->ver, count + 1);
		tmp = tmp->next;
	}
}

void main()
{
	setlocale(LC_ALL, "RUS");
	srand(time(NULL));
	LARGE_INTEGER start, end, f;
	queue <int> q;
	int** a, n = 9, num, v;
	Node** head = (Node**)malloc(n * sizeof(Node*));
	for (int i = 0; i < n; i++)
		head[i] = NULL;

	int* visited = (int*)malloc(n * sizeof(int));
	for (int i = 0; i < n; i++)
		visited[i] = -1;

	a = (int**)malloc(n * sizeof(int*));
	for (int i = 0; i < n; i++)
	{
		a[i] = (int*)malloc(n * sizeof(int));
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = n - 1; j >= 0; j--)
		{
			a[j][i] = a[i][j] = rand() % 2;
		}
	}
	for (int i = 0; i < n; i++)
	{
		cout << "\n\n";
		for (int j = 0; j < n; j++)
		{
			cout << a[i][j] << setw(5);
		}
	}


	cout << "\n\nВыберите вершину с которой начинать поиск растояний, используя обход в ширину: ";
	cin >> v;
	v--;
	QueryPerformanceCounter(&start);
	BFS(a, visited, n, v);
	QueryPerformanceCounter(&end);
	QueryPerformanceFrequency(&f);
	double sec = double(end.QuadPart - start.QuadPart) / f.QuadPart;
	cout << "\nРасстояния от вешины " << v + 1 << " до всех остальныйх используя обход в ширину на матрице смежности:\n";

	for (int i = 0; i < n; i++)
	{
		cout << i + 1 << " - " << visited[i] << endl;
	}

	for (int i = 0; i < n; i++)
		visited[i] = -1;

	initializinglist(a, head, n);
	QueryPerformanceCounter(&start);
	BFSlist(head, visited, v);
	QueryPerformanceCounter(&end);
	double sec1 = double(end.QuadPart - start.QuadPart) / f.QuadPart;

	cout << "\nРасстояния от вешины " << v + 1 << " до всех остальныйх используя обход в ширину на списках смежности::\n";
	for (int i = 0; i < n; i++)
	{
		cout << i + 1 << " - " << visited[i] << endl;
	}

	for (int i = 0; i < n; i++)
		visited[i] = -1;

	const int count = 0;
	QueryPerformanceCounter(&start);
	DFS(a, visited, n, v, count);
	QueryPerformanceCounter(&end);
	double sec2 = double(end.QuadPart - start.QuadPart) / f.QuadPart;
	cout << "\nРасстояния от вешины " << v + 1 << " до всех остальныйх используя обход в глубину на матрице смежности:\n";
	for (int i = 0; i < n; i++)
	{
		cout << i + 1 << " - " << visited[i] << endl;
	}

	for (int i = 0; i < n; i++)
		head[i] = NULL;

	for (int i = 0; i < n; i++)
		visited[i] = -1;

	initializinglist(a, head, n);
	QueryPerformanceCounter(&start);
	DFSlist(head, visited, v, count);
	QueryPerformanceCounter(&end);
	double sec3 = double(end.QuadPart - start.QuadPart) / f.QuadPart;

	cout << "\nРасстояния от вешины " << v + 1 << " до всех остальныйх используя обход в глубину на списках смежности:\n";
	for (int i = 0; i < n; i++)
	{
		cout << i + 1 << " - " << visited[i] << endl;
	}


	cout << "Время работы поиска расстояний в графк с помощью обхода в ширину на матрицах смежности: " << sec << endl;
	cout << "Время работы поиска расстояний в графк с помощью обхода в ширину на списках смежности: " << sec1 << endl;
	cout << "Время работы поиска расстояний в графк с помощью обхода в глубину на матрицах смежности: " << sec2 << endl;
	cout << "Время работы поиска расстояний в графк с помощью обхода в глубину на списках смежности: " << sec3 << endl;
}
