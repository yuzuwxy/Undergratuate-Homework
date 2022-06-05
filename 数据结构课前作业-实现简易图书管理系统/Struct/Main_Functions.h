#pragma once
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<ctime>
#include<cstring>
#include<string>
#include<cmath>
#include<fstream>
#include"functions.h"

#define MAXN (int)1e5

using namespace std;

int tot;
// ͳ���ļ���ͼ�������

string title[5];


struct Book {
	string isbn="";
	string name="";
	double cost=0;
}Book_info[MAXN+7];
// �洢ͼ����Ϣ�Ľṹ������


/*****************************************************
* ���ͼ����Ϣ����ϵͳ�����˵�
* ***************************************************/
void main_menu() {
	cout << "��ӭʹ��ͼ����Ϣ����ϵͳ��\n";
	cout << "***************************************************\n";
	cout << "���˵�\n";
	cout << "1.��ʾ��¼�������ͼ����Ϣ\n";
	cout << "2.��ָ��λ�����ͼ����Ϣ\n";
	cout << "3.ɾ��ָ��λ�õ�ͼ����Ϣ\n";
	cout << "4.����ͼ����Ϣ\n";
	cout << "5.�޸�ͼ����Ϣ\n";
	cout << "6.��ͼ����ݼ۸���������д�����ļ���\n";
	cout << "7.��ȫ�˳�ϵͳ�������������޸Ŀ����޷����棩\n";
	cout << "***************************************************\n";
}


/*****************************************************
* ���ļ��ж�ȡȫ����ͼ����Ϣ������ṹ������
* ***************************************************/
int Get_info() {
	ifstream iFile;
	iFile.open("book.txt", ios::in);
	int suc = iFstream(iFile);

	if (!suc) {
		system("cls");
		cout << "�ļ�����\n";
		exit(0);
	}

	int count = 0;

	iFile >> title[0] >> title[1] >> title[2] >> title[3];

	while (!iFile.eof()) {
		iFile >> Book_info[count].isbn >> Book_info[count].name >> Book_info[count].cost;
		count++;
	}

	iFile.close();
	return count;
}


/*****************************************************
* �Ķ�ͼ����Ϣ����д���ļ�
* ***************************************************/
void Write_info(string File_name) {
	ofstream oFile;
	oFile.open(File_name, ios::out);
	int suc = oFstream(oFile);

	if (!suc) {
		system("cls");
		return;
	}

	Print_title(oFile);

	for (int i = 0; i < tot-1; i++)
		oFile << Book_info[i].isbn << ' ' << Book_info[i].name << ' ' << Book_info[i].cost << '\n';
	oFile << Book_info[tot - 1].isbn << ' ' << Book_info[tot - 1].name << ' ' << Book_info[tot - 1].cost;

	oFile.close();

}


/*****************************************************
* ��ʾȫ����ͼ����Ϣ
* ***************************************************/
void Show_info() {
	system("cls");

	for (int i = 0; i < tot; i++)
		cout << Book_info[i].isbn << "    " << Book_info[i].name << "    " << Book_info[i].cost << '\n';

	printf("�� %d ��ͼ����Ϣ\n", tot);
}


