/// <summary>
/// 创建要使用的数据结构
/// <summary>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <stdio.h>
#include <vector>
#include <limits>
#include <sstream>
#include"Stock.h"

using namespace std;

/// <summary>
/// 初始化类对象：创建链表、哈希表、二叉排序树，从文件中读取股票基本信息和涨跌信息存入数组中
/// </summary>
Stock::Stock() {
	/* 从csv文件中读取基本信息并存储到数组中 */
	ifstream iFile1;															// 定义读取基本信息的文件流对象
	iFile1.open("股票基本信息数据/A股公司简介.csv");

	int sum = -1;																// 计数器，计算信息的总条数（60）
	getline(iFile1, line_Basic);												// 读入标题
	string line;
	while (getline(iFile1, line)) {
		//cout << line << endl;
		istringstream ss(line);													// 字符串流读入一行信息
		Insert_BasicInfo(ss, ST.Data, ++sum);									// 将信息插入到数组中
	}
	ST.length = sum + 1;

	/* 从txt中读取涨跌信息存储到数组中 */
	for (int i = 0; i < ST.length; i++) {										// 读取每一支股票的最近一段时间的涨跌信息
		ifstream iFile2;														// 定义读取涨跌信息的文件流对象
		string filename = "股票涨跌数据/" + ST.Data[i].TickerSymbol + ".txt";		// 得到对应股票相关信息存储的文件相对路径
		//cout << filename << endl;
		iFile2.open(filename, ios::in);
		ST.Data[i].UDInfo_num = Insert_UDInfo(iFile2, ST.Data[i].UDInfo);								// 将读到的信息插入到数组中
	}

	/* 初始化其他类对象 */
	Del_Mark = 0;

	for (int i = 0; i < 97; i++) {												// 哈希表
		H.H[i] = new LinkNode();
		H.H[i]->next = NULL;
	}

	T = new BSTNode();															// 二叉排序树
	T = NULL;

	/* 输出验证 */
	/*for (int i = 0; i < ST.length; i++)
		cout << ST.Data[i].FullName<<' '<<ST.Data[i].TickerSymbol<<' '<< ST.Data[i].UDInfo[1].Date<<' '<< ST.Data[i].UDInfo[2].Date <<' '<<ST.Data[i].UDInfo[1].TurnoverRate<<endl;*/

}


/// <summary>
/// 构建哈希表，哈希函数定义为 H(key)= 股票代码的字符值之和	MOD	97
/// </summary>
void Stock::CreateHash() {
	H.tot = ST.length;
	for (int i = 0; i < ST.length; i++) {										// 遍历所有股票信息，以股票代码的ASCII码值之和为关键字建立哈希表
		LinkList p;																// 定义临时工作指针
		p = new LinkNode();
		p->Data = ST.Data + i;													// 工作指针的数据域为当前股票的信息
		p->next = NULL;

		int key = Hash_Key(ST.Data[i].TickerSymbol);							// 求哈希函数值 

		if (H.H[key]->next != NULL) {											// 将结点插入到对应的链表中
			p->next = H.H[key]->next;
			H.H[key]->next = p;
		}
		else {
			H.H[key]->next = new LinkNode();
			H.H[key]->next = p;
		}
	}

	Hashed = 1;

	/* 测试输出 */
/*	for (int i = 0; i < 97; i++) {
		LinkList p = H.H[i]->next;
		while (p != NULL) {
			cout <<i<<' '<< p->Data->FullName << ' ' << p->Data->index << ' ' << p->Data->TickerSymbol << endl;
			p = p->next;
		}
	}
*/
}


/// <summary>
/// 根据日期构建单链表
/// </summary>
void Stock::CreateList() {
	for (int i = 0; i < ST.length; i++) {										// 遍历每一个股票信息
		int Days = ST.Data[i].UDInfo_num;
		for (int j = 0; j < Days; j++) {										// 遍历每支股票存储的每一条涨跌信息
			string date = ST.Data[i].UDInfo[j].Date;
			map<string, DateLink>::iterator iter = L.find(date);
			if (iter == L.end()) {												// 该日期的股票信息还未插入
				DateLink tmp = new DateLNode();									// 创建新结点作为头结点
				tmp->next = NULL;
				L.insert(map<string, DateLink>::value_type(date, tmp));			// 创建该日期股票信息单链表的头结点
			}
			DateLink p = new DateLNode();											// 建立新结点插入到单链表中
			p->BasicInfo = ST.Data + i;											// 基本信息域指向该股票的基本信息
			p->UDInfo = ST.Data[i].UDInfo + j;									// 涨跌信息域指向该股票当天的涨跌信息
			p->next = L[date]->next;
			L[date]->next = p;													// 使用头插法插入到对应日期的链表中	
		}
	}

	/* 测试输出 */
	/*for (map<string, DateLink>::iterator it = L.begin(); it != L.end(); it++) {
		cout << "日期: " << it->first << endl;
		DateLink p = it->second;
		p = p->next;
		while (p != NULL) {
			cout << p->BasicInfo->TickerName << ' ' << p->BasicInfo->TickerSymbol << ' ' << p->UDInfo->Date << endl;
			p = p->next;
		}
	}*/
}


