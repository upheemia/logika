// LOG 1.1.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "windows.h"
#include "stdio.h"
#include "string.h"

int   main(void)
{
	setvbuf(stdin, NULL, _IONBF, 0);
	setvbuf(stdout, NULL, _IONBF, 0);
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int i;
	struct student
	{
		char famil[20];
		char name[20], facult[20];
		int Nomzach;
	} stud[3];

	for (i = 0; i < 3; i++)
	{
		printf("Введите фамилию студента\n"); scanf("%20s", stud[i].famil);
	}
	for (i = 0; i < 3; i++)
	{
		printf("Введите имя студента %s\n", stud[i].famil); scanf("%20s", stud[i].name);
	}
	for (i = 0; i < 3; i++)
	{
		printf("Введите название факультета студента %s %s\n", stud[i].famil, stud[i].name); scanf("%20s", stud[i].facult);
	}
	for (i = 0; i < 3; i++)
	{
		printf("Введите номер зачётной книжки студента %s %s\n", stud[i].famil, stud[i].name); scanf("%d", &stud[i].Nomzach);
	}

	for (i = 0; i < 3; i++)
	{
		printf("Cтудент %s %s обучается на факультете %s, номер зачётной книжки %d \n", stud[i].famil, stud[i].name,
			stud[i].facult, stud[i].Nomzach);
	}
	system("cls");
	for (;;)
	{
		int count;
		char word[32];
		printf(" 1. Фамилия\n 2. Имя\n 3. Название факультета\n 4. Номер зачетной книжки\n Выберите пункт для поиска: "); scanf("%d", &count);
		printf("Введите ключевое слово: "); scanf("%s", word);
		printf("Результат поиска:\n");
		switch (count)
		{
		case 1:
			for (int i = 0; i < 3; i++)
				if (strstr(stud[i].famil, word))
					printf("%5s %5s %5s %5d\n\n", stud[i].famil, stud[i].name, stud[i].facult, stud[i].Nomzach);
			break;
		case 2:
			for (int i = 0; i < 3; i++)
				if (strstr(stud[i].name, word))
					printf("%5s %5s %5s %5d\n\n", stud[i].famil, stud[i].name, stud[i].facult, stud[i].Nomzach);
			break;
		case 3:
			for (int i = 0; i < 3; i++)
				if (strstr(stud[i].facult, word))
					printf("%5s %5s %5s %5d\n\n", stud[i].famil, stud[i].name, stud[i].facult, stud[i].Nomzach);
			break;
		case 4:
			for (int i = 0; i < 3; i++)
				if (stud[i].Nomzach = atoi(word))
					printf("%5s %5s %5s %5d\n\n", stud[i].famil, stud[i].name, stud[i].facult, stud[i].Nomzach);
			break;
		default: break;
		}
		system("pause");
		system("cls");
	}

}
