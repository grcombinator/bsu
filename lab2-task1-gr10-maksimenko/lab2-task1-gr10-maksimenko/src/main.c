#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Задача 1: Функция для подсчета дней с 1 января 1970 года
int daysFromEpoch(int day, int month, int year) {
		// Массив с количеством дней в месяцах
		int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

		// Проверка на високосный год и корректировка февраля
		int isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
		if (isLeapYear) {
				daysInMonth[2] = 29;
		}

		// Подсчет дней
		int totalDays = 0;

		// Считаем дни за полные годы
		for (int y = 1970; y < year; y++) {
				totalDays += (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0) ? 366 : 365;
		}

		// Считаем дни за полные месяцы текущего года
		for (int m = 1; m < month; m++) {
				totalDays += daysInMonth[m];
		}

		// Добавляем дни текущего месяца
		totalDays += day - 1; // -1 потому что не считаем текущий день

		return totalDays;
}

// Функция для определения количества дней между двумя датами
int daysBetweenDates(int day1, int month1, int year1, int day2, int month2, int year2) {
		int days1 = daysFromEpoch(day1, month1, year1);
		int days2 = daysFromEpoch(day2, month2, year2);

		return days2 - days1;
}

// Задача 3: Структура DATE для хранения даты
typedef struct {
		int year;
		int month;
		int day;
} DATE;

// Структура PERSON для хранения информации о студенте
typedef struct {
		char Name[100];
		char FAC[50];
		char GROUP[20];
		DATE DATE;
} PERSON;

// Функция для сравнения дат при сортировке по дате поступления
int compareDates(DATE date1, DATE date2) {
		if (date1.year != date2.year)
				return date1.year - date2.year;
		if (date1.month != date2.month)
				return date1.month - date2.month;
		return date1.day - date2.day;
}

// Функция сортировки массива по дате поступления
void sortByDate(PERSON vuz[], int n) {
		for (int i = 0; i < n - 1; i++) {
				for (int j = 0; j < n - i - 1; j++) {
						if (compareDates(vuz[j].DATE, vuz[j+1].DATE) > 0) {
								PERSON temp = vuz[j];
								vuz[j] = vuz[j+1];
								vuz[j+1] = temp;
						}
				}
		}
}

// Функция для вывода информации о студентах по факультетам, группам и дате
void printStudentInfo(PERSON vuz[], int n) {
		// Сначала сортируем по факультетам
		for (int i = 0; i < n - 1; i++) {
				for (int j = 0; j < n - i - 1; j++) {
						int facCompare = strcmp(vuz[j].FAC, vuz[j+1].FAC);
						if (facCompare > 0 || 
								(facCompare == 0 && strcmp(vuz[j].GROUP, vuz[j+1].GROUP) > 0) ||
								(facCompare == 0 && strcmp(vuz[j].GROUP, vuz[j+1].GROUP) == 0 && 
								 compareDates(vuz[j].DATE, vuz[j+1].DATE) > 0) ||
								(facCompare == 0 && strcmp(vuz[j].GROUP, vuz[j+1].GROUP) == 0 && 
								 compareDates(vuz[j].DATE, vuz[j+1].DATE) == 0 && 
								 strcmp(vuz[j].Name, vuz[j+1].Name) > 0)) {
								PERSON temp = vuz[j];
								vuz[j] = vuz[j+1];
								vuz[j+1] = temp;
						}
				}
		}

		// Вывод информации
		printf("\nСписок студентов по факультетам, группам и дате поступления:\n");
		printf("-----------------------------------------------------------\n");

		for (int i = 0; i < n; i++) {
				printf("ФИО: %s\n", vuz[i].Name);
				printf("Факультет: %s\n", vuz[i].FAC);
				printf("Группа: %s\n", vuz[i].GROUP);
				printf("Дата поступления: %02d.%02d.%04d\n", 
							 vuz[i].DATE.day, vuz[i].DATE.month, vuz[i].DATE.year);
				printf("-----------------------------------------------------------\n");
		}
}

// Задача 4: Структура для хранения адреса
typedef struct {
		int postalCode;
		char country[50];
		char region[50];
		char district[50];
		char city[50];
		char street[50];
		int house;
		int apartment;
} Address;

// Структура для хранения информации о владельце телефона
typedef struct {
		char lastName[50];
		char firstName[50];
		char middleName[50];
		Address address;
		char phoneNumber[20];
} PhoneOwner;

