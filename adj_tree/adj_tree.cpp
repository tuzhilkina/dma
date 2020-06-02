#include <iostream>
#include <vector>

// Лабораторная работа №3. Дерево на смежной памяти
// Ракутундрамбула Д.А.
// Тужилкина Н.Г.

class SmezhnDerevo {
public:
	SmezhnDerevo() = default;
	~SmezhnDerevo();

	void insert(int);
	ptrdiff_t search(int);
	void print();

private:
	void insert(int, ptrdiff_t);

	size_t capacity{ 16 };
	int* data{ new int[capacity] {0} };
};

SmezhnDerevo::~SmezhnDerevo() {
	delete[] data;
}

void SmezhnDerevo::insert(int value, ptrdiff_t i) {
	if (2 * i + 1 >= capacity) {
		int* buffer = new int[capacity * 2]{ 0 };
		std::copy(data, data + capacity, buffer);
		delete[] data;
		capacity *= 2;
		data = buffer;
		buffer = nullptr;
	}
	if (value < data[i]) {
		if (data[2 * i] != 0)
			insert(value, 2 * i);
		else
			data[2 * i] = value;
	}
	else {
		if (data[2 * i + 1] != 0)
			insert(value, 2 * i + 1);
		else 
			data[2 * i + 1] = value;
	}
}

void SmezhnDerevo::insert(int value) {
	if (data[1] != 0)
		insert(value, 1);
	else
		data[1] = value;
}

ptrdiff_t SmezhnDerevo::search(int value) {
	for (ptrdiff_t i(0); i < capacity; ++i) {
		if (data[i] == value) return i;
	}
	return 0;
}

void SmezhnDerevo::print() {
	for (ptrdiff_t i(0); i < capacity; ++i) {
		if (data[i] != 0)
			std::cout << "[" << i << "]: = " << data[i] << "\n";
	}
}


int main() {
	SmezhnDerevo* tree = new SmezhnDerevo();
	setlocale(LC_ALL, "Russian");
	std::cout << "Лабораторная работа №3. Дерево на смежной памяти\n";
	std::cout << "Тужилкина Н.Г.\n\n";
	std::cout << "-- -- -- -- -- -- -- -- -- -- -- -- 10 -- -- -- -- -- -- -- -- -- -- --\n\n";
	std::cout << "-- -- -- -- -- -- 06 -- -- -- -- -- -- -- -- -- -- -- 14 -- -- -- -- --\n\n";
	std::cout << "-- -- -- 05 -- -- -- -- -- 08 -- -- -- -- -- 11 -- -- -- -- -- 18 -- --\n\n";
	std::cout << "-- 01 -- -- -- -- -- 07 -- -- -- -- -- -- -- -- -- -- -- 15 -- -- -- 20\n\n";
	std::cout << "-- -- 04 -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --\n\n\n";

	tree->insert(10);
	tree->insert(6);
	tree->insert(14);
	tree->insert(5);
	tree->insert(8);
	tree->insert(11);
	tree->insert(18);
	tree->insert(15);
	tree->insert(20);
	tree->insert(1);
	tree->insert(4);
	tree->insert(7);
	tree->print();

	delete tree;
}