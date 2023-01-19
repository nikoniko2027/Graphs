#pragma once
#include <iostream>
#include <vector>

#define TRUE 1
#define FALSE 0

using namespace std;

typedef struct Zveno* svqz;

typedef struct Zveno {
    int Element;
    svqz Sled;
};

class Spisok {
private:
    vector<vector<int>> Mas;
    vector<vector<int>> DD;
    vector<vector<int>> SS;
    svqz Stack; // ��������� �� ������� ����
    void UDALENIE(svqz*, int*);
    void W_S(svqz*, int);
    void Small_Put(int, int);

public:
    int MaxNodes, c, v1, v2;

    Spisok() { 
        Stack = NULL; 
    }

    void Vvod_Ves(vector<vector<int>> matrix, int cc, int vv1, int vv2) {
        c = cc;
        v1 = vv1;
        v2 = vv2;
        MaxNodes = matrix.size();
        for (int i = 0; i < matrix.size(); i++) {
            vector <int> a;
            for (int j = 0; j < matrix.size(); j++)
                a.push_back(0);
            Mas.push_back(a);
            DD.push_back(a);
            SS.push_back(a);
        }
        Mas = matrix;
    }

    void Vvod_Ves2(vector<vector<int>> matrix, vector <int> x, int cc) {
        c = cc;
        MaxNodes = matrix.size();
        for (int i = 0; i < matrix.size(); i++) {
            vector <int> a;
            for (int j = 0; j < matrix.size(); j++)
                a.push_back(0);
            Mas.push_back(a);
            DD.push_back(a);
            SS.push_back(a);
        }
        Mas = matrix;
        for (int i = 0; i < x.size(); i++)
            if (x[i] != c) {
                v1 = x[i];
                Reshenie();
            }
    }

    void Reshenie();
    void Reshenie2();
};


void Spisok::Small_Put(int one, int two) { //���������� ����������� ����
    svqz St = NULL; // ��������� �� ��������������� ����
    svqz UkZv;
    int Flag = FALSE; //���� ���������� ����������� ����
    int elem1, elem2, k; // ��������� � ���� �������� � ��������� ������
    W_S(&Stack, two);
    W_S(&Stack, one);
    while (!Flag) {
        //�������� ������� ��� ��������.
        UDALENIE(&Stack, &elem1);
        UDALENIE(&Stack, &elem2);
        if (SS[elem1][elem2] == elem2) //���� ���� ����...
            if (elem2 == two) { //� ��� �������� ����...

                Flag = TRUE;   //�� ���������� ���� ������.
                W_S(&St, elem1);
                W_S(&St, elem2);
            }
            else { //� ��� �� �������� ����...
                W_S(&St, elem1); //� ��������������� ����.
                W_S(&Stack, elem2); //������� � ������� ����.
            }
        else { //���� ���� ���.
            W_S(&Stack, elem2); //������� � ������� ����.
            k = SS[elem1][elem2];
            W_S(&Stack, k);     //��������� ������������� �������.
            W_S(&Stack, elem1); //������� � ������� ����.
        }
    }
    UkZv = St;
    while (UkZv != NULL) {
        cout << (UkZv->Element + 1) << " ";
        UkZv = UkZv->Sled;
    }
    cout << endl;
}

void Spisok::W_S(svqz* stk, int Elem) {
//��������� Elem � ���� stk.
    svqz q = new (Zveno);
    (*q).Element = Elem;
    (*q).Sled = *stk; *stk = q;
}

void Spisok::UDALENIE(svqz* stk, int* Klad) {
//�������� ����� �� �����, ��������� ���������� *stk.
//�������� ��������������� ���� ���������� ����� �������-
//���� � ��������� Klad.
    svqz q;

    if (*stk == NULL) 
        cout << "������� ������ �� ������� �����!\n";
    else {
        *Klad = (**stk).Element;
        q = *stk; *stk = (**stk).Sled; delete q;
    }
}


void Spisok::Reshenie() {
    int one, two;
    int i, j;

    //�������������.
    for (i = 0; i < MaxNodes; i++)
        for (j = 0; j < MaxNodes; j++) {
            if (Mas[i][j] > 0)  SS[i][j] = j;
            else SS[i][j] = 0;
            DD[i][j] = Mas[i][j];
        }
    cout << "\n======================\n��������� �������: " << c;
    cout << "\n�������� �������: " << v1 << endl;
    one = c - 1;
    two = v1 - 1;
    int ved = 0;
    while (ved < MaxNodes) {
        for (i = 0; i < MaxNodes; i++)
            for (j = 0; j < MaxNodes; j++)
                if (i != j && i != ved && j != ved &&
                    DD[i][ved] > 0 && DD[ved][j] > 0)
                    if (DD[i][ved] + DD[ved][j] < DD[i][j] || DD[i][j] == 0) {
                        DD[i][j] = DD[i][ved] + DD[ved][j];
                        SS[i][j] = ved;
                    }
        ved++;
    }
    i = one;
    if (SS[i][two] != two && SS[i][two] != 0)
        while (SS[i][two] != two) {
            j = SS[i][two];
            while (SS[i][j] != j)  j = SS[i][j];
            i = j;
        }
    cout << "\n���������� ���� (� �������� �������): ";
    Small_Put(one, two);
    cout << "����� ������������ ���� ����� ����� ���������: " << DD[one][two] << "\n======================\n\n";
}

void Spisok::Reshenie2() {
    int one, two;
    int i, j;

    //�������������.
    for (i = 0; i < MaxNodes; i++)
        for (j = 0; j < MaxNodes; j++) {
            if (Mas[i][j] > 0)  SS[i][j] = j;
            else SS[i][j] = 0;
            DD[i][j] = Mas[i][j];
        }
    cout << "\n======================\n��������� �������: " << c;
    cout << "\n�������� �������: " << v2 << endl;
    one = c - 1;
    two = v2 - 1;
    int ved = 0;
    while (ved < MaxNodes) {
        for (i = 0; i < MaxNodes; i++)
            for (j = 0; j < MaxNodes; j++)
                if (i != j && i != ved && j != ved &&
                    DD[i][ved] > 0 && DD[ved][j] > 0)
                    if (DD[i][ved] + DD[ved][j] < DD[i][j] || DD[i][j] == 0) {
                        DD[i][j] = DD[i][ved] + DD[ved][j];
                        SS[i][j] = ved;
                    }
        ved++;
    }
    i = one;
    if (SS[i][two] != two && SS[i][two] != 0)
        while (SS[i][two] != two) {
            j = SS[i][two];
            while (SS[i][j] != j)  j = SS[i][j];
            i = j;
        }
    cout << "\n���������� ���� (� �������� �������): ";
    Small_Put(one, two);
    cout << "����� ������������ ���� ����� ����� ���������: " << DD[one][two] << "\n======================\n\n";
}