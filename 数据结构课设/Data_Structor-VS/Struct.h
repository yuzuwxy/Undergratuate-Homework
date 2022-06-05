/// <summary>
/// 用于定义存储数据所用的结构体
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


/* 定义涨跌信息存储数据类型 */
struct udinfo{
	string Date = "";						// 日期
	double OpenPrice = 0.0;					// 开盘价
	double ClosingPrice = 0.0;				// 收盘价
	double HighestPrice = 0.0;				// 最高价
	double LowestPrice = 0.0;				// 最低价
	double Turnover_Hand = 0.0;				// 成交量（手）
	int Turnover_Yuan = 0;					// 成交额（万元）
	string TurnoverRate = "";				// 换手率（%）
	double ChangeAmount = 0.0;				// 涨跌额
	double FluctuationRange = 0;			// 涨跌幅（%）
};

/* 定义基本信息数据类型*/
struct basicinfo{
	int index=0;							// 股票信息编号
	int Del_flag = 0;						// 删除标志，若该信息已被删除，Del_flag=1
	int UDInfo_num = 0;
	string TickerSymbol = "";				// 股票代码
	string TickerName = "";					// 股票简称
	string IndustryCode = "";				// 行业编码
	string PriClass = "";					// 一级门类
	string SecClass = "";					// 二级门类
	string Exchange = "";					// 上市公司
	string FullName = "";					// 公司全称
	string ListingData = "";				// 上市日期
	string Province = "";					// 省份
	string City = "";						// 城市
	string LegalPerson = "";				// 法人
	string Address = "";					// 地址
	string WebAddress = "";					// 网址
	string Email = "";						// 邮箱
	string Tel = "";						// 电话
	string MainBusiness = "";				// 主营业务
	string BusinessScope = "";				// 经营范围
	double Score = 0;						// 股票评分（若有）
	udinfo UDInfo[205];						// 该支股票近一段时间的涨跌信息
};

/* 定义单链表存储结构 */
typedef struct LinkNode{
	basicinfo* Data;							// 链表结点数据域
	LinkNode* next;								// 链表结点指针域
}*LinkList, LinkNode;

/* 定义存储股票每日涨跌信息的单链表结构 */
typedef struct DateLNode {
	basicinfo* BasicInfo;						// 股票基本信息
	udinfo* UDInfo;								// 股票某日的涨跌信息
	DateLNode* next;							// 指针域
}DateLNode, * DateLink;

/* 定义顺序表数据类型 */
struct STable{
	basicinfo Data[205];						// 顺序表数组
	int length=0;								// 顺序表长度
};

/* 定义哈希表存储数据类型 */
typedef struct {
	LinkList H[100];							// 哈希表的头表
	int tot;									// 哈希表中的元素个数
}Hash, * HNode;

/* 定义二叉排序树存储类型 */
typedef struct BSTNode{
	basicinfo* Data;							// 二叉树结点数据域
	BSTNode* lchild, *rchild;					// 结点的左右孩子
}*BSTree,BSTNode;

/* 存储六十支股票的信息 */
typedef struct SixtyStock {
	int idx;
	basicinfo* BasicInfo;						// 指向全部股票中在这六十支中的基本信息存储的内存空间
	udinfo* MaxFluctuation;						// 指向这六十支股票中每支股票最大涨跌幅所在涨跌信息存储的空间（在快速排序时使用）
}SixtyStock;

/* 使用Prim求最小生成树的辅助数据结构 */
typedef struct PrimEdge {
	int adjvex = 0;						// 最小边在U中的那个顶点
	int lowcost = 0;					// 最小边上的权值
}PrimEdge;

/* 存储最小生成树的各条边 & 实现Kruscal引入的辅助数据结构 */
typedef struct BSTedge{
	int u, v;							// 与边关联的两个顶点					
	int w=0;							// 边上的权值
}BSTedge,KruscalEdge;

/* 基于二部图进行股票价格筛选用于存储含有BNode个顶点的子图 */
typedef struct BGraph {
	int vex[BNode + 7] = { 0 };
	int arcs[BNode + 7][BNode + 7];
}BGraph;