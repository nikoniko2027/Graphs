#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <list>
#include <algorithm>
#include <map>
#include <queue>
#include "Floid.h"

using namespace std;

ifstream in("input.txt");
ofstream out("Result.txt");

struct structia8 { // Структура для задания ia8
	int node;
	int inputs = 0;
	int outputs;
};

struct check { // Структура для проверки ориентированности графа
	int node;
	vector <int> tonode;
};

//////////////////////////////////////////////////////////////
struct ves { // Структура для веса ребра между узлами
	int toNode;
	int mass;
};

struct Node { // Структура узла
	int inf; // Узел
	vector <ves> smej; // Смежные
};
//////////////////////////////////////////////////////////////

class MainGraph { // Класс графа
private:
	list <Node> ML; // Список
	string Type; // Neor - неориентированный | Or - ориентированный
public:

	MainGraph() { // Конструктор-инициализатор
		ML.clear();
	}

	MainGraph(bool fl) : MainGraph() // Конструктор для чтения из файла
	{
		if (in.is_open()) { // Чтение из файла
			if (fl) {
				int x, i;
				vector <ves> smej;
				string m;
				in >> m;
				Type = m;
				while (in.peek() != EOF) {
					string m;
					in >> x;
					// cout << x << ": ";
					in >> m;
					in >> i;
					in >> m;
					for (int ii = 0; ii < i; ii++) {
						ves j;
						in >> j.toNode;
						in >> j.mass;
						smej.push_back(j);
					}
					Push(x, smej);
					smej.clear();
				}
			}
		}
	else
		cout << "Не удалось открыть файл." << endl;
	}

	MainGraph(const MainGraph &newclass) { // Конструктор копирования
		ML = newclass.ML;
		Type = newclass.Type;
	}

	~MainGraph() { // Деструктор
		ML.clear();
		Type.clear();
	}

	string GetType() {
		if (Type == "Neor")
			return "Неориентированный";
		else
			return "Ориентированный";
	}

	void Push(int i, vector <ves> smej) { // Добавление узла в список
		Node A; // Создаем ноду
		A.inf = i;
		A.smej = smej;
		ML.push_back(A); // Отправляем ее в список
	}

	void Print() { // Вывод информации обо всех узлах
		for (auto i = ML.begin(); i != ML.end(); i++) { // Цикл обхода всего списка
			cout << "[" << i->inf << "] : ";
			for (int j = 0; j < i->smej.size(); j++)
				cout << i->smej[j].toNode << "(" << i->smej[j].mass << ") ";
			cout << endl;
		}
	}

	void AddNode(int i) { // Добавление узла
		bool fl = true;
		for (auto j = ML.begin(); j != ML.end(); j++) // Цикл обхода всего списка
			if (j->inf == i) {
				fl = false;
				cout << "\nУзел [" << i << "] уже существует в данном графе!\n" << endl;
				break;
			}

		if (fl) {
			vector <ves> smej; // Инициализируем вектор указателей
			Push(i, smej); // Вызываем функцию добавления узла
		}
	}

	void AddSmej(int a, int b, int mass, bool fl) { // Добавление смежности
		if (CheckSmej(a, b, true)) {
			ves A;
			for (auto i = ML.begin(); i != ML.end(); i++) { // Цикл обхода всего списка
				if (i->inf == a) {// Для найденого узла
					A.toNode = b;
					A.mass = mass;
					i->smej.push_back(A); // Добавляем указатель на смежный узел
				}
				if (i->inf == b && !fl) {// Так же и для второго
					A.toNode = a;
					A.mass = mass;
					i->smej.push_back(A);
				}
			}
			cout << "\nРебро между узлами [" << a << "] и [" << b << "] успешно добавлено\n" << endl;
		}
	}

