#include "GraphClass.h"
#include <string>

int main() {
	setlocale(LC_ALL, "RUS");
	MainGraph a{ true };
	int c;
	do {
		string type;
		type = a.GetType();
		int f, m1, m2, ves, cc;
		bool fl;
		cout << "=== МЕНЮ ===\n\nГраф <<" << type << ">>\n\n";
		cout << "1 - Добавить узел\n2 - Добавить ребро\n3 - Удалить узел\n4 - Удалить ребро\n5 - Вывести все в файл\n6 - Вывести граф в консоль\n7 - Выполнить задание ia 13\n8 - Выполнить задание ia 8\n9 - Выполнить задание ib 2\n10 - Выполнить задание ii 7\n11 - Выполнить задание ii 21\n12 - Выполнить задание iii ПРИМ\n13 - Выполнить задание iv_a5\n14 - Выполнить задание iv_b13\n15 - Выполнить задание iv_c14\n16 - Закрыть программу\n\nВаш ответ: ";
		cin >> c;
		system("cls");
		switch (c) {
		case 1:
			cout << "=== Добавление узла ===\nВведите номер узла: ";
			cin >> f;
			a.AddNode(f);
			break;
		case 2:
			//do {
			//	system("cls");
			//	cout << "=== Добавление ребра ===\n\nВыберите тип ребра:\n1 - Ориентированное ребро\n2 - Неориентированное ребро\nВаш ответ: ";
			//	cin >> cc;
			//} while (cc < 1 || cc > 2);
			if (a.GetType() == "Ориентированный")
				fl = true;
			else
				fl = false;

			if (fl)
				cout << "Введите номер узла: ";
			else
				cout << "Введите номер первого узла: ";
			cin >> m1;
			if (fl)
				cout << "\nВведите номер узла, к которому идет переход: ";
			else
				cout << "\nВведите номер второго узла: ";
			cin >> m2;
			cout << "\nВведите вес ребра: ";
			cin >> ves;
			a.AddSmej(m1, m2, ves, fl);
			break;
		case 3:
			cout << "=== Удаление узла ===\nВведите номер узла: ";
			cin >> f;
			a.DelNode(f);
			break;
		case 4:
			//do {
			//	system("cls");
			//	cout << "=== Удаление ребра ===\n\nВыберите тип ребра:\n1 - Ориентированное ребро\n2 - Неориентированное ребро\nВаш ответ: ";
			//	cin >> cc;
			//} while (cc < 1 || cc > 2);
			if (a.GetType() == "Ориентированный")
				fl = true;
			else
				fl = false;

			if (fl)
				cout << "Введите номер узла: ";
			else
				cout << "Введите номер первого узла: ";
			cin >> m1;
			if (fl)
				cout << "\nВведите номер узла, к которому идет переход: ";
			else
				cout << "\nВведите номер второго узла: ";
			cin >> m2;
			a.DelSmej(m1, m2, fl);
			break;
		case 5:
			cout << "=== Вывод графа в файл ===\n\nГраф успешно выведен в файл.\n";
			a.Result();
			break;
		case 6:
			cout << "=== Вывод графа ===\n";
			a.Print();
			cout << endl;
			break;
		case 7:
			a.ia13();
			break;
		case 8:
			a.ia8();
			break;
		case 9:
			a.ib2();
			break;
		case 10:
			a.ll7();
			break;
		case 11:
			a.ii21();
			break;
		case 12:
			a.Prim();
			break;
		case 13:
			a.iv_a5();
			break;
		case 14:
			a.iv_b13();
			break;
		case 15:
			a.iv_c14();
			break;
		case 16:
			return 0;
			break;
		}
		system("pause");
		system("cls");
	} while (c != 11);
}