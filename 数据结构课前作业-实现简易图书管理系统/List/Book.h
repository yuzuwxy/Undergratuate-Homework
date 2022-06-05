#pragma once
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<fstream>
#include"functions.h"
#include"Main_Functions.h"

using namespace std;

struct Info {
	string isbn = "", name = "";
	double cost = 0;
	Info* next=NULL;
	//Info* priority;
}Book_info;


class Book {
private:
	Info* head;
	Info* temp;
	static int tot;

public:
	// 构造函数
	Book();

	// 析构函数
	~Book();

	// tot图书信息的数量
	static void add_tot() {
		tot++;
	};

	static void dif_tot() {
		tot--;
	};

	// 从文件中读取图书信息
	void Get_info();

	// 将存储的信息写入文件中
	void Write_info(string);

	// 显示所有读取的信息
	void Show_info();

	// 插入图书信息到指定位置
	void Insert_info();

	// 删除指定位置的图书信息
	void Delete_info();

	// 按照位置查找图书信息
	void Search_with_Pos();

	// 按照名字查找图书信息
	void Search_with_Name();

	// 查找图书信息
	void Search_info();

	// 修改图书信息
	void Change_info();

	// 对图书信息采用冒泡排序
	void Bubble_Sort();

	// 排序时需要交换两条信息
	void Exchange_Info(Info*, Info* right);

	// 退出系统
	char Exit_system();
};

