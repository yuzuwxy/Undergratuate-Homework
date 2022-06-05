/// <summary>
/// 实现股票类中定义的非主要函数
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
/// 从文件中读取A股基本信息存入数组中
/// </summary>
/// <param name="ss">读入某一行信息的字符串流</param>
/// <param name="BasicInfo">基本信息数组</param>
/// <param name="sum">当前信息的编号</param>
void Stock::Insert_BasicInfo(istringstream& ss, basicinfo BasicInfo[], int sum) {
	getline(ss, BasicInfo[sum].TickerSymbol, ',');
	getline(ss, BasicInfo[sum].TickerName, ',');
	getline(ss, BasicInfo[sum].IndustryCode, ',');
	getline(ss, BasicInfo[sum].PriClass, ',');
	getline(ss, BasicInfo[sum].SecClass, ',');
	getline(ss, BasicInfo[sum].Exchange, ',');
	getline(ss, BasicInfo[sum].FullName, ',');
	getline(ss, BasicInfo[sum].ListingData, ',');
	getline(ss, BasicInfo[sum].Province, ',');
	getline(ss, BasicInfo[sum].City, ',');
	getline(ss, BasicInfo[sum].LegalPerson, ',');
	getline(ss, BasicInfo[sum].Address, ',');
	getline(ss, BasicInfo[sum].WebAddress, ',');
	getline(ss, BasicInfo[sum].Email, ',');
	getline(ss, BasicInfo[sum].Tel, ',');
	getline(ss, BasicInfo[sum].MainBusiness, ',');
	getline(ss, BasicInfo[sum].BusinessScope, ',');
	BasicInfo[sum].index = sum;
	BasicInfo[sum].Del_flag = 0;
}


/// <summary>
/// 从文件中读入股票的涨跌信息
/// </summary>
/// <param name="iFile">文件流</param>
/// <param name="UDInfo">存储涨跌信息数组</param>
/// <param name="i">计数器</param>
int Stock::Insert_UDInfo(ifstream& iFile, udinfo UDInfo[]) {
	string line;
	getline(iFile, line_UDInfo);
	int i = -1;

	while (getline(iFile, line)) {
		istringstream ss(line);
		getline(ss, UDInfo[++i].Date, ' ');
		ss >> UDInfo[i].OpenPrice;
		ss >> UDInfo[i].ClosingPrice;
		ss >> UDInfo[i].HighestPrice;
		ss >> UDInfo[i].LowestPrice;
		ss >> UDInfo[i].Turnover_Hand;
		ss >> UDInfo[i].Turnover_Yuan;
		ss >> UDInfo[i].TurnoverRate;
		ss >> UDInfo[i].ChangeAmount;
		ss >> UDInfo[i].FluctuationRange;
	}
	return i + 1;
}


/// <summary>
/// 计算哈希函数值
/// </summary>
/// <param name="TickerSymbol">股票信息中存储的股票代码部分</param>
/// <returns>返回哈希函数值</returns>
int Stock::Hash_Key(string const& TickerSymbol) {
	int len = TickerSymbol.size();
	int sum = 0;
	for (int i = 0; i < len; i++)
		sum += TickerSymbol[i];
	return sum % MOD;																	// 定义的哈希函数为股票代码的字符值之后%97
}


/// <summary>
/// 插入新结点的方式插入二叉树
/// </summary>
/// <param name="T">当前递归到的二叉树结点</param>
/// <param name="i">待插入结点在顺序表中的位置</param>
void Stock::InsertBST(BSTree &T, int i) {
	if (T == NULL) {														// 找到插入位置，递归结束
		BSTree S = new BSTNode();											// 生成新结点
		S->Data = ST.Data + i;												// 新结点的数据域为待插入的股票信息
		S->lchild = NULL, S->rchild = NULL;									// 将新结点作为叶子结点
		T = S;																// 把新结点链接到已经找到的插入位置
	}
	else if (ST.Data[i].TickerSymbol < T->Data->TickerSymbol)				// 将新结点S插入左子树
		InsertBST(T->lchild, i);
	else if (ST.Data[i].TickerSymbol > T->Data->TickerSymbol)				// 将新结点S插入右子树
		InsertBST(T->rchild, i);
}