/*****************************************************
* ��ָ��λ�����ͼ����Ϣ
* ***************************************************/
void Insert_info() {
	int flag = 1;
	while (flag) {
		system("cls");

		string spos = "";
		int pos;
		if(tot!=0) {	 
			printf("����������ͼ����Ϣ��ӵ���λ��(1-%d)��", tot + 1);
	
			cin >> spos;
			getchar();
			/*��ǿ����׳�ԣ��û�����һ����ĸʱ�����������*/
	
			pos = To_num(spos);
			if (pos == 0 || pos > tot + 1) {
				printf("λ����Ч���޷��������.\n");
				system("pause");
				continue;
			}
		}
		else {
			int pos=1;
		}

		string tempi, tempn;
		double tempc;
		cout << "������ͼ�����ţ�";
		cin >> tempi;
		getchar();
		cout << "������ͼ���������";
		getline(cin, tempn);
		//getchar();
		cout << "������ͼ��ļ۸�";
		cin >> tempc;
		getchar();

		char y_or_n;
		while (1) {
			cout << "ȷ����ӣ���y/n)";
			cin >> y_or_n;
			getchar();
			if (y_or_n != 'y' && y_or_n != 'n') {
				cout << "��Ч���룡������ѡ��\n";
			}
			else break;
		}

		if (y_or_n == 'y') {
			if (tot == 0) {
				Book_info[0].isbn = tempi;
				Book_info[0].name = tempn;
				Book_info[0].cost = tempc;
			}
			else {
				for (int i = tot - 1; i >= pos - 1; i--)
					Book_info[i + 1] = Book_info[i];

				Book_info[pos - 1].isbn = tempi;
				Book_info[pos - 1].name = tempn;
				Book_info[pos - 1].cost = tempc;
			}

			system("cls");
			cout << "��ӳɹ���\n";
			tot++;
			while (1) {
				cout << "�Ƿ������ӣ���y/n)\n";
				cin >> y_or_n;
				getchar();
				if (y_or_n != 'y' && y_or_n != 'n') {
					cout << "��Ч���룡������ѡ��\n";
				}
				else break;
			}
			if (y_or_n == 'n') flag = 0;
			continue;
		}

		int mark = 0;
		while (1) {
			cout << "****************************\n";
			cout << "1.�˳���Ϣ���\n";
			cout << "2.��������ͼ����Ϣ\n";
			cout << "****************************\n";

			cin >> mark;
			getchar();
			if (mark == 1) {
				return;
			}
			if (mark == 2) {
				flag = 1;
				break;
			}

			cout << "������Ч��������ѡ��\n";

		}

	}
	system("cls");
	Write_info("book.txt");
}


/*****************************************************
* ɾ��ָ��λ�õ�ͼ����Ϣ
* ***************************************************/
void Delete_info() {
	system("cls");
	int flag = 1;
	while (flag) {
		system("cls");
		if (tot == 0) {
			cout << "ϵͳ����ͼ����Ϣ��\n";
			system("pause");
			flag = 0;
			break;
		}
		printf("��������Ҫɾ����ͼ��λ��(1-%d)��", tot);

		string spos = "";
		cin >> spos;
		getchar();
		/*��ǿ����׳�ԣ��û�����һ����ĸʱ�����������*/

		int pos = To_num(spos);
		if (pos == 0 || pos > tot) {
			printf("λ����Ч���޷�����ɾ��.\n");
			system("pause");
			continue;
		}

		cout << Book_info[pos-1].isbn << "    " << Book_info[pos-1].name << "    " << Book_info[pos-1].cost << '\n';

		for (int i = pos - 1; i < tot - 1; i++)
			Book_info[i] = Book_info[i + 1];

		char y_or_n;
		while (1) {
			cout << "ȷ��ɾ������y/n)";
			cin >> y_or_n;
			getchar();
			if (y_or_n != 'y' && y_or_n != 'n') {
				cout << "��Ч���룡������ѡ��\n";
			}
			else break;
		}

		if (y_or_n == 'y') {
			system("cls");
			cout << "ɾ���ɹ���\n";
			tot--;
			while (1) {
				cout << "�Ƿ����ɾ������y/n)\n";
				cin >> y_or_n;
				getchar();
				if (y_or_n != 'y' && y_or_n != 'n') {
					cout << "��Ч���룡������ѡ��\n";
				}
				else break;
			}
			if (y_or_n == 'n') flag = 0;
			continue;
		}

		int mark = 0;
		while (1) {
			cout << "****************************\n";
			cout << "1.�˳���Ϣɾ��\n";
			cout << "2.����ѡ��ɾ��ͼ��λ��\n";
			cout << "****************************\n";

			cin >> mark;
			getchar();
			if (mark == 1) {
				return;
			}
			if (mark == 2) {
				flag = 1;
				system("cls");
				break;
			}

			cout << "������Ч��������ѡ��\n";

		}

	}
	system("cls");
	Write_info("book.txt");
}


