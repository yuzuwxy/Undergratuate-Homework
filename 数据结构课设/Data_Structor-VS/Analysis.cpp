/// <summary>
/// 实现分析功能
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
/// 对某天所有股票根据不同关键字直接插入排序，可选关键字为开盘价、收盘价、涨跌幅，可选升降序
/// </summary>
void Stock::InsertionSort() {
	string Date;
	cout << "请输入日期: ";
	cin >> Date;

	map<string, DateLink>::iterator it = L.find(Date);
	if (it != L.end()) {
		int mark1;
		cout << "您选择的排序关键字：1.开盘价；2.收盘价；3.涨跌幅。";
		cin >> mark1;

		int mark2;
		cout << "您希望选择：1.升序；2.降序。";
		cin >> mark2;

		DateLink p = L[Date]->next;
		DateLink p_pre = L[Date];
		while (p != NULL) {
			DateLink q = L[Date]->next, pre = L[Date];
			int flag = 0;
			while (q != p) {													// 将当前结点插入到已经排好序的序列中
				if ((q->UDInfo->OpenPrice < p->UDInfo->OpenPrice&&mark1==1&&mark2==2)||(q->UDInfo->OpenPrice > p->UDInfo->OpenPrice &&mark1==1 && mark2 == 1)||
					(q->UDInfo->ClosingPrice < p->UDInfo->ClosingPrice && mark1 == 2 && mark2 == 2) || (q->UDInfo->ClosingPrice > p->UDInfo->ClosingPrice && mark1 == 2 && mark2 == 1)|| 
					(q->UDInfo->FluctuationRange < p->UDInfo->FluctuationRange&& mark1 == 3 && mark2 == 2) || (q->UDInfo->FluctuationRange > p->UDInfo->FluctuationRange && mark1 == 3 && mark2 == 1)){
					flag = 1;
					DateLink s = p;
					p = p->next;
					p_pre->next = p;
					s->next = q;
					pre->next = s;
					break;
				}
				q = q->next;
				pre = pre->next;
			}
			if (flag == 0) p = p->next, p_pre = p_pre->next;
		}
		p = L[Date]->next;
		while (p != NULL) {
			cout <<p->BasicInfo->index<<'\t'<< p->BasicInfo->TickerSymbol<<'\t'<<p->BasicInfo->TickerName << '\t' << p->UDInfo->OpenPrice<<'\t' <<p->UDInfo->ClosingPrice<<'\t'<<fixed<<setprecision(2)<< p->UDInfo->FluctuationRange<<'%'<< endl;
			p = p->next;
		}
		return;
	}

	cout << "未找到该日期的相关股票信息！\n";
}


/// <summary>
/// 基于快速排序的股票价格分析（针对60支股票信息），输入一级行业名称，按照涨跌幅对股票信息排序输出
/// </summary>
void Stock::QuickSort_Sixty() {
	if (Sixty_Read == 0) {																	// 六十支股票信息还未被读入
		Read_SixtyStock();																	// 读入信息
		Sixty_Read = 1;																		// 标志置为1
	}

	string Industry_1;
	cout << "请您输入您所关注的一级行业: ";
	cin >> Industry_1;

	/* 对读入的六十支股票信息测试输出 */
	/*for (int i = 1; i <= 60; i++)
		cout << Stock_60[i].BasicInfo->TickerSymbol << '\t' << Stock_60[i].BasicInfo->TickerName << '\t' << Stock_60[i].MaxFluctuation->FluctuationRange<<'%' << '\t' << Stock_60[i].MaxFluctuation->Date << endl;*/


	/* 对60支股票信息基于最大涨跌幅进行快速排序 */
	int way;
	cout << "请选择排序方式: 1.升序；2.降序.";
	cin >> way;
	QSort(1, 60,way);																			// 待排序的数组长度为60

	/* 输出查询的行业的股票信息 */
	for (int i = 1; i <= 60; i++) 
		if(Stock_60[i].BasicInfo->PriClass==Industry_1&&Stock_60[i].BasicInfo->Del_flag==0)
			cout << Stock_60[i].idx << '\t' << Stock_60[i].BasicInfo->TickerSymbol << '\t' << Stock_60[i].BasicInfo->TickerName << '\t' << Stock_60[i].MaxFluctuation->FluctuationRange << '%' << '\t' << Stock_60[i].MaxFluctuation->Date << endl;
	
}

