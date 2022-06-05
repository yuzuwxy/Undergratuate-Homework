#pragma once
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<fstream>
#include"functions.h"
#include"Book.h"

using namespace std;


/**********************************************
* ���캯��������ͷ���
* ********************************************/
Book::Book() {
	head = new Info();
	head->next = NULL;
	//head->priority = NULL;
	temp = head;
}


int Book::tot = 0;


/**********************************************
* ��������
* ********************************************/
Book::~Book() {
	Info* left = head;
	Info* right = NULL;
	while (left != NULL)
	{
		right = left;
		left = left->next;
		delete right;
	}
}


/**********************************************
* ���ļ��ж�ȡ���е�����
* ********************************************/
void Book::Get_info() {
	ifstream iFile;
	iFile.open("book.txt", ios::in);
	int suc = iFstream(iFile);

	if (!suc) {
		system("cls");
		cout << "�ļ�����\n";
		exit(0);
	}

	int count = 0;

	Info* tail = head;

	string title;
	for (int i = 1; i <= 4; i++) iFile >> title;

	while (!iFile.eof()) {
		if (head->next== NULL) {
			head->next= new Info();
			head->next->next = NULL;
			iFile >> head->next->isbn >> head->next->name >> head->next->cost;
			add_tot();
			tail = head->next;
		}
		else {
			Info* newinfo = new Info();
			newinfo->next = NULL;
			iFile >> newinfo->isbn >> newinfo->name >> newinfo->cost;
			tail->next = newinfo;
			tail = tail->next;
			add_tot();
		}
	}

	if (head->next->isbn == "") {
		tot = 0;
		head->next = NULL;
	}

	iFile.close();
	//return count;
}


/**********************************************
* ���޸ĺ���ļ�д��
* ********************************************/
void Book::Write_info(string filename){
	ofstream oFile;
	oFile.open(filename, ios::out);
	int suc = oFstream(oFile);

	if (!suc) {
		system("cls");
		return;
	}

	Print_title(oFile);

	Info* p = head->next;

	if (p == NULL) {
		oFile.close();
		return;
	}

	for (; p->next != NULL; p = p->next) {
		oFile << p->isbn << "    " << p->name << "    " << p->cost << '\n';
	}
	oFile << p->isbn << "    " << p->name << "    " << p->cost;

	oFile.close();
}


/**********************************************
* ��ʾ���е�ѧ����Ϣ
* ********************************************/
void Book::Show_info() {
	system("cls");

	Info* p = head->next;
	//temp = temp->next;

	for (; p != NULL; p = p->next) {
		cout << p->isbn << "    " << p->name << "    " << p ->cost << '\n';
	}

	printf("�� %d ��ͼ����Ϣ\n", tot);
}


/**********************************************
* ��ָ����λ�����ͼ����Ϣ
* ********************************************/
void Book::Insert_info() {
	int flag = 1;
	while (flag) {
		system("cls");


		string spos = "";
		int pos;
		if (tot != 0) {
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

		string tempi, tempn;
		int tempc;
		cout << "������ͼ�����ţ�";
		cin >> tempi;
		getchar();
		cout << "������ͼ���������";
		getline(cin, tempn);
		//getchar();
		cout << "������ͼ��ļ۸�";
		cin >> tempc;
		getchar();

		Info* temp = new Info();
		temp->isbn = tempi;
		temp->name = tempn;
		temp->cost = tempc;
		temp->next = NULL;

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
			if (head->next == NULL||tot==0) {
				head->next = new Info();
				head->next->next = NULL;
				head->next->cost = temp->cost;
				head->next->isbn = temp->isbn;
				head->next->name = temp->name;
			}

			else {
				if (pos == 1) {
					temp->next = head->next;
					head->next = temp;
				}
				else {
					Info* p = head->next;
					int count = 0;
					for (; p != NULL; p = p->next) {
						count++;
						if (count == pos - 1) break;
					}

					temp->next = p->next;
					p->next = temp;
				}
			}

			system("cls");
			cout << "��ӳɹ���" << endl;
			add_tot();
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
void Book::Delete_info() {
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

		Info* p = head->next;
		int count = 0;
		for (; p != NULL; p = p->next) {
			count++;
			if (count == pos) break;
		}
		cout << p->isbn << "    " << p->name << "    " << p->cost << '\n';

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

			if (pos == 1) {
				Info* p = head->next;
				head->next = p->next;
			}
			else {
				Info* p = head->next;
				int count = 0;
				for (; p != NULL; p = p->next) {
					count++;
					if (count == pos - 1) break;
				}
				Info* temp = p->next;
				p->next = temp->next;
			}

			cout << "ɾ���ɹ���" << endl;
			dif_tot();
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
void Book::Search_with_Pos() {
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

	//int count = 0;
	int cur = 0;
	Info* p = head->next;
	for (; p != NULL; p = p->next) {
		cur++;
		if (cur == pos) {
			cout << "λ��: " << cur << "    ���: " << p->isbn << "    ����: " << p->name << "    �۸�: " << p->cost << '\n';
			//count++;
		}
	}

	system("pause");
}


/*****************************************************
* ����������ͼ����Ϣ
* ***************************************************/
void Book::Search_with_Name() {
	system("cls");

	cout << "���������ͼ�������: ";
	string name;
	getline(cin, name);

	int count = 0;
	int cur = 0;
	Info* p = head->next;
	for (; p != NULL;p=p->next) {
		cur++;
		if (p->name == name) {
			cout << "λ��: " << cur  << "    ���: " << p->isbn << "    ����: " << p->name << "    �۸�: " << p->cost << '\n';
			count++;
		}
	}

	printf("���ҵ� %d ����Ϣ\n", count);
	system("pause");
}


/*****************************************************
* ����ͼ����Ϣ
* ***************************************************/
void Book::Search_info() {
	system("cls");

	int flag = 1;
	while (flag) {
		cout << "****************************\n";
		cout << "4.1 ��λ�ò���\n";
		cout << "4.2 ����������\n";
		cout << "������ 1 �� 2 ����ͼ����Ϣ����\n";
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
void Book::Change_info() {
	// �޸ļ۸�д�������ļ�

	Info* p = head->next;
	for (; p != NULL; p = p->next) {
		if (p->cost >= 25) p->cost *= 1.1;
		if (p->cost < 25) p->cost *= 0.8;
	}

	Write_info("book.txt");
	Write_info("book_newprice.txt");
	printf("�޸���ɣ�\n");
}


/*****************************************************
* ����
* ***************************************************/
void Book::Bubble_Sort() {
	Info* p, * q, * tail;
	Info* h = head;

	tail = NULL;

	while ((h->next->next) != tail)
	{
		p = h;
		q = h->next;
		while (q->next != tail)
		{
			if ((q->cost) > (q->next->cost))
			{
				p->next = q->next;
				q->next = q->next->next;
				p->next->next = q;
				q = p->next;
			}
			q = q->next;
			p = p->next;
		}
		tail = q;
	}

	Write_info("book_newsort.txt");
	cout << "ͼ����Ϣ�ѳɹ�д���ļ�book_newsort.txt�У�\n";
}

/*****************************************************
* �˳�ϵͳ
* ***************************************************/
char Book::Exit_system() {

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
		Write_info("book.txt");
	}

	return y_or_n;
}