// Функция для вывода информации о владельцах телефонов, начинающихся на 621
void printPhoneOwners(PhoneOwner owners[], int n) {
		printf("\nВладельцы телефонов, начинающихся на 621:\n");
		printf("-----------------------------------------------------------\n");

		for (int i = 0; i < n; i++) {
				if (strncmp(owners[i].phoneNumber, "621", 3) == 0) {
						printf("ФИО: %s %s %s\n", 
									 owners[i].lastName, owners[i].firstName, owners[i].middleName);
						printf("Адрес: %d, %s, %s, %s, %s, %s, д.%d, кв.%d\n",
									 owners[i].address.postalCode, owners[i].address.country,
									 owners[i].address.region, owners[i].address.district,
									 owners[i].address.city, owners[i].address.street,
									 owners[i].address.house, owners[i].address.apartment);
						printf("Номер телефона: %s\n", owners[i].phoneNumber);
						printf("-----------------------------------------------------------\n");
				}
		}
}

int main() {
		// Демонстрация задачи 1
		printf("Задача 1: Определение количества дней между датами\n");
		int day1 = 1, month1 = 1, year1 = 1970;
		int day2, month2, year2;

		printf("Введите дату (день месяц год): ");
		scanf("%d %d %d", &day2, &month2, &year2);

		int days = daysFromEpoch(day2, month2, year2);
		printf("С 1 января 1970 года прошло %d дней\n", days);

		// Демонстрация задачи 3
		printf("\nЗадача 3: Информация о студентах\n");
		PERSON vuz[10];
		int n = 3; // Для демонстрации используем 3 записи вместо 10

		// Заполнение тестовыми данными
		strcpy(vuz[0].Name, "Иванов И.И.");
		strcpy(vuz[0].FAC, "ФКП");
		strcpy(vuz[0].GROUP, "10701219");
		vuz[0].DATE.day = 1;
		vuz[0].DATE.month = 9;
		vuz[0].DATE.year = 2019;

		strcpy(vuz[1].Name, "Петров П.П.");
		strcpy(vuz[1].FAC, "ФИТ");
		strcpy(vuz[1].GROUP, "10701220");
		vuz[1].DATE.day = 1;
		vuz[1].DATE.month = 9;
		vuz[1].DATE.year = 2020;

		strcpy(vuz[2].Name, "Сидоров С.С.");
		strcpy(vuz[2].FAC, "ФКП");
		strcpy(vuz[2].GROUP, "10701219");
		vuz[2].DATE.day = 5;
		vuz[2].DATE.month = 9;
		vuz[2].DATE.year = 2019;

		// Сортировка по дате поступления
		sortByDate(vuz, n);

		// Вывод отсортированных данных
		printf("\nСписок студентов, отсортированный по дате поступления:\n");
		for (int i = 0; i < n; i++) {
				printf("%s, %s, %s, %02d.%02d.%04d\n", 
							 vuz[i].Name, vuz[i].FAC, vuz[i].GROUP, 
							 vuz[i].DATE.day, vuz[i].DATE.month, vuz[i].DATE.year);
		}

		// Вывод по факультетам, группам и дате
		printStudentInfo(vuz, n);

		// Демонстрация задачи 4
		printf("\nЗадача 4: Владельцы телефонов\n");
		PhoneOwner owners[3];

		// Заполнение тестовыми данными
		strcpy(owners[0].lastName, "Иванов");
		strcpy(owners[0].firstName, "Иван");
		strcpy(owners[0].middleName, "Иванович");
		owners[0].address.postalCode = 220000;
		strcpy(owners[0].address.country, "Беларусь");
		strcpy(owners[0].address.region, "Минская");
		strcpy(owners[0].address.district, "Минский");
		strcpy(owners[0].address.city, "Минск");
		strcpy(owners[0].address.street, "Независимости");
		owners[0].address.house = 4;
		owners[0].address.apartment = 100;
		strcpy(owners[0].phoneNumber, "621123456");

		strcpy(owners[1].lastName, "Петров");
		strcpy(owners[1].firstName, "Петр");
		strcpy(owners[1].middleName, "Петрович");
		owners[1].address.postalCode = 220000;
		strcpy(owners[1].address.country, "Беларусь");
		strcpy(owners[1].address.region, "Минская");
		strcpy(owners[1].address.district, "Минский");
		strcpy(owners[1].address.city, "Минск");
		strcpy(owners[1].address.street, "Ленина");
		owners[1].address.house = 10;
		owners[1].address.apartment = 20;
		strcpy(owners[1].phoneNumber, "375291234567");

		strcpy(owners[2].lastName, "Сидоров");
		strcpy(owners[2].firstName, "Сидор");
		strcpy(owners[2].middleName, "Сидорович");
		owners[2].address.postalCode = 220000;
		strcpy(owners[2].address.country, "Беларусь");
		strcpy(owners[2].address.region, "Минская");
		strcpy(owners[2].address.district, "Минский");
		strcpy(owners[2].address.city, "Минск");
		strcpy(owners[2].address.street, "Пушкина");
		owners[2].address.house = 15;
		owners[2].address.apartment = 25;
		strcpy(owners[2].phoneNumber, "621987654");

		// Вывод информации о владельцах телефонов, начинающихся на 621
		printPhoneOwners(owners, 3);

		return 0;
}