/// <summary>
/// 依据股票评分对60支股票信息进行简单选择排序，并输出到excel文件中
/// </summary>
void Stock::SelectionSort_By_Scr() {
	if (Sixty_Read == 0) {																// 六十支股票信息是否已读入																// 六十支股票信息还未被读入
		Read_SixtyStock();																// 读入信息
		Sixty_Read = 1;																	// 标志置为1
	}

	int way = 0;
	cout << "请选择排序方式: 1.升序；2.降序.";
	cin >> way;

	/* 按照指定的排序方式对60支股票信息进行排序 */
	for (int i = 1; i < 60; i++) {
		int k = i;
		for (int j = i + 1; j <= 60; j++) {
			if ((Stock_60[j].BasicInfo->Score < Stock_60[k].BasicInfo->Score && way == 1) ||	// 升序排序，k指向此趟评分最小的股票信息
				(Stock_60[j].BasicInfo->Score > Stock_60[k].BasicInfo->Score && way == 2))		// 降序排序，k指向此趟评分最大的股票信息
				k = j;
			if (k != i) {
				SixtyStock tmp;
				tmp = Stock_60[i];
				Stock_60[i] = Stock_60[k];
				Stock_60[k] = tmp;
			}
		}
	}

	/* 输出排序后的股票信息 */
	for(int i=1;i<=60;i++) 
		if(Stock_60[i].BasicInfo->Del_flag==0)
			cout << Stock_60[i].idx << '\t' << Stock_60[i].BasicInfo->TickerSymbol << '\t' << Stock_60[i].BasicInfo->TickerName << '\t' <<fixed<<setprecision(1)<< Stock_60[i].BasicInfo->Score << endl;
}

/// <summary>
/// 依据收盘价对60支股票信息进行简单选择排序，并输出到excel文件中
/// </summary>
void Stock::SelectionSort_By_CloPrice() {
	if (Sixty_Read == 0) {																// 六十支股票信息是否已读入																// 六十支股票信息还未被读入
		Read_SixtyStock();																// 读入信息
		Sixty_Read = 1;																	// 标志置为1
	}

	int way = 0;
	cout << "请选择排序方式: 1.升序；2.降序.";
	cin >> way;

	/* 按照指定的排序方式对60支股票信息进行排序 */
	for (int i = 1; i < 60; i++) {
		int k = i;
		for (int j = i + 1; j <= 60; j++) {
			if ((Stock_60[j].BasicInfo->UDInfo[0].ClosingPrice < Stock_60[k].BasicInfo->UDInfo[0].ClosingPrice && way == 1) ||	// 升序排序，k指向此趟评分最小的股票信息
				(Stock_60[j].BasicInfo->UDInfo[0].ClosingPrice > Stock_60[k].BasicInfo->UDInfo[0].ClosingPrice && way == 2))	// 降序排序，k指向此趟评分最大的股票信息
				k = j;
			if (k != i) {
				SixtyStock tmp;
				tmp = Stock_60[i];
				Stock_60[i] = Stock_60[k];
				Stock_60[k] = tmp;
			}
		}
	}

	/* 输出排序后的股票信息 */
	for (int i = 1; i <= 60; i++)
		if (Stock_60[i].BasicInfo->Del_flag == 0)
			cout << Stock_60[i].idx << '\t' << Stock_60[i].BasicInfo->TickerSymbol << '\t' << Stock_60[i].BasicInfo->TickerName << '\t' <<fixed<<setprecision(2)<< Stock_60[i].BasicInfo->UDInfo[0].ClosingPrice << endl;
}


/// <summary>
/// 基于Floyd的股票相关性计算，输出任意两点间的最短路径
/// </summary>
void Stock::ShortestPath_By_Floyd() {
	if (Floyded == 0) {
		Relevance_Floyd();																// 首先使用弗洛伊德算法得到最短路径
		Floyded = 1;
	}

	/* 输出Floyd算法得到的最短路径 */
	for (int i = 1; i <= Some; i++) {
		for (int j = i + 1; j <= Some; j++) {
			if (!Stock_60[i].BasicInfo->Del_flag && !Stock_60[j].BasicInfo->Del_flag) {	// 股票信息未在其他的操作中被删除
				cout << i << ':' << Stock_60[i].BasicInfo->TickerName << "<->" << j << ':' << Stock_60[j].BasicInfo->TickerName << endl;
				cout << "最短路径长度为: " << Compt_Graph[i][j] << endl;
				cout << Stock_60[j].BasicInfo->TickerName;
				int k = Path[i][j];
				while (k != i) {
					cout << "<->" << Stock_60[k].BasicInfo->TickerName;
					k = Path[i][k];
				}
				cout << "<->" << Stock_60[k].BasicInfo->TickerName << endl;
			}
		}
	}
}