	void DelNode(int x) { // Удаление узла
		bool fl = false;
		for (auto i = ML.begin(); i != ML.end(); i++) // Цикл обхода всего списка
			if (i->inf == x) { // Если нашелся нужный узел
				fl = true;
				ML.erase(i); // Стриаем узел из памяти
				break;
			}
		if (!fl)
			cout << "\nУзел [" << x << "] не найден в данном графе!\n" << endl;
		else {
			vector <ves> sup; // Вспомогательный вектор
			for (auto i = ML.begin(); i != ML.end(); i++) { // Цикл обхода всего списка
				if (i->inf != x) { // Если текущий узел не является удаляемым
					for (int j = 0; j < i->smej.size(); j++) // Пробегаемся по всем его указателям
						if (i->smej[j].toNode != x)
							sup.push_back(i->smej[j]); // И переносим все, кроме указателей на удаляемый узел
					i->smej.swap(sup);
					sup.clear();
				}
			}
			cout << "\nУзел [" << x << "] успешно удален!\n" << endl;
		}
	}

	bool CheckSmej(int a, int b, bool adddel) {
		if (a == b) {
			cout << "\nВведены одинаковые узлы!\n" << endl;
			return false;
		}
		else {
			bool fla = false, flb = false;
			for (auto i = ML.begin(); i != ML.end(); i++) { // Цикл обхода всего списка
				if (i->inf == a)
					fla = true;
				else if (i->inf == b)
					flb = true;
			}
			if (!fla && !flb){
				cout << "\nУзел [" << a << "] и узел [" << b << "] отсутствуют в графе\n" << endl;
			return false;
			}
			else if (!fla && flb) {
			cout << "\nУзел [" << a << "] отсутствует в графе!\n" << endl;
			return false;
			}
			else if (fla && !flb) {
			cout << "\nУзел [" << b << "] отсутствует в графе!\n" << endl;
			return false;
			} 
			else {
				vector <check> sup;
				for (auto i = ML.begin(); i != ML.end(); i++) { // Цикл обхода всего списка
					check a;
					a.node = i->inf;
					for (int j = 0; j < i->smej.size(); j++) // Выгружаем смежные для текущего узла
						a.tonode.push_back(i->smej[j].toNode);
					sup.push_back(a);
				}
				bool fl1 = false, fl2 = false;
				for (int i = 0; i < sup.size(); i++) {
					if (sup[i].node == a)
						for (int j = 0; j < sup[i].tonode.size(); j++)
							if (sup[i].tonode[j] == b)
								fl1 = true;
					if (sup[i].node == b)
						for (int j = 0; j < sup[i].tonode.size(); j++)
							if (sup[i].tonode[j] == a)
								fl2 = true;
				}
				if (fl1 && fl2 && adddel) {
					cout << "\nМежду узлами [" << a << "] и [" << b << "] уже есть неориентированное ребро\n" << endl;
					return false;
				}
				if (!fl1 && fl2 && adddel) {
					cout << "\nМежду узлами [" << b << "] и [" << a << "] уже есть ориентированное ребро\n" << endl;
					return false;
				}
				if (fl1 && !fl2 && adddel) {
					cout << "\nМежду узлами [" << a << "] и [" << b << "] уже есть ориентированное ребро\n" << endl;
					return false;
				}
				if (!fl1 && !fl2 && !adddel) {
					cout << "\nМежду узлами [" << a << "] и [" << b << "] нет ребра\n" << endl;
					return false;
				}
				if (!fl1 && fl2 && !adddel) {
					cout << "\nМежду узлами [" << b << "] и [" << a << "] нет ориентированного ребра\n" << endl;
					return false;
				}
				if (fl1 && !fl2 && !adddel) {
					cout << "\nМежду узлами [" << a << "] и [" << b << "] нет ориентированного  ребра\n" << endl;
					return false;
				}
				return true;
			}
		}
	}

	void DelSmej(int a, int b, bool fl) { // Удаление смежных узлов "a" и "b"
		if (CheckSmej(a, b, false)) {
			vector <ves> sup; // Вспомогательный массив указателей
			for (auto i = ML.begin(); i != ML.end(); i++) { // Цикл обхода всего списка
				if (i->inf == a) { // Если нашелся нужный узел
					for (int j = 0; j < i->smej.size(); j++) // Цикл для переноса нужных указателей
						if (i->smej[j].toNode != b)
							sup.push_back(i->smej[j]); // Переносятся только указатели, не включающие в себя удаляемую смежность
					i->smej.swap(sup); // После цикла свапаем вектора и в итоге получаем вектор указателей без смежности
					sup.clear();
				}
				if (i->inf == b && !fl) { // Тоже самое для второго указателя
					for (int j = 0; j < i->smej.size(); j++)
						if (i->smej[j].toNode != a)
							sup.push_back(i->smej[j]);
					i->smej.swap(sup);
					sup.clear();
				}
			}
			cout << "\nРебро между узлами [" << a << "] и [" << b << "] успешно удалено\n" << endl;
		}
	}

