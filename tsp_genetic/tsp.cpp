#include "tsp.h"
using namespace std;

using namespace std;

// �������� �����
void Graph::addEdge(int src, int dest, int weight) { 
	map_edges[make_pair(src, dest)] = weight; // �������� ����� � map
}

// ���������, ���������� �� �����
int Graph::existsEdge(int src, int dest) { 
	map<pair<int, int>, int>::iterator it = map_edges.find(make_pair(src, dest));

	if (it != map_edges.end())
		return it->second; // ���������� ���������
	return -1;
}

// ���������� ��� ���������� �������
void Graph::showGraph() {
	map<pair<int, int>, int>::iterator it;
	for (it = map_edges.begin(); it != map_edges.end(); ++it)
		cout << it->first.first << " ������ � �������� " << it->first.second << " | ���: " << it->second << endl;
}

void Graph::showInfoGraph() {
	cout << "���������� � �����\n\n";
	cout << "���������� ������: " << V;
	cout << "\n���������� �����: " << map_edges.size() << "\n";
}


Genetic::Genetic(Graph* g, const size_t& sp, const size_t& gen, const size_t& mr, const bool& s)
	: graph(g), size_population(sp), generations(gen), mutation_rate (mr), show_population(s)
{
	// ���������, ������ �� ������� �������, ��� 0
	if (mutation_rate < 0 || mutation_rate > 100) { 
		cout << "������: mutation_rate ������ ���� >= 0 � <= 100\n";
		exit(1);
	}
}

// ��������� ������������ �������, ���������� ����� ��������� ����, ����� ���������� -1
int Genetic::isValidSolution(vector<int>& solution) {
	int total_cost(0);
	set<int> set_solution;

	// ���������, �� �������� �� ������������� ��������
	for (auto& it : solution)
		set_solution.insert(it);
	if (set_solution.size() != graph->V)
		return -1;

	// ���������, ��������� �� ����������
	for (ptrdiff_t i(0); i < graph->V; ++i) {
		// ���������, ���������� �� ����������
		if (i + 1 < graph->V) {
			int cost = graph->existsEdge(solution[i], solution[i + 1]);
			if (cost == -1) return -1;
			else total_cost += cost;
		}
		// ���������, ���������� �� ���������� ����� ��������� ������� � ������� ����
		else {
			int cost = graph->existsEdge(solution[i], solution[0]);
			if (cost == -1) return -1;
			else total_cost += cost;
			break;
		}
	}
	return total_cost;
}

// ��������� ������������� ���������
bool Genetic::existsChromosome(const vector<int>& v) {
	// ���������, ���������� �� � ���������
	for (auto& it : population) {
		const vector<int>& vec = it.first;
		if (equal(v.begin(), v.end(), vec.begin()))
			return true;
	}
	return false;
}

// ���������� ��������� ���������
void Genetic::initialPopulation() {
	vector<int> parent;

	// ��������� ��������� ������� � ������������
	parent.push_back(graph->initial_vertex);

	// c������ ��������: ���� ���������� � ��������� �������,
	// ��������� ������� ������� � ������� ����������� ������ 
	for (ptrdiff_t i(0); i < graph->V; ++i) {
		if (i != graph->initial_vertex)
			parent.push_back(i);
	}

	// ���������, �������� �� �������� ��������������
	int total_cost = isValidSolution(parent);
	if (total_cost != -1) {
		population.push_back(make_pair(parent, total_cost)); // ��������� � ���������
		++real_size_population;
	}

	// ������ ��������� ������������ "���������" ���
	// ������� ��������� ���������
	for (ptrdiff_t i(0); i < generations; ++i) {
		// ���������� ��������� ������������
		std::random_shuffle(parent.begin() + 1, parent.begin() + (rand() % (graph->V - 1) + 1));
		// ��������� ������������ ������� � ������� ���������
		int total_cost = isValidSolution(parent); 

		// ���������, �������� �� ������������ ������ �������� � �� ���������� � ���������
		if (total_cost != -1 && !existsChromosome(parent)) {
			population.push_back(make_pair(parent, total_cost)); // �������� � ���������
			++real_size_population;
		}
		if (real_size_population == size_population) // ��������� ������ ���������
			break;
	}

	// ���������, �������� �� real_size_population 0
	if (real_size_population == 0)
		cout << "\n������ ��������� ���������. ���������� ��� ��� ��������� �������� ...";
	else
		// ���������� ��������� �� ����������� ���������
		sort(population.begin(),
			population.end(), 
			[](const individual& obj1, const individual& obj2) {
				return obj1.second < obj2.second;
			});
}

