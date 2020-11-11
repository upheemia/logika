#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<time.h>
#include<locale.h>

typedef struct Node {
	char ver;
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

void printLinkedList(const Node* head) {
	if (head) {
		printf("%c", head->ver);
		head = head->next;
	}
	while (head) {
		printf("--->%c", head->ver);
		head = head->next;
	}
	printf("\n");
}

void pushBack(Node* head, char value) {
	Node* last = getLast(head);
	Node* tmp = (Node*)malloc(sizeof(Node));
	tmp->ver = value;
	tmp->next = NULL;
	last->next = tmp;
}

void printarray(int** a, int n)
{
	char letter = 'A';
	if (n > 0)
		printf("%10c", letter);
	for (int i = 0; i < n - 1; i++)
	{
		letter++;
		printf("%5c", letter);
	}
	printf("\n\n");
	letter = 'A';
	for (int i = 0; i < n; i++)
	{
		printf("%5c", letter);
		letter++;
		for (int j = 0; j < n; j++)
		{
			printf("%5d", a[i][j]);
		}
		printf("\n\n");
	}
	printf("\n\n\n\n");
}

void identification(int v1, int v2, int** a, int n)
{
	int del, field;
	if (v1 > v2)
	{
		del = v1 - 1;
		field = v2 - 1;
	}
	else
	{
		del = v2 - 1;
		field = v1 - 1;
	}

	for (int i = 0; i < n; i++)
	{
		if (a[del][i] == 1)
			a[field][i] = 1;

		if (a[i][del] == 1)
			a[i][field] = 1;
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = del; j < n - 1; j++)
		{
			a[i][j] = a[i][j + 1];
		}
	}

	for (int i = del; i < n - 1; i++)
	{
		for (int j = 0; j < n; j++)
		{
			a[i][j] = a[i + 1][j];
		}
	}

	printarray(a, n - 1);
}

void initializinglist(int** a, Node** head, int n, char letter)
{
	for (int i = 0; i < n; i++)
	{
		push(&head[i], letter + i);
		for (int j = 0; j < n; j++)
		{
			if (a[i][j] == 1)
			{
				pushBack(head[i], letter + j);
			}
		}
	}
}

void cleanlist(Node** head, int n)
{
	for (int i = 0; i < n; i++)
		head[i] = NULL;
}

void cleanlistfield(Node** head, int del, int n)
{
	char letter = 'A', pressF;
	letter += del;
	Node* tmp;

	for (int i = 0; i < n; i++)
	{
		tmp = head[i];
		while (tmp)
		{
			if (tmp->next)
				if (tmp->next->ver == letter)
				{
					tmp->next = tmp->next->next;
				}
			if (tmp->ver >= letter)
			{
				pressF = tmp->ver;
				pressF--;
				tmp->ver = pressF;
			}
			tmp = tmp->next;
		}
	}

	for (int i = del; i < n - 1; i++)
	{
		head[i] = head[i + 1];
	}
	head[n - 1] = NULL;
}

void paste(Node* head, char letter)
{
	Node* tmp;
	tmp = (Node*)malloc(sizeof(Node));
	tmp->ver = letter;
	tmp->next = head->next;
	head->next = tmp;
}

void addver(Node** head, int field, int n)
{
	Node* ptr, * tmp;
	char letter = head[field]->ver, search;
	tmp = head[field];
	tmp = tmp->next;
	while (tmp)
	{
		search = tmp->ver;
		for (int i = 0; i < n - 1; i++)
		{
			if (head[i]->ver == search)
			{
				if (!head[i]->next)
				{
					push(&head[i], letter);
				}
				ptr = head[i];
				while (ptr->next)
				{
					if (ptr->next->ver == letter)
					{
						break;
					}
					if (ptr->next->ver > letter)
					{
						paste(ptr, letter);
					}
				}
				break;
			}
		}
		tmp = tmp->next;
	}
}

