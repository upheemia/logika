// LOG 1.1.cpp: ���������� ����� ����� ��� ����������� ����������.
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
		printf("������� ������� ��������\n"); scanf("%20s", stud[i].famil);
	}
	for (i = 0; i < 3; i++)
	{
		printf("������� ��� �������� %s\n", stud[i].famil); scanf("%20s", stud[i].name);
	}
	for (i = 0; i < 3; i++)
	{
		printf("������� �������� ���������� �������� %s %s\n", stud[i].famil, stud[i].name); scanf("%20s", stud[i].facult);
	}
	for (i = 0; i < 3; i++)
	{
		printf("������� ����� �������� ������ �������� %s %s\n", stud[i].famil, stud[i].name); scanf("%d", &stud[i].Nomzach);
	}

	for (i = 0; i < 3; i++)
	{
		printf("C������ %s %s ��������� �� ���������� %s, ����� �������� ������ %d \n", stud[i].famil, stud[i].name,
			stud[i].facult, stud[i].Nomzach);
	}
	system("cls");
	for (;;)
	{
		int count;
		char word[32];
		printf(" 1. �������\n 2. ���\n 3. �������� ����������\n 4. ����� �������� ������\n �������� ����� ��� ������: "); scanf("%d", &count);
		printf("������� �������� �����: "); scanf("%s", word);
		printf("��������� ������:\n");
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
