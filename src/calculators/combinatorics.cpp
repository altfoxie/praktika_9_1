#include "combinatorics.h"

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

void combinatorics_entry() {
	bool process = true;
	cout << "Меню комбинаторики:\n1. Размещение с повторением.\n2. Размещение без повторений.\n3. Сочетание с повторением.\n4. Сочетание без повторений.\n5. Перестановка\n";
	while (process)
	{		
		int choice;
		cout << "\nВыберите пункт: "; cin >> choice;
		switch (choice)
		{
		case 0:
			process = false;
			break;
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
	}
}