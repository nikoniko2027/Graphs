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

struct structia8 { // ��������� ��� ������� ia8
	int node;
	int inputs = 0;
	int outputs;
};

struct check { // ��������� ��� �������� ����������������� �����
	int node;
	vector <int> tonode;
};

//////////////////////////////////////////////////////////////
struct ves { // ��������� ��� ���� ����� ����� ������
	int toNode;
	int mass;
};

struct Node { // ��������� ����
	int inf; // ����
	vector <ves> smej; // �������
};
//////////////////////////////////////////////////////////////

class MainGraph { // ����� �����
private:
	list <Node> ML; // ������
	string Type; // Neor - ����������������� | Or - ���������������
public:

	MainGraph() { // �����������-�������������
		ML.clear();
	}

	MainGraph(bool fl) : MainGraph() // ����������� ��� ������ �� �����
	{
		if (in.is_open()) { // ������ �� �����
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
		cout << "�� ������� ������� ����." << endl;
	}

	MainGraph(const MainGraph &newclass) { // ����������� �����������
		ML = newclass.ML;
		Type = newclass.Type;
	}

	~MainGraph() { // ����������
		ML.clear();
		Type.clear();
	}

	string GetType() {
		if (Type == "Neor")
			return "�����������������";
		else
			return "���������������";
	}

	void Push(int i, vector <ves> smej) { // ���������� ���� � ������
		Node A; // ������� ����
		A.inf = i;
		A.smej = smej;
		ML.push_back(A); // ���������� �� � ������
	}

	void Print() { // ����� ���������� ��� ���� �����
		for (auto i = ML.begin(); i != ML.end(); i++) { // ���� ������ ����� ������
			cout << "[" << i->inf << "] : ";
			for (int j = 0; j < i->smej.size(); j++)
				cout << i->smej[j].toNode << "(" << i->smej[j].mass << ") ";
			cout << endl;
		}
	}

	void AddNode(int i) { // ���������� ����
		bool fl = true;
		for (auto j = ML.begin(); j != ML.end(); j++) // ���� ������ ����� ������
			if (j->inf == i) {
				fl = false;
				cout << "\n���� [" << i << "] ��� ���������� � ������ �����!\n" << endl;
				break;
			}

		if (fl) {
			vector <ves> smej; // �������������� ������ ����������
			Push(i, smej); // �������� ������� ���������� ����
		}
	}

	void AddSmej(int a, int b, int mass, bool fl) { // ���������� ���������
		if (CheckSmej(a, b, true)) {
			ves A;
			for (auto i = ML.begin(); i != ML.end(); i++) { // ���� ������ ����� ������
				if (i->inf == a) {// ��� ��������� ����
					A.toNode = b;
					A.mass = mass;
					i->smej.push_back(A); // ��������� ��������� �� ������� ����
				}
				if (i->inf == b && !fl) {// ��� �� � ��� �������
					A.toNode = a;
					A.mass = mass;
					i->smej.push_back(A);
				}
			}
			cout << "\n����� ����� ������ [" << a << "] � [" << b << "] ������� ���������\n" << endl;
		}
	}

	void DelNode(int x) { // �������� ����
		bool fl = false;
		for (auto i = ML.begin(); i != ML.end(); i++) // ���� ������ ����� ������
			if (i->inf == x) { // ���� ������� ������ ����
				fl = true;
				ML.erase(i); // ������� ���� �� ������
				break;
			}
		if (!fl)
			cout << "\n���� [" << x << "] �� ������ � ������ �����!\n" << endl;
		else {
			vector <ves> sup; // ��������������� ������
			for (auto i = ML.begin(); i != ML.end(); i++) { // ���� ������ ����� ������
				if (i->inf != x) { // ���� ������� ���� �� �������� ���������
					for (int j = 0; j < i->smej.size(); j++) // ����������� �� ���� ��� ����������
						if (i->smej[j].toNode != x)
							sup.push_back(i->smej[j]); // � ��������� ���, ����� ���������� �� ��������� ����
					i->smej.swap(sup);
					sup.clear();
				}
			}
			cout << "\n���� [" << x << "] ������� ������!\n" << endl;
		}
	}

	bool CheckSmej(int a, int b, bool adddel) {
		if (a == b) {
			cout << "\n������� ���������� ����!\n" << endl;
			return false;
		}
		else {
			bool fla = false, flb = false;
			for (auto i = ML.begin(); i != ML.end(); i++) { // ���� ������ ����� ������
				if (i->inf == a)
					fla = true;
				else if (i->inf == b)
					flb = true;
			}
			if (!fla && !flb){
				cout << "\n���� [" << a << "] � ���� [" << b << "] ����������� � �����\n" << endl;
			return false;
			}
			else if (!fla && flb) {
			cout << "\n���� [" << a << "] ����������� � �����!\n" << endl;
			return false;
			}
			else if (fla && !flb) {
			cout << "\n���� [" << b << "] ����������� � �����!\n" << endl;
			return false;
			} 
			else {
				vector <check> sup;
				for (auto i = ML.begin(); i != ML.end(); i++) { // ���� ������ ����� ������
					check a;
					a.node = i->inf;
					for (int j = 0; j < i->smej.size(); j++) // ��������� ������� ��� �������� ����
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
					cout << "\n����� ������ [" << a << "] � [" << b << "] ��� ���� ����������������� �����\n" << endl;
					return false;
				}
				if (!fl1 && fl2 && adddel) {
					cout << "\n����� ������ [" << b << "] � [" << a << "] ��� ���� ��������������� �����\n" << endl;
					return false;
				}
				if (fl1 && !fl2 && adddel) {
					cout << "\n����� ������ [" << a << "] � [" << b << "] ��� ���� ��������������� �����\n" << endl;
					return false;
				}
				if (!fl1 && !fl2 && !adddel) {
					cout << "\n����� ������ [" << a << "] � [" << b << "] ��� �����\n" << endl;
					return false;
				}
				if (!fl1 && fl2 && !adddel) {
					cout << "\n����� ������ [" << b << "] � [" << a << "] ��� ���������������� �����\n" << endl;
					return false;
				}
				if (fl1 && !fl2 && !adddel) {
					cout << "\n����� ������ [" << a << "] � [" << b << "] ��� ����������������  �����\n" << endl;
					return false;
				}
				return true;
			}
		}
	}

	void DelSmej(int a, int b, bool fl) { // �������� ������� ����� "a" � "b"
		if (CheckSmej(a, b, false)) {
			vector <ves> sup; // ��������������� ������ ����������
			for (auto i = ML.begin(); i != ML.end(); i++) { // ���� ������ ����� ������
				if (i->inf == a) { // ���� ������� ������ ����
					for (int j = 0; j < i->smej.size(); j++) // ���� ��� �������� ������ ����������
						if (i->smej[j].toNode != b)
							sup.push_back(i->smej[j]); // ����������� ������ ���������, �� ���������� � ���� ��������� ���������
					i->smej.swap(sup); // ����� ����� ������� ������� � � ����� �������� ������ ���������� ��� ���������
					sup.clear();
				}
				if (i->inf == b && !fl) { // ���� ����� ��� ������� ���������
					for (int j = 0; j < i->smej.size(); j++)
						if (i->smej[j].toNode != a)
							sup.push_back(i->smej[j]);
					i->smej.swap(sup);
					sup.clear();
				}
			}
			cout << "\n����� ����� ������ [" << a << "] � [" << b << "] ������� �������\n" << endl;
		}
	}

	void Result() { // ����� �������� ����� � ����
		for (auto i = ML.begin(); i != ML.end(); i++) { // ���� ������ ����� ������
			out << i->inf << ": ";
			for (int j = 0; j < i->smej.size(); j++)
				out << i->smej[j].toNode << "(" << i->smej[j].mass << ") ";
			out << endl;
		}
	}

	//bool CheckValid() { // �������� ����������������� �����
	//	bool fl = true;
	//	vector <check> sup;
	//	for (auto i = ML.begin(); i != ML.end(); i++) { // ���� ������ ����� ������
	//		check a;
	//		a.node = i->inf;
	//		for (int j = 0; j < i->smej.size(); j++) // ��������� ������� ��� �������� ����
	//			a.tonode.push_back(i->smej[j].toNode);
	//		sup.push_back(a);
	//	}
	//	for (int i = 0; i < sup.size(); i++) { // ����������� �� ������ ����� � �� ���������
	//		int m = 0;
	//		for (int j = 0; j < sup[i].tonode.size(); j++) // ����������� �� ������ ��������� � ���� i
	//			for (int k = 0; k < sup.size(); k++) // ����������� �� ����� �����, ����� ��������� ����� ����� i �����������
	//				if (sup[i].tonode[j] == sup[k].node) // ���� ��� ����� i ������� ���� 
	//					for (int l = 0; l < sup[k].tonode.size(); l++) // ������� � ���� ���� �� �������� �����
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
		for (auto i = ML.begin(); i != ML.end(); i++) { // ���� ������ ����� ������
			check a;
			a.node = i->inf;
			for (int j = 0; j < i->smej.size(); j++) // ��������� ������� ��� �������� ����
				a.tonode.push_back(i->smej[j].toNode);
			sup.push_back(a);
		}
		bool fl = false;
		int ii, c;
		do {
			system("cls");
			cout << "������� �� ������� �������, ������� �������� ������������ ���������� � ���������� ��� �������� �������.\n" << endl;
			cout << "������� �������: ";
			cin >> c;
			for (int i = 0; i < sup.size(); i++)
				if (c == sup[i].node) {
					fl = true;
					ii = i;
					break;
				}
		} while (!fl);
		vector <int> m;
		for (int j = 0; j < sup[ii].tonode.size(); j++) // ����������� �� ������ ��������� � ���� ii
			for (int k = 0; k < sup.size(); k++) // ����������� �� ����� �����, ����� ��������� ����� ����� i �����������
				if (sup[ii].tonode[j] == sup[k].node) // ���� ��� ����� i ������� ���� 
					for (int l = 0; l < sup[k].tonode.size(); l++) // ������� � ���� ���� �� �������� �����
						if (sup[k].tonode[l] == sup[ii].node)
							m.push_back(sup[k].node);
		if (m.size() > 0) {
			cout << endl;
			for (int i = 0; i < m.size(); i++)
				cout << "[" << m[i] << "] ";
		}
		else cout << "\n��� ������� [" << c << "] �� ������� �������������� ������� ������� �������.";
		cout << "\n" << endl;
	}

