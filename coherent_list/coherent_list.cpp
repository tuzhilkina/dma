#include <iostream>
#include <stdexcept>
#include <string>

// Лабораторная работа №3
// Связанная память
// Ракутундрамбула Д.А.
// Тужилкина Н.Г.
// БПМ-18-2

class Svyazn
{
public:
	Svyazn() = default;
	Svyazn(const Svyazn&);
	Svyazn& operator=(const Svyazn&);
	~Svyazn();
	void push(const ptrdiff_t& pos, const int& value);
	void push_back(const int& value);
	void pop(const ptrdiff_t& pos);
	void pop();
	bool is_empty() const;
	int size() const;
	void print() const;
	int& get(const ptrdiff_t& pos) const;

private:
	struct Node	{
		int data_{ 0 };
		Node* next_{ nullptr };
	};
	Node* end_{ nullptr };
	Node* beginning_{ nullptr };
};

Svyazn::Svyazn(const Svyazn& rhs) {
	if (!rhs.is_empty()) {
		beginning_ = new Node{ rhs.beginning_->data_, nullptr };
		end_ = beginning_;
		Node* thisIterator = beginning_;
		Node* rhsIterator = rhs.beginning_;
		while (rhsIterator->next_ != nullptr) {
			rhsIterator = rhsIterator->next_;
			thisIterator->next_ = new Node{ rhsIterator->data_, nullptr };
			thisIterator = thisIterator->next_;
			if (rhsIterator->next_ == nullptr)
				end_ = thisIterator;
		}
	}
}

Svyazn& Svyazn::operator=(const Svyazn& rhs) {
	if (this != &rhs) {
		while (!is_empty())
			pop();
		Svyazn boofer = Svyazn(rhs);
		Node* booferbeginning = boofer.beginning_;
		boofer.beginning_ = beginning_;
		beginning_ = booferbeginning;
	}
	return *this;
}

Svyazn::~Svyazn() {
	while (!is_empty()) {
		pop();
	}
}

void Svyazn::push_back(const int& value) {
	if (is_empty()) {
		end_ = new Node{ value, nullptr };
		beginning_ = end_;
	}
	else {
		end_->next_ = new Node{ value, nullptr };
		end_ = end_->next_;
	}
}

void Svyazn::push(const ptrdiff_t& pos, const int& value) {
	if (pos >= size() || pos < 0) return;
	if (pos == 0) {
		beginning_ = new Node{ value, beginning_ };
		return;
	}
	Node* it(beginning_);
	for (ptrdiff_t i(0); i < pos - 1; ++i) it = it->next_;
	Node* buffer = it->next_;
	it->next_ = new Node{ value, buffer };
}

void Svyazn::pop(const ptrdiff_t& pos) {
	if (pos >= size() || pos < 0) return;
	if (pos == 0) {
		beginning_ = beginning_->next_;
		return;
	}
	Node* it = beginning_;
	for (ptrdiff_t i(1); i < pos; ++i) it = it->next_;
	if (!is_empty()) {
		Node* kill = it->next_;
		it->next_ = it->next_->next_;
		delete kill;
	}
	if (beginning_ == nullptr)
		end_ = nullptr;
}

void Svyazn::pop() {
	if (!is_empty()) {
		Node* kill = beginning_;
		beginning_ = beginning_->next_;
		delete kill;
	}
	if (beginning_ == nullptr)
		end_ = nullptr;
}

bool Svyazn::is_empty() const {
	return (nullptr == beginning_);
}

void Svyazn::print() const {
	Node* it = beginning_;
	std::cout << it->data_ << " ";
	while (it->next_ != nullptr) {
		it = it->next_;
		std::cout << it->data_ << " ";
	}
}

int Svyazn::size() const {
	if (is_empty()) return 0;
	int size(1);
	Node* it = beginning_;
	while (it->next_ != nullptr) {
		it = it->next_;
		++size;
	}
	return size;
}

int& Svyazn::get(const ptrdiff_t& pos) const {
	if (pos < 0 || pos >= size()) throw std::out_of_range{ "" };
	if (pos == 0) return beginning_->data_;
	Node* it = beginning_;
	for (ptrdiff_t i(0); i < pos; ++i) {
		it = it->next_;
	}
	return it->data_;
}

int main() {
	int type(-1);
	setlocale(LC_ALL, "Russian");
	std::cout << "Создайте связное представление. Вводите элементы, нажимая Enter после ввода очередного элемента. \nДля завершения введите текстовый символ.\n";

	Svyazn data = Svyazn();

	bool flag(false);

	while (!flag) {
		std::string tmp;
		std::cin >> tmp;
		try {
			if (std::stoi(tmp) || tmp == "0") {
				if (tmp == "0") data.push_back(0);
				else data.push_back(std::stoi(tmp));
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
			data.push(pos, value);
			data.print();
			break;
		case 2:
			std::cout << "\nВведите номер индекса удаляемого элемента: ";
			std::cin >> pos;
			data.pop(pos);
			data.print();
			break;
		case 3:
			std::cout << "\nВведите номер индекса: ";
			std::cin >> pos;
			std::cout << data.get(pos);
			break;
		case 4:
			std::cout << "\nРазмер смежного представления: " << data.size();
			break;
		}
	}
}