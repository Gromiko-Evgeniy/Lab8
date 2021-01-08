#define _CRT_SECURE_NO_WARNINGS
#include  <stdio.h>
#include  <conio.h>
#include  <locale.h>
#include  <stdlib.h>
#include  <string.h>



// Описание структуры.
struct workShop{
   char name[20]; 			// Наименование цеха.
   int quantity; 				// Кол-во изделий.
   int workshopNumber; 				// Номер цеха.
   int year; 		// Год начала работы цеха.
   char city[25]; 				// Город, в котором расположен цех.   
   workShop* nextElement;    // Указатель на следующий элемент.
};

workShop* workShoph = NULL;

// Функция для вывода данных.
void outputData();
// Функция для ввода данных. 
void inputData();
// Функция для изменения данных.
void changeData();
// Функция для удаления данных.
void deleteData();
// Функция для сортировки данных по кол-ву.
void sortDataByQuantity(char y[20]);


int main() {
	setlocale(LC_ALL, "Rus");
	int k = -1;

	while (k != 0) {
		printf("\n");
		
		puts("\t Главное меню. Выберите действие                   ");
		puts("\t1. Добавление записи (-сей)");
		puts("\t2. Вывод данных на экран в виде таблицы");
		puts("\t3. Изменение данных по номеру");
		puts("\t4. Удаление данных по номеру");
		puts("\t5. Сортировка данных по кол-ву изделий");
		puts("\t0. Завершение программы");
		printf("\n\nВаш выбор(0-5):\t");
		scanf("%d", &k);
		switch (k)
		{
		case 1: inputData();
			break;
		case 2: outputData();
			break;
		case 3: changeData();
			break;
		case 4: deleteData();
			break;
		case 5:
			printf("Введите наименование цеха:\t");
			char inputWorkshopNumber[20];
			scanf("%s", &inputWorkshopNumber);
			sortDataByQuantity(inputWorkshopNumber);
			break;
		case 0: return 0;
			break;
		default: puts("Неправильный ввод! Введите число от 0 до 5!");
			break;
		}
	}
}

void outputData()
{
	workShop* pointerworkShop;
	int i;
	if (workShoph == NULL)
		printf("!!! Нет данных !!!\n");
	else {
		printf("№  Наименование\tКол-во\tНомер цех\tГод начала рабты\tГород\n");
		for (pointerworkShop = workShoph, i = 1; pointerworkShop != NULL; pointerworkShop = pointerworkShop->nextElement, i++) {
			printf("%-2d %-4s\t\t%-6d\t%-4d\t\t%-8d\t\t%-4s\n", i, pointerworkShop->name, pointerworkShop->quantity, pointerworkShop->workshopNumber, pointerworkShop->year, pointerworkShop->city);

		}
	}
}

void inputData() {
	workShop* listHead = NULL, * listTail = NULL;
	int i = 1;
	char answer[20];

	do {
		if (workShoph != NULL)
			for (++i, listHead = workShoph; listHead->nextElement != NULL; listHead = listHead->nextElement, i++);

		
		// Выделение памяти под новую запись.
		listTail = (workShop*)malloc(sizeof(workShop));

		printf("Введите наименование цеха: ");
		scanf("%s", &(listTail->name));
		printf("Введите колво изделий: ");
		scanf("%d", &(listTail->quantity));
		printf("Введите номер цеха: ");
		scanf("%d", &(listTail->workshopNumber));
		printf("Введите год начала работы цеха: ");
		scanf("%d", &(listTail->year));
		printf("Введите город, в котором расположен цех: ");
		scanf("%s", &(listTail->city));

		listTail->nextElement = NULL;
		if (workShoph == NULL)
			workShoph = listTail;
		else
			listHead->nextElement = listTail;

		printf("Хотите ввести еще запись (Y/N)???:\t");
		scanf("%s", &answer);

	} while (!strcmp(answer, "Y") || !strcmp(answer, "y")); 
}

int inputRecordNumberOfChange() {
	int recordNumberOfChange;
	do {
		scanf("%d", &recordNumberOfChange);
		if (recordNumberOfChange <= 0) {
			printf("!!! Неправильный ввод !!!");
			recordNumberOfChange = 0;
		}
	} while (!recordNumberOfChange);
	return recordNumberOfChange;
}

void changeData() {
	char massData[1000];
	workShop* pointerworkShop;

	printf("Введите номер записи, которую хотите изменить\t");
	// Номер записи для изменения данных
	int recordNumberOfChange = inputRecordNumberOfChange() - 1;

	for (pointerworkShop = workShoph; recordNumberOfChange && pointerworkShop != NULL; recordNumberOfChange--, pointerworkShop = pointerworkShop->nextElement);

	/* Запись новых значений в список */
	printf("Старое название = %s\tНовое название = ", pointerworkShop->name);
	gets_s(massData); gets_s(massData);
	if (*massData) sscanf(massData, "%s", &(pointerworkShop->name));

	printf("Старое кол-во = %d\tНовое кол-во = ", pointerworkShop->quantity);
	gets_s(massData);
	if (*massData) sscanf(massData, "%d", &(pointerworkShop->quantity));

	printf("Старый номер цеха = %d\tНовый номер цеха = ", pointerworkShop->workshopNumber);
	gets_s(massData);
	if (*massData) sscanf(massData, "%d", &(pointerworkShop->workshopNumber));

	printf("Старый год = %d\tНовый год = ", pointerworkShop->year);
	gets_s(massData);
	if (*massData) sscanf(massData, "%d", &(pointerworkShop->year));

	printf("Старый город = %s\tНовый город = ", pointerworkShop->city);
	gets_s(massData);
	if (*massData) sscanf(massData, "%s", &(pointerworkShop->city));
}

void deleteData() {
	workShop* listHead, * listTail;

	if (workShoph == NULL)
		printf("!!! Нет данных !!!\n");
	else {
		printf("Введите номер записи, которую хотите удалить\t");
		// Номер записи для изменения данных
		int recordNumberOfChange = inputRecordNumberOfChange() - 1;

		if (!recordNumberOfChange) {
			listHead = workShoph;
			workShoph = listHead->nextElement;
			free(listHead);
		}
		else {
			for (recordNumberOfChange--, listHead = workShoph; recordNumberOfChange && (listHead != NULL); listHead = listHead->nextElement, recordNumberOfChange--);
			if (listHead != NULL)
				if ((listTail = listHead->nextElement) != NULL) {
					listHead->nextElement = listTail->nextElement;
					free(listTail);
				}
		}
	}
}

void sortDataByQuantity(char y[20]) {
	int n;
	workShop* a, * b, * c = NULL;
	workShop* pointerworkShop;
	int i;
	if (workShoph == NULL || (workShoph->nextElement == NULL))
		printf("!!! Нет данных !!!\n");

	for (n = 1; n; ) {
		n = 0;

		for (a = workShoph, b = workShoph->nextElement; b != NULL; )
			if (a->quantity < b->quantity) {
				a->nextElement = b->nextElement;
				b->nextElement = a;
				if (a == workShoph)
					workShoph = b;
				else
					c->nextElement = b;
				c = b;
				b = a->nextElement;
				n = 1;
			}
			else {
				c = a;
				a = b;
				b = b->nextElement;
			}
	}

	printf("№  Цех\tКол-во изделий\n");
	for (pointerworkShop = workShoph, i = 1; pointerworkShop != NULL; pointerworkShop = pointerworkShop->nextElement, i++) {
		if (!strcmp(pointerworkShop->name, y)) {
			printf("%-2d %s\t%d\n", i, pointerworkShop->name, pointerworkShop->quantity);
		}
	}
}
