#include "common_fractions.h"
#include "../common/menu.h"
#include <iostream>
#include <stdio.h>

void SumDrob(int x1, int x2, int y1, int y2) {
    int z1 = 0, z2 = 0, z3 = 0, z = 0;
    if (x2 != 0 and y2 != 0) {
        if (x2 == y2) {
            z = x1 + y1;
            printf("%d/%d", z, x2);
        }
        else {
            z1 = x1 * y2;
            z2 = y1 * x2;
            z3 = x2 * y2;
            z = z1 + z2;
            printf("%d/%d", z, z3);
        }
    }
    else {
        printf("деление на 0");
    }
}

void SubtractDrob(int x1, int x2, int y1, int y2) {
    int z1 = 0, z2 = 0, z3 = 0, z = 0;
    if (x2 != 0 and y2 != 0) {
        if (x2 == y2) {
            z = x1 - y1;
            printf("%d/%d", z, x2);
        }
        else {
            z1 = x1 * y2;
            z2 = y1 * x2;
            z3 = x2 * y2;
            z = z1 - z2;
            printf("%d/%d", z, z3);
        }
    }
    else {
        printf("деление на 0");
    }
}

void MultiplicatDrob(int x1, int x2, int y1, int y2) {
    if (x2 != 0 and y2 != 0) {
        int z1 = 0, z2 = 0;
        z1 = x1 * y1;
        z2 = x2 * y2;
        printf("%d/%d", z1, z2);
    }
    else {
        printf("деление на 0");
    }
}

void DelDrob(int x1, int x2, int y1, int y2) {
    if (x2 != 0 and y2 != 0) {
        int z1 = 0, z2 = 0;
        z1 = x1 * y2;
        z2 = x2 * y1;
        printf("%d/%d", z1, z2);
    }
    else {
        printf("деление на 0");
    }
}

void ComparisDrob(int x1, int x2, int y1, int y2) {
    if (x2 != 0 and y2 != 0) {
        int z1 = 0, z2 = 0;
        z1 = x1 * y2;
        z2 = y1 * x2;
        if (z1 > z2) {
            printf("%d/%d > %d/%d", x1, x2, y1, y2);
        }
        else {
            printf("%d/%d < %d/%d", x1, x2, y1, y2);
        }
    }
    else {
        printf("деление на 0");
    }
}

int NOD(int a, int b) {
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

void ReductDrob(int x1, int x2) {
    if (x2 != 0) {
        int z = NOD(x1, x2);
        x1 /= z;
        x2 /= z;
        printf("%d/%d", x1, x2);
    }
    else {
        printf("деление на 0");
    }
}

void printDecimal(int x1, int x2, int p) {
    if (x2 != 0) {
        int t = x1 / x2;
        printf("%d.", t);
        x1 = x1 % x2;
        for (int i = 0; i < p; i++) {
            x1 *= 10;
            int t = x1 / x2;
            printf("%d", t);
            x1 = x1 % x2;
            if (x1 == 0) {
                break;
            }
        }
    }
    else {
        printf("деление на 0");
    }
}

int common_fractions_entry() {
    int x1, x2, y1, y2, p;
	const char *title = "Обыкновенные дроби";
	const char *entries[] = {"Сложение дробней", "Вычитание дробей", "Умножение", 
		"Деление", "Сравнение", "Сокращение", "Представление в виде десятичной дроби"};

	while (true)
	{
		int choice = menu_ask(title, entries, sizeof(entries) / sizeof(entries[0]));
		switch (choice)
		{
		case 0:
			return 0;
		case 1:
			cout << "Введите числитель и знаменатель дроби x1/x2: "; cin >> x1 >> x2;
			cout << "Введите числитель и знаменатель дроби y1/y2: "; cin >> y1 >> y2;
			SumDrob(x1, x2, y1, y2);
			break;
		case 2:
			cout << "Введите числитель и знаменатель дроби x1/x2: "; cin >> x1 >> x2;
			cout << "Введите числитель и знаменатель дроби y1/y2: "; cin >> y1 >> y2;
			SubtractDrob(x1, x2, y1, y2);
			break;
		case 3:
			cout << "Введите числитель и знаменатель дроби x1/x2: "; cin >> x1 >> x2;
			cout << "Введите числитель и знаменатель дроби y1/y2: "; cin >> y1 >> y2;
			MultiplicatDrob(x1, x2, y1, y2);
			break;
		case 4:
			cout << "Введите числитель и знаменатель дроби x1/x2: "; cin >> x1 >> x2;
			cout << "Введите числитель и знаменатель дроби y1/y2: "; cin >> y1 >> y2;
			DelDrob(x1, x2, y1, y2);
			break;
		case 5:
			cout << "Введите числитель и знаменатель дроби x1/x2: "; cin >> x1 >> x2;
			cout << "Введите числитель и знаменатель дроби y1/y2: "; cin >> y1 >> y2;
			ComparisDrob(x1, x2, y1, y2);
			break;
		case 6:
			cout << "Введите числитель и знаменатель дроби x1/x2: "; cin >> x1 >> x2;
			ReductDrob(x1, x2);
			break;
		case 7:
			cout << "Введите числитель и знаменатель дроби x1/x2: "; cin >> x1 >> x2;
			cout << "Введите количество знаков после запятой: "; cin >> p;
			printDecimal(x1, x2, p);
			break;
		default:
			break;
		}
		cout << endl;
	}
	return 0;
}