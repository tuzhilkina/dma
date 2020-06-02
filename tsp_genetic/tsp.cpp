#include "tsp.h"
using namespace std;

using namespace std;

// добавить ребро
void Graph::addEdge(int src, int dest, int weight) { 
	map_edges[make_pair(src, dest)] = weight; // добавить ребро в map
}

// проверяет, существует ли ребро
int Graph::existsEdge(int src, int dest) { 
	map<pair<int, int>, int>::iterator it = map_edges.find(make_pair(src, dest));

	if (it != map_edges.end())
		return it->second; // возвращает стоимость
	return -1;
}

// показывает все соединения графика
void Graph::showGraph() {
	map<pair<int, int>, int>::iterator it;
	for (it = map_edges.begin(); it != map_edges.end(); ++it)
		cout << it->first.first << " связан с вершиной " << it->first.second << " | вес: " << it->second << endl;
}

void Graph::showInfoGraph() {
	cout << "Информация о графе\n\n";
	cout << "Количество вершин: " << V;
	cout << "\nКоличество ребер: " << map_edges.size() << "\n";
}


Genetic::Genetic(Graph* g, const size_t& sp, const size_t& gen, const size_t& mr, const bool& s)
	: graph(g), size_population(sp), generations(gen), mutation_rate (mr), show_population(s)
{
	// проверяет, меньше ли частота мутаций, чем 0
	if (mutation_rate < 0 || mutation_rate > 100) { 
		cout << "Ошибка: mutation_rate должен быть >= 0 и <= 100\n";
		exit(1);
	}
}

// проверяет правильность решения, возвращает общую стоимость пути, иначе возвращает -1
int Genetic::isValidSolution(vector<int>& solution) {
	int total_cost(0);
	set<int> set_solution;

	// проверяет, не содержит ли повторяющиеся элементы
	for (auto& it : solution)
		set_solution.insert(it);
	if (set_solution.size() != graph->V)
		return -1;

	// проверяет, актуальны ли соединения
	for (ptrdiff_t i(0); i < graph->V; ++i) {
		// проверяет, существует ли соединение
		if (i + 1 < graph->V) {
			int cost = graph->existsEdge(solution[i], solution[i + 1]);
			if (cost == -1) return -1;
			else total_cost += cost;
		}
		// проверяет, существует ли соединение между последним городом и началом пути
		else {
			int cost = graph->existsEdge(solution[i], solution[0]);
			if (cost == -1) return -1;
			else total_cost += cost;
			break;
		}
	}
	return total_cost;
}

// проверяет существование хромосомы
bool Genetic::existsChromosome(const vector<int>& v) {
	// проверяет, существует ли в популяции
	for (auto& it : population) {
		const vector<int>& vec = it.first;
		if (equal(v.begin(), v.end(), vec.begin()))
			return true;
	}
	return false;
}

// генерирует начальную популяцию
void Genetic::initialPopulation() {
	vector<int> parent;

	// вставляет начальную вершину в родительский
	parent.push_back(graph->initial_vertex);

	// cоздает родителя: путь начинается в начальной вершине,
	// следующие вершины следуют в порядке возрастания номера 
	for (ptrdiff_t i(0); i < graph->V; ++i) {
		if (i != graph->initial_vertex)
			parent.push_back(i);
	}

	// проверяет, является ли родитель действительным
	int total_cost = isValidSolution(parent);
	if (total_cost != -1) {
		population.push_back(make_pair(parent, total_cost)); // вставляет в популяцию
		++real_size_population;
	}

	// делает случайные перестановки "поколений" раз
	// создает начальную популяцию
	for (ptrdiff_t i(0); i < generations; ++i) {
		// генерирует случайную перестановку
		std::random_shuffle(parent.begin() + 1, parent.begin() + (rand() % (graph->V - 1) + 1));
		// проверяет правильность решения и находит стоимость
		int total_cost = isValidSolution(parent); 

		// проверяет, является ли перестановка верным решением и не существует в популяции
		if (total_cost != -1 && !existsChromosome(parent)) {
			population.push_back(make_pair(parent, total_cost)); // добавить в популяцию
			++real_size_population;
		}
		if (real_size_population == size_population) // проверяет размер популяции
			break;
	}

	// проверяет, является ли real_size_population 0
	if (real_size_population == 0)
		cout << "\nПустая начальная популяция. Попробуйте еще раз запустить алгоритм ...";
	else
		// сортировка популяции по возрастанию стоимости
		sort(population.begin(),
			population.end(), 
			[](const individual& obj1, const individual& obj2) {
				return obj1.second < obj2.second;
			});
}