	void ia8() {
		vector <check> sup;
		for (auto i = ML.begin(); i != ML.end(); i++) { // ���� ������ ����� ������
			check a;
			a.node = i->inf;
			for (int j = 0; j < i->smej.size(); j++) // ��������� ������� ��� �������� ����
				a.tonode.push_back(i->smej[j].toNode);
			sup.push_back(a);
		}

			system("cls");
			cout << "������� �� �������, � ������� ����������� ������ ������ ����������� ������.\n" << endl;

			vector <structia8> m;
			for (int i = 0; i < sup.size(); i++) { // ����������� �� ����� �����
				structia8 l; // ����������, � ������� �������� ����, ���-�� �������� � ���-�� ���������
				l.node = sup[i].node;
				l.outputs = sup[i].tonode.size();
				for (int j = 0; j < sup.size(); j++) // ����������� �� ����� �����, �� �� ��������� ���� �� ������� �����
					if (i != j)
						for (int k = 0; k < sup[j].tonode.size(); k++) // ���� ������ ��������� � ����������� ����
							if (sup[j].tonode[k] == sup[i].node)
								l.inputs++;
				m.push_back(l);
			}

			cout << "���������: ";
			for (int i = 0; i < m.size(); i++)
				if (m[i].outputs > m[i].inputs)
					cout << "[" << m[i].node << "] ";
			cout << "\n" << endl;
	}

