#include <iostream>
#include <vector>
#include <string>
// Тужилкина Н.Г., БПМ-18-2
// Лабораторная работа №1
// Комбинаторные схемы

std::vector<int> userdata() {
	std::vector<int> data;
	bool flag(false);

	while (!flag) {
		std::string tmp;
		std::cin >> tmp;
		try {
			data.push_back(std::stoi(tmp));
		}
		catch (...) {
			flag = true;
		}
	}
	return data;
}

long int fact(const int& n) {
	if (n < 0) return 0;
	if (n == 0) return 1;
	if (n > 0) return n * fact(n - 1);
}

void sum() {
	std::cout << "\nВведите, нажимая Enter после каждого введенного числа, количество способов выбрать элемент из каждого множества.\n";
	std::cout << "Для завершения ввода введите любой текстовый символ.\n";

	std::vector<int> data = userdata();

	int sum(0);
	for (int n : data) sum += n;

	std::cout << "\nКоличество способов выбрать элемент из объединения введенных множеств: ";
	std::cout << sum << "\n\n";
}

void multiply() {
	std::cout << "\nВведите, нажимая Enter после каждого введенного числа, количество способов выбрать элемент из каждого множества.\n";
	std::cout << "Для завершения ввода введите любой текстовый символ.\n";

	std::vector<int> data = userdata();

	int mult(1);
	for (int n : data) mult *= n;

	std::cout << "\nКоличество способов выбрать элемент из прямого произведения введенных множеств: ";
	std::cout << mult << "\n\n";
}

void razm_povt() {
	std::cout << "\nВведите количество видов элементов: ";
	int n(0);
	std::cin >> n;
	std::cout << "Введите длину расстановки: ";
	int k(0);
	std::cin >> k;
	int result(1);

	for (int i(0); i < k; ++i) result *= n;

	std::cout << "Количество размещений с повторениями: ";
	std::cout << result << "\n\n";
}

void razm_bez() {
	std::cout << "\nВведите количество видов элементов: ";
	int n(0);
	std::cin >> n;
	std::cout << "Введите длину расстановки: ";
	int k(0);
	std::cin >> k;

	int result = fact(n) / fact(n - k);

	std::cout << "Количество размещений без повторений: ";
	std::cout << result << "\n\n";
}

void soch_povt() {
	std::cout << "\nВведите количество видов элементов: ";
	int n(0);
	std::cin >> n;
	std::cout << "Введите длину расстановки: ";
	int k(0);
	std::cin >> k;

	int result = fact(n + k - 1) / (fact(k) * fact(n - 1));

	std::cout << "Количество сочетаний с повторениями: ";
	std::cout << result << "\n\n";
}

void soch_bez() {
	std::cout << "\nВведите количество видов элементов: ";
	int n(0);
	std::cin >> n;
	std::cout << "Введите длину расстановки: ";
	int k(0);
	std::cin >> k;

	int result = fact(n) / (fact(k) * fact(n - k));

	std::cout << "Количество сочетаний без повторений: ";
	std::cout << result << "\n\n";
}

void pere_povt() {
	std::cout << "\nВведите, нажимая Enter после каждого введенного числа, количество элементов каждого вида.\n";
	std::cout << "Для завершения ввода введите любой текстовый символ.\n";

	std::vector<int> data = userdata();

	long int num(0);
	for (int n : data) num += n;

	long int denum(1);
	for (int n : data) denum *= fact(n);

	long int result = fact(num) / denum;

	std::cout << "\nКоличество перестановок с повторениями: ";
	std::cout << result << "\n\n";
}

void pere_bez() {
	std::cout << "\nВведите количество видов элементов: ";
	int n(0);
	std::cin >> n;

	int result = fact(n);

	std::cout << "Количество перестановок без повторений: ";
	std::cout << result << "\n\n";
}

int main() {
	int type(-1);

	setlocale(LC_ALL, "Russian");
	std::cout << "Тужилкина Н.Г., БПМ-18-2\nЛабораторная работа №1\nКомбинаторные схемы\n\n";
	std::cout << "1 - Комбинаторная сумма\n";
	std::cout << "2 - Комбинаторное произведение\n";
	std::cout << "3 - Число размещений с повторениями\n";
	std::cout << "4 - Число размещений без повторений\n";
	std::cout << "5 - Число сочетаний с повторениями\n";
	std::cout << "6 - Число сочетаний без повторений\n";
	std::cout << "7 - Число перестановок с повторениями\n";
	std::cout << "8 - Число перестановок без повторений\n";
	std::cout << "0 - Завершение работы программы\n";

	while (type != 0) {
		std::cout << "Введите номер опции для подсчета: ";
		std::cin >> type;

		switch (type) {
		case 1:
			sum();
			break;
		case 2:
			multiply();
			break;
		case 3:
			razm_povt();
			break;
		case 4:
			razm_bez();
			break;
		case 5:
			soch_povt();
			break;
		case 6:
			soch_bez();
			break;
		case 7:
			pere_povt();
			break;
		case 8:
			pere_bez();
			break;
		}
	}
}