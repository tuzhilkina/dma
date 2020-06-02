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

// особь: маршрут и обща€ стоимость
typedef std::pair<std::vector<int>, int> individual;

// класс представл€ющий граф
class Graph {
public:
	Graph() = default;
	~Graph() = default;
	Graph(const Graph&) = default;
	Graph& operator=(const Graph&) = default;
	Graph(const size_t& v, const int& iv) : V(v), initial_vertex(iv) { };

	// добавление ребра (начало, конец, стоимость)
	void addEdge(int v1, int v2, int weight);
	// показать все св€зи в графе
	void showGraph();
	// показать информацию о графе
	void showInfoGraph();
	// провер€ем существование ребра в графе и возвращает стоимость
	int existsEdge(int src, int dest);

	friend class Genetic;

private:
	// число вершин
	size_t V{ 0 };
	// число рЄбер
	size_t total_edges{ 0 };
	// начальна€ вершина
	int initial_vertex{ 0 };
	// map рЄбер <<начало, конец>, стоимость>
	std::map<std::pair<int, int>, int> map_edges;
};

//  ласс представл€ющий алгоритм генерации
class Genetic {
public:
	// (граф, размер попул€ции, количество поколений, процент мутаций, флаг дл€ показа попул€ции)
	Genetic(Graph* graph, const size_t& size_population, const size_t& generations, const size_t& mutation_rate, const bool& show_population = true);
	// провер€ем на действительность решение
	int isValidSolution(std::vector<int>& solution);
	// показать попул€цию
	void showPopulation();
	// делаем скрещивание
	void crossOver(std::vector<int>& parent1, std::vector<int>& parent2);
	// бинарный поиск дл€ вставки
	void insertChild(std::vector<int>& child, const int& total_cost);
	// запускаем алгоритм генерации
	void run();
	// возвращаем стоимость лучшего решени€
	int getCostBestSolution();
	// провер€ем существование хромосомы
	bool existsChromosome(const std::vector<int>& v);

private:
	// генераци€ начальной попул€ции
	void initialPopulation();

	// граф
	Graph* graph{ nullptr };
	// попул€ци€, состо€ща€ из особей
	std::vector<individual> population;
	// размер попул€ции
	size_t size_population{ 0 };
	// реальный размер попул€ции
	size_t real_size_population{ 0 };
	// количество поколений
	size_t generations{ 0 };
	// процент мутаций
	int mutation_rate{ 0 };
	// флаг дл€ показа попул€ции
	bool show_population{ true };
};

#endif