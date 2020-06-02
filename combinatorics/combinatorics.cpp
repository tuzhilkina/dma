#include <iostream>
#include <vector>
#include <string>
// ��������� �.�., ���-18-2
// ������������ ������ �1
// ������������� �����

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
	std::cout << "\n�������, ������� Enter ����� ������� ���������� �����, ���������� �������� ������� ������� �� ������� ���������.\n";
	std::cout << "��� ���������� ����� ������� ����� ��������� ������.\n";

	std::vector<int> data = userdata();

	int sum(0);
	for (int n : data) sum += n;

	std::cout << "\n���������� �������� ������� ������� �� ����������� ��������� ��������: ";
	std::cout << sum << "\n\n";
}

void multiply() {
	std::cout << "\n�������, ������� Enter ����� ������� ���������� �����, ���������� �������� ������� ������� �� ������� ���������.\n";
	std::cout << "��� ���������� ����� ������� ����� ��������� ������.\n";

	std::vector<int> data = userdata();

	int mult(1);
	for (int n : data) mult *= n;

	std::cout << "\n���������� �������� ������� ������� �� ������� ������������ ��������� ��������: ";
	std::cout << mult << "\n\n";
}

void razm_povt() {
	std::cout << "\n������� ���������� ����� ���������: ";
	int n(0);
	std::cin >> n;
	std::cout << "������� ����� �����������: ";
	int k(0);
	std::cin >> k;
	int result(1);

	for (int i(0); i < k; ++i) result *= n;

	std::cout << "���������� ���������� � ������������: ";
	std::cout << result << "\n\n";
}

void razm_bez() {
	std::cout << "\n������� ���������� ����� ���������: ";
	int n(0);
	std::cin >> n;
	std::cout << "������� ����� �����������: ";
	int k(0);
	std::cin >> k;

	int result = fact(n) / fact(n - k);

	std::cout << "���������� ���������� ��� ����������: ";
	std::cout << result << "\n\n";
}

void soch_povt() {
	std::cout << "\n������� ���������� ����� ���������: ";
	int n(0);
	std::cin >> n;
	std::cout << "������� ����� �����������: ";
	int k(0);
	std::cin >> k;

	int result = fact(n + k - 1) / (fact(k) * fact(n - 1));

	std::cout << "���������� ��������� � ������������: ";
	std::cout << result << "\n\n";
}

void soch_bez() {
	std::cout << "\n������� ���������� ����� ���������: ";
	int n(0);
	std::cin >> n;
	std::cout << "������� ����� �����������: ";
	int k(0);
	std::cin >> k;

	int result = fact(n) / (fact(k) * fact(n - k));

	std::cout << "���������� ��������� ��� ����������: ";
	std::cout << result << "\n\n";
}

void pere_povt() {
	std::cout << "\n�������, ������� Enter ����� ������� ���������� �����, ���������� ��������� ������� ����.\n";
	std::cout << "��� ���������� ����� ������� ����� ��������� ������.\n";

	std::vector<int> data = userdata();

	long int num(0);
	for (int n : data) num += n;

	long int denum(1);
	for (int n : data) denum *= fact(n);

	long int result = fact(num) / denum;

	std::cout << "\n���������� ������������ � ������������: ";
	std::cout << result << "\n\n";
}

void pere_bez() {
	std::cout << "\n������� ���������� ����� ���������: ";
	int n(0);
	std::cin >> n;

	int result = fact(n);

	std::cout << "���������� ������������ ��� ����������: ";
	std::cout << result << "\n\n";
}

int main() {
	int type(-1);

	setlocale(LC_ALL, "Russian");
	std::cout << "��������� �.�., ���-18-2\n������������ ������ �1\n������������� �����\n\n";
	std::cout << "1 - ������������� �����\n";
	std::cout << "2 - ������������� ������������\n";
	std::cout << "3 - ����� ���������� � ������������\n";
	std::cout << "4 - ����� ���������� ��� ����������\n";
	std::cout << "5 - ����� ��������� � ������������\n";
	std::cout << "6 - ����� ��������� ��� ����������\n";
	std::cout << "7 - ����� ������������ � ������������\n";
	std::cout << "8 - ����� ������������ ��� ����������\n";
	std::cout << "0 - ���������� ������ ���������\n";

	while (type != 0) {
		std::cout << "������� ����� ����� ��� ��������: ";
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