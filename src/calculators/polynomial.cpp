#include "polynomial.h"
#include "../common/menu.h"

void InputPolinom(vector<int>* a) {
	cout << "Введите коэффициенты многочлена начиная со старшей степени" << endl;
	for (int i = 0; i < a->size(); i++) {
		cin >> (*a)[i];
	}

}
void SumPolinom(vector<int>* a) {
	int degree1;
	cout << "Введите степень второго многочлена: " << endl;
	cin >> degree1;
	vector<int> polinom1(degree1 + 1);
	vector<int>* polinomY1 = &polinom1;
	InputPolinom(polinomY1);
	for (int i = 0; i < polinom1.size(); i++) {
		if (i >= (a->size())) {
			a->push_back(0);
		}
		(*a)[i] = (*a)[i] + polinom1[i];
	}
}
void MinPolinom(vector<int>* a) {
	int degree1;
	cout << "Введите степень второго многочлена: " << endl;
	cin >> degree1;
	vector<int> polinom1(degree1 + 1);
	vector<int>* polinomY1 = &polinom1;
	InputPolinom(polinomY1);
	for (int i = 0; i < polinom1.size(); i++) {
		if (i >= (a->size())) {
			a->push_back(0);
		}
		(*a)[i] = (*a)[i] - polinom1[i];
	}
}
void MultNumPolinom(vector<int>* a) {
	int number;
	cout << "Введите число " << endl;
	cin >> number;
	for (int i = 0; i < a->size(); i++) {
		(*a)[i] = (*a)[i] * number;
	}
}
void ProizvPolinom(vector<int>* a) {
	vector<int> result(a->size() - 1);
	for (int i = 0; i < a->size() - 1; i++) {
		result[i] = (*a)[i] * (a->size() - 1 - i);
	}
	a->swap(result);
}
void DelPolinom(vector<int>* a) {
	int degree2;
	cout << "Введите степень делимого многочлена: " << endl;
	cin >> degree2;
	vector<int> divisor(degree2 + 1);
	InputPolinom(&divisor);
	vector<int> result(a->size() - divisor.size() + 1, 0);
	for (int i = a->size() - 1; i >= divisor.size() - 1; --i) {
		if ((*a)[i] != 0) {
			int coeff = (*a)[i] / divisor[degree2];
			result[i - degree2] = coeff;
			for (int j = 0; j <= degree2; ++j) {
				if ((i - j) >= 0)
					(*a)[i - j] -= coeff * divisor[degree2 - j];
			}
		}
	}
	a->swap(result);
}
void MultPolinom(vector<int>* a) {
	int degree2;
	cout << "Введите степень второго многочлена: " << endl;
	cin >> degree2;
	vector<int> polinom2(degree2 + 1);
	InputPolinom(&polinom2);
	vector<int> result(a->size() + polinom2.size() - 1, 0);
	for (int i = 0; i < a->size(); ++i) {
		for (int j = 0; j < polinom2.size(); ++j) {
			result[i + j] += (*a)[i] * polinom2[j];
		}
	}
	a->swap(result);
}
void OutputPolinom(vector<int>* a) {
	bool firstM = true;
	for (int i = (*a).size() - 1; i >= 0; i--) {
		if ((*a)[i] > 0) {
			if (!firstM) {
				cout << " +";
			}
			cout << " " << (*a)[i] << " * x ^ " << i;
			firstM = false;
		}
		else if ((*a)[i] < 0) {
			cout << " " << (*a)[i] << " * x ^ " << i;
			firstM = false;
		}
	}
	if (firstM) {
		cout << "0";
	}
	cout << endl;
}

void polynomial_entry() {
	setlocale(LC_ALL, "RU");
	int choice, degree;
	do {
		cout << "Выберите функцию:\n1. Сложение многочленов\n2. Вычитание многочленов\n3. Умножение многочлена на число\n4. Производная от многочлена\n5. Деление в столбик многочлена на многочлен\n6. Умножение многочлена на многочлен\n0. Выход " << endl;
		cin >> choice;
		cout << "Введите степень многочлена: " << endl;
		cin >> degree;
		if (degree <= 0) {
			cout << "Неправильная степень!" << endl;
			continue;
		}
		else {
			vector<int> polinom(degree + 1);
			vector<int>* polinomY = &polinom;
			switch (choice) {
			case 1:
				InputPolinom(polinomY);
				SumPolinom(polinomY);
				OutputPolinom(polinomY);
				break;
			case 2:
				InputPolinom(polinomY);
				MinPolinom(polinomY);
				OutputPolinom(polinomY);
				break;
			case 3:
				InputPolinom(polinomY);
				MultNumPolinom(polinomY);
				OutputPolinom(polinomY);
				break;
			case 4:
				InputPolinom(polinomY);
				ProizvPolinom(polinomY);
				OutputPolinom(polinomY);
				break;
			case 5:
				InputPolinom(polinomY);
				DelPolinom(polinomY);
				OutputPolinom(polinomY);
				break;
			case 6:
				InputPolinom(polinomY);
				MultPolinom(polinomY);
				OutputPolinom(polinomY);
				break;
			default:
				cout << "Неправильный выбор функции!" << endl;
			}
			cout << "Выберите функцию:\n1. Сложение многочленов\n2. Вычитание многочленов\n3. Умножение многочлена на число\n4. Производная от многочлена\n5. Деление в столбик многочлена на многочлен\n6. Умножение многочлена на многочлен\n0. Выход " << endl;
			cin >> choice;
		}
	} while (choice != 0);
}