	void Result() { // Вывод текущего графа в файл
		for (auto i = ML.begin(); i != ML.end(); i++) { // Цикл обхода всего списка
			out << i->inf << ": ";
			for (int j = 0; j < i->smej.size(); j++)
				out << i->smej[j].toNode << "(" << i->smej[j].mass << ") ";
			out << endl;
		}
	}

	//bool CheckValid() { // Проверка ориентированности графа
	//	bool fl = true;
	//	vector <check> sup;
	//	for (auto i = ML.begin(); i != ML.end(); i++) { // Цикл обхода всего списка
	//		check a;
	//		a.node = i->inf;
	//		for (int j = 0; j < i->smej.size(); j++) // Выгружаем смежные для текущего узла
	//			a.tonode.push_back(i->smej[j].toNode);
	//		sup.push_back(a);
	//	}
	//	for (int i = 0; i < sup.size(); i++) { // Пробегаемся по списку узлов и их смежности
	//		int m = 0;
	//		for (int j = 0; j < sup[i].tonode.size(); j++) // Пробегаемся по списку смежности у узла i
	//			for (int k = 0; k < sup.size(); k++) // Пробегаемся по всему графу, чтобы проверить связи между i смежностями
	//				if (sup[i].tonode[j] == sup[k].node) // Если для ребер i нашелся узел 
	//					for (int l = 0; l < sup[k].tonode.size(); l++) // Смотрим у него есть ли обратное ребро
	//						if (sup[k].tonode[l] == sup[i].node)
	//							m++;
	//		if (sup[i].tonode.size() != m) {
	//			fl = false;
	//			break;
	//		}
	//	}
	//	return fl;
	//}

	void ia13() {
		vector <check> sup;
		for (auto i = ML.begin(); i != ML.end(); i++) { // Цикл обхода всего списка
			check a;
			a.node = i->inf;
			for (int j = 0; j < i->smej.size(); j++) // Выгружаем смежные для текущего узла
				a.tonode.push_back(i->smej[j].toNode);
			sup.push_back(a);
		}
		bool fl = false;
		int ii, c;
		do {
			system("cls");
			cout << "Вывести те вершины орграфа, которые являются одновременно заходящими и выходящими для заданной вершины.\n" << endl;
			cout << "Введите вершину: ";
			cin >> c;
			for (int i = 0; i < sup.size(); i++)
				if (c == sup[i].node) {
					fl = true;
					ii = i;
					break;
				}
		} while (!fl);
		vector <int> m;
		for (int j = 0; j < sup[ii].tonode.size(); j++) // Пробегаемся по списку смежности у узла ii
			for (int k = 0; k < sup.size(); k++) // Пробегаемся по всему графу, чтобы проверить связи между i смежностями
				if (sup[ii].tonode[j] == sup[k].node) // Если для ребер i нашелся узел 
					for (int l = 0; l < sup[k].tonode.size(); l++) // Смотрим у него есть ли обратное ребро
						if (sup[k].tonode[l] == sup[ii].node)
							m.push_back(sup[k].node);
		if (m.size() > 0) {
			cout << endl;
			for (int i = 0; i < m.size(); i++)
				cout << "[" << m[i] << "] ";
		}
		else cout << "\nДля вершины [" << c << "] не нашлось удовлетворящих условию задания вершины.";
		cout << "\n" << endl;
	}

