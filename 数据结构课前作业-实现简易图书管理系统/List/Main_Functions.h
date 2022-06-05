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
* 构造函数，创建头结点
* ********************************************/
Book::Book() {
	head = new Info();
	head->next = NULL;
	//head->priority = NULL;
	temp = head;
}


int Book::tot = 0;


/**********************************************
* 析构函数
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
* 从文件中读取所有的数据
* ********************************************/
void Book::Get_info() {
	ifstream iFile;
	iFile.open("book.txt", ios::in);
	int suc = iFstream(iFile);

	if (!suc) {
		system("cls");
		cout << "文件错误！\n";
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
* 将修改后的文件写入
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
* 显示所有的学生信息
* ********************************************/
void Book::Show_info() {
	system("cls");

	Info* p = head->next;
	//temp = temp->next;

	for (; p != NULL; p = p->next) {
		cout << p->isbn << "    " << p->name << "    " << p ->cost << '\n';
	}

	printf("共 %d 条图书信息\n", tot);
}


/**********************************************
* 在指定的位置添加图书信息
* ********************************************/
void Book::Insert_info() {
	int flag = 1;
	while (flag) {
		system("cls");


		string spos = "";
		int pos;
		if (tot != 0) {
			printf("请输入您将图书信息添加到的位置(1-%d)：", tot + 1);

			cin >> spos;
			getchar();
			/*增强程序健壮性，用户输入一串字母时警告错误输入*/

			pos = To_num(spos);
			if (pos == 0 || pos > tot + 1) {
				printf("位置无效，无法进行添加.\n");
				system("pause");
				continue;
			}
		}

		string tempi, tempn;
		int tempc;
		cout << "请输入图书的书号：";
		cin >> tempi;
		getchar();
		cout << "请输入图书的书名：";
		getline(cin, tempn);
		//getchar();
		cout << "请输入图书的价格：";
		cin >> tempc;
		getchar();

		Info* temp = new Info();
		temp->isbn = tempi;
		temp->name = tempn;
		temp->cost = tempc;
		temp->next = NULL;

		char y_or_n;
		while (1) {
			cout << "确认添加？（y/n)";
			cin >> y_or_n;
			getchar();
			if (y_or_n != 'y' && y_or_n != 'n') {
				cout << "无效输入！请重新选择\n";
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
			cout << "添加成功！" << endl;
			add_tot();
			while (1) {
				cout << "是否继续添加？（y/n)\n";
				cin >> y_or_n;
				getchar();
				if (y_or_n != 'y' && y_or_n != 'n') {
					cout << "无效输入！请重新选择\n";
				}
				else break;
			}
			if (y_or_n == 'n') flag = 0;
			continue;
		}

		int mark = 0;
		while (1) {
			cout << "****************************\n";
			cout << "1.退出信息添加\n";
			cout << "2.重新输入图书信息\n";
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

			cout << "输入无效！请重新选择\n";

		}

	}
	system("cls");
	Write_info("book.txt");
}


/*****************************************************
* 删除指定位置的图书信息
* ***************************************************/
void Book::Delete_info() {
	system("cls");
	int flag = 1;
	while (flag) {
		system("cls");
		if (tot == 0) {
			cout << "系统中无图书信息！\n";
			system("pause");
			flag = 0;
			break;
		}
		printf("请输入需要删除的图书位置(1-%d)：", tot);

		string spos = "";
		cin >> spos;
		getchar();
		/*增强程序健壮性，用户输入一串字母时警告错误输入*/

		int pos = To_num(spos);
		if (pos == 0 || pos > tot) {
			printf("位置无效，无法进行删除.\n");
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
			cout << "确认删除？（y/n)";
			cin >> y_or_n;
			getchar();
			if (y_or_n != 'y' && y_or_n != 'n') {
				cout << "无效输入！请重新选择\n";
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

			cout << "删除成功！" << endl;
			dif_tot();
			while (1) {
				cout << "是否继续删除？（y/n)\n";
				cin >> y_or_n;
				getchar();
				if (y_or_n != 'y' && y_or_n != 'n') {
					cout << "无效输入！请重新选择\n";
				}
				else break;
			}
			if (y_or_n == 'n') flag = 0;
			continue;
		}

		int mark = 0;
		while (1) {
			cout << "****************************\n";
			cout << "1.退出信息删除\n";
			cout << "2.重新选择删除图书位置\n";
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

			cout << "输入无效！请重新选择\n";

		}

	}
	system("cls");
	Write_info("book.txt");
}


/*****************************************************
* 按位置查找图书信息
* ***************************************************/
void Book::Search_with_Pos() {
	system("cls");
	printf("请输入所查找图书的位置(1-%d): ", tot + 1);

	string spos = "";
	cin >> spos;
	getchar();
	/*增强程序健壮性，用户输入一串字母时警告错误输入*/

	int pos = To_num(spos);
	if (pos == 0 || pos > tot + 1) {
		printf("位置无效，无法进行查找.\n");
		system("pause");
		return;
	}

	//int count = 0;
	int cur = 0;
	Info* p = head->next;
	for (; p != NULL; p = p->next) {
		cur++;
		if (cur == pos) {
			cout << "位置: " << cur << "    书号: " << p->isbn << "    书名: " << p->name << "    价格: " << p->cost << '\n';
			//count++;
		}
	}

	system("pause");
}


/*****************************************************
* 按书名查找图书信息
* ***************************************************/
void Book::Search_with_Name() {
	system("cls");

	cout << "请输入查找图书的书名: ";
	string name;
	getline(cin, name);

	int count = 0;
	int cur = 0;
	Info* p = head->next;
	for (; p != NULL;p=p->next) {
		cur++;
		if (p->name == name) {
			cout << "位置: " << cur  << "    书号: " << p->isbn << "    书名: " << p->name << "    价格: " << p->cost << '\n';
			count++;
		}
	}

	printf("查找到 %d 条信息\n", count);
	system("pause");
}


/*****************************************************
* 查找图书信息
* ***************************************************/
void Book::Search_info() {
	system("cls");

	int flag = 1;
	while (flag) {
		cout << "****************************\n";
		cout << "4.1 按位置查找\n";
		cout << "4.2 按书名查找\n";
		cout << "请输入 1 或 2 进行图书信息查找\n";
		cout << "****************************\n";

		int choi = 0;
		cin >> choi;
		getchar();

		if (choi != 1 && choi != 2) {
			cout << "输入无效，请重新输入\n";
			continue;
		}

		if (choi == 1)
			Search_with_Pos();

		if (choi == 2)
			Search_with_Name();

		char y_or_n = 'n';
		while (1) {
			system("cls");
			cout << "是否继续查找？（y/n)\n";
			cin >> y_or_n;
			getchar();
			if (y_or_n != 'y' && y_or_n != 'n') {
				cout << "无效输入！请重新选择\n";
			}
			else break;
		}
		if (y_or_n == 'n') flag = 0;
		system("cls");
	}
	system("cls");
}


/*****************************************************
* 修改图书信息
* ***************************************************/
void Book::Change_info() {
	// 修改价格并写入两个文件

	Info* p = head->next;
	for (; p != NULL; p = p->next) {
		if (p->cost >= 25) p->cost *= 1.1;
		if (p->cost < 25) p->cost *= 0.8;
	}

	Write_info("book.txt");
	Write_info("book_newprice.txt");
	printf("修改完成！\n");
}


/*****************************************************
* 排序
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
	cout << "图书信息已成功写入文件book_newsort.txt中！\n";
}

/*****************************************************
* 退出系统
* ***************************************************/
char Book::Exit_system() {

	char y_or_n;
	while (1) {
		cout << "确认退出？（y/n)\n";
		cin >> y_or_n;
		getchar();
		if (y_or_n != 'y' && y_or_n != 'n') {
			cout << "无效输入！请重新选择\n";
		}
		else break;
	}

	if (y_or_n == 'y') {
		Write_info("book.txt");
	}

	return y_or_n;
}