/// <summary>
/// 中序遍历输出二叉排序树，对二叉树建立进行测试输出
/// </summary>
/// <param name="T">二叉树当前结点</param>
void Stock::PrintBST(BSTree T) {
	if (T == NULL) return;
	PrintBST(T->lchild);
	if (T->Data->Del_flag == 0) {														// 判断结点是否已经在二叉树中删除
		cout << T->Data->TickerSymbol << endl;
		if (T->rchild == NULL && T->lchild == NULL) cout << "NULL\n";
	}
	PrintBST(T->rchild);
}


/// <summary>
/// 读取六十支股票文件，将信息（基本信息+最大涨跌幅当天的涨跌信息）存储在结构体数组中
/// </summary>
void Stock::Read_SixtyStock() {
	if (Hashed == 0) {
		CreateHash();
		Hashed = 1;																		// 可通过哈希表查询到对应信息
	}
	ifstream iFile;
	iFile.open("股票基本信息数据/60支股票信息2.csv", ios::in);								// 定义读入文件的文件流

	string line;
	iFile >> line_SixtyScr;																		// 读入第一行表头

	while (!iFile.eof()) {
		int idx;																		// 文件中的股票序号
		string idx_s, scr_s, name, code;												// 股票名称和代码
		double scr;																		// 股票评分
		stringstream ss;

		iFile >> line;
		ss << line;

		getline(ss, idx_s, ',');
		idx = stoi(idx_s);
		getline(ss, name, ',');
		getline(ss, code, ',');
		getline(ss, scr_s, ',');
		scr = stod(scr_s);

		Stock_60[idx].idx = idx;
		Stock_60[idx].BasicInfo = Search60_InAll(code);
		//cout << Stock_60[idx].BasicInfo->FullName << endl;
		Stock_60[idx].BasicInfo->Score = scr;
		Stock_60[idx].MaxFluctuation = GetMaxFlutuation(Stock_60[idx].BasicInfo);
	}
}


/// <summary>
/// 在全部的信息中找到60支股票对应的信息
/// </summary>
/// <param name="Code">60支股票代码</param>
/// <returns>股票基本信息数据域</returns>
basicinfo* Stock::Search60_InAll(string Code) {
	int key = Hash_Key(Code);										// 计算输入代码的哈希函数值

	LinkList p = H.H[key];											// 定义工作结点查找指定股票

	if (p == NULL) {
		return NULL;
	}
	else {
		p = p->next;
		while (p != NULL) {
			if (p->Data->TickerSymbol == Code && p->Data->Del_flag == 0) {// 找到目标股票且未在之前的操作中被删除,输出相关信息
				return p->Data;
			}
			p = p->next;
		}
	}
	return NULL;
}


/// <summary>
/// 遍历股票所有涨跌信息，寻找最大涨跌幅
/// </summary>
/// <param name="Info">存储某支股票信息的结构体指针类型</param>
/// <returns>指向最大涨跌幅存储空间的指针</returns>
udinfo* Stock::GetMaxFlutuation(basicinfo* Info) {
	int days = Info->UDInfo_num;
	udinfo* max=new udinfo();
	max->FluctuationRange = -1;

	for (int i = 0; i < days; i++) {															// 遍历所有涨跌信息，寻找最大涨跌幅
		if (Info->UDInfo[i].FluctuationRange > max->FluctuationRange)
			max = Info->UDInfo + i;
	}

	return max;
}


/// <summary>
/// 对数组的low到high元素进行快速排序
/// </summary>
/// <param name="low">左边界</param>
/// <param name="high">右边界</param>
/// <param name="way">排序方式</param>
void Stock::QSort(int low, int high, int way) {
	if (low < high) {
		int piv = Partition(low, high,way);													// 将表一分为二，piv是枢轴位置
		QSort(low, piv - 1,way);															// 对左子表递归排序
		QSort(piv + 1, high,way);															// 对右子表递归排序
	}
}