	void ib2() {
		vector <check> sup;
		vector <check> sup2;
		for (auto i = ML.begin(); i != ML.end(); i++) { // ���� ������ ����� ������
			check a;
			a.node = i->inf;
			for (int j = 0; j < i->smej.size(); j++) // ��������� ������� ��� �������� ����
				a.tonode.push_back(i->smej[j].toNode);
			sup.push_back(a);
		}

		system("cls");
		cout << "��������� ����, ���������� ����������� ������� �����.\n" << endl;

		//if (Type == "�����������������") { // ���� ������� ������ ����������� ������ ��� ������������������ �����
			for (int i = 0; i < sup.size(); i++) { // ����������� �� ���� ����� �����
				check a; // ������� ����� ���� ��� ������ �����-����������
				a.node = sup[i].node;
				for (int j = 0; j < sup.size(); j++) { // ����� ����������� �� ���� �����
					bool fl = false;
					for (int k = 0; k < sup[i].tonode.size(); k++) // ����������� �� ���������� ����
						if (sup[j].node == sup[i].tonode[k] || i == j) // ���� ����� ��������� ������������ ��� ���������� ���������� ��������
							fl = true; // ����� ������ ���������� �� ���
					if (!fl) // ���� �� �� ������� ����������, �� ���� ������� 
						a.tonode.push_back(sup[j].node); // ����� ������� �� � ����� ����
				}
				sup2.push_back(a); // ������� ����� ����-����������
			}

			cout << "���������� ��� ��������� �����\n" << endl;

			for (int i = 0; i < sup2.size(); i++) {
				cout << sup2[i].node << ": ";
				for (int j = 0; j < sup2[i].tonode.size(); j++)
					cout << sup2[i].tonode[j] << " ";
				cout << endl;
			}

			cout << endl;
		//}
		//else
		//	cout << "��������! ���� ���������������. ��� ���������� ������� ����� ������������ ����������������� ����.\n" << endl;
	}

