#define _CRT_SECURE_NO_WARNINGS
#include  <locale.h>
#include  <stdlib.h>
#include  <string.h>
#include  <stdio.h>
#include  <conio.h>


// Функция пдля вывода данных
void outputData();
// Функция для ввода данных
void inputData();
// Функция для изменения данных
void changeData();
// Функция для удаления данных
void deleteData();
// Функция для сортировки данных по наименованию
void sortDataByName(int year);
// Функция для сохранения данных в файл
void saveDataInFile();
// Функция для загрузки данных из файл в динамическую память
void loadingFataFromAFile();


// Описание структуры
struct book{
   char author[50]; 			// Автор.
   int number; 				// Номер.
   int year; 				// Год.
   char title[50];			// Название.
   int pages; 		// Кол-во страниц.
   char publish[50]; 				// Издание.   
   book* nextElement;    // Указатель на следующий элемент.
};

book* bookh = NULL;
char fname[] = "data.txt";

int main() {
	setlocale(LC_ALL, "Rus");
	int k = -1;

	while (k != 0) {
		printf("\n");
		puts("\tГлавное меню. Выберите действие");
		puts("\t1. Добавление записи (-сей)");
		puts("\t2. Вывод данных на экран в виде таблицы");
		puts("\t3. Изменение данных по номеру");
		puts("\t4. Удаление данных по номеру");
		puts("\t5. Сортировка данных по ФИО авторов");
		puts("\t6. Сохранение данных в файл dataOutput.txt");
		puts("\t7. Считывание данных с файла data.txt");
		puts("\t0. Завершение программы");
		printf("\n\nВаш выбор(0-7):\t");
		scanf("%d", &k);
		switch (k)
		{
		case 1: inputData();
			break;
		case 2:  outputData();
			break;
		case 3: changeData();
			break;
		case 4: deleteData();
			break;
		case 5:
			printf("Введите год:\t");
			int year;
			scanf("%d", &year);
			sortDataByName(year);
			break;
		case 6: saveDataInFile();
			break;
		case 7: loadingFataFromAFile(); outputData();
			break;
		case 0: return 0;
			break;
		default: puts("Неправильный ввод! Введите число от 0 до 7!");
			break;
		}
	}
	return 0;
}

void outputData() {
	book* pointerbook;
	int i, j;
	if (bookh == NULL)
		printf("!!! Нет данных !!!\n");
	else {
		printf("№  Автор   Рег. номер         Год      Название  Кол-во страниц  Издание\n");
		for (pointerbook = bookh, i = 1, j = 1; pointerbook != NULL; pointerbook = pointerbook->nextElement, j++, i++) {
			printf("%-2d %-4s    %-6d\t      %-4d     %-4s\t %-8d\t %-4s\n", i, pointerbook->author, pointerbook->number, pointerbook->year, pointerbook->title, pointerbook->pages, pointerbook->publish);
			printf("--------------------------------------------------------------------------------\n");
		}
	}
}

