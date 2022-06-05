/// <summary>
/// ����Ҫʹ�õ����ݽṹ
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
/// ��ʼ������󣺴���������ϣ�����������������ļ��ж�ȡ��Ʊ������Ϣ���ǵ���Ϣ����������
/// </summary>
Stock::Stock() {
	/* ��csv�ļ��ж�ȡ������Ϣ���洢�������� */
	ifstream iFile1;															// �����ȡ������Ϣ���ļ�������
	iFile1.open("��Ʊ������Ϣ����/A�ɹ�˾���.csv");

	int sum = -1;																// ��������������Ϣ����������60��
	getline(iFile1, line_Basic);												// �������
	string line;
	while (getline(iFile1, line)) {
		//cout << line << endl;
		istringstream ss(line);													// �ַ���������һ����Ϣ
		Insert_BasicInfo(ss, ST.Data, ++sum);									// ����Ϣ���뵽������
	}
	ST.length = sum + 1;

	/* ��txt�ж�ȡ�ǵ���Ϣ�洢�������� */
	for (int i = 0; i < ST.length; i++) {										// ��ȡÿһ֧��Ʊ�����һ��ʱ����ǵ���Ϣ
		ifstream iFile2;														// �����ȡ�ǵ���Ϣ���ļ�������
		string filename = "��Ʊ�ǵ�����/" + ST.Data[i].TickerSymbol + ".txt";		// �õ���Ӧ��Ʊ�����Ϣ�洢���ļ����·��
		//cout << filename << endl;
		iFile2.open(filename, ios::in);
		ST.Data[i].UDInfo_num = Insert_UDInfo(iFile2, ST.Data[i].UDInfo);								// ����������Ϣ���뵽������
	}

	/* ��ʼ����������� */
	Del_Mark = 0;

	for (int i = 0; i < 97; i++) {												// ��ϣ��
		H.H[i] = new LinkNode();
		H.H[i]->next = NULL;
	}

	T = new BSTNode();															// ����������
	T = NULL;

	/* �����֤ */
	/*for (int i = 0; i < ST.length; i++)
		cout << ST.Data[i].FullName<<' '<<ST.Data[i].TickerSymbol<<' '<< ST.Data[i].UDInfo[1].Date<<' '<< ST.Data[i].UDInfo[2].Date <<' '<<ST.Data[i].UDInfo[1].TurnoverRate<<endl;*/

}