/// <summary>
/// 对数组low到high的一部分进行一趟排序，返回枢轴位置
/// </summary>
/// <param name="low">左边界</param>
/// <param name="high">右边界</param>
/// <param name="way">排序方式</param>
/// <returns>枢轴位置</returns>
int Stock::Partition(int low, int high,int way) {
	Stock_60[0] = Stock_60[low];														// 用数组的第一个元素做枢轴记录
	double pivkey = Stock_60[low].MaxFluctuation->FluctuationRange;						// 枢轴关键字保存
	while (low < high) {																// 从表的两端交替地向中间扫描
		while ((low < high && Stock_60[high].MaxFluctuation->FluctuationRange >= pivkey&&way==1)||
			   (low < high && Stock_60[high].MaxFluctuation->FluctuationRange <= pivkey && way == 2))
			--high;
		Stock_60[low] = Stock_60[high];													// 将比枢轴小的股票信息移动到低端

		while ((low < high && Stock_60[low].MaxFluctuation->FluctuationRange <= pivkey&&way==1)||
			   (low < high && Stock_60[low].MaxFluctuation->FluctuationRange >= pivkey && way == 2))
			++low;
		Stock_60[high] = Stock_60[low];													// 将比枢轴大的股票信息移动到高端

	}
	Stock_60[low] = Stock_60[0];
	return low;
}


/// <summary>
/// 使用Floyd进行最短路计算即股票相关性分析
/// </summary>
void Stock::Relevance_Floyd() {
	if (Read_Graph == 0) {
		CreateGraph();
		Read_Graph = 1;
	}

	/* Floyd算法 */
	for (int i = 1; i <= Some; i++)
		for (int j = 1; j <= Some; j++) {
			Compt_Graph[i][j] = Graph[i][j];
			if (Compt_Graph[i][j] < Maxn) Path[i][j] = i;								// i与j之间有弧
			else Path[i][j] = -1;
		}

	for (int k = 1; k <= Some; k++)
		for (int i = 1; i <= Some; i++)
			for (int j = 1; j <= Some; j++)
				if (Compt_Graph[i][k] + Compt_Graph[k][j] < Compt_Graph[i][j]) {
					Compt_Graph[i][j] = Compt_Graph[i][k] + Compt_Graph[k][j];
					Path[i][j] = Path[k][j];
				}
	Floyded = 1;																		// 标志已经得到完全图与最短路径
}


/// <summary>
/// 使用sort对最小生成树中的边按照权值进行排序
/// </summary>
bool cmp1(BSTedge a, BSTedge b) {
	return a.w < b.w;
}


/// <summary>
/// 使用Prim算法求出已经得到的完全图的最小生成树，存储数组按边权升序排序
/// </summary>
void Stock::Prim() {
	int k = 1;																	// 从序号为1的结点出发构造最小生成树

	for (int j = 1; j <= Some; j++)												// 初始化
		if (j != k) Prim_Closedge[j].adjvex = j, Prim_Closedge[j].lowcost = Compt_Graph[k][j];

	Prim_Closedge[k].lowcost = 0;													// 初始U={1}
	int edge = 0;																// 已经加入到最小生成树中的边数

	/* 选择其余Some-1个顶点，生成Some-1条边 */
	for (int i = 2; i <= Some; i++) {
		for (int j = 1; j <= Some; j++)											// 求出最小生成树的下一个结点，序号为k，Prim_Closedge[k]中存有当前最小边
			if (Prim_Closedge[j].lowcost != 0 && Prim_Closedge[j].lowcost < Maxn)
				k = j;

		int u0 = Prim_Closedge[k].adjvex;										// 该边上在U中的顶点
		int v0 = k;																// 另一个顶的定点为序号为k的顶点

		BSTEdge[++edge] = { u0,v0,Compt_Graph[u0][v0] };						// 该边加入到最小生成树

		Prim_Closedge[k].lowcost = 0;											// 第k个顶点并入集合
		for (int j = 1; j <= Some; j++)
			if (Compt_Graph[k][j] < Prim_Closedge[j].lowcost)					// 新顶点并入后更新最小边
				Prim_Closedge[j].adjvex = k, Prim_Closedge[j].lowcost = Compt_Graph[k][j];
	}

	sort(BSTEdge + 1, BSTEdge + edge + 1, cmp1);								// 对最小生成树的边进行排序，便于后续筛选
}


