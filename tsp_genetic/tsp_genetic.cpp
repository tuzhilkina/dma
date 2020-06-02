#include <iostream>
#include "tsp.h"
using namespace std;

int main() {
	setlocale(LC_ALL, "Russian");
	srand(time(NULL)); // ��������� �����

	// ������� graph1 � �����������: ���������� ������ � ��������� �������
	Graph* graph1 = new Graph(10, 0);
	// ��������� �����
	graph1->addEdge(0, 1, 5);
	graph1->addEdge(0, 9, 6);
	graph1->addEdge(1, 9, 10);
	graph1->addEdge(1, 2, 13);
	graph1->addEdge(1, 8, 26);
	graph1->addEdge(8, 9, 14);
	graph1->addEdge(6, 9, 16);
	graph1->addEdge(8, 6, 20);
	graph1->addEdge(2, 8, 15);
	graph1->addEdge(2, 3, 7);
	graph1->addEdge(2, 7, 28);
	graph1->addEdge(3, 8, 10);
	graph1->addEdge(3, 7, 8);
	graph1->addEdge(3, 4, 9);
	graph1->addEdge(4, 7, 3);
	graph1->addEdge(4, 5, 9);
	graph1->addEdge(5, 7, 6);
	graph1->addEdge(5, 8, 13);
	graph1->addEdge(7, 8, 3);
	graph1->addEdge(7, 6, 18);
	graph1->addEdge(5, 6, 10);

	// (����, ������ ���������, ���������� ���������, ������� �������, ���� ��� ������ ���������)
	Genetic genetic(graph1, 30, 100, 10, true);

	const clock_t begin_time = clock(); // �������� �����
	genetic.run(); // ��������� ������������ ��������
	cout << "\n\n ����� ������ ������������� ���������: " << float(clock() - begin_time) / CLOCKS_PER_SEC << " ������.\n\n"; // ���������� ����� � ��������
}