/*****************************************************
* ��λ�ò���ͼ����Ϣ
* ***************************************************/
void Search_with_Pos() {
	system("cls");
	printf("������������ͼ���λ��(1-%d): ", tot + 1);

	string spos = "";
	cin >> spos;
	getchar();
	/*��ǿ����׳�ԣ��û�����һ����ĸʱ�����������*/

	int pos = To_num(spos);
	if (pos == 0 || pos > tot + 1) {
		printf("λ����Ч���޷����в���.\n");
		system("pause");
		return;
	}

	cout << "������ͼ������Ϊ��" << Book_info[pos - 1].isbn << '\n';
	cout << "������ͼ�������Ϊ��" << Book_info[pos - 1].name << '\n';
	cout << "������ͼ��ļ۸�Ϊ��" << Book_info[pos - 1].cost << '\n';

	system("pause");
}


/*****************************************************
* ����������ͼ����Ϣ
* ***************************************************/
void Search_with_Name() {
	system("cls");

	cout << "���������ͼ�������: ";
	string name;
	getline(cin, name);

	int count = 0;
	for (int i = 0; i < tot; i++) {
		if (Book_info[i].name == name) {
			cout << "λ��: " << i + 1 << "    ���: " << Book_info[i].isbn << "    ����: " << Book_info[i].name << "    �۸�: " << Book_info[i].cost << '\n';
			count++;
		}
	}

	printf("���ҵ� %d ����Ϣ\n", count);
	system("pause");
}


/*****************************************************
* ����ͼ����Ϣ
* ***************************************************/
void Search_info() {
	system("cls");

	int flag = 1;
	while (flag) {
		cout << "****************************\n";
		cout << "4.1 ��λ�ò���\n";
		cout << "4.2 ����������\n";
		cout << "������ 1 �� 2\n";
		cout << "****************************\n";

		int choi = 0;
		cin >> choi;
		getchar();

		if (choi != 1 && choi != 2) {
			cout << "������Ч������������\n";
			continue;
		}

		if (choi == 1)
			Search_with_Pos();

		if (choi == 2)
			Search_with_Name();

		char y_or_n = 'n';
		while (1) {
			system("cls");
			cout << "�Ƿ�������ң���y/n)\n";
			cin >> y_or_n;
			getchar();
			if (y_or_n != 'y' && y_or_n != 'n') {
				cout << "��Ч���룡������ѡ��\n";
			}
			else break;
		}
		if (y_or_n == 'n') flag = 0;
		system("cls");
	}
	system("cls");
}


/*****************************************************
* �޸�ͼ����Ϣ
* ***************************************************/
void Change_info() {
	// �޸ļ۸�д�������ļ�
	int i;
	for (i = 0; i < tot; i++) {
		if (Book_info[i].cost >= 25) Book_info[i].cost *= 1.1;
		if (Book_info[i].cost < 25) Book_info[i].cost *= 0.8;
	}

	Write_info("book.txt");
	Write_info("book_newprice.txt");

	printf("�޸���ɣ�\n");
}


/* ð������ */
void Bubble_Sort() {
	cout << "ʹ��ð������ķ��������ݽ�������\n";

	int i, j;
	for (i = 0; i < tot - 1; i++) {
		for (j = 0; j < tot - 1 - i; j++) {
			if (Book_info[j].cost > Book_info[j + 1].cost) {
				Book temp;
				temp = Book_info[j + 1];
				Book_info[j + 1] = Book_info[j];
				Book_info[j] = temp;
			}
		}
	}
}
				

/* ѡ������ */
void Selection_Sort() {
	cout << "ʹ��ѡ������ķ��������ݽ�������\n";

	if (tot < 2) {
		return;
	}

	for (int i = 0; i < tot - 1; i++) {
		int minIndex = i;
		for (int j = i + 1; j < tot; j++) {
			if (Book_info[j].cost < Book_info[minIndex].cost) {
				minIndex = j;
			}
		}
		Book temp;
		temp = Book_info[i];
		Book_info[i] = Book_info[minIndex];
		Book_info[minIndex] = temp;
	}
}


