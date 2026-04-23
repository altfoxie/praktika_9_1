#include "cj.h"
#include "../common/menu.h"

int cj_entry()
{
    cout << "Ah shit, here we go again." << endl;
    cout << endl;

    const char *title = "Сан-Андреас";
    const char *entries[] = {"Узнать количество денег на счету Карла", "Подсчитать прыжки по городу", "Рассчитать уважение (Respect)"};

    while (true)
    {
        int choice = menu_ask(title, entries, sizeof(entries) / sizeof(entries[0]));
        switch (choice)
        {
        case 0:
            return 0;
        case 1:
        {
            double balance;
            cout << "Введите текущий баланс Карла ($): ";
            cin >> balance;
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
            cout << "Введите общее количество прыжков в городе: ";
            cin >> jumps;
            cout << "Введите количество собранных прыжков: ";
            cin >> collected;
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
            int kills, missions, territories;
            cout << "Введите количество убийств: ";
            cin >> kills;
            cout << "Введите количество пройденных миссий: ";
            cin >> missions;
            cout << "Введите количество захваченных территорий: ";
            cin >> territories;
            if (kills < 0 || missions < 0 || territories < 0)
            {
                cout << "Ошибка: значения не могут быть отрицательными." << endl;
                break;
            }
            int respect = kills * 2 + missions * 10 + territories * 5;
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
