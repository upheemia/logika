#include "stdafx.h"
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int compare(const void* x1, const void* x2)
{
	return(*(int*)x1 - *(int*)x2);
}

int main(void)
{
	setvbuf(stdin, NULL, _IONBF, 0);
	setvbuf(stdout, NULL, _IONBF, 0);

	FILE* S;
	char name[] = "data2.txt";

	clock_t start, end; // объявляем переменные для определения времени выполнения

	int arr[100000];
	srand(time(NULL));
	for (int i = 0; i < 100000; i++)
	{
		arr[i] = rand() % 100;
	}

	int i, j, step;
	int tmp;
	start = clock();
	for (step = 100000 / 2; step > 0; step /= 2)
	{
		for (i = step; i < 100000; i++)
		{
			tmp = arr[i];
			for (j = i; j >= step; j -= step)
			{
				if (tmp < arr[j - step])
					arr[j] = arr[j - step];
				else
					break;
			}
			arr[j] = tmp;
		}
	}
	end = clock();
	printf("\n\ntime start - %fms\n\n", start / 1000.0);
	printf("time end - %fms\n\n", end / 1000.0);
	printf("\nFunction execution time - %fms\n\n", (end - start) / 1000.0);
	printf("Program execution time - %fms\n\n", clock() / 1000.0);
	S = fopen(name, "a");
	fprintf(S, "\n\ntime start - %fms\n\n", start / 1000.0);
	fprintf(S, "time end - %fms\n\n", end / 1000.0);
	fprintf(S, "\nFunction execution time - %fms\n\n", (end - start) / 1000.0);
	fprintf(S, "Program execution time - %fms\n\n", clock() / 1000.0);
	fclose(S);
	system("pause");
	return(0);
}
