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
	// ���캯��
	Book();

	// ��������
	~Book();

	// totͼ����Ϣ������
	static void add_tot() {
		tot++;
	};

	static void dif_tot() {
		tot--;
	};

	// ���ļ��ж�ȡͼ����Ϣ
	void Get_info();

	// ���洢����Ϣд���ļ���
	void Write_info(string);

	// ��ʾ���ж�ȡ����Ϣ
	void Show_info();

	// ����ͼ����Ϣ��ָ��λ��
	void Insert_info();

	// ɾ��ָ��λ�õ�ͼ����Ϣ
	void Delete_info();

	// ����λ�ò���ͼ����Ϣ
	void Search_with_Pos();

	// �������ֲ���ͼ����Ϣ
	void Search_with_Name();

	// ����ͼ����Ϣ
	void Search_info();

	// �޸�ͼ����Ϣ
	void Change_info();

	// ��ͼ����Ϣ����ð������
	void Bubble_Sort();

	// ����ʱ��Ҫ����������Ϣ
	void Exchange_Info(Info*, Info* right);

	// �˳�ϵͳ
	char Exit_system();
};

