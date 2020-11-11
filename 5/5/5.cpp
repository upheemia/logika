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

void BFS(int** a, bool* visited, int n, int v)
{
	queue <int> q;
	q.push(v);
	visited[v] = true;
	while (!q.empty())
	{
		v = q.front();
		q.pop();
		cout << v + 1;
		for (int i = 0; i < n; i++)
		{
			if (a[v][i] == 1 && visited[i] == false)
			{
				q.push(i);
				visited[i] = true;
			}
		}
	}
}

void BFSlist(Node** head, bool* visited, int v)
{
	Node** tmp = head;
	queue <int> q;
	q.push(tmp[v]->ver);
	visited[tmp[v]->ver] = true;
	while (!q.empty())
	{
		v = q.front();
		q.pop();
		cout << v + 1;
		while (tmp[v])
		{
			if (visited[tmp[v]->ver] == false)
			{
				q.push(tmp[v]->ver);
				visited[tmp[v]->ver] = true;
			}
			tmp[v] = tmp[v]->next;
		}
	}
}

void BFSline(int** a, bool* visited, int v, int n)
{
	Node* head = NULL;
	push(&head, v);
	visited[v] = true;
	while (head)
	{
		v = pop(&head);
		cout << v + 1;
		for (int i = 0; i < n; i++)
		{
			if (a[v][i] == 1 && visited[i] == false)
			{
				if (head == NULL)
				{
					push(&head, i);
				}
				else
				{
					pushBack(head, i);
				}
				visited[i] = true;
			}
		}
	}
}

void main()
{
	setlocale(LC_ALL, "RUS");
	srand(time(NULL));
	LARGE_INTEGER start, end, f, start1, end1, f1;
	queue <int> q;
	int** a, n = 7, num, v;
	Node** head = (Node**)malloc(n * sizeof(Node*));
	for (int i = 0; i < n; i++)
		head[i] = NULL;

	bool* visited = (bool*)malloc(n * sizeof(bool));
	for (int i = 0; i < n; i++)
		visited[i] = false;

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

	cout << "\n\nВыберите вершину для начала обхода в глубину: ";
	cin >> num;
	if (num > n || num < 1)
	{
		cout << "\aОшибка ввода, попробуйте снова\n\nВыберите вершину для начала обхода в глубину: ";
		cin >> num;
	}

	num--;

	cout << "\n\nОбход в ширину для графа, представленного матрицей смежности: ";
	QueryPerformanceCounter(&start);
	BFS(a, visited, n, num);
	QueryPerformanceCounter(&end);
	QueryPerformanceFrequency(&f);
	double sec = double(end.QuadPart - start.QuadPart) / f.QuadPart;
	for (int i = 0; i < n; i++)
		visited[i] = false;


	initializinglist(a, head, n);
	cout << "\n\n";
	cout << "\n\nОбход в ширину для графа, представленного списками смежности:\n";
	for (int i = 0; i < n; i++)
		printLinkedList(head[i]);
	cout << "\n\n";
	BFSlist(head, visited, num);

	for (int i = 0; i < n; i++)
		visited[i] = false;

	cout << "\n\nОбход в ширину для графа, представленного матрицей смежности, реализованный с использованием очереди, построенной на основе структуры данных «список» : ";
	QueryPerformanceCounter(&start1);
	BFSline(a, visited, num, n);
	QueryPerformanceCounter(&end1);
	QueryPerformanceFrequency(&f1);
	double sec1 = double(end1.QuadPart - start1.QuadPart) / f1.QuadPart;
	cout << "\n\n";

	cout << "Время работы обхода в ширину использующего стандартный класс queue - " << sec << "\n\n";
	cout << "Время работы обхода в ширину использующего использующего очередь, реализованную самостоятельно - " << sec1 << "\n\n";
}