	void ia8() {
		vector <check> sup;
		for (auto i = ML.begin(); i != ML.end(); i++) { // Цикл обхода всего списка
			check a;
			a.node = i->inf;
			for (int j = 0; j < i->smej.size(); j++) // Выгружаем смежные для текущего узла
				a.tonode.push_back(i->smej[j].toNode);
			sup.push_back(a);
		}

			system("cls");
			cout << "Вывести те вершины, у которых полустепень исхода больше полустепени захода.\n" << endl;

			vector <structia8> m;
			for (int i = 0; i < sup.size(); i++) { // Пробегаемся по всему графу
				structia8 l; // Переменная, в которой хранится нода, кол-во входящих и кол-во исходящих
				l.node = sup[i].node;
				l.outputs = sup[i].tonode.size();
				for (int j = 0; j < sup.size(); j++) // Пробегаемся по всему графу, но не проверяем узел из первого цикла
					if (i != j)
						for (int k = 0; k < sup[j].tonode.size(); k++) // Цикл поиска переходов в првоеряемый узел
							if (sup[j].tonode[k] == sup[i].node)
								l.inputs++;
				m.push_back(l);
			}

			cout << "Результат: ";
			for (int i = 0; i < m.size(); i++)
				if (m[i].outputs > m[i].inputs)
					cout << "[" << m[i].node << "] ";
			cout << "\n" << endl;
	}

	void ib2() {
		vector <check> sup;
		vector <check> sup2;
		for (auto i = ML.begin(); i != ML.end(); i++) { // Цикл обхода всего списка
			check a;
			a.node = i->inf;
			for (int j = 0; j < i->smej.size(); j++) // Выгружаем смежные для текущего узла
				a.tonode.push_back(i->smej[j].toNode);
			sup.push_back(a);
		}

		system("cls");
		cout << "Построить граф, являющийся дополнением данного графа.\n" << endl;

		//if (Type == "Неориентированный") { // Если задание должно выполняться только для неориентированного графа
			for (int i = 0; i < sup.size(); i++) { // Пробегаемся по всем узлам графа
				check a; // Создаем новую ноду для нового графа-дополнения
				a.node = sup[i].node;
				for (int j = 0; j < sup.size(); j++) { // Опять пробегаемся по всем узлам
					bool fl = false;
					for (int k = 0; k < sup[i].tonode.size(); k++) // Пробегаемся по указателям узла
						if (sup[j].node == sup[i].tonode[k] || i == j) // Если такой указатель присутствует или сравниваем одинаковые элементы
							fl = true; // Тогда меняем переменную на тру
					if (!fl) // Если же не нашлись одинаковые, то узел заносим 
						a.tonode.push_back(sup[j].node); // Тогда заносим их в новую ноду
				}
				sup2.push_back(a); // Создаем новый граф-дополнения
			}

			cout << "Дополнение для заданного графа\n" << endl;

			for (int i = 0; i < sup2.size(); i++) {
				cout << sup2[i].node << ": ";
				for (int j = 0; j < sup2[i].tonode.size(); j++)
					cout << sup2[i].tonode[j] << " ";
				cout << endl;
			}

			cout << endl;
		//}
		//else
		//	cout << "Внимание! Граф ориентированный. Для выполнения задания нужно использовать неориентированный граф.\n" << endl;
	}

	void ll7() {
		vector <check> sup;
		for (auto i = ML.begin(); i != ML.end(); i++) { // Цикл обхода всего списка
			check a;
			a.node = i->inf;
			for (int j = 0; j < i->smej.size(); j++) // Выгружаем смежные для текущего узла
				a.tonode.push_back(i->smej[j].toNode);
			sup.push_back(a);
		}

		system("cls");
		cout << "Корнем ацикличного орграфа называется такая вершина u, что из неё существуют пути в каждую из остальных вершин орграфа. Определить, имеет ли данный ацикличный орграф корень.\n" << endl;

		if (Type != "Neor") {
			vector <int> m;
			for (int i = 0; i < sup.size(); i++)
				if (sup[i].tonode.size() == sup.size() - 1)
					m.push_back(sup[i].node);
			cout << "Найдено корней орграфа: " << m.size();
			if (m.size() > 0)
				for (int i = 0; i < m.size(); i++)
					cout << " -> [" << m[i] << "] ";
			cout << "\n" << endl;
		}
		else
			cout << "Внимание! Граф неориентированный. Для выполнения задания нужно использовать ориентированный граф.\n" << endl;
	}