void identificationlist(int v1, int v2, Node** head, int n)
{
	int del, field;
	char letter = 'A';
	Node* ptr = NULL, * tmp;
	if (v1 > v2)
	{
		del = v1 - 1;
		field = v2 - 1;
	}
	else
	{
		del = v2 - 1;
		field = v1 - 1;
	}
	tmp = head[del]->next;
	ptr = (Node*)malloc(sizeof(Node));
	ptr->ver = head[field]->ver;
	ptr->next = NULL;
	head[field] = head[field]->next;
	while (head[field] || tmp)
	{
		if (head[field] && tmp)
		{
			if (head[field]->ver > tmp->ver)
			{
				pushBack(ptr, tmp->ver);
				tmp = tmp->next;
				continue;
			}
			if (head[field]->ver < tmp->ver)
			{
				pushBack(ptr, head[field]->ver);
				head[field] = head[field]->next;
				continue;
			}
			if (head[field]->ver == tmp->ver)
			{
				pushBack(ptr, tmp->ver);
				tmp = tmp->next;
				head[field] = head[field]->next;
				continue;
			}
		}
		if (head[field])
		{
			while (head[field])
			{
				pushBack(ptr, head[field]->ver);
				head[field] = head[field]->next;
			}
		}
		else
		{
			while (tmp)
			{
				pushBack(ptr, tmp->ver);
				tmp = tmp->next;
			}
		}
	}
	head[field] = ptr;
	fflush(stdin);
	cleanlistfield(head, del, n);
	addver(head, field, n);
}

void spliting(int** a, int v, int n)
{
	v--;
	int i = v;
	for (; i <= n; i++)
	{
		if (a[v][i] == 1)
		{
			a[n - 1][i] = a[i][n - 1] = 1;
			a[v][i] = a[i][v] = 0;
			i++;
			break;
		}
		a[n - 1][i] = a[i][n - 1] = 0;
	}

	while (i <= n)
	{
		a[n - 1][i] = a[i][n - 1] = 0;
		i++;
	}

	a[n - 1][v] = a[v][n - 1] = 1;
}

void combiningarray(int** a, int** b, int** c, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (a[i][j] == 1 || b[i][j] == 1)
			{
				c[i][j] = 1;
			}
			else
			{
				c[i][j] = 0;
			}
		}
	}
}

void intersectionarray(int** a, int** b, int** c, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (a[i][j] == 1 && b[i][j] == 1)
			{
				c[i][j] = 1;
			}
			else
			{
				c[i][j] = 0;
			}
		}
	}
}

void ringsumarray(int** a, int** b, int** c, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if ((a[i][j] == 1 && b[i][j] == 0) || (a[i][j] == 0 && b[i][j] == 1))
			{
				c[i][j] = 1;
			}
			else
			{
				c[i][j] = 0;
			}
		}
	}
}

void splitinglist(Node** head, int v, int n)
{
	push(&head[n - 1], 'A' + n - 1);
	Node* ptr = head[v - 1];
	if (ptr->next)
	{
		if (ptr->ver < ptr->next->ver)
		{
			pushBack(head[n - 1], ptr->ver);
			pushBack(head[n - 1], ptr->next->ver);
			ptr->next = ptr->next->next;
		}
		else
		{
			pushBack(head[n - 1], ptr->next->ver);
			pushBack(head[n - 1], ptr->ver);
			ptr->next = ptr->next->next;
		}
	}
	else
	{
		pushBack(head[n], ptr->ver);
	}
}