// ��������� ������� � ���������
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
		// ���������� ����(������� ����) �� ����������
		// ���������(�������) - ������������������ �����(������)
		genes1[parent1[i]] = 0;
		genes2[parent2[i]] = 0;
	}

	// ���������� ��� ��������� �����
	int point1 = rand() % (graph->V - 1) + 1;
	int point2 = rand() % (graph->V - point1) + point1;

	// ������������ �����, ���� ��� �����
	if (point1 == point2) {
		if (point1 - 1 > 1) --point1;
		else if (point2 + 1 < graph->V) ++point2;
		else {
			int point = rand() % 10 + 1;
			if (point <= 5) ++point1;
			else ++point2;
		}
	}

	// ���������� �����
	for (ptrdiff_t i (0); i < point1; ++i) {
		// ��������� ����
		child1.push_back(parent1[i]);
		child2.push_back(parent2[i]);
		// �������� ����
		genes1[parent1[i]] = 1;
		genes2[parent2[i]] = 1;
	}
	 
	// �������� ���������� ����
	for (int i = point2 + 1; i < graph->V; ++i) {
		genes1[parent1[i]] = 1;
		genes2[parent2[i]] = 1;
	}

	// ����� ��������� �������������
	// child1 �������� ���� parent2 �
	// child2 �������� ���� parent1
	for (int i = point2; i >= point1; i--) {
		// ���� ��� �� ������������
		if (genes1[parent2[i]] == 0) { 
			child1.push_back(parent2[i]);
			// �������� ���
			genes1[parent2[i]] = 1;
		}
		else {
			// ���� ��� ��� ������������, �������� ���, ������� �� ������������
			for (map<int, int>::iterator it = genes1.begin(); it != genes1.end(); ++it) {
				// ���������, �� ������������ ��
				if (it->second == 0) {
					child1.push_back(it->first);
					// �������� ��� ��������������
					genes1[it->first] = 1;
					break;
				}
			}
		}

		// ���� ��� �� ������������
		if (genes2[parent1[i]] == 0) { 
			child2.push_back(parent1[i]);
			genes2[parent1[i]] = 1; // �������� ���
		}
		else {
			// ���� ��� ��� ������������, �������� ���, ������� �� ������������
			for (map<int, int>::iterator it = genes2.begin(); it != genes2.end(); ++it) {
				// ���������, �� ������������ ��
				if (it->second == 0) { 
					child2.push_back(it->first);
					genes2[it->first] = 1; // �������� ��� ��������������
					break;
				}
			}
		}
	}

	// ramaining genes: child1 �������� ���� parent1
	// � child2 �������� ���� parent2
	for (int i = point2 + 1; i < graph->V; ++i) {
		child1.push_back(parent1[i]);
		child2.push_back(parent2[i]);
	}

	// �������
	int mutation = rand() % 100 + 1;
	// ���������, �������� �� ��������� ����� <= ������� �������
	if (mutation <= mutation_rate) {
		// ���������� �������: ����� ���� �����
		int index_gene1, index_gene2;
		index_gene1 = rand() % (graph->V - 1) + 1;
		index_gene2 = rand() % (graph->V - 1) + 1;

		// ������ ��� child1
		int aux = child1[index_gene1];
		child1[index_gene1] = child1[index_gene2];
		child1[index_gene2] = aux;

		// ������ ��� child2
		aux = child2[index_gene1];
		child2[index_gene1] = child2[index_gene2];
		child2[index_gene2] = aux;
	}

	int total_cost_child1 = isValidSolution(child1);
	int total_cost_child2 = isValidSolution(child2);

	// ���������, �������� �� ������� ������ � �� ���������� � ���������
	if (total_cost_child1 != -1 && !existsChromosome(child1)) {
		// �������� ������� � ���������
		insertChild(child1, total_cost_child1); // ���������� �������� ����� ��� �������
		real_size_population++; // ����������� �������� real_size_population
	}

	// ��������� ����� ...
	if (total_cost_child2 != -1 && !existsChromosome(child2)) {
		// �������� ������� � ���������
		insertChild(child2, total_cost_child2);// ���������� �������� ����� ��� �������
		real_size_population++; // ����������� �������� real_size_population
	}
}

// ��������� ������������ ��������
void Genetic::run() {
	initialPopulation(); // �������� ��������� ���������
	if (real_size_population == 0)
		return;

	for (ptrdiff_t i(0); i < generations; ++i) {
		int  old_size_population = real_size_population;

		// �������� ���� ���������, ������� ����� ����������� � �������� �����������
		if (real_size_population >= 2) {
			if (real_size_population == 2) {
				// ���������� ���������� � ������������ ���� ��������� � ���������
				crossOver(population[0].first, population[1].first);
			}
			else {
				// real_size_population > 2
				int parent1, parent2;
				do {
					// �������� ���� ��������� ���������
					parent1 = rand() % real_size_population;
					parent2 = rand() % real_size_population;
				} while (parent1 == parent2);

				// ��������� ��������� � ���� ���������
				crossOver(population[parent1].first, population[parent2].first);
			}

			// �������� �������, ����� ���������, ������� �� ���������
			int diff_population = real_size_population - old_size_population;

			if (diff_population == 2) {
				if (real_size_population > size_population) {
					// ������� ���� ������ ��������� ���������
					population.pop_back();
					population.pop_back();
					real_size_population -= 2;
				}
			}
			else if (diff_population == 1) {
				if (real_size_population > size_population) {
					population.pop_back(); // ������� ������� �� ���������
					--real_size_population;
				}
			}
		}
		else {
			// ��������� �������� ������ 1 ��������
			crossOver(population[0].first, population[0].first);

			if (real_size_population > size_population) {
				population.pop_back(); // ������� ������� �� ���������
				--real_size_population;
			}
		}
	}

	if (show_population == true)
		showPopulation();

	cout << "\n ������ �������: ";
	const vector<int>& vec = population[0].first;
	for (const auto& it : vec)
		cout << it << " ";
	cout << graph->initial_vertex;
	cout << " | ���������: " << population[0].second;
}

int Genetic::getCostBestSolution() {
	if (real_size_population > 0)
		return population[0].second;
	return -1;
}

void Genetic::showPopulation() {
	cout << "\n �������: \n\n ";
	for (const auto& it : population) {
		const vector<int>& vec = it.first;
		for (int i = 0; i < graph->V; ++i)
			cout << vec[i] << " ";
		cout << graph->initial_vertex;
		cout << " | ���������: " << it.second << "\n ";
	}
	cout << "\n ����������� ���������: " << real_size_population << endl;
}