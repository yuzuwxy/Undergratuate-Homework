#pragma once
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<ctime>
#include<cstring>
#include<cmath>
#include<fstream>
#include"Main_Functions.h"

using namespace std;


/*****************************************************
* �Զ��塰���������������ʾ����ʵ�ְ�������������˵�
* ***************************************************/
void Back_to_Mainmenu() {
	printf("\n���س���/Enter�������˵�����");
	getchar();
}


/*****************************************************
* �ж�ֻ���ļ��Ƿ����������
*****************************************************/
bool iFstream(ifstream& inStream) {
	if (!inStream) {
		cout << "ͼ����Ϣ�޷���ȡ��\n";
		return 0;
	}
	return 1;
}


/*****************************************************
* �ж�д���ļ��Ƿ����������
*****************************************************/
bool oFstream(ofstream& inStream) {
	if (!inStream) {
		cout << "�ļ�����\n";
		return 0;
	}
	return 1;
}

/*****************************************************
* �ж������λ����һ�����ֲ�����Ч
* ***************************************************/
int To_num(string spos) {
	int s = spos.size();
	int pos = 0;


	for (int i = 0; i < s; i++) {
		if (spos[i] < '0' || spos[i]>'9') {
			pos = 0;
			break;
		}
		pos = pos * 10 + spos[i] - '0';
	}

	return pos;
}


/*****************************************************
* ��ÿ�ν�ͼ����Ϣд���ļ�ʱ����д�����ͱ�ͷ
* ***************************************************/
void Print_title(ofstream& oFile) {
	oFile << "������ҵ��ѧͼ��ݼ������ͼ��ɹ��б�\n";
	oFile << "ISBN	                  ����	                ����\n";
}