	void ll7() {
		vector <check> sup;
		for (auto i = ML.begin(); i != ML.end(); i++) { // ���� ������ ����� ������
			check a;
			a.node = i->inf;
			for (int j = 0; j < i->smej.size(); j++) // ��������� ������� ��� �������� ����
				a.tonode.push_back(i->smej[j].toNode);
			sup.push_back(a);
		}

		system("cls");
		cout << "������ ����������� ������� ���������� ����� ������� u, ��� �� �� ���������� ���� � ������ �� ��������� ������ �������. ����������, ����� �� ������ ���������� ������ ������.\n" << endl;

		if (Type != "Neor") {
			vector <int> m;
			for (int i = 0; i < sup.size(); i++)
				if (sup[i].tonode.size() == sup.size() - 1)
					m.push_back(sup[i].node);
			cout << "������� ������ �������: " << m.size();
			if (m.size() > 0)
				for (int i = 0; i < m.size(); i++)
					cout << " -> [" << m[i] << "] ";
			cout << "\n" << endl;
		}
		else
			cout << "��������! ���� �����������������. ��� ���������� ������� ����� ������������ ��������������� ����.\n" << endl;
	}

	struct Node21 { // ��������� ��� �������� ����������������� �����
		int inf; // ����
		bool ischeck = false;
		vector <ves> smej; // �������
	};

