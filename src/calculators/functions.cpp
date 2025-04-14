#include "functions.h"

void functions_entry() {
	const char* title = "Работа с функциями";
	const char* entries[] = { "Вычисление определенного интеграла на отрезке", "Построение графика"};
	while (true)
	{
		int choice = menu_ask(title, entries, sizeof(entries) / sizeof(entries[0]));
		std::cout << "Выбрано " << choice << " но ничё не реализовано 👍" << endl;
		break;
	}
}