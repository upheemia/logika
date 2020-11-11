#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <stack>
#include <iostream>
#include <iomanip>

using namespace std;

typedef struct Node {
	int ver;
	struct	Node* next;
} Node;

void push(Node** head, char data)
{
	Node* tmp = (Node*)malloc(sizeof(Node));
	tmp->ver = data;
	tmp->next = (*head);
	(*head) = tmp;
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

void pushBack(Node* head, char value) {
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

void DFS(int** a, bool* visited, int n, int v)
{
	cout << v + 1;
	visited[v] = true;
	for (int i = 0; i < n; i++)
	{
		if (a[v][i] == 1 && visited[i] == false)
		{
			DFS(a, visited, n, i);
		}
	}
}

void DFSlist(Node** head, bool* visited, int v)
{
	cout << v + 1;
	visited[v] = true;
	Node* tmp = head[v];
	while (tmp)
	{
		if (visited[tmp->ver] == false)
			DFSlist(head, visited, tmp->ver);
		tmp = tmp->next;
	}
}

void main()
{
	setlocale(LC_ALL, "RUS");
	srand(time(NULL));
	stack <int> steck;
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

	cout << "Проход в глубину с помощью рекурсивной функции для графа представленного матрицей смежности:\n\n";
	DFS(a, visited, n, num);
	cout << "\n\n";

	for (int i = 0; i < n; i++)
		visited[i] = false;

	cout << "Проход в глубину с помощью рекурсивной функции для графа представленного списками смежности:\n\n";
	initializinglist(a, head, n);
	cout << "Список смежности для матрицы А:\n\n";
	for (int i = 0; i < n; i++)
		printLinkedList(head[i]);

	cout << "\n\n";
	DFSlist(head, visited, num);
	cout << "\n\n";

	for (int i = 0; i < n; i++)
		visited[i] = false;

	cout << "Проход в глубину с помощью не рекурсивной функции для графа представленного матрицей смежности:\n\n";
	steck.push(num);
	while (!steck.empty())
	{
		if (visited[steck.top()] == false)
		{
			visited[steck.top()] = true;
			cout << steck.top() + 1;
			v = steck.top();
			steck.pop();
			for (int i = n - 1; i > 0; i--)
			{
				if (a[v][i] == 1 && visited[i] == false)
				{
					steck.push(i);
				}
			}
		}
		else
		{
			steck.pop();
		}
	}
	cout << "\n\n";
	system("pause");
}
