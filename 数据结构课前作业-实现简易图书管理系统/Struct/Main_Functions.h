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
// 统计文件中图书的总数

string title[5];


struct Book {
	string isbn="";
	string name="";
	double cost=0;
}Book_info[MAXN+7];
// 存储图书信息的结构体数组


/*****************************************************
* 输出图书信息管理系统的主菜单
* ***************************************************/
void main_menu() {
	cout << "欢迎使用图书信息管理系统！\n";
	cout << "***************************************************\n";
	cout << "主菜单\n";
	cout << "1.显示已录入的所有图书信息\n";
	cout << "2.在指定位置添加图书信息\n";
	cout << "3.删除指定位置的图书信息\n";
	cout << "4.查找图书信息\n";
	cout << "5.修改图书信息\n";
	cout << "6.对图书根据价格升序排序并写入新文件中\n";
	cout << "7.安全退出系统（否则您做的修改可能无法保存）\n";
	cout << "***************************************************\n";
}


/*****************************************************
* 从文件中读取全部的图书信息并存入结构体数组
* ***************************************************/
int Get_info() {
	ifstream iFile;
	iFile.open("book.txt", ios::in);
	int suc = iFstream(iFile);

	if (!suc) {
		system("cls");
		cout << "文件错误！\n";
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
* 改动图书信息后将其写入文件
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
* 显示全部的图书信息
* ***************************************************/
void Show_info() {
	system("cls");

	for (int i = 0; i < tot; i++)
		cout << Book_info[i].isbn << "    " << Book_info[i].name << "    " << Book_info[i].cost << '\n';

	printf("共 %d 条图书信息\n", tot);
}


/*****************************************************
* 在指定位置添加图书信息
* ***************************************************/
void Insert_info() {
	int flag = 1;
	while (flag) {
		system("cls");

		string spos = "";
		int pos;
		if(tot!=0) {	 
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
		else {
			int pos=1;
		}

		string tempi, tempn;
		double tempc;
		cout << "请输入图书的书号：";
		cin >> tempi;
		getchar();
		cout << "请输入图书的书名：";
		getline(cin, tempn);
		//getchar();
		cout << "请输入图书的价格：";
		cin >> tempc;
		getchar();

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
			cout << "添加成功！\n";
			tot++;
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
void Delete_info() {
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

		cout << Book_info[pos-1].isbn << "    " << Book_info[pos-1].name << "    " << Book_info[pos-1].cost << '\n';

		for (int i = pos - 1; i < tot - 1; i++)
			Book_info[i] = Book_info[i + 1];

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
			cout << "删除成功！\n";
			tot--;
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
void Search_with_Pos() {
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

	cout << "所查找图书的书号为：" << Book_info[pos - 1].isbn << '\n';
	cout << "所查找图书的书名为：" << Book_info[pos - 1].name << '\n';
	cout << "所查找图书的价格为：" << Book_info[pos - 1].cost << '\n';

	system("pause");
}


/*****************************************************
* 按书名查找图书信息
* ***************************************************/
void Search_with_Name() {
	system("cls");

	cout << "请输入查找图书的书名: ";
	string name;
	getline(cin, name);

	int count = 0;
	for (int i = 0; i < tot; i++) {
		if (Book_info[i].name == name) {
			cout << "位置: " << i + 1 << "    书号: " << Book_info[i].isbn << "    书名: " << Book_info[i].name << "    价格: " << Book_info[i].cost << '\n';
			count++;
		}
	}

	printf("查找到 %d 条信息\n", count);
	system("pause");
}


/*****************************************************
* 查找图书信息
* ***************************************************/
void Search_info() {
	system("cls");

	int flag = 1;
	while (flag) {
		cout << "****************************\n";
		cout << "4.1 按位置查找\n";
		cout << "4.2 按书名查找\n";
		cout << "请输入 1 或 2\n";
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
void Change_info() {
	// 修改价格并写入两个文件
	int i;
	for (i = 0; i < tot; i++) {
		if (Book_info[i].cost >= 25) Book_info[i].cost *= 1.1;
		if (Book_info[i].cost < 25) Book_info[i].cost *= 0.8;
	}

	Write_info("book.txt");
	Write_info("book_newprice.txt");

	printf("修改完成！\n");
}


/* 冒泡排序 */
void Bubble_Sort() {
	cout << "使用冒泡排序的方法对数据进行排序\n";

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
				

/* 选择排序 */
void Selection_Sort() {
	cout << "使用选择排序的方法对数据进行排序\n";

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


/* 归并排序 */
Book temp[MAXN];
void Merge_Sort(int s, int t) {
	cout << "使用归并排序的方法对数据进行排序\n";

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


/* 快速排序 */
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


/* 堆排序 */
void Heap_Sort() {
	cout << "使用堆排序的方法对数据进行排序\n";

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
* 随机使用几种排序算法
* ***************************************************/
void Sort_info() {
	/*
	* 1 冒泡排序
	* 2 选择排序
	* 3 归并排序
	* 4 快速排序
	* 5 堆排序
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

	cout << "图书信息已成功写入文件book_newsort.txt中！\n";
}


/*****************************************************
* 退出系统
* ***************************************************/
char Exit_system() {

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
		Write_info("book_newsort.txt");
	}

	return y_or_n;
}
