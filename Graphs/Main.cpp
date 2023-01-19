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
		cout << "=== ���� ===\n\n���� <<" << type << ">>\n\n";
		cout << "1 - �������� ����\n2 - �������� �����\n3 - ������� ����\n4 - ������� �����\n5 - ������� ��� � ����\n6 - ������� ���� � �������\n7 - ��������� ������� ia 13\n8 - ��������� ������� ia 8\n9 - ��������� ������� ib 2\n10 - ��������� ������� ii 7\n11 - ��������� ������� ii 21\n12 - ��������� ������� iii ����\n13 - ��������� ������� iv_a5\n14 - ��������� ������� iv_b13\n15 - ��������� ������� iv_c14\n16 - ������� ���������\n\n��� �����: ";
		cin >> c;
		system("cls");
		switch (c) {
		case 1:
			cout << "=== ���������� ���� ===\n������� ����� ����: ";
			cin >> f;
			a.AddNode(f);
			break;
		case 2:
			//do {
			//	system("cls");
			//	cout << "=== ���������� ����� ===\n\n�������� ��� �����:\n1 - ��������������� �����\n2 - ����������������� �����\n��� �����: ";
			//	cin >> cc;
			//} while (cc < 1 || cc > 2);
			if (a.GetType() == "���������������")
				fl = true;
			else
				fl = false;

			if (fl)
				cout << "������� ����� ����: ";
			else
				cout << "������� ����� ������� ����: ";
			cin >> m1;
			if (fl)
				cout << "\n������� ����� ����, � �������� ���� �������: ";
			else
				cout << "\n������� ����� ������� ����: ";
			cin >> m2;
			cout << "\n������� ��� �����: ";
			cin >> ves;
			a.AddSmej(m1, m2, ves, fl);
			break;
		case 3:
			cout << "=== �������� ���� ===\n������� ����� ����: ";
			cin >> f;
			a.DelNode(f);
			break;
		case 4:
			//do {
			//	system("cls");
			//	cout << "=== �������� ����� ===\n\n�������� ��� �����:\n1 - ��������������� �����\n2 - ����������������� �����\n��� �����: ";
			//	cin >> cc;
			//} while (cc < 1 || cc > 2);
			if (a.GetType() == "���������������")
				fl = true;
			else
				fl = false;

			if (fl)
				cout << "������� ����� ����: ";
			else
				cout << "������� ����� ������� ����: ";
			cin >> m1;
			if (fl)
				cout << "\n������� ����� ����, � �������� ���� �������: ";
			else
				cout << "\n������� ����� ������� ����: ";
			cin >> m2;
			a.DelSmej(m1, m2, fl);
			break;
		case 5:
			cout << "=== ����� ����� � ���� ===\n\n���� ������� ������� � ����.\n";
			a.Result();
			break;
		case 6:
			cout << "=== ����� ����� ===\n";
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