#include "menu.h"

// Возвращает номер выбранного пункта начиная с 1.
// При выходе возвращает 0.
// Вывод содержит пустую строку в конце.
int menu_ask(const char* title, const char** entries, int entries_count)
{
	int choice;
	while (true)
	{
		cout << title << '\n';

		for (int i = 0; i < entries_count; i++)
		{
			cout << i + 1 << ". " << entries[i] << '\n';
		}
		cout << "0. Выход" << endl;

		cout << "Выберите пункт: ";
		cin >> choice;

		if (choice >= 0 && choice <= entries_count)
		{
			std::cout << endl;
			return choice;
		}

		std::cout << "Неверный выбор!\n" << endl;
	}
}