void main()
{
	setlocale(LC_ALL, "RUS");
	char letter = 'A';
	int** a, ** b, n = 5, v1, v2, del;
	Node** head = (Node**)malloc(n * sizeof(Node*));
	for (int i = 0; i < n; i++)
		head[i] = NULL;
	srand(time(NULL));
	a = (int**)malloc(n * sizeof(int*));
	b = (int**)malloc(n * sizeof(int*));
	for (int i = 0; i < n; i++)
	{
		a[i] = (int*)malloc(n * sizeof(int));
		b[i] = (int*)malloc(n * sizeof(int));
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = n - 1; j >= 0; j--)
		{
			a[j][i] = a[i][j] = rand() % 2;
			b[j][i] = b[i][j] = rand() % 2;
		}
	}

	printarray(a, n);
	printarray(b, n);

	initializinglist(a, head, n, letter);
	printf("list A:\n");

	for (int i = 0; i < n; i++)
		printLinkedList(head[i]);
	cleanlist(head, n);
	printf("\n\n");


	initializinglist(b, head, n, letter);
	printf("list B:\n");

	for (int i = 0; i < n; i++)
		printLinkedList(head[i]);
	cleanlist(head, n);
	printf("\n\n");

	initializinglist(a, head, n, letter);
	printf("Выберите вершины в матрице А для отождествления\n Вершина 1: ");
	scanf_s("%d", &v1);
	printf("\n Вершина 2: ");
	scanf_s("%d", &v2);

	identification(v1, v2, a, n);
	identificationlist(v1, v2, head, n);

	for (int i = 0; i < n; i++)
		printLinkedList(head[i]);
	cleanlist(head, n);
	printf("\n\n");

	initializinglist(b, head, n, letter);
	printf("Выберите вершины в матрице В для отождествления\n Вершина 1: ");
	scanf_s("%d", &v1);
	printf("\n Вершина 2: ");
	scanf_s("%d", &v2);

	identification(v1, v2, b, n);
	identificationlist(v1, v2, head, n);

	for (int i = 0; i < n; i++)
		printLinkedList(head[i]);
	cleanlist(head, n);

	n--;

	initializinglist(a, head, n, letter);
	printf("\nВыберите вершину в матрице А для расщепления");
	for (;;)
	{
		printf("\n Вершина 1: ");
		scanf_s("%d", &v1);
		printf("\n Вершина 2: ");
		scanf_s("%d", &v2);
		if (a[v1 - 1][v2 - 1] == 1)
			break;
		else
			printf("Error enter again!!!");
	}

	identification(v1, v2, a, n);
	identificationlist(v1, v2, head, n);

	for (int i = 0; i < n; i++)
		printLinkedList(head[i]);
	cleanlist(head, n);



	initializinglist(b, head, n, letter);
	printf("\nВыберите вершину в матрице В для расщепления");
	for (;;)
	{
		printf("\n Вершина 1: ");
		scanf_s("%d", &v1);
		printf("\n Вершина 2: ");
		scanf_s("%d", &v2);
		if (b[v1 - 1][v2 - 1] == 1)
			break;
		else
			printf("Error enter again!!!");
	}

	identification(v1, v2, b, n);
	identificationlist(v1, v2, head, n);

	for (int i = 0; i < n; i++)
		printLinkedList(head[i]);
	cleanlist(head, n);


	initializinglist(a, head, n - 1, letter);

	printf("Выберите вершину в матрице А для рсщепления: ");
	scanf_s("%d", &v1);
	spliting(a, v1, n);
	splitinglist(head, v1, n);
	printarray(a, n);

	for (int i = 0; i < n; i++)
		printLinkedList(head[i]);
	cleanlist(head, n);


	printf("Выберите вершину в матрице В для рсщепления: ");
	scanf_s("%d", &v1);
	spliting(b, v1, n);
	printarray(b, n);


	int** c = (int**)malloc(n * sizeof(int*));
	for (int i = 0; i < n; i++)
	{
		c[i] = (int*)malloc(n * sizeof(int));
	}

	printf("\n\nОбъединиение матриц А и В:\n\n");
	combiningarray(a, b, c, n);
	printarray(c, n);


	printf("\n\nПересечение мартиц А и В:\n\n");
	intersectionarray(a, b, c, n);
	printarray(c, n);

	printf("\n\nКольцевая сумма матриц А и В:\n\n");
	ringsumarray(a, b, c, n);
	printarray(c, n);

	printf("Декартово произведение A и B");

	for (int i = 0; i < n; i++)
	{
		for (int q = 0; q < n; q++)
		{
			printf("\n\n");
			for (int j = 0; j < n; j++)
			{
				for (int k = 0; k < n; k++)
				{

					if (i == j) {
						printf("%5d", b[q][k]);
					}
					if (q == k)
					{
						printf("%5d", a[i][j]);
					}
					if ((i != j) && (q != k))
					{
						printf("%5d", 0);
					}

				}
			}
		}
	}
	printf("\n\n");
	system("pause");

}
