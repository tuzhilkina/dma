#include <iostream>
#include <array>

// Сортировка всплытием Флойда
// Тужилкина Н.Г.
// БПМ-18-2

class tree {
public:
    tree();
    ~tree() = default;
    void surface(ptrdiff_t i, ptrdiff_t k);
    void sort();
    void print();

private:
    std::array<int, 17> data{ 0 };
    size_t n{ data.size() - 1 };
};

tree::tree() {
    for (ptrdiff_t i(1); i <= n; ++i)
        data[i] = std::rand() % 100;
}

void tree::print() {
    for (ptrdiff_t i(1); i <= n; ++i)
        std::cout << data[i] << " ";
    std::cout << "\n";
}

void tree::surface(ptrdiff_t i, ptrdiff_t k) {
    int j(0), m(2 * i);
    int copy(data[i]);
    while (m <= k) {
        if (m == k) j = m;
        else
            if (data[m] > data[m + 1]) j = m;
            else j = m + 1;
        if (data[j] > copy) {
            data[i] = data[j];
            i = j;
            m = 2 * i;
        }
        else break;
    }
    data[i] = copy;
}

void tree::sort() {
    int w(0);
    for (ptrdiff_t i(n / 2); i >= 2; --i)
        surface(i, n);
    for (ptrdiff_t i(n); i >= 2; --i) {
        surface(1, i);
        w = data[i];
        data[i] = data[1];
        data[1] = w;
    }
}



int main() {
    setlocale(LC_ALL, "Russian");
    std::cout << "Лабораторная работа №6. Сортировка всплытием Флойда\n";
    std::cout << "Тужилкина Н.Г., БПМ-18-2\n";
    std::cout << "\nНеотсортированный массив:\n";
    tree data = tree();
    data.print();
    data.sort();
    std::cout << "\nОтсортированный массив:\n";
    data.print();
}