/* �鲢���� */
Book temp[MAXN];
void Merge_Sort(int s, int t) {
	cout << "ʹ�ù鲢����ķ��������ݽ�������\n";

	if (s == t) return;
	int mid = (s + t) >> 1;

	Merge_Sort(s, mid);
	Merge_Sort(mid + 1, t);
	int i = s, j = mid + 1, k = s;

	while (i <= mid && j <= t)
	{
		if (Book_info[i].cost <= Book_info[j].cost)
		{
			temp[k] = Book_info[i];
			k++;
			i++;
		}
		else
		{
			temp[k] = Book_info[j];
			j++;
			k++;
		}
	}
	while (i <= mid)
	{
		temp[k] = Book_info[i];
		k++;
		i++;
	}
	while (j <= t)
	{
		temp[k] = Book_info[j];
		k++;
		j++;
	}
	for (int i = s; i <= t; i++)
	{
		Book_info[i] = temp[i];
	}
}


/* �������� */
void Quick_Sort(int l,int r) {
	int i, j;
	double mid;
	i = l;
	j = r;
	mid = Book_info[(l + r) >> 1].cost;

	do {
		while (Book_info[i].cost < mid) i++;
		while (Book_info[j].cost > mid) j--;
		if (i <= j)
		{
			Book temp;
			temp = Book_info[i], Book_info[i] = Book_info[j], Book_info[j] = temp;
			i++, j--;
		}
	} while (i <= j);
	if (l < j) Quick_Sort(l, j);
	if (i < r) Quick_Sort(i, r);
}


/* ������ */
void Heap_Sort() {
	cout << "ʹ�ö�����ķ��������ݽ�������\n";

	for (int i = tot / 2 - 1; i >= 0; i--) {
		int parent = i;
		int child = 2 * i + 1;
		while (child < tot) {
			if (child + 1 < tot && Book_info[child].cost < Book_info[child + 1].cost) {
				child++;
			}
			if (Book_info[parent].cost < Book_info[child].cost) {
				Book temp;
				temp = Book_info[child], Book_info[child] = Book_info[parent], Book_info[parent] = temp;
				parent = child;
			}
			child = child * 2 + 1;
		}
	}

	for (int i = tot - 1; i > 0; i--) {
		Book temp;
		temp = Book_info[i], Book_info[i] = Book_info[0], Book_info[0] = temp;

		int parent = i;
		int child = 2 * i + 1;
		while (child < tot) {
			if (child + 1 < tot && Book_info[child].cost < Book_info[child + 1].cost) {
				child++;
			}
			if (Book_info[parent].cost < Book_info[child].cost) {
				Book temp;
				temp = Book_info[child], Book_info[child] = Book_info[parent], Book_info[parent] = temp;
				parent = child;
			}
			child = child * 2 + 1;
		}
	}

}


/*****************************************************
* ���ʹ�ü��������㷨
* ***************************************************/
void Sort_info() {
	/*
	* 1 ð������
	* 2 ѡ������
	* 3 �鲢����
	* 4 ��������
	* 5 ������
	*/

	srand((unsigned)time(NULL));
	int method = rand() % 5 + 1;
	switch (method) {
	case 1:
		Bubble_Sort();
		break;
	case 2:
		Selection_Sort();
		break;
	case 3:
		Merge_Sort(0,tot-1);
		break;
	case 4:
		Quick_Sort(0,tot-1);
		break;
	case 5:
		Heap_Sort();
		break;
	default:
		break;
	}

	ofstream oFile;
	oFile.open("book_newsort.txt", ios::out);
	int suc = oFstream(oFile);

	if (!suc) {
		system("cls");
		return;
	}

	for (int i = 0; i < tot; i++)
		oFile << Book_info[i].isbn << ' ' << Book_info[i].name << ' ' << Book_info[i].cost << '\n';

	cout << "ͼ����Ϣ�ѳɹ�д���ļ�book_newsort.txt�У�\n";
}


/*****************************************************
* �˳�ϵͳ
* ***************************************************/
char Exit_system() {

	char y_or_n;
	while (1) {
		cout << "ȷ���˳�����y/n)\n";
		cin >> y_or_n;
		getchar();
		if (y_or_n != 'y' && y_or_n != 'n') {
			cout << "��Ч���룡������ѡ��\n";
		}
		else break;
	}

	if (y_or_n == 'y') {
		Write_info("book_newsort.txt");
	}

	return y_or_n;
}
