#include "stdafx.h"
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main(void)
{
	setvbuf(stdin, NULL, _IONBF, 0);
	setvbuf(stdout, NULL, _IONBF, 0);

	FILE* S;
	char name[] = "data.txt";

	clock_t start, end; // объявляем переменные для определения времени выполнения

	const unsigned int h = 150;

	int i = 0, j = 0, r;
	int a[h][h], b[h][h], c[h][h], elem_c;

	srand(time(NULL)); // инициализируем параметры генератора случайных чисел
	while (i < h)
	{
		while (j < h)
		{
			a[i][j] = rand() % 100 + 1; // заполняем массив случайными числами
			j++;
		}
		i++;
	}
	srand(time(NULL)); // инициализируем параметры генератора случайных чисел
	i = 0; j = 0;
	while (i < h)
	{
		while (j < h)
		{
			b[i][j] = rand() % 100 + 1; // заполняем массив случайными числами
			j++;
		}
		i++;
	}
	start = clock();
	for (i = 0; i < h; i++)
	{
		for (j = 0; j < h; j++)
		{
			elem_c = 0;
			for (r = 0; r < h; r++)
			{
				elem_c = elem_c + a[i][r] * b[r][j];
				c[i][j] = elem_c;
			}
		}
	}
	end = clock();
	double seconds = (double)(end - start) / CLOCKS_PER_SEC;
	printf("Function execution time - %fms\n\n", seconds);
	S = fopen(name, "a");
	fprintf(S, "Function execution time - %fms arr[%d]\n\n", seconds, h);
	fclose(S);
	system("pause");
	return(0);
}

