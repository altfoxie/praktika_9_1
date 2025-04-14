#include <iostream>
#if defined(_WINDOWS)
#include <Windows.h>
#endif

#include "common/menu.h"
#include "calculators/matrix.h"
#include "calculators/common_fractions.h"
#include "calculators/combinatorics.h"
#include "calculators/polynomial.h"
#include "calculators/probability_and_stats.h"
#include "calculators/functions.h"

using namespace std;

int main()
{
#if defined(_WINDOWS)
	SetConsoleOutputCP(CP_UTF8);
#endif

	const char* title = "Меню выбора вида калькулятора";
	const char* entries[] = { "Матричный", "Обыкновенных дробей", "Формул комбинаторики",
		"Многочленов", "Теории вероятностей и математическая статистика", "Работа с функциями" };

	while (true)
	{
		int choice = menu_ask(title, entries, sizeof(entries) / sizeof(entries[0]));
		switch (choice)
		{
		case 0: // выход
			return 0;
		case 1: // матричный
			matrix_entry();
			break;
		case 2: // обыкновенных дробей
			common_fractions_entry();
			break;
		case 3: // формул комбинаторики
			combinatorics_entry();
			break;
		case 4: // многочленов
			polynomial_entry();
			break;
		case 5: // теории вероятностей
			probability_and_stats_entry();
			break;
		case 6: // работа с функциями
			functions_entry();
			break;
		}

		std::cout << endl;
	}

	return 0;
}