/// <summary>
/// ������ϣ����ϣ��������Ϊ H(key)= ��Ʊ������ַ�ֵ֮��	MOD	97
/// </summary>
void Stock::CreateHash() {
	H.tot = ST.length;
	for (int i = 0; i < ST.length; i++) {										// �������й�Ʊ��Ϣ���Թ�Ʊ�����ASCII��ֵ֮��Ϊ�ؼ��ֽ�����ϣ��
		LinkList p;																// ������ʱ����ָ��
		p = new LinkNode();
		p->Data = ST.Data + i;													// ����ָ���������Ϊ��ǰ��Ʊ����Ϣ
		p->next = NULL;

		int key = Hash_Key(ST.Data[i].TickerSymbol);							// ���ϣ����ֵ 

		if (H.H[key]->next != NULL) {											// �������뵽��Ӧ��������
			p->next = H.H[key]->next;
			H.H[key]->next = p;
		}
		else {
			H.H[key]->next = new LinkNode();
			H.H[key]->next = p;
		}
	}

	Hashed = 1;

	/* ������� */
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
/// �������ڹ���������
/// </summary>
void Stock::CreateList() {
	for (int i = 0; i < ST.length; i++) {										// ����ÿһ����Ʊ��Ϣ
		int Days = ST.Data[i].UDInfo_num;
		for (int j = 0; j < Days; j++) {										// ����ÿ֧��Ʊ�洢��ÿһ���ǵ���Ϣ
			string date = ST.Data[i].UDInfo[j].Date;
			map<string, DateLink>::iterator iter = L.find(date);
			if (iter == L.end()) {												// �����ڵĹ�Ʊ��Ϣ��δ����
				DateLink tmp = new DateLNode();									// �����½����Ϊͷ���
				tmp->next = NULL;
				L.insert(map<string, DateLink>::value_type(date, tmp));			// ���������ڹ�Ʊ��Ϣ�������ͷ���
			}
			DateLink p = new DateLNode();											// �����½����뵽��������
			p->BasicInfo = ST.Data + i;											// ������Ϣ��ָ��ù�Ʊ�Ļ�����Ϣ
			p->UDInfo = ST.Data[i].UDInfo + j;									// �ǵ���Ϣ��ָ��ù�Ʊ������ǵ���Ϣ
			p->next = L[date]->next;
			L[date]->next = p;													// ʹ��ͷ�巨���뵽��Ӧ���ڵ�������	
		}
	}

	/* ������� */
	/*for (map<string, DateLink>::iterator it = L.begin(); it != L.end(); it++) {
		cout << "����: " << it->first << endl;
		DateLink p = it->second;
		p = p->next;
		while (p != NULL) {
			cout << p->BasicInfo->TickerName << ' ' << p->BasicInfo->TickerSymbol << ' ' << p->UDInfo->Date << endl;
			p = p->next;
		}
	}*/
}


/// <summary>
/// ���������������������е�ÿһ��Ԫ�ع��������뵽��������
/// </summary>
void Stock::CreateBST() {
	this->T = NULL;
	for (int i = 0; i < ST.length; i++)												// �������飬��ÿһ��Ԫ�ؽ��������뵽��������
		InsertBST(this->T, i);
}


/// <summary>
/// ���ļ��ж�ȡ���ݽ�����Ȩͼ
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
	iFile.open("��Ʊ������Ϣ����/60֧��Ʊ��Ϣ1.csv");

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
	Read_Graph = 1;																		// ��Ǵ�Ȩͼ��Ϣ�Ѿ�����

	/* ������� */
	/*for (int i = 1; i <= 60; i++)
		for (int j = 1; j <= 60; j++)
			if (Graph[i][j] != Maxn)
				cout << i << '\t' << j <<'\t'<< Graph[i][j] << endl;*/
}


/// <summary>
/// �������ж���Ķ���������
/// </summary>
/// <returns>���ض������ĸ��ڵ�</returns>
BSTree Stock::ReturnBST() {
	return T;
}


/// <summary>
/// ������й�ɾ����������Ҫ���˳�ϵͳʱ������Ϣ
/// </summary>
void Stock::Write_File() {
	if (Del_Mark == 0) return;						// δ�����޸Ĳ���Ҫ����д��

	ofstream oFile_Basic;						// ����д�������Ϣ���ļ���
	oFile_Basic.open("��Ʊ������Ϣ����/A�ɹ�˾���.csv", ios::out);
	oFile_Basic << line_Basic << endl;
	for (int i = 0; i < ST.length; i++) {
		if (ST.Data[i].Del_flag == 1) continue;		// ��������Ѿ���ɾ��������Ҫд��
		cout << ST.Data[i].Del_flag << ' ' << ST.Data[i].TickerName << endl;

		/* ��������Ϣд�������Ϣ�ļ� */
		oFile_Basic << ST.Data[i].TickerSymbol << ',' << ST.Data[i].TickerName << ','
			<< ST.Data[i].IndustryCode << ',' << ST.Data[i].PriClass << ','
			<< ST.Data[i].SecClass << ',' << ST.Data[i].Exchange << ','
			<< ST.Data[i].FullName << ',' << ST.Data[i].ListingData << ','
			<< ST.Data[i].Province << ',' << ST.Data[i].City << ','
			<< ST.Data[i].LegalPerson << ',' << ST.Data[i].Address << ','
			<< ST.Data[i].WebAddress << ',' << ST.Data[i].Email << ','
			<< ST.Data[i].Tel << ',' << ST.Data[i].MainBusiness << ','
			<< ST.Data[i].BusinessScope << endl;

		/* ���ǵ���Ϣд���ǵ���Ϣ�ļ� */
		ofstream oFile_UDInfo;
		string filename = "��Ʊ�ǵ�����/" + ST.Data[i].TickerSymbol + ".txt";
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