void inputData() {
	book* listHead = NULL, * listTail;
	int i = 1;
	char answer[20];

	do {
		if (bookh != NULL)
			for (++i, listHead = bookh; listHead->nextElement != NULL; listHead = listHead->nextElement, i++);

		// Выделение памяти под новую запись
		listTail = (book*)malloc(sizeof(book));

		printf("Введите ФИО автора: ");
		scanf("%s", (listTail->author));
		printf("Введите номер книги: ");
		scanf("%d", &(listTail->number));
		printf("Введите год: ");
		scanf("%d", &(listTail->year));
		printf("Введите название: ");
		scanf("%s", &(listTail->title));
		printf("Введите кол-во страниц: ");
		scanf("%d", &(listTail->pages));
		printf("Введите издательство: ");
		scanf("%s", &(listTail->publish));

		listTail->nextElement = NULL;
		if (bookh == NULL)
			bookh = listTail;
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
	book* pointerbook;

	printf("Введите номер записи, которую хотите изменить\t");
	// Номер записи для изменения данных
	int recordNumberOfChange = inputRecordNumberOfChange() - 1;

	for (pointerbook = bookh; recordNumberOfChange && pointerbook != NULL; recordNumberOfChange--, pointerbook = pointerbook->nextElement);

	/* Запись новых значений в список */
	printf("Старое ФИО = %s\tНовое ФИО = ", pointerbook->author);
	gets_s(massData); gets_s(massData);
	if (*massData) sscanf(massData, "%s", &(pointerbook->author));

	printf("Старый номер = %d\tНовый номер = ", pointerbook->number);
	gets_s(massData);
	if (*massData) sscanf(massData, "%d", &(pointerbook->number));

	printf("Старый год = %d\tНовый год = ", pointerbook->year);
	gets_s(massData);
	if (*massData) sscanf(massData, "%d", &(pointerbook->year));

	printf("Старое название = %s\tНовое название = ", pointerbook->title);
	gets_s(massData);
	if (*massData) sscanf(massData, "%s", &(pointerbook->title));

	printf("Старое кол-во страниц = %d\tНовое кол-во страниц = ", pointerbook->pages);
	gets_s(massData);
	if (*massData) sscanf(massData, "%d", &(pointerbook->pages));

	printf("Старое издательство = %s\tНовое издательство = ", pointerbook->publish);
	gets_s(massData);
	if (*massData) sscanf(massData, "%s", &(pointerbook->publish));
}

void deleteData() {
	book* listHead, * listTail;

	if (bookh == NULL)
		printf("!!! Нет данных !!!\n");
	else {
		printf("Введите номер записи, которую хотите удалить\t");
		// Номер записи для изменения данных
		int recordNumberOfChange = inputRecordNumberOfChange() - 1;

		if (!recordNumberOfChange) {
			listHead = bookh;
			bookh = listHead->nextElement;
			free(listHead);
		}
		else {
			for (recordNumberOfChange--, listHead = bookh; recordNumberOfChange && (listHead != NULL); listHead = listHead->nextElement, recordNumberOfChange--);
			if (listHead != NULL)
				if ((listTail = listHead->nextElement) != NULL) {
					listHead->nextElement = listTail->nextElement;
					free(listTail);
				}
		}
	}
}

void sortDataByName(int y) {
	int n;
	book* a, * b, * c = NULL;
	book* pointerbook;
	int i, j;

	if (bookh == NULL || (bookh->nextElement == NULL))
		printf("!!! Нет данных !!!\n");

	for (n = 1; n; ) {
		n = 0;
		for (a = bookh, b = bookh->nextElement; b != NULL; )
			if (strcmp(a->author, b->author) > 0) {
				a->nextElement = b->nextElement;
				b->nextElement = a;
				if (a == bookh)
					bookh = b;
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
	printf("\n-------------------------------------\n");
	printf("№       Автор\tНазвание\tГод\n");
	for (pointerbook = bookh, i = 1, j = 1; pointerbook != NULL; pointerbook = pointerbook->nextElement, j++, i++) {
		if (pointerbook->year >= y) {
			printf("%-2d\t%s\t%-6s\t\t%d\n", i, pointerbook->author, pointerbook->title, pointerbook->year);
		}
		printf("-------------------------------------\n");
	}
}

void saveDataInFile() {
	FILE* f;
	book* pointerbook;
	f = fopen("dataOtput.txt", "w");

	// Запись данных в файл
	for (pointerbook = bookh; pointerbook != NULL; pointerbook = pointerbook->nextElement)
		fprintf(f, "%s %d %d %s %d %s\n", pointerbook->author, pointerbook->number, pointerbook->year, pointerbook->title, pointerbook->pages, pointerbook->publish);

	fprintf(f, "***\n");
	fclose(f);
}

void loadingFataFromAFile() {
	FILE* f;
	char massData[1000];
	book* listHead = NULL, * listTail;

	// Открытие файла для чтения
	if ((f = fopen(fname, "r")) == NULL) {
		printf("!!! Файл не найден !!! : %s\n", fname);
	}
	else {
		bookh = NULL;
		do {
			// Чтение из файла по полям пока не дошли до спецкода
			fscanf(f, "%s", massData);
			if (massData[0] != '*') {
				// Выделение памяти под новый элемент
				listTail = (book*)malloc(sizeof(book));
				if (bookh == NULL)
					bookh = listTail;
				else listHead->nextElement = listTail;
				strcpy(listTail->author, massData);
				fscanf(f, "%d", &(listTail->number));
				fscanf(f, "%d", &(listTail->year));
				fscanf(f, "%s", &(listTail->title));
				fscanf(f, "%d", &(listTail->pages));
				fscanf(f, "%s", &(listTail->publish));
				listTail->nextElement = NULL;
				listHead = listTail;
			}
		} while (massData[0] != '*'); 
		fclose(f);
	}
}