#include <cstddef>
#include <iostream>
#include <string>

// Лабораторная работа №3
// Смежная память
// Тужилкина Н.Г., Ракутундрамбула Д.А.
// БПМ-18-2

class Smezhn {
public:
	Smezhn() = default;
	Smezhn(const Smezhn& arr);
	Smezhn(const std::ptrdiff_t size);
	Smezhn& operator=(const Smezhn& rhs);
	~Smezhn() { delete[] data_; }
	std::ptrdiff_t size() const { return size_; }
	int& operator[](const std::ptrdiff_t i);
	const int& operator[](const std::ptrdiff_t i) const;
	void resize(const std::ptrdiff_t size);
	void insert(const std::ptrdiff_t& pos, const int& value);
	void del(const std::ptrdiff_t pos);
	void print() const;

private:
	std::ptrdiff_t capacity_{ 0 };
	std::ptrdiff_t size_{ 0 };
	int* data_{ 0 };
};

Smezhn::Smezhn(const Smezhn& obj) :
	capacity_(obj.capacity_),
	size_(obj.size_),
	data_(new int[capacity_]) {
	std::copy(obj.data_, obj.data_ + obj.size_, data_);
}

Smezhn::Smezhn(const ptrdiff_t size) : capacity_(size), size_(size) {
	if (size < 0)
		throw std::invalid_argument("Change the size of array");
	data_ = new int[capacity_];
	for (ptrdiff_t i(0); i < size; i += 1) {
		data_[i] = 0;
	}
}

Smezhn& Smezhn::operator=(const Smezhn& obj) {
	if (this != &obj) {
		delete[] data_;
		capacity_ = obj.capacity_;
		size_ = obj.size_;
		data_ = new int[capacity_] {0};
		std::copy(obj.data_, obj.data_ + obj.size_, data_);
	}
	return *this;
}

int& Smezhn::operator[] (const ptrdiff_t i) {
	if (i < 0 || size_ <= i)
		throw std::out_of_range("Index is out of range");
	return data_[i];
}

const int& Smezhn::operator[] (const ptrdiff_t i) const {
	if (i < 0 || size_ <= i)
		throw std::out_of_range("Index is out of range");
	return data_[i];
}

void Smezhn::resize(const ptrdiff_t new_size) {
	if (new_size < 0)
		throw std::invalid_argument("The size of array can not be negative");
	else if (new_size > capacity_) {
		int* buffer = new int[size_];
		std::copy(data_, data_ + size_, buffer);
		delete[] data_;
		capacity_ = new_size;
		data_ = new int[capacity_] {0};
		std::copy(buffer, buffer + size_, data_);
		size_ = new_size;
		delete[] buffer;
	}
	else {
		size_ = new_size;
	}
}

void Smezhn::insert(const std::ptrdiff_t& pos, const int& value) {
	if (pos < 0 && pos > size_)
		throw std::invalid_argument("Out of range");
	int* buffer = new int[size_+ 1];
	std::copy(data_, data_ + pos, buffer);
	buffer[pos] = value;
	std::copy(data_ + pos, data_ + size_, buffer + pos + 1);

	delete[] data_;
	capacity_ += 1;
	size_ += 1;
	data_ = new int[capacity_] {0};	
	std::copy(buffer, buffer + size_, data_);
	delete[] buffer;
}

void Smezhn::del(const std::ptrdiff_t pos) {
	if (pos < 0 && pos > size_)
		throw std::invalid_argument("Out of range");
	int* buffer = new int[size_ - 1];
	std::copy(data_, data_ + pos, buffer);
	std::copy(data_ + pos + 1, data_ + size_, buffer + pos);

	delete[] data_;
	size_ -= 1;
	data_ = new int[capacity_] {0};
	std::copy(buffer, buffer + size_, data_);
	delete[] buffer;
}

void Smezhn::print() const {
	std::cout << "\n";
	for (std::ptrdiff_t i(0); i < size_; ++i)
		std::cout << *(data_ + i) << " ";
}


int main() {
	int type(-1);
	setlocale(LC_ALL, "Russian");
	std::cout << "Создайте смежное представление. Вводите элементы, нажимая Enter после ввода очередного элемента. \nДля завершения введите текстовый символ.\n";

	Smezhn data = Smezhn();

	bool flag(false);
	size_t i(0);

	while (!flag) {
		std::string tmp;
		std::cin >> tmp;
		try {
			if (std::stoi(tmp) || tmp == "0") {
				data.resize(i + 1);
				if (tmp == "0") data[i] = 0;
				else data[i] = (std::stoi(tmp));
				++i;
			}
		}
		catch (...) {
			flag = true;
		}
	}

	data.print();

	std::cout << "\n1 - Вставить элемент по индексу.\n";
	std::cout << "2 - Удалить элемент по индексу.\n";
	std::cout << "3 - Доступ к элементу по индексу.\n";
	std::cout << "4 - Размер множества.";

	int pos(0);
	int value(0);

	while (type != 0) {
		std::cout << "\nВведите номер опции: ";
		std::cin >> type;

		switch (type) {
		case 1:
			std::cout << "\nВведите номер индекса, в который необходимо вставить элемент: ";
			std::cin >> pos;
			std::cout << "Введите значение элементa: ";
			std::cin >> value;
			data.insert(pos, value);
			data.print();
			break;
		case 2:
			std::cout << "\nВведите номер индекса удаляемого элемента: ";
			std::cin >> pos;
			data.del(pos);
			data.print();
			break;
		case 3:
			std::cout << "\nВведите номер индекса: ";
			std::cin >> pos;
			std::cout << data[pos];
			break;
		case 4:
			std::cout << "\nРазмер смежного представления: " << data.size();
			break;
		}
	}
}