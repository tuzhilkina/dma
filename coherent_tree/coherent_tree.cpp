#include <iostream>

// Лабораторная работа №3. Дерево на связанной памяти
// Ракутундрамбула Д.А.
// Тужилкина Н.Г.

struct Node {
	int value{ 0 };
	Node* left{ nullptr };
	Node* right{ nullptr };
};

class SvyaznDerevo {
public:
	SvyaznDerevo() = default;
	~SvyaznDerevo();

	void insert(int value);
	Node* search(int value);
	void print();

private:
	void destroyTree(Node* leaf);
	void insert(int value, Node* leaf);
	Node* search(int value, Node* leaf);
	void print(Node* leaf);

	Node* root{ nullptr };
};

SvyaznDerevo::~SvyaznDerevo() {
	destroyTree(root);
}

void SvyaznDerevo::destroyTree(Node* leaf) {
	if (leaf != nullptr) {
		destroyTree(leaf->left);
		destroyTree(leaf->right);
		delete leaf;
	}
}

void SvyaznDerevo::insert(int value, Node* leaf) {
	if (value < leaf->value) {
		if (leaf->left != nullptr)
			insert(value, leaf->left);
		else {
			leaf->left = new Node;
			leaf->left->value = value;
			leaf->left->left = nullptr;
			leaf->left->right = nullptr;
		}
	}
	else if (value >= leaf->value) {
		if (leaf->right != nullptr)
			insert(value, leaf->right);
		else {
			leaf->right = new Node;
			leaf->right->value = value;
			leaf->right->right = nullptr;
			leaf->right->left = nullptr;
		}
	}
}

void SvyaznDerevo::insert(int value) {
	if (root != nullptr)
		insert(value, root);
	else {
		root = new Node;
		root->value = value;
		root->left = nullptr;
		root->right = nullptr;
	}
}

Node* SvyaznDerevo::search(int value, Node* leaf) {
	if (leaf != nullptr) {
		if (value == leaf->value)
			return leaf;
		if (value < leaf->value)
			return search(value, leaf->left);
		else
			return search(value, leaf->right);
	}
	else return nullptr;
}

Node* SvyaznDerevo::search(int value) {
	return search(value, root);
}

void SvyaznDerevo::print() {
	print(root);
	std::cout << "\n";
}

void SvyaznDerevo::print(Node* leaf) {
	if (leaf != nullptr) {
		print(leaf->left);
		std::cout << leaf->value << " ";
		print(leaf->right);
	}
}

int main() {
	SvyaznDerevo* tree = new SvyaznDerevo();
	setlocale(LC_ALL, "Russian");
	std::cout << "Лабораторная работа №3. Дерево на связанной памяти\n";
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