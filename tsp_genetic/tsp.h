#ifndef TSP_H
#define TSP_H

#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <utility>
#include <time.h>
#include <stdlib.h>

// �����: ������� � ����� ���������
typedef std::pair<std::vector<int>, int> individual;

// ����� �������������� ����
class Graph {
public:
	Graph() = default;
	~Graph() = default;
	Graph(const Graph&) = default;
	Graph& operator=(const Graph&) = default;
	Graph(const size_t& v, const int& iv) : V(v), initial_vertex(iv) { };

	// ���������� ����� (������, �����, ���������)
	void addEdge(int v1, int v2, int weight);
	// �������� ��� ����� � �����
	void showGraph();
	// �������� ���������� � �����
	void showInfoGraph();
	// ��������� ������������� ����� � ����� � ���������� ���������
	int existsEdge(int src, int dest);

	friend class Genetic;

private:
	// ����� ������
	size_t V{ 0 };
	// ����� ����
	size_t total_edges{ 0 };
	// ��������� �������
	int initial_vertex{ 0 };
	// map ���� <<������, �����>, ���������>
	std::map<std::pair<int, int>, int> map_edges;
};

// ����� �������������� �������� ���������
class Genetic {
public:
	// (����, ������ ���������, ���������� ���������, ������� �������, ���� ��� ������ ���������)
	Genetic(Graph* graph, const size_t& size_population, const size_t& generations, const size_t& mutation_rate, const bool& show_population = true);
	// ��������� �� ���������������� �������
	int isValidSolution(std::vector<int>& solution);
	// �������� ���������
	void showPopulation();
	// ������ �����������
	void crossOver(std::vector<int>& parent1, std::vector<int>& parent2);
	// �������� ����� ��� �������
	void insertChild(std::vector<int>& child, const int& total_cost);
	// ��������� �������� ���������
	void run();
	// ���������� ��������� ������� �������
	int getCostBestSolution();
	// ��������� ������������� ���������
	bool existsChromosome(const std::vector<int>& v);

private:
	// ��������� ��������� ���������
	void initialPopulation();

	// ����
	Graph* graph{ nullptr };
	// ���������, ��������� �� ������
	std::vector<individual> population;
	// ������ ���������
	size_t size_population{ 0 };
	// �������� ������ ���������
	size_t real_size_population{ 0 };
	// ���������� ���������
	size_t generations{ 0 };
	// ������� �������
	int mutation_rate{ 0 };
	// ���� ��� ������ ���������
	bool show_population{ true };
};

#endif