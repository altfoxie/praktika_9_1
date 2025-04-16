#include "combinatorics.h"
#include "../common/menu.h"

void arrangement_with_repetition()
{
    int n, k;
    cout << "Введите общее количество элементов n: "; cin >> n;
    cout << "Введите количество элементов k, выбираемых из n: "; cin >> k;

    cout << "Ответ: " << pow(n, k) << "\n";
}

long long factorial(long long int number)
{
    long long fact = 1;
    for (int i = 2; i <= number; i++)
    {
        fact *= i;
    }
    return fact;
}

void arrangement_without_repetition()
{
    int n, k;
    cout << "Введите общее количество элементов n: "; cin >> n;
    cout << "Введите количество элементов k, выбираемых из n: "; cin >> k;
    cout << "Ответ: " << factorial(n) / (factorial(n-k)) << "\n";
}

void combinations_with_repetition()
{
    int n, k;
    cout << "Введите общее количество элементов n: "; cin >> n;
    cout << "Введите количество элементов k, выбираемых из n: "; cin >> k;
    cout << "Ответ: " << factorial(n+k-1) / (factorial(k)*factorial(n-1)) << "\n";
}

void combinations_without_repetition()
{
    int n, k;
    cout << "Введите общее количество элементов n: "; cin >> n;
    cout << "Введите количество элементов k, выбираемых из n: "; cin >> k;
    cout << "Ответ: " << factorial(n) / (factorial(k)*factorial(n-k)) << "\n";
}

void permutations()
{
    int n;
    cout << "Введите общее количество элементов n: "; cin >> n;
    cout << "Ответ: " << factorial(n) << "\n";
}

int combinatorics_entry()
{
	const char *title = "Комбинаторика";
	const char *entries[] = {"Размещение с повторением", "Размещение без повторений", "Сочетание с повторением", 
		"Сочетание без повторений", "Перестановка"};

	while (true)
	{
		int choice = menu_ask(title, entries, sizeof(entries) / sizeof(entries[0]));
		switch (choice)
		{
		case 0:
			return 0;
		case 1:
			arrangement_with_repetition();
			break;
		case 2:
			arrangement_without_repetition();
			break;
		case 3:
			combinations_with_repetition();
			break;
		case 4:
			combinations_without_repetition();
			break;
		case 5:
			permutations();
			break;
		default:
			break;
		}
		cout << endl;
	}
	return 0;
}