	struct Node21 { // Структура для проверки ориентированности графа
		int inf; // Узел
		bool ischeck = false;
		vector <ves> smej; // Смежные
	};

	void ii21() {
		
		vector <check> sup;
		for (auto i = ML.begin(); i != ML.end(); i++) { // Цикл обхода всего списка
			check a;
			a.node = i->inf;
			for (int j = 0; j < i->smej.size(); j++) // Выгружаем смежные для текущего узла
				a.tonode.push_back(i->smej[j].toNode);
			sup.push_back(a);
		}

		system("cls");
		cout << "Проверить, можно ли из графа удалить какую-либо вершину так, чтобы получилось дерево.\n" << endl;

		for (int A = 0; A < sup.size(); A++) {

			vector<check> sup2;

			for (int B = 0; B < sup.size(); B++) {
				if (A != B) {
					check a;
					a.node = sup[B].node;
					vector <int> tn;
					for (int i = 0; i < sup[B].tonode.size(); i++)
						if (sup[A].node != sup[B].tonode[i])
							tn.push_back(sup[B].tonode[i]);
					a.tonode = tn;
					sup2.push_back(a);
				}
			}

			int max = INT_MIN;

			for (int i = 0; i < sup2.size(); i++) // Находим максимальный узел
				if (sup2[i].node > max)
					max = sup2[i].node;

			vector<vector<int>> mas;

			for (int i = 0; i <= max * 2; i++) { // Загружаем вспомогательный двумерный массив нулями
				vector<int> mas2;
				for (int j = 0; j <= max * 2; j++)
					mas2.push_back(0);
				mas.push_back(mas2);
			}

			for (int i = 0; i < sup2.size(); i++) // Если есть смежность, то в двумерном массиве ставим 1 на их пересечении
				for (int j = 0; j < sup2[i].tonode.size(); j++) {
					mas[sup2[i].node][sup2[i].tonode[j]] = 1;
				}

			int edin = 0;

			for (int i = 0; i <= max; i++) // Находим количество смежностей
				for (int j = 0; j <= max; j++)
					if (mas[i][j] == 1)
						edin++;

			edin /= 2;

			if (sup2.size() - edin == 1)
				cout << "Если удалить узел [" << sup[A].node << "], то получится дерево." << "\n\n";
			else
				cout << "Если удалить узел [" << sup[A].node << "], то дерево не получится." << "\n\n";
		}
	}

	void Prim() {
		map<int, map<int, int>> dist; // Растояние
		map<int, vector<pair<int, int>>> edges; // Ребра

		for (auto i = ML.begin(); i != ML.end(); i++) { // Цикл обхода всего списка
			edges[i->inf];
			for (int j = 0; j < i->smej.size(); j++) { // Смежные для текущей вершины
				edges[i->inf].push_back({ i->smej[j].toNode, i->smej[j].mass });
				dist[i->inf][i->smej[j].toNode] = i->smej[j].mass;
			}
		}

		map<int, bool> visited; // Пара ключ-значение для посещённых вершин
		map<int, int> mincost; // Пара ключ-значение для минимальной стоимости
		map<int, int> from; // Пара ключ-значение для исходящих рёбер

		vector<pair<int, int>> ans; // Список вершин в порядке остовного дерева

		int INF = INT_MAX;

		for (auto it = edges.begin(); it != edges.end(); it++) { //цикл обхода всего списка
			int to = it->first; // Первое значение - вершина
			mincost[to] = INF; // Минимальная стоимость принимается за «бесконечность»
		}

		mincost[edges.begin()->first] = 0; // Минимальная стоимость приравнивается нулю
		int sumcost = 0; // Стоимость остовного дерева  приравнивается нулю

		for (int i = 0; i < edges.size(); i++) { // Цикл обхода всего списка
			int v = 0;
			for (auto it = edges.begin(); it != edges.end(); it++) { // Цикл обхода всего списка
				int to = it->first; // Первое значение - вершина
				if (!visited.count(to) && (v == 0 || mincost[to] < mincost[v])) // Если вершина не была посещена и текущая минимальная стоимость меньше предыдущей
					v = to; // То присвоить новое значение
			}

			if (mincost[v] == INF) { // Если минимальное значение равно «максимуму»
				cout << "\nНе существует минимального остовного дерева!\n\n";
				return;
			}

			visited[v] = true; // Посещение вершины

			if (from.count(v)) {
				ans.push_back({ v, from[v] }); // Заполнение списка остовного дерева
				sumcost += dist[v][from[v]]; // Стоимость остовного дерева
			}

			for (auto it = edges[v].begin(); it != edges[v].end(); it++) { // Цикл обхода всего списка
				int to = it->first; // Первое значение - вершина
				int cost = it->second; // Второе значение - стоимость
				if (cost < mincost[to]) { // Если стоимость меньше минимальной стоимости,
					mincost[to] = cost; //То минимальная стоимость принимает значение стоимости
					from[to] = v; // И присвоить новое значение
				}
			}
		}
		cout << "Минимальное остовное дерево\n\nСписок рёбер:\n";

		for (int i = 0; i < ans.size(); i++)
			cout << ans[i].first << " - " << ans[i].second << endl;

		cout << "\nСтоимость остовного дерева: " << sumcost << endl << endl;
	}