// добавляет ребенка в популяцию
void Genetic::insertChild(vector<int>& child, const int& total_cost) {
	ptrdiff_t imin(0);
	ptrdiff_t imax(real_size_population - 1);

	while (imax >= imin) 	{
		ptrdiff_t imid = imin + (imax - imin) / 2;

		if (total_cost == population[imid].second) {
			population.insert(population.begin() + imid, make_pair(child, total_cost));
			return;
		}
		else if (total_cost > population[imid].second)
			imin = imid + 1;
		else
			imax = imid - 1;
	}
	population.insert(population.begin() + imin, make_pair(child, total_cost));
}

void Genetic::crossOver(vector<int>& parent1, vector<int>& parent2) {
	vector<int> child1, child2;
	map<int, int> genes1, genes2;

	for (ptrdiff_t i(0); i < graph->V; ++i) {
		// изначально гены(вершины пути) не определены
		// хромосома(маршрут) - последовательность генов(вершин)
		genes1[parent1[i]] = 0;
		genes2[parent2[i]] = 0;
	}

	// генерирует две случайные точки
	int point1 = rand() % (graph->V - 1) + 1;
	int point2 = rand() % (graph->V - point1) + point1;

	// корректирует точки, если они равны
	if (point1 == point2) {
		if (point1 - 1 > 1) --point1;
		else if (point2 + 1 < graph->V) ++point2;
		else {
			int point = rand() % 10 + 1;
			if (point <= 5) ++point1;
			else ++point2;
		}
	}

	// генерирует детей
	for (ptrdiff_t i (0); i < point1; ++i) {
		// добавляет гены
		child1.push_back(parent1[i]);
		child2.push_back(parent2[i]);
		// помечает гены
		genes1[parent1[i]] = 1;
		genes2[parent2[i]] = 1;
	}
	 
	// отмечает оставшиеся гены
	for (int i = point2 + 1; i < graph->V; ++i) {
		genes1[parent1[i]] = 1;
		genes2[parent2[i]] = 1;
	}

	// здесь подстрока инвертирована
	// child1 получает гены parent2 и
	// child2 получает гены parent1
	for (int i = point2; i >= point1; i--) {
		// если ген не используется
		if (genes1[parent2[i]] == 0) { 
			child1.push_back(parent2[i]);
			// отмечает ген
			genes1[parent2[i]] = 1;
		}
		else {
			// если ген уже используется, выбирает ген, который не используется
			for (map<int, int>::iterator it = genes1.begin(); it != genes1.end(); ++it) {
				// проверяет, не используется ли
				if (it->second == 0) {
					child1.push_back(it->first);
					// помечает как использованный
					genes1[it->first] = 1;
					break;
				}
			}
		}

		// если ген не используется
		if (genes2[parent1[i]] == 0) { 
			child2.push_back(parent1[i]);
			genes2[parent1[i]] = 1; // помечает ген
		}
		else {
			// если ген уже используется, выбирает ген, который не используется
			for (map<int, int>::iterator it = genes2.begin(); it != genes2.end(); ++it) {
				// проверяет, не используется ли
				if (it->second == 0) { 
					child2.push_back(it->first);
					genes2[it->first] = 1; // помечает как использованный
					break;
				}
			}
		}
	}

	// ramaining genes: child1 получает гены parent1
	// и child2 получает гены parent2
	for (int i = point2 + 1; i < graph->V; ++i) {
		child1.push_back(parent1[i]);
		child2.push_back(parent2[i]);
	}

	// мутация
	int mutation = rand() % 100 + 1;
	// проверяет, является ли случайное число <= частота мутаций
	if (mutation <= mutation_rate) {
		// производит мутацию: смена двух генов
		int index_gene1, index_gene2;
		index_gene1 = rand() % (graph->V - 1) + 1;
		index_gene2 = rand() % (graph->V - 1) + 1;

		// делает для child1
		int aux = child1[index_gene1];
		child1[index_gene1] = child1[index_gene2];
		child1[index_gene2] = aux;

		// делает для child2
		aux = child2[index_gene1];
		child2[index_gene1] = child2[index_gene2];
		child2[index_gene2] = aux;
	}

	int total_cost_child1 = isValidSolution(child1);
	int total_cost_child2 = isValidSolution(child2);

	// проверяет, является ли решение верным и не существует в популяции
	if (total_cost_child1 != -1 && !existsChromosome(child1)) {
		// добавить ребенка в популяцию
		insertChild(child1, total_cost_child1); // использует бинарный поиск для вставки
		real_size_population++; // увеличивает значение real_size_population
	}

	// проверяет снова ...
	if (total_cost_child2 != -1 && !existsChromosome(child2)) {
		// добавить ребенка в популяцию
		insertChild(child2, total_cost_child2);// использует бинарный поиск для вставки
		real_size_population++; // увеличивает значение real_size_population
	}
}