/// <summary>
/// 基于两种最小生成树算法（可选）的股票基金筛选
/// </summary>
void Stock::Selection_By_BST() {
	if (Floyded == 0) {
		Relevance_Floyd();																// 先建立完全图
		Floyded = 1;
	}

	int way;
	cout << "请输入您选择的筛选算法:1.Prim算法;2.Kruscal算法.";
	cin >> way;

	/* 根据选择的算法求最小生成树 */
	if (way == 1) Prim();																// 使用Prim算法得到最小生成树（存储边）
	else Kruscal();																		// 使用Kruscal算法得到最小生成树（存储边）

	/* 预处理最小生成树的每条边对筛选出6个结点的贡献 */
	int choosen[Some + 7] = { 0 };														// choosen[i]==1表示编号为i的点已经被选择
	int edgesum[Some + 7] = { 0 };														// edgesum[i]记录截至第i条边可以选出的顶点数
	for (int i = 1; i <= Some - 1; i++) {												// 最小生成树Some个顶点一定有Some-1条边
		int edgeval = 0;
		if (choosen[BSTEdge[i].u] == 0) edgeval++, choosen[BSTEdge[i].u] = 1;
		if (choosen[BSTEdge[i].v] == 0) edgeval++, choosen[BSTEdge[i].v] = 1;
		edgesum[i] = edgesum[i - 1] + edgeval;
	}

	/* 预处理每条边与之权值相同的最前和最后的边在数组中存储的序号 */
	int pre[Some + 7] = { 0 };															// 每条边与之相同权值的边最先出现的位置
	int flw[Some + 7] = { 0 };															// 每条边与之相同权值的边最后出现的位置

	for (int i = 1; i <= Some - 1; i++)
		if (BSTEdge[i].w == BSTEdge[i - 1].w)											// 如果该边与上一条边相等，则前驱相同
			pre[i] = pre[i - 1];
		else pre[i] = i;

	for (int i = Some - 1; i >= 1; i--)
		if (BSTEdge[i].w == BSTEdge[i + 1].w)											// 如果该边与下一条边相等，则后继相同
			flw[i] = flw[i + 1];
		else
			flw[i] = i;

	/* 进行股票筛选 */
	int i;
	for (i = 1; i <= Some - 1; i++) {
		if (edgesum[i] == ChooseNode && flw[i] == i) break;								// 不需要进行额外筛选的情况
		else if (edgesum[i] > ChooseNode || (edgesum[i] == ChooseNode && flw[i] != i))												// 无法恰好筛出个指定个数顶点 || 可以刚好选中指定个数的点但是后续还有其他权值相同的边
			break;
	}

	/* 输出可以直接选中的前i条边关联的顶点对应的股票信息 与 对无法直接选中的顶点进行额外的筛选 */
	int k = i;
	i = pre[i] - 1;																// 截止到第i条边关联的顶点可以直接被选中
	memset(choosen, 0, sizeof(choosen));										// 标记该股票信息是否已输出过
	cout << "筛选出的 " << ChooseNode << " 支股票分别为: \n";
	for (int j = 1; j <= i; j++) {
		if (choosen[BSTEdge[i].u] == 0) {
			cout << Stock_60[BSTEdge[i].u].BasicInfo->TickerName << '\t' << Stock_60[BSTEdge[i].u].BasicInfo->TickerSymbol<<endl;
			choosen[BSTEdge[i].u] = 1;
		}
		if (choosen[BSTEdge[i].v] == 0) {
			cout << Stock_60[BSTEdge[i].v].BasicInfo->TickerName << '\t' << Stock_60[BSTEdge[i].v].BasicInfo->TickerSymbol << endl;
			choosen[BSTEdge[i].v] = 1;
		}
	}

	Choose(ChooseNode - edgesum[pre[k]-1], pre[k], flw[k]);					// ChooseNode - edgesum[pre[k]-1]为需要筛选出的点的个数，pre[i]和flw[i]是选择的范围
}