	void iv_a5() {

		vector <check> sup;
		for (auto i = ML.begin(); i != ML.end(); i++) { // Цикл обхода всего списка
			check a;
			a.node = i->inf;
			for (int j = 0; j < i->smej.size(); j++) // Выгружаем смежные для текущего узла
				a.tonode.push_back(i->smej[j].toNode);
			sup.push_back(a);
		}

		int max = INT_MIN;

		for (int i = 0; i < sup.size(); i++) // Находим максимальный узел
			if (sup[i].node > max)
				max = sup[i].node;

		vector<vector<int>> matrix;

		for (int i = 0; i < max; i++) { // Загружаем вспомогательный двумерный массив нулями
			vector<int> mas2;
			for (int j = 0; j < max; j++)
				mas2.push_back(0);
			matrix.push_back(mas2);
		}

		for (auto i = ML.begin(); i != ML.end(); i++) // Цикл обхода всего списка
			for (int j = 0; j < i->smej.size(); j++) // Выгружаем смежные для текущего узла
				matrix[i->inf - 1][i->smej[j].toNode - 1] = i->smej[j].mass;

		bool fl = false;
		int c;
		do {
			system("cls");
			cout << "Вывести длины кратчайших путей от u до всех остальных вершин.\n" << endl;

			cout << "\nВведите узел графа, от которого будет вестись поиск: ";
			cin >> c;

			for (int i = 0; i < sup.size(); i++)
				if (sup[i].node == c) {
					fl = true;
					break;
				}

			if (!fl)
				cout << "\nУзла с номером [" << c << "] нет в веденном графе.";


		} while (!fl);

		cout << endl;

		const int Inf = 30000;
		for (int A = 0; A < sup.size(); A++) {
			if (sup[A].node != c) {

				vector <int> d(sup.size(), Inf);
				d[c - 1] = 0;
				priority_queue <pair <int, int > > q;
				q.push(make_pair(0, c - 1));
				while (!q.empty()) {
					int len = -q.top().first;
					int v = q.top().second;
					q.pop();
					if (len > d[v]) continue;
					for (int i = 0; i < sup.size(); i++) {
						int to = i;
						int length = matrix[v][i];
						if (d[to] > d[v] + length && length >= 0) {
							d[to] = d[v] + length;
							q.push(make_pair(-d[to], to));
						}
					}
				}
				if (d[sup[A].node - 1] == Inf)
					cout << "False" << endl;
				else
					cout << "Из " << c << " в " << sup[A].node << " = " << d[sup[A].node - 1] << endl << endl;
			}
		}
	}