// запускает генетический алгоритм
void Genetic::run() {
	initialPopulation(); // получает начальную популяцию
	if (real_size_population == 0)
		return;

	for (ptrdiff_t i(0); i < generations; ++i) {
		int  old_size_population = real_size_population;

		// выбирает двух родителей, которые будут участвовать в процессе размножения
		if (real_size_population >= 2) {
			if (real_size_population == 2) {
				// применение кроссовера у единственных двух родителей в популяции
				crossOver(population[0].first, population[1].first);
			}
			else {
				// real_size_population > 2
				int parent1, parent2;
				do {
					// выбираем двух случайных родителей
					parent1 = rand() % real_size_population;
					parent2 = rand() % real_size_population;
				} while (parent1 == parent2);

				// применяем кроссовер у двух родителей
				crossOver(population[parent1].first, population[parent2].first);
			}

			// получает разницу, чтобы проверить, выросла ли популяция
			int diff_population = real_size_population - old_size_population;

			if (diff_population == 2) {
				if (real_size_population > size_population) {
					// удаляет двух худших родителей популяции
					population.pop_back();
					population.pop_back();
					real_size_population -= 2;
				}
			}
			else if (diff_population == 1) {
				if (real_size_population > size_population) {
					population.pop_back(); // удаляет худшего из родителей
					--real_size_population;
				}
			}
		}
		else {
			// население содержит только 1 родителя
			crossOver(population[0].first, population[0].first);

			if (real_size_population > size_population) {
				population.pop_back(); // удаляет худшего из родителей
				--real_size_population;
			}
		}
	}

	if (show_population == true)
		showPopulation();

	cout << "\n Лучшее решение: ";
	const vector<int>& vec = population[0].first;
	for (const auto& it : vec)
		cout << it << " ";
	cout << graph->initial_vertex;
	cout << " | Стоимость: " << population[0].second;
}

int Genetic::getCostBestSolution() {
	if (real_size_population > 0)
		return population[0].second;
	return -1;
}

void Genetic::showPopulation() {
	cout << "\n Решения: \n\n ";
	for (const auto& it : population) {
		const vector<int>& vec = it.first;
		for (int i = 0; i < graph->V; ++i)
			cout << vec[i] << " ";
		cout << graph->initial_vertex;
		cout << " | Стоимость: " << it.second << "\n ";
	}
	cout << "\n Численность популяции: " << real_size_population << endl;
}