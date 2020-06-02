//��������� �.�. ���-18-2
//���������� � ������������ �������� 
#include <iostream>
#include <vector>

void sortaddress(std::vector<int>& a, int n) {
	int r(a[0]), s(a[0]);
	for (size_t i = 1; i < a.size(); ++i) { //����� ��������� � ��������
		if (r > a[i])
			r = a[i];
		else
			if (s < a[i])
				s = a[i];
	}
	std::vector<int> c(s + 1);
	for (size_t i = 0; i < n; ++i)
		c[a[i]] += 1;
	int k(0);
	for (int i = r; i <= s; ++i) {
		while (c[i] != 0) {
			a[k] = i;
			c[i] -= 1;
			++k;
		}
	}
}

int main() {
	using namespace std;
	setlocale(LC_ALL, "Russian");
	printf("��������� ���-18-2");
	std::cout << "\n";
	printf("���������� � ������������ �������� ");
	std::cout << "\n";
	cout << "������� ����� ����� n - ���������� ���������" << "\n";
	int n;
	cin >> n;
	std::vector<int> k(n);
	cout << "������� n ���������" << "\n";
	for (int i = 0; i < n; i++)
		cin >> k[i];
	sortaddress(k, n);
	cout << "��������������� ������:" << "\n";
	for (int i = 0; i < n; i++)
		cout << k[i] << " ";
	cout << "\n";
	return 0;
}