//Ракутундрамбула, Тужилкина, БПМ-18-2
//Генерация разбиений
#include <iostream>
#include <vector>

std::vector<int> a;

void fragmentation(int n, int k, int i) {
	if (n < 0) return;
	if (n == 0) {
		for (int j(0); j < i; ++j)
			std::cout << a[j] << " ";
		std::cout << "\n";
	}
	else {
		if (n - k >= 0) {
			a[i] = k;
			fragmentation(n - k, k, i + 1);
		}
		if (k - 1 > 0)
			fragmentation(n, k - 1, i);
	}
	return;
}


int main() {
	setlocale(LC_ALL, "Russian");
	printf("Тужилкина БПМ-18-2");
	std::cout << "\n";
	printf("Генерация разбиений");
	std::cout << "\n";
	std::cout << "Введите целое число n" << "\n";
	int n;
	std::cin >> n;
	std::cout << "Разбиение числа " << n << "\n";
	for (int i = 0; i <= n; i++)
		a.push_back(0);
	fragmentation(n, n, 0);
}