	void iv_b13() {

		vector <check> sup; // Данный вектор содержит в себе графы без веса

		for (auto i = ML.begin(); i != ML.end(); i++) { // Цикл обхода всего списка
			check a;
			a.node = i->inf;
			for (int j = 0; j < i->smej.size(); j++) // Выгружаем смежные для текущего узла
				a.tonode.push_back(i->smej[j].toNode);
			sup.push_back(a);
		}

		bool fl = false, fl1 = false, fl2 = false;
		int c, v1, v2;


		do {
			system("cls");
			cout << "Вывести кратчайшие пути из вершины u до v1 и v2.\n" << endl;

			cout << "\nВведите узел графа, от которого будет вестись поиск: ";
			cin >> c;

			cout << "\nВведите первый узел графа, до которого будет вестись поиск: ";
			cin >> v1;

			cout << "\nВведите второй узел графа, до которого будет вестись поиск: ";
			cin >> v2;

			cout << endl;

			for (int i = 0; i < sup.size(); i++) {
				if (sup[i].node == c)
					fl = true;
				if (sup[i].node == v1)
					fl1 = true;
				if (sup[i].node == v2)
					fl2 = true;
			}

			if (!fl)
				cout << "\nУзла с номером [" << c << "] нет в веденном графе.\n";
			if (!fl2)
				cout << "\nУзла с номером [" << v1 << "] нет в веденном графе.\n";
			if (!fl2)
				cout << "\nУзла с номером [" << v2 << "] нет в веденном графе.\n";

		} while (!fl && !fl1 && !fl2);

		int max = INT_MIN;

		for (int i = 0; i < sup.size(); i++) // Находим максимальный узел
			if (sup[i].node > max)
				max = sup[i].node;

		vector<vector<int>> matrix; // Матрица смежности -> индекс массива является узлом. Пересечение столбца со строкой хранит вес.

		for (int i = 0; i < max; i++) { // Загружаем вспомогательный двумерный массив нулями
			vector<int> mas2;
			for (int j = 0; j <= max; j++)
				mas2.push_back(0);
			matrix.push_back(mas2);
		}

		for (auto i = ML.begin(); i != ML.end(); i++) // Цикл обхода всего списка
			for (int j = 0; j < i->smej.size(); j++) // Выгружаем смежные для текущего узла
				matrix[i->inf - 1][i->smej[j].toNode - 1] = i->smej[j].mass;

		Spisok A;

		A.Vvod_Ves(matrix, c, v1, v2);
		A.Reshenie();
		A.Reshenie2();
	}

	void iv_c14() {
		
		vector <check> sup; // Данный вектор содержит в себе графы без веса

		for (auto i = ML.begin(); i != ML.end(); i++) { // Цикл обхода всего списка
			check a;
			a.node = i->inf;
			for (int j = 0; j < i->smej.size(); j++) // Выгружаем смежные для текущего узла
				a.tonode.push_back(i->smej[j].toNode);
			sup.push_back(a);
		}

		bool fl = false, fl1 = false, fl2 = false;
		int c, v1, v2;

		do { 
			system("cls");
			cout << "Вывести кратчайшие пути из вершины u до v1 и v2.\n" << endl;

			cout << "\nВведите узел графа, от которого будет вестись поиск: ";
			cin >> c;

			cout << endl;

			for (int i = 0; i < sup.size(); i++)
				if (sup[i].node == c)
					fl = true;

			if (!fl)
				cout << "\nУзла с номером [" << c << "] нет в веденном графе.\n";

		} while (!fl);

		int max = INT_MIN;

		for (int i = 0; i < sup.size(); i++) // Находим максимальный узел
			if (sup[i].node > max)
				max = sup[i].node;

		vector<vector<int>> matrix; // Матрица смежности -> индекс массива является узлом. Пересечение столбца со строкой хранит вес.

		for (int i = 0; i < max; i++) { // Загружаем вспомогательный двумерный массив нулями
			vector<int> mas2;
			for (int j = 0; j <= max; j++)
				mas2.push_back(0);
			matrix.push_back(mas2);
		}

		for (auto i = ML.begin(); i != ML.end(); i++) // Цикл обхода всего списка
			for (int j = 0; j < i->smej.size(); j++) // Выгружаем смежные для текущего узла
				matrix[i->inf - 1][i->smej[j].toNode - 1] = i->smej[j].mass;

		vector <int> x;

		for (int i = 0; i < sup.size(); i++)
			x.push_back(sup[i].node);

		Spisok A;

		A.Vvod_Ves2(matrix, x, c);
	}

};