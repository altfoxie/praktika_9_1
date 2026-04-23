#include "cj.h"
#include "../common/menu.h"
#include <array>
#include <limits>
#include <string_view>

namespace {
template <typename T>
bool read_value(std::string_view prompt, T &value) {
  std::cout << prompt;
  if (std::cin >> value) {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return true;
  }

  std::cout << "Ошибка: некорректный ввод.\n";
  std::cin.clear();
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  return false;
}
} // namespace

int cj_entry()
{
    cout << "Ah shit, here we go again." << endl;
    cout << endl;

    constexpr std::string_view title = "Сан-Андреас";
    constexpr std::array<const char*, 3> entries{
        "Узнать количество денег на счету Карла",
        "Подсчитать прыжки по городу",
        "Рассчитать уважение (Respect)"
    };

    while (true)
    {
        int choice = menu_ask(title.data(), entries.data(), entries.size());
        switch (choice)
        {
        case 0:
            return 0;
        case 1:
        {
            double balance;
            if (!read_value("Введите текущий баланс Карла ($): ", balance))
            {
                break;
            }
            if (balance < 0)
            {
                cout << "Ошибка: баланс не может быть отрицательным." << endl;
                break;
            }
            double tax = balance * 0.10;
            cout << "После уплаты 10% налога Биг Смоуку осталось: $" << balance - tax << endl;
            break;
        }
        case 2:
        {
            int jumps, collected;
            if (!read_value("Введите общее количество прыжков в городе: ", jumps))
            {
                break;
            }
            if (!read_value("Введите количество собранных прыжков: ", collected))
            {
                break;
            }
            if (jumps <= 0 || collected < 0)
            {
                cout << "Ошибка: количество прыжков должно быть положительным, а собранных — неотрицательным." << endl;
                break;
            }
            if (collected > jumps)
            {
                cout << "Ошибка: собранных прыжков не может быть больше общего количества." << endl;
                break;
            }
            cout << "Осталось собрать: " << jumps - collected << " прыжков ("
                 << (double)collected / jumps * 100.0 << "% выполнено)" << endl;
            break;
        }
        case 3:
        {
            int activities, missions, territories;
            if (!read_value("Введите количество выполненных активностей: ", activities))
            {
                break;
            }
            if (!read_value("Введите количество пройденных миссий: ", missions))
            {
                break;
            }
            if (!read_value("Введите количество захваченных территорий: ", territories))
            {
                break;
            }
            if (activities < 0 || missions < 0 || territories < 0)
            {
                cout << "Ошибка: значения не могут быть отрицательными." << endl;
                break;
            }
            int respect = activities * 2 + missions * 10 + territories * 5;
            cout << "Уважение (Respect) Карла Джонсона: " << respect << " очков" << endl;
            break;
        }
        default:
            break;
        }
        cout << endl;
    }
    return 0;
}