/// <summary>
/// 使用sort对Kruscal辅助数组
/// </summary>
bool cmp2(KruscalEdge a, KruscalEdge b) {
	return a.w < b.w;
}


/// <summary>
/// 使用Kruscal算法得到完全图的最小生成树，存储数组按边的权值升序排序
/// </summary>
void Stock::Kruscal() {
	/* 初始化辅助数组 */
	int arcnum = 0;																// 存储边的信息，包括边的两个顶点信息和权值
	for (int i = 1; i <= Some; i++)
		for (int j = i + 1; j <= Some; j++)
			Krus_Edge[++arcnum] = { i,j,Compt_Graph[i][j] };

	int Vexset[Some + 7];														// 标识各个顶点所属的联通分量

	sort(Krus_Edge + 1, Krus_Edge + arcnum + 1, cmp2);							// 按权值从小到大排序
	for (int i = 1; i <= Some; i++)
		Vexset[i] = i;															// 初始各顶点自成一个连通分量

	/* Kruscal算法 */
	int edge = 0;																// 记录加入最小生成树中的边
	for (int i = 1; i <= arcnum; i++) {											// 依次查看边
		int v1 = Krus_Edge[i].u;
		int v2 = Krus_Edge[i].v;
		int v1_Cpnt = Vexset[v1];
		int v2_Cpnt = Vexset[v2];                                               // 当前边关联的两个顶点所在的连通分量

		if (v1_Cpnt != v2_Cpnt) {												// 两顶点不属于同一个连通分量
			BSTEdge[++edge] = { v1,v2,Compt_Graph[v1][v2] };					// 将该边加入最小生成树
			for (int j = 1; j <= Some; j++)
				if (Vexset[j] == v2) Vexset[j] = v1;							// 合并两个连通分量
		}
	}

	/* 由于Krus_Edge数组是按权值排序的，最终加入到最小生成树中的边也是有序加入的 */
	sort(BSTEdge + 1, BSTEdge + edge + 1, cmp1);
}
		

/// <summary>
/// 对权值相等的边关联的顶点进一步筛选（基于评分）
/// </summary>
/// <param name="VNum">需要选出的点的个数</param>
/// <param name="l">左边界</param>
/// <param name="r">右边界</param>
void Stock::Choose(int VNum, int l, int r) {
	int chosen[Some] = { 0 };															// 标标记在此之前已经选中的点

	/* 去除已经被直接选中的顶点 */
	for (int i = 1; i <= l-1; i++)
		chosen[BSTEdge[i].u] = 1, chosen[BSTEdge[i].v] = 1;

	int Node[Some] = { 0 };																// 存储需要进一步筛选的点的编号
	int tmp = 0;
	for (int i = l; i <= r; i++) {
		if (chosen[BSTEdge[i].u] == 0) Node[++tmp] = BSTEdge[i].u, chosen[BSTEdge[i].u] = 1;
		if (chosen[BSTEdge[i].v] == 0) Node[++tmp] = BSTEdge[i].v, chosen[BSTEdge[i].v] = 1;
	}

	for (int i = 1; i < tmp; i++) {
		int k = i;
		for (int j = i + 1; j <= tmp; j++) {
			//cout << Node[i] << ' ' << Node[j] << endl;
			if (Stock_60[Node[j]].BasicInfo->Score > Stock_60[Node[i]].BasicInfo->Score)// 升序排序，k指向此趟评分最大的股票信息
				k = j;
			if (k != i) {
				int tmp;
				tmp = Node[i];
				Node[i] = Node[k];
				Node[k] = tmp;
			}
		}
	}																			// 对进一步筛选的点按照一定规则进行排序

	for (int i = 1; i <= VNum; i++)
		cout << Stock_60[Node[i]].BasicInfo->TickerName<<'\t'<<Stock_60[Node[i]].BasicInfo->TickerSymbol << endl;
}


