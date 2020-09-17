#include "stdafx.h"
#include "stdlib.h"
#include "time.h"
#include "locale.h"
#include "stdio.h"

int main()
{
	setlocale(LC_CTYPE, "rus");
	srand(time(NULL));
	int n = 5, m = 5;
	int** arr;
	arr = (int**)malloc(n * sizeof(int*));
	for (int i = 0; i < n; i++)
	{
		arr[i] = (int*)malloc(m * sizeof(int));
		for (int j = 0; j < m; j++)
		{
			arr[i][j] = rand() % 100;
		}
	}

	for (;;)
	{
		printf("Ваш массив: \n\n");
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				printf("%3d", arr[i][j]);
			}
			printf("\n\n");
		}
		printf(" 1. Вычислить разницу между максимальным и минимальным элементами массива. \n 2. Инициализавать массив случайными числами. \n 3. Создание массива произвольного размера, вводимого с клавиатуры. \n 4. Вычислить сумму значений в каждом столбце (или строке) двумерного массива.");
		int count;
		printf("\n\nВыберите пункт меню: ");
		scanf("%d", &count);
		switch (count)
		{
			case 1:
			{
			int min = arr[0][0], max = arr[0][0];
			for (int i = 0; i < n; i++)
			{
				for (int j = 0; j < m; j++)
				{
					if (arr[i][j] > max)
						max = arr[i][j];
					if (arr[i][j] < min)
						min = arr[i][j];
				}
			}
			printf("Разница между максимальным и минимальным элементами массива %d\n\n", (max - min));
			break;
		}
			case 2:
			{
			for (int i = 0; i < n; i++)
			{
				for (int j = 0; j < m; j++)
				{
					arr[i][j] = rand() % 100;
				}
			}
			break;
		}
			case 3:
			{
			printf("Введите количество строк:");
			scanf("%d", &n);
			printf("Введите количество столбцов:");
			scanf("%d", &m);
			free(arr);
			arr = (int**)malloc(n * sizeof(int*));
			for (int i = 0; i < n; i++)
			{
				arr[i] = (int*)malloc(m * sizeof(int));
				for (int j = 0; j < m; j++)
				{
					arr[i][j] = rand() % 100;
				}
			}
			break;
		}
			case 4:
			{
			printf(" 1. Вычислить сумму значений в каждой строке. \n 2. Вычислить сумму значений в каждом столбце. \n\n");
			int num;
			printf("Выберите пункт меню: ");
			scanf("%d", &num);
			switch (num)
			{
			case 1:
			{
				int sum;
				for (int i = 0; i < n; i++)
				{
					sum = 0;
					for (int j = 0; j < m; j++)
					{
						sum += arr[i][j];
					}
					printf("Сумма элементов строки №%d - %d\n", i+1, sum);
				}
				break;
			}
			case 2:
			{
				int sum;
				for (int i = 0; i < m; i++)
				{
					sum = 0;
					for (int j = 0; j < n; j++)
					{
						sum += arr[j][i];
					}
					printf("Сумма элементов столбца №%d - %d\n", i+1, sum);
				}
				break;
			}
			default:
				break;
			}


		}
			default: 
				break;
		}
		system("pause");
		system("cls");
	}
}