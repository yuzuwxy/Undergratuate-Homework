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
* 自定义“按任意键继续“显示文字实现按任意键返回主菜单
* ***************************************************/
void Back_to_Mainmenu() {
	printf("\n按回车键/Enter返回主菜单……");
	getchar();
}


/*****************************************************
* 判断只读文件是否可以正常打开
*****************************************************/
bool iFstream(ifstream& inStream) {
	if (!inStream) {
		cout << "图书信息无法读取！\n";
		return 0;
	}
	return 1;
}


/*****************************************************
* 判断写入文件是否可以正常打开
*****************************************************/
bool oFstream(ofstream& inStream) {
	if (!inStream) {
		cout << "文件错误！\n";
		return 0;
	}
	return 1;
}

/*****************************************************
* 判断输入的位置是一串数字并且有效
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
* 在每次将图书信息写入文件时，先写入标题和表头
* ***************************************************/
void Print_title(ofstream& oFile) {
	oFile << "北京林业大学图书馆计算机类图书采购列表\n";
	oFile << "ISBN	                  书名	                定价\n";
}