	void ii21() {
		
		vector <check> sup;
		for (auto i = ML.begin(); i != ML.end(); i++) { // ���� ������ ����� ������
			check a;
			a.node = i->inf;
			for (int j = 0; j < i->smej.size(); j++) // ��������� ������� ��� �������� ����
				a.tonode.push_back(i->smej[j].toNode);
			sup.push_back(a);
		}

		system("cls");
		cout << "���������, ����� �� �� ����� ������� �����-���� ������� ���, ����� ���������� ������.\n" << endl;

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

			for (int i = 0; i < sup2.size(); i++) // ������� ������������ ����
				if (sup2[i].node > max)
					max = sup2[i].node;

			vector<vector<int>> mas;

			for (int i = 0; i <= max * 2; i++) { // ��������� ��������������� ��������� ������ ������
				vector<int> mas2;
				for (int j = 0; j <= max * 2; j++)
					mas2.push_back(0);
				mas.push_back(mas2);
			}

			for (int i = 0; i < sup2.size(); i++) // ���� ���� ���������, �� � ��������� ������� ������ 1 �� �� �����������
				for (int j = 0; j < sup2[i].tonode.size(); j++) {
					mas[sup2[i].node][sup2[i].tonode[j]] = 1;
				}

			int edin = 0;

			for (int i = 0; i <= max; i++) // ������� ���������� ����������
				for (int j = 0; j <= max; j++)
					if (mas[i][j] == 1)
						edin++;

			edin /= 2;

			if (sup2.size() - edin == 1)
				cout << "���� ������� ���� [" << sup[A].node << "], �� ��������� ������." << "\n\n";
			else
				cout << "���� ������� ���� [" << sup[A].node << "], �� ������ �� ���������." << "\n\n";
		}
	}

	void Prim() {
		map<int, map<int, int>> dist; // ���������
		map<int, vector<pair<int, int>>> edges; // �����

		for (auto i = ML.begin(); i != ML.end(); i++) { // ���� ������ ����� ������
			edges[i->inf];
			for (int j = 0; j < i->smej.size(); j++) { // ������� ��� ������� �������
				edges[i->inf].push_back({ i->smej[j].toNode, i->smej[j].mass });
				dist[i->inf][i->smej[j].toNode] = i->smej[j].mass;
			}
		}

		map<int, bool> visited; // ���� ����-�������� ��� ���������� ������
		map<int, int> mincost; // ���� ����-�������� ��� ����������� ���������
		map<int, int> from; // ���� ����-�������� ��� ��������� ����

		vector<pair<int, int>> ans; // ������ ������ � ������� ��������� ������

		int INF = INT_MAX;

		for (auto it = edges.begin(); it != edges.end(); it++) { //���� ������ ����� ������
			int to = it->first; // ������ �������� - �������
			mincost[to] = INF; // ����������� ��������� ����������� �� ���������������
		}

		mincost[edges.begin()->first] = 0; // ����������� ��������� �������������� ����
		int sumcost = 0; // ��������� ��������� ������  �������������� ����

		for (int i = 0; i < edges.size(); i++) { // ���� ������ ����� ������
			int v = 0;
			for (auto it = edges.begin(); it != edges.end(); it++) { // ���� ������ ����� ������
				int to = it->first; // ������ �������� - �������
				if (!visited.count(to) && (v == 0 || mincost[to] < mincost[v])) // ���� ������� �� ���� �������� � ������� ����������� ��������� ������ ����������
					v = to; // �� ��������� ����� ��������
			}

			if (mincost[v] == INF) { // ���� ����������� �������� ����� ����������
				cout << "\n�� ���������� ������������ ��������� ������!\n\n";
				return;
			}

			visited[v] = true; // ��������� �������

			if (from.count(v)) {
				ans.push_back({ v, from[v] }); // ���������� ������ ��������� ������
				sumcost += dist[v][from[v]]; // ��������� ��������� ������
			}

			for (auto it = edges[v].begin(); it != edges[v].end(); it++) { // ���� ������ ����� ������
				int to = it->first; // ������ �������� - �������
				int cost = it->second; // ������ �������� - ���������
				if (cost < mincost[to]) { // ���� ��������� ������ ����������� ���������,
					mincost[to] = cost; //�� ����������� ��������� ��������� �������� ���������
					from[to] = v; // � ��������� ����� ��������
				}
			}
		}
		cout << "����������� �������� ������\n\n������ ����:\n";

		for (int i = 0; i < ans.size(); i++)
			cout << ans[i].first << " - " << ans[i].second << endl;

		cout << "\n��������� ��������� ������: " << sumcost << endl << endl;
	}

	void iv_a5() {

		vector <check> sup;
		for (auto i = ML.begin(); i != ML.end(); i++) { // ���� ������ ����� ������
			check a;
			a.node = i->inf;
			for (int j = 0; j < i->smej.size(); j++) // ��������� ������� ��� �������� ����
				a.tonode.push_back(i->smej[j].toNode);
			sup.push_back(a);
		}

		int max = INT_MIN;

		for (int i = 0; i < sup.size(); i++) // ������� ������������ ����
			if (sup[i].node > max)
				max = sup[i].node;

		vector<vector<int>> matrix;

		for (int i = 0; i < max; i++) { // ��������� ��������������� ��������� ������ ������
			vector<int> mas2;
			for (int j = 0; j < max; j++)
				mas2.push_back(0);
			matrix.push_back(mas2);
		}

		for (auto i = ML.begin(); i != ML.end(); i++) // ���� ������ ����� ������
			for (int j = 0; j < i->smej.size(); j++) // ��������� ������� ��� �������� ����
				matrix[i->inf - 1][i->smej[j].toNode - 1] = i->smej[j].mass;

		bool fl = false;
		int c;
		do {
			system("cls");
			cout << "������� ����� ���������� ����� �� u �� ���� ��������� ������.\n" << endl;

			cout << "\n������� ���� �����, �� �������� ����� ������� �����: ";
			cin >> c;

			for (int i = 0; i < sup.size(); i++)
				if (sup[i].node == c) {
					fl = true;
					break;
				}

			if (!fl)
				cout << "\n���� � ������� [" << c << "] ��� � �������� �����.";


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
					cout << "�� " << c << " � " << sup[A].node << " = " << d[sup[A].node - 1] << endl << endl;
			}
		}
	}

	void iv_b13() {

		vector <check> sup; // ������ ������ �������� � ���� ����� ��� ����

		for (auto i = ML.begin(); i != ML.end(); i++) { // ���� ������ ����� ������
			check a;
			a.node = i->inf;
			for (int j = 0; j < i->smej.size(); j++) // ��������� ������� ��� �������� ����
				a.tonode.push_back(i->smej[j].toNode);
			sup.push_back(a);
		}

		bool fl = false, fl1 = false, fl2 = false;
		int c, v1, v2;


		do {
			system("cls");
			cout << "������� ���������� ���� �� ������� u �� v1 � v2.\n" << endl;

			cout << "\n������� ���� �����, �� �������� ����� ������� �����: ";
			cin >> c;

			cout << "\n������� ������ ���� �����, �� �������� ����� ������� �����: ";
			cin >> v1;

			cout << "\n������� ������ ���� �����, �� �������� ����� ������� �����: ";
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
				cout << "\n���� � ������� [" << c << "] ��� � �������� �����.\n";
			if (!fl2)
				cout << "\n���� � ������� [" << v1 << "] ��� � �������� �����.\n";
			if (!fl2)
				cout << "\n���� � ������� [" << v2 << "] ��� � �������� �����.\n";

		} while (!fl && !fl1 && !fl2);

		int max = INT_MIN;

		for (int i = 0; i < sup.size(); i++) // ������� ������������ ����
			if (sup[i].node > max)
				max = sup[i].node;

		vector<vector<int>> matrix; // ������� ��������� -> ������ ������� �������� �����. ����������� ������� �� ������� ������ ���.

		for (int i = 0; i < max; i++) { // ��������� ��������������� ��������� ������ ������
			vector<int> mas2;
			for (int j = 0; j <= max; j++)
				mas2.push_back(0);
			matrix.push_back(mas2);
		}

		for (auto i = ML.begin(); i != ML.end(); i++) // ���� ������ ����� ������
			for (int j = 0; j < i->smej.size(); j++) // ��������� ������� ��� �������� ����
				matrix[i->inf - 1][i->smej[j].toNode - 1] = i->smej[j].mass;

		Spisok A;

		A.Vvod_Ves(matrix, c, v1, v2);
		A.Reshenie();
		A.Reshenie2();
	}

	void iv_c14() {
		
		vector <check> sup; // ������ ������ �������� � ���� ����� ��� ����

		for (auto i = ML.begin(); i != ML.end(); i++) { // ���� ������ ����� ������
			check a;
			a.node = i->inf;
			for (int j = 0; j < i->smej.size(); j++) // ��������� ������� ��� �������� ����
				a.tonode.push_back(i->smej[j].toNode);
			sup.push_back(a);
		}

		bool fl = false, fl1 = false, fl2 = false;
		int c, v1, v2;

		do { 
			system("cls");
			cout << "������� ���������� ���� �� ������� u �� v1 � v2.\n" << endl;

			cout << "\n������� ���� �����, �� �������� ����� ������� �����: ";
			cin >> c;

			cout << endl;

			for (int i = 0; i < sup.size(); i++)
				if (sup[i].node == c)
					fl = true;

			if (!fl)
				cout << "\n���� � ������� [" << c << "] ��� � �������� �����.\n";

		} while (!fl);

		int max = INT_MIN;

		for (int i = 0; i < sup.size(); i++) // ������� ������������ ����
			if (sup[i].node > max)
				max = sup[i].node;

		vector<vector<int>> matrix; // ������� ��������� -> ������ ������� �������� �����. ����������� ������� �� ������� ������ ���.

		for (int i = 0; i < max; i++) { // ��������� ��������������� ��������� ������ ������
			vector<int> mas2;
			for (int j = 0; j <= max; j++)
				mas2.push_back(0);
			matrix.push_back(mas2);
		}

		for (auto i = ML.begin(); i != ML.end(); i++) // ���� ������ ����� ������
			for (int j = 0; j < i->smej.size(); j++) // ��������� ������� ��� �������� ����
				matrix[i->inf - 1][i->smej[j].toNode - 1] = i->smej[j].mass;

		vector <int> x;

		for (int i = 0; i < sup.size(); i++)
			x.push_back(sup[i].node);

		Spisok A;

		A.Vvod_Ves2(matrix, x, c);
	}

};