/// <summary>
/// 创建二叉树，即将数组中的每一个元素构建结点加入到二叉树中
/// </summary>
void Stock::CreateBST() {
	this->T = NULL;
	for (int i = 0; i < ST.length; i++)												// 遍历数组，将每一个元素建立结点插入到二叉树中
		InsertBST(this->T, i);
}


/// <summary>
/// 从文件中读取数据建立带权图
/// </summary>
void Stock::CreateGraph() {
	if (Sixty_Read == 0) {
		Read_SixtyStock();
		Sixty_Read = 1;
	}

	for (int i = 1; i <= 60; i++)
		for (int j = 1; j <= 60; j++)
			Graph[i][j] = Maxn;

	ifstream iFile;
	iFile.open("股票基本信息数据/60支股票信息1.csv");

	string line;
	getline(iFile, line_Graph);

	while (!iFile.eof()) {
		stringstream ss;
		iFile >> line;
		ss << line;

		string u, v, w;
		getline(ss, u, ',');
		getline(ss, v, ',');
		getline(ss, w, ',');
		Graph[stoi(u)][stoi(v)] = Graph[stoi(v)][stoi(u)] = stoi(w);
	}
	Read_Graph = 1;																		// 标记带权图信息已经读入

	/* 测试输出 */
	/*for (int i = 1; i <= 60; i++)
		for (int j = 1; j <= 60; j++)
			if (Graph[i][j] != Maxn)
				cout << i << '\t' << j <<'\t'<< Graph[i][j] << endl;*/
}


/// <summary>
/// 访问类中定义的二叉树对象
/// </summary>
/// <returns>返回二叉树的根节点</returns>
BSTree Stock::ReturnBST() {
	return T;
}


/// <summary>
/// 如果进行过删除操作，需要在退出系统时更新信息
/// </summary>
void Stock::Write_File() {
	if (Del_Mark == 0) return;						// 未做过修改不需要重新写入

	ofstream oFile_Basic;						// 定义写入基本信息的文件流
	oFile_Basic.open("股票基本信息数据/A股公司简介.csv", ios::out);
	oFile_Basic << line_Basic << endl;
	for (int i = 0; i < ST.length; i++) {
		if (ST.Data[i].Del_flag == 1) continue;		// 如果数据已经被删除，不需要写入
		cout << ST.Data[i].Del_flag << ' ' << ST.Data[i].TickerName << endl;

		/* 将基本信息写入基本信息文件 */
		oFile_Basic << ST.Data[i].TickerSymbol << ',' << ST.Data[i].TickerName << ','
			<< ST.Data[i].IndustryCode << ',' << ST.Data[i].PriClass << ','
			<< ST.Data[i].SecClass << ',' << ST.Data[i].Exchange << ','
			<< ST.Data[i].FullName << ',' << ST.Data[i].ListingData << ','
			<< ST.Data[i].Province << ',' << ST.Data[i].City << ','
			<< ST.Data[i].LegalPerson << ',' << ST.Data[i].Address << ','
			<< ST.Data[i].WebAddress << ',' << ST.Data[i].Email << ','
			<< ST.Data[i].Tel << ',' << ST.Data[i].MainBusiness << ','
			<< ST.Data[i].BusinessScope << endl;

		/* 将涨跌信息写入涨跌信息文件 */
		ofstream oFile_UDInfo;
		string filename = "股票涨跌数据/" + ST.Data[i].TickerSymbol + ".txt";
		oFile_UDInfo.open(filename);
		oFile_UDInfo << line_UDInfo;
		for (int j = 0; j < ST.Data[i].UDInfo_num; j++)
			oFile_UDInfo << fixed << setprecision(2) << ST.Data[i].UDInfo[j].Date << '\t' << ST.Data[i].UDInfo[j].OpenPrice << '\t'
			<< ST.Data[i].UDInfo[j].ClosingPrice << '\t' << ST.Data[i].UDInfo[j].HighestPrice << '\t'
			<< ST.Data[i].UDInfo[j].LowestPrice << '\t' << ST.Data[i].UDInfo[j].Turnover_Hand << '\t'
			<< ST.Data[i].UDInfo[j].Turnover_Yuan << '\t' << ST.Data[i].UDInfo[j].TurnoverRate << '\t'
			<< ST.Data[i].UDInfo[j].ChangeAmount << '\t' << ST.Data[i].UDInfo[j].FluctuationRange << endl;

	}
}



