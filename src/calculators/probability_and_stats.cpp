#include "probability_and_stats.h"
#include "../common/menu.h"
#include <stdio.h>

double VerMAndN(int m, int n) {
    if (n == 0) {
        printf("Ошибка: деление на ноль!\n");
        return 0;
    }
    return ((double)m / n)*100;
}

double expected_value(int* a, double* b, int size) {
    double m = 0.0;
    for (int i = 0; i < size; i++) {
        m += a[i] * b[i];
    }
    return m;
}

double variance(int* a, double* b, int size) {
    double mean = expected_value(a, b, size);
    double var = 0.0;

    for (int i = 0; i < size; i++) {
        var += b[i] * (a[i] - mean) * (a[i] - mean);
    }

    return var;
}

int probability_and_stats_entry() {
	const char *title = "Теория вероятности и статистика";
	const char *entries[] = {"Вероятность m/n", "Дисперсия для дискретного распределения величин", "Математическое ожидание для дискретного распределения величин"};

	while (true)
	{
		int *a, size;
		double *b, var;
		int choice = menu_ask(title, entries, sizeof(entries) / sizeof(entries[0]));
		switch (choice)
		{
		case 0:
			return 0;
		case 1:
			int m, n;
			cout << "Введите m и n: "; cin >> m >> n;
			cout << VerMAndN(m, n);
			break;
		case 2:
			int size;
			printf("Введите количество значений: ");
			cin >> size;

			int* a;
			a = (int*)malloc(size * sizeof(int));
			double* b;
			b = (double*)malloc(size * sizeof(double));

			if (a == NULL or b == NULL) {
				printf("Ошибка выделения памяти!\n");
				return 1;
			}

			printf("Введите значения:\n");
			for (int i = 0; i < size; i++) {
				printf("Значение %d: ", i + 1);
				cin >> a[i];
			}

			printf("Введите вероятности:\n");
			for (int i = 0; i < size; i++) {
				printf("Вероятность %d: ", i + 1);
				cin >> b[i];
			}

			var = variance(a, b, size);
			printf("Дисперсия: %f\n", var);
			break;
		case 3:
			printf("Введите количество значений: ");
			cin >> size;
			a = (int*)malloc(size * sizeof(int));
			b = (double*)malloc(size * sizeof(double));

			if (a == NULL or b == NULL) {
				printf("Ошибка выделения памяти!\n");
				return 1;
			}

			printf("Введите значения:\n");
			for (int i = 0; i < size; i++) {
				printf("Значение %d: ", i + 1);
				cin >> a[i];
			}

			printf("Введите вероятности:\n");
			for (int i = 0; i < size; i++) {
				printf("Вероятность %d: ", i + 1);
				cin >> b[i];
			}

			var = variance(a, b, size);
			printf("Математическое ожидание: %f\n", var);
			break;
		default:
			break;
		}
		cout << endl;
	}
	return 0;
}