/// <summary>
/// 基于二部图的股票基金筛选:输入结点判断是否连通再判断是否为二部图，并输出二部图的两组结点
/// </summary>
void Stock::Selection_By_BGraph() {
	if (Read_Graph == 0) {
		CreateGraph();
		Read_Graph = 1;
	}

	/*输入要进行判断的结点 */
	cout << "请输入进行分析的股票序号（以空格为间隔）[1-60]: \n";
	for (int i = 1; i <= BNode; i++)
		cin >> BiGraph.vex[i];

	/* 基于并查集判断子图是否连通 */
	int Vexset[BNode + 7] = { 0 };											// Vexset[i]==Vexset[j]表示序号为i与序号为j的顶点连通

	for (int i = 1; i <= BNode; i++)
		Vexset[i] = i;														// 进行初始化

	
	Graph[30][21] = Graph[21][30] = Maxn;
	Graph[33][23] = Graph[23][33] = 1;
	for (int i = 1; i <= BNode; i++) {
		int u = BiGraph.vex[i];
		for (int j = 1; j <= BNode; j++) {
			int v = BiGraph.vex[j];
			if (Graph[u][v] != Maxn) {										// 两顶点在原图中连通
				BiGraph.arcs[i][j] = Graph[u][v];
				BiGraph.arcs[j][i] = Graph[u][v];
			}
		}
	}

	for (int i = 1; i <= BNode; i++)										// 将联通的点合并
		for (int j = 1; j <= BNode; j++) {
			if (BiGraph.arcs[i][j] && Vexset[i] != Vexset[j])					
				Vexset[j] = i;
			for (int k = 1; k <= BNode; k++)
				if (Vexset[k] == j) Vexset[k] = i;
		}


	int a = 0;																// 统计联通块个数，如果>=2，则子图不是连通图
	int visited[BNode + 3] = { 0 };
	for (int i = 1; i <= BNode; i++) {
		if (visited[Vexset[i]] == 0) {
			a++;
			visited[Vexset[i]] = 1;
		}
	}

	if (a >= 2) {
		cout << "您选择的顶点无法构成连通图！\n";
		return;
	}


	/* 当子图联通时，判断是否可以构成二部图 */
	int Color[BNode + 3];													// 每个点的颜色，-1表示未染色，1表示白色，0表示黑色
	memset(Color, -1, sizeof(Color));										// 初始化为-1即全部未染色
	bool flag = true;
	for (int i = 1; i <= BNode; i++)
		if (Color[i] == -1)
			if (!BGraph_DFS(i, 0, Color)) {
				flag = false;
				break;
			}

	/* 结果输出 */
	if (flag == false) cout << "您选择的顶点无法构成二部图！\n";
	else {
		cout << "二部图的第一组结点: \n";
		for (int i = 1; i <= BNode; i++)
			if (Color[i] == 0)												// Color的数组的两个值表示二部图的两个部分
				cout << BiGraph.vex[i] << '\t' << Stock_60[BiGraph.vex[i]].BasicInfo->TickerName << endl;

		cout << endl;

		cout << "二部图的第二组结点: \n";
		for (int i = 1; i <= BNode; i++)
			if (Color[i] == 1)												// Color的数组的两个值表示二部图的两个部分
				cout << BiGraph.vex[i] << '\t' << Stock_60[BiGraph.vex[i]].BasicInfo->TickerName << endl;
	}
}

/// <summary>
/// 基于深度优先搜索染色法判断连通图是否为二部图
/// </summary>
/// <param name="u">当前搜索的顶点</param>
/// <param name="col">当前结点涂色</param>
/// <param name="Color">颜色数组</param>
/// <returns>返回布尔类型，true表示是二部图，false表示不是</returns>
bool Stock::BGraph_DFS(int u, int col, int Color[]) {
	Color[u] = col;
	for (int i = 1; i <= BNode; i++) {												// 遍历u邻接的顶点对其染色
		if (BiGraph.arcs[u][i] == 0) continue;
		if (Color[i] == -1 && i != u) { 											// 如果该顶点未染色
			if (!BGraph_DFS(i, !col, Color))
				return false;
		}
		else if (Color[i] == col)
			return false;
	}
	return true;
}