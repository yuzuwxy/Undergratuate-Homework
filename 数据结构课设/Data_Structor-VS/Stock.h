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
#include <map>
#include "Struct.h"

using namespace std;

/// <summary>
/// 定义股票类，封装数据类型和操作
/// </summary>

class Stock
{
private:
	map<string, DateLink> L;					// 定义单链表用于涨跌信息查询,根据日期存储，使用map映射
	Hash H;										// 定义哈希表用于基本信息查询：根据股票代码
	BSTree T;									// 定义二叉排序树用于涨跌信息查询：根据股票代码
	STable ST;									// 定义顺序表用于快速排序和存储信息
	SixtyStock Stock_60[70];					// 定义结构体数组存储六十支股票的相关信息
	int Graph[Some+7][Some+7] = { 0 };			// 存储文件中读入的图
	int Compt_Graph[Some + 7][Some + 7] = { 0 };// 存储运行Floyed之后生成的完全图
	int Path[Some + 7][Some + 7] = { 0 };		// 存储Floyd算法得到的任意两点间的最短路径
	BSTedge BSTEdge[Some + 7];					// 存储最小生成树的边
	BGraph BiGraph;								// 存储子图


	KruscalEdge Krus_Edge[Some*Some/2];			// Kruscal算法使用的辅助结构体数组
	PrimEdge Prim_Closedge[Some + 7];			// Prim算法使用的辅助数组，同来记录权值最小的边
	int Hashed = 0;								// Hashed==1时表示已经建立过哈希表，在分析功能中读取60支股票信息时可以通过哈希表查询到对应信息
	int Del_Mark = 0;							// Del_Mark==1时表示已经进行过删除操作，需要在退出系统时重写文件
	int Sixty_Read = 0;							// Sixty_Read==1时表示已经读入过60支股票信息，后续使用时不需要再读入
	int Read_Graph = 0;							// Read_Grah==1表示已经从文件中读入图
	int Floyded = 0;							// Floyded==1表示已经使用Floyd算法得到了完全图

	string line_Basic;							// 存储基本信息的文件表头
	string line_UDInfo;							// 存储涨跌信息的文件表头
	string line_SixtyScr;						// 存储六十支股票评分的文件表头
	string line_Graph;							// 存储图的文件表头

protected:


public:
	// 对类进行初始化，仅将数据存储在单链表中
	Stock();
	
	void Insert_BasicInfo(istringstream& ss, basicinfo BasicInfo[], int sum);	// 将读入的一行基本信息通过字符串流存储到数组中
	int Insert_UDInfo(ifstream&, udinfo UDInfo[]);								// 将读入的涨跌信息存储到数组中
	int  Hash_Key(string const&);												// 求哈希函数值
	void InsertBST(BSTree&,int);												// 通过递归插入建立二叉树
	void PrintBST(BSTree);														// 检验二叉树是否建立成功的测试输出
	void Read_SixtyStock();														// 从文件中读入60支股票信息
	basicinfo* Search60_InAll(string);											// 读入六十支股票的名称和代码后寻找其其他信息
	udinfo* GetMaxFlutuation(basicinfo*);										// 找到某只股票最大涨跌幅
	void QSort(int, int,int);													// 对存储60支股票信息的数组进行快速排序
	int Partition(int, int,int);												// 对数组进行一趟排序，返回枢轴位置 
	void Relevance_Floyd();														// 使用Floyd算法计算最短路径即相关性分析
	void Prim();																// 使用Prim算法求连通图的最小生成树
	void Kruscal();																// 使用Kruscal算法求连通图的最小生成树
	void Choose(int ,int ,int );												// 最小生成树筛选顶点时出现边权重复或无法恰好选出时，需要额外进行筛选
	bool BGraph_DFS(int, int, int[]);											// 利用深度优先搜索染色法判断是否为二部图


	void CreateHash();															// 创建哈希表
	void CreateList();															// 创建单链表
	void CreateBST();															// 创建二叉树
	void CreateGraph();															// 从文件中读入信息建立带权图



	void Search_By_Hash();														// 基于哈希表的股票基本信息查询
	void Search_By_KMP();														// 基于KMP的股票网址查询
	void Search_By_BST();														// 基于二叉树的股票基本信息查询
	void Delete_By_BST();														// 基于二叉排序树的股票基本信息删除
	void Search_By_List();														// 基于单链表的股票价格信息查询



	void InsertionSort();													
	void QuickSort_Sixty();														// 针对60支股票信息基于快速排序的股票价格分析
	void SelectionSort_By_Scr();												// 针对60支股票信息基于简单选择排序的股票价格分析(根据评分排序）
	void SelectionSort_By_CloPrice();											// 针对60支股票信息基于简单选择排序的股票价格分析(根据最近一日收盘价排序）
	void ShortestPath_By_Floyd();												// 基于Floyd的股票相关性计算（任意两点间的最短路径）
	void Selection_By_BST();													// 基于Prim最小生成树的股票基金筛选
	void Selection_By_BGraph();													// 基于二部图的股票基金筛选

	double GetASL_Hash();														// 计算使用哈希表查找的平均查找长度
	double GetASL_BST();														// 计算使用二叉排序树的平均查找长度

	BSTree ReturnBST();															// 访问类中定义的二叉树对象
	
	void Write_File();															// 退出系统时将（可能）修改过的数据写回

	~Stock() {};

};