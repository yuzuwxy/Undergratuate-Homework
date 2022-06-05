/// <summary>
/// ���ڶ���洢�������õĽṹ��
/// <summary>
#pragma once
#define _CRT_SECURE_NO_WARNINGS
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

#define MOD 97
#define Maxn 9999999
#define Some 60
#define ChooseNode 6
#define BNode 10

using namespace std;


/* �����ǵ���Ϣ�洢�������� */
struct udinfo{
	string Date = "";						// ����
	double OpenPrice = 0.0;					// ���̼�
	double ClosingPrice = 0.0;				// ���̼�
	double HighestPrice = 0.0;				// ��߼�
	double LowestPrice = 0.0;				// ��ͼ�
	double Turnover_Hand = 0.0;				// �ɽ������֣�
	int Turnover_Yuan = 0;					// �ɽ����Ԫ��
	string TurnoverRate = "";				// �����ʣ�%��
	double ChangeAmount = 0.0;				// �ǵ���
	double FluctuationRange = 0;			// �ǵ�����%��
};

/* ���������Ϣ��������*/
struct basicinfo{
	int index=0;							// ��Ʊ��Ϣ���
	int Del_flag = 0;						// ɾ����־��������Ϣ�ѱ�ɾ����Del_flag=1
	int UDInfo_num = 0;
	string TickerSymbol = "";				// ��Ʊ����
	string TickerName = "";					// ��Ʊ���
	string IndustryCode = "";				// ��ҵ����
	string PriClass = "";					// һ������
	string SecClass = "";					// ��������
	string Exchange = "";					// ���й�˾
	string FullName = "";					// ��˾ȫ��
	string ListingData = "";				// ��������
	string Province = "";					// ʡ��
	string City = "";						// ����
	string LegalPerson = "";				// ����
	string Address = "";					// ��ַ
	string WebAddress = "";					// ��ַ
	string Email = "";						// ����
	string Tel = "";						// �绰
	string MainBusiness = "";				// ��Ӫҵ��
	string BusinessScope = "";				// ��Ӫ��Χ
	double Score = 0;						// ��Ʊ���֣����У�
	udinfo UDInfo[205];						// ��֧��Ʊ��һ��ʱ����ǵ���Ϣ
};

/* ���嵥����洢�ṹ */
typedef struct LinkNode{
	basicinfo* Data;							// ������������
	LinkNode* next;								// ������ָ����
}*LinkList, LinkNode;

/* ����洢��Ʊÿ���ǵ���Ϣ�ĵ�����ṹ */
typedef struct DateLNode {
	basicinfo* BasicInfo;						// ��Ʊ������Ϣ
	udinfo* UDInfo;								// ��Ʊĳ�յ��ǵ���Ϣ
	DateLNode* next;							// ָ����
}DateLNode, * DateLink;

/* ����˳����������� */
struct STable{
	basicinfo Data[205];						// ˳�������
	int length=0;								// ˳�����
};

/* �����ϣ��洢�������� */
typedef struct {
	LinkList H[100];							// ��ϣ���ͷ��
	int tot;									// ��ϣ���е�Ԫ�ظ���
}Hash, * HNode;

/* ��������������洢���� */
typedef struct BSTNode{
	basicinfo* Data;							// ���������������
	BSTNode* lchild, *rchild;					// �������Һ���
}*BSTree,BSTNode;

/* �洢��ʮ֧��Ʊ����Ϣ */
typedef struct SixtyStock {
	int idx;
	basicinfo* BasicInfo;						// ָ��ȫ����Ʊ��������ʮ֧�еĻ�����Ϣ�洢���ڴ�ռ�
	udinfo* MaxFluctuation;						// ָ������ʮ֧��Ʊ��ÿ֧��Ʊ����ǵ��������ǵ���Ϣ�洢�Ŀռ䣨�ڿ�������ʱʹ�ã�
}SixtyStock;

/* ʹ��Prim����С�������ĸ������ݽṹ */
typedef struct PrimEdge {
	int adjvex = 0;						// ��С����U�е��Ǹ�����
	int lowcost = 0;					// ��С���ϵ�Ȩֵ
}PrimEdge;

/* �洢��С�������ĸ����� & ʵ��Kruscal����ĸ������ݽṹ */
typedef struct BSTedge{
	int u, v;							// ��߹�������������					
	int w=0;							// ���ϵ�Ȩֵ
}BSTedge,KruscalEdge;

/* ���ڶ���ͼ���й�Ʊ�۸�ɸѡ���ڴ洢����BNode���������ͼ */
typedef struct BGraph {
	int vex[BNode + 7] = { 0 };
	int arcs[BNode + 7][BNode + 7];
}BGraph;