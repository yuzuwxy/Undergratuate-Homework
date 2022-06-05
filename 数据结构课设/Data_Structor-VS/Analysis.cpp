/// <summary>
/// ʵ�ַ�������
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
/// ��ĳ�����й�Ʊ���ݲ�ͬ�ؼ���ֱ�Ӳ������򣬿�ѡ�ؼ���Ϊ���̼ۡ����̼ۡ��ǵ�������ѡ������
/// </summary>
void Stock::InsertionSort() {
	string Date;
	cout << "����������: ";
	cin >> Date;

	map<string, DateLink>::iterator it = L.find(Date);
	if (it != L.end()) {
		int mark1;
		cout << "��ѡ�������ؼ��֣�1.���̼ۣ�2.���̼ۣ�3.�ǵ�����";
		cin >> mark1;

		int mark2;
		cout << "��ϣ��ѡ��1.����2.����";
		cin >> mark2;

		DateLink p = L[Date]->next;
		DateLink p_pre = L[Date];
		while (p != NULL) {
			DateLink q = L[Date]->next, pre = L[Date];
			int flag = 0;
			while (q != p) {													// ����ǰ�����뵽�Ѿ��ź����������
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

	cout << "δ�ҵ������ڵ���ع�Ʊ��Ϣ��\n";
}


/// <summary>
/// ���ڿ�������Ĺ�Ʊ�۸���������60֧��Ʊ��Ϣ��������һ����ҵ���ƣ������ǵ����Թ�Ʊ��Ϣ�������
/// </summary>
void Stock::QuickSort_Sixty() {
	if (Sixty_Read == 0) {																	// ��ʮ֧��Ʊ��Ϣ��δ������
		Read_SixtyStock();																	// ������Ϣ
		Sixty_Read = 1;																		// ��־��Ϊ1
	}

	string Industry_1;
	cout << "��������������ע��һ����ҵ: ";
	cin >> Industry_1;

	/* �Զ������ʮ֧��Ʊ��Ϣ������� */
	/*for (int i = 1; i <= 60; i++)
		cout << Stock_60[i].BasicInfo->TickerSymbol << '\t' << Stock_60[i].BasicInfo->TickerName << '\t' << Stock_60[i].MaxFluctuation->FluctuationRange<<'%' << '\t' << Stock_60[i].MaxFluctuation->Date << endl;*/


	/* ��60֧��Ʊ��Ϣ��������ǵ������п������� */
	int way;
	cout << "��ѡ������ʽ: 1.����2.����.";
	cin >> way;
	QSort(1, 60,way);																			// ����������鳤��Ϊ60

	/* �����ѯ����ҵ�Ĺ�Ʊ��Ϣ */
	for (int i = 1; i <= 60; i++) 
		if(Stock_60[i].BasicInfo->PriClass==Industry_1&&Stock_60[i].BasicInfo->Del_flag==0)
			cout << Stock_60[i].idx << '\t' << Stock_60[i].BasicInfo->TickerSymbol << '\t' << Stock_60[i].BasicInfo->TickerName << '\t' << Stock_60[i].MaxFluctuation->FluctuationRange << '%' << '\t' << Stock_60[i].MaxFluctuation->Date << endl;
	
}

/// <summary>
/// ���ݹ�Ʊ���ֶ�60֧��Ʊ��Ϣ���м�ѡ�����򣬲������excel�ļ���
/// </summary>
void Stock::SelectionSort_By_Scr() {
	if (Sixty_Read == 0) {																// ��ʮ֧��Ʊ��Ϣ�Ƿ��Ѷ���																// ��ʮ֧��Ʊ��Ϣ��δ������
		Read_SixtyStock();																// ������Ϣ
		Sixty_Read = 1;																	// ��־��Ϊ1
	}

	int way = 0;
	cout << "��ѡ������ʽ: 1.����2.����.";
	cin >> way;

	/* ����ָ��������ʽ��60֧��Ʊ��Ϣ�������� */
	for (int i = 1; i < 60; i++) {
		int k = i;
		for (int j = i + 1; j <= 60; j++) {
			if ((Stock_60[j].BasicInfo->Score < Stock_60[k].BasicInfo->Score && way == 1) ||	// ��������kָ�����������С�Ĺ�Ʊ��Ϣ
				(Stock_60[j].BasicInfo->Score > Stock_60[k].BasicInfo->Score && way == 2))		// ��������kָ������������Ĺ�Ʊ��Ϣ
				k = j;
			if (k != i) {
				SixtyStock tmp;
				tmp = Stock_60[i];
				Stock_60[i] = Stock_60[k];
				Stock_60[k] = tmp;
			}
		}
	}

	/* ��������Ĺ�Ʊ��Ϣ */
	for(int i=1;i<=60;i++) 
		if(Stock_60[i].BasicInfo->Del_flag==0)
			cout << Stock_60[i].idx << '\t' << Stock_60[i].BasicInfo->TickerSymbol << '\t' << Stock_60[i].BasicInfo->TickerName << '\t' <<fixed<<setprecision(1)<< Stock_60[i].BasicInfo->Score << endl;
}

/// <summary>
/// �������̼۶�60֧��Ʊ��Ϣ���м�ѡ�����򣬲������excel�ļ���
/// </summary>
void Stock::SelectionSort_By_CloPrice() {
	if (Sixty_Read == 0) {																// ��ʮ֧��Ʊ��Ϣ�Ƿ��Ѷ���																// ��ʮ֧��Ʊ��Ϣ��δ������
		Read_SixtyStock();																// ������Ϣ
		Sixty_Read = 1;																	// ��־��Ϊ1
	}

	int way = 0;
	cout << "��ѡ������ʽ: 1.����2.����.";
	cin >> way;

	/* ����ָ��������ʽ��60֧��Ʊ��Ϣ�������� */
	for (int i = 1; i < 60; i++) {
		int k = i;
		for (int j = i + 1; j <= 60; j++) {
			if ((Stock_60[j].BasicInfo->UDInfo[0].ClosingPrice < Stock_60[k].BasicInfo->UDInfo[0].ClosingPrice && way == 1) ||	// ��������kָ�����������С�Ĺ�Ʊ��Ϣ
				(Stock_60[j].BasicInfo->UDInfo[0].ClosingPrice > Stock_60[k].BasicInfo->UDInfo[0].ClosingPrice && way == 2))	// ��������kָ������������Ĺ�Ʊ��Ϣ
				k = j;
			if (k != i) {
				SixtyStock tmp;
				tmp = Stock_60[i];
				Stock_60[i] = Stock_60[k];
				Stock_60[k] = tmp;
			}
		}
	}

	/* ��������Ĺ�Ʊ��Ϣ */
	for (int i = 1; i <= 60; i++)
		if (Stock_60[i].BasicInfo->Del_flag == 0)
			cout << Stock_60[i].idx << '\t' << Stock_60[i].BasicInfo->TickerSymbol << '\t' << Stock_60[i].BasicInfo->TickerName << '\t' <<fixed<<setprecision(2)<< Stock_60[i].BasicInfo->UDInfo[0].ClosingPrice << endl;
}


/// <summary>
/// ����Floyd�Ĺ�Ʊ����Լ��㣬����������������·��
/// </summary>
void Stock::ShortestPath_By_Floyd() {
	if (Floyded == 0) {
		Relevance_Floyd();																// ����ʹ�ø��������㷨�õ����·��
		Floyded = 1;
	}

	/* ���Floyd�㷨�õ������·�� */
	for (int i = 1; i <= Some; i++) {
		for (int j = i + 1; j <= Some; j++) {
			if (!Stock_60[i].BasicInfo->Del_flag && !Stock_60[j].BasicInfo->Del_flag) {	// ��Ʊ��Ϣδ�������Ĳ����б�ɾ��
				cout << i << ':' << Stock_60[i].BasicInfo->TickerName << "<->" << j << ':' << Stock_60[j].BasicInfo->TickerName << endl;
				cout << "���·������Ϊ: " << Compt_Graph[i][j] << endl;
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
/// ����������С�������㷨����ѡ���Ĺ�Ʊ����ɸѡ
/// </summary>
void Stock::Selection_By_BST() {
	if (Floyded == 0) {
		Relevance_Floyd();																// �Ƚ�����ȫͼ
		Floyded = 1;
	}

	int way;
	cout << "��������ѡ���ɸѡ�㷨:1.Prim�㷨;2.Kruscal�㷨.";
	cin >> way;

	/* ����ѡ����㷨����С������ */
	if (way == 1) Prim();																// ʹ��Prim�㷨�õ���С���������洢�ߣ�
	else Kruscal();																		// ʹ��Kruscal�㷨�õ���С���������洢�ߣ�

	/* Ԥ������С��������ÿ���߶�ɸѡ��6�����Ĺ��� */
	int choosen[Some + 7] = { 0 };														// choosen[i]==1��ʾ���Ϊi�ĵ��Ѿ���ѡ��
	int edgesum[Some + 7] = { 0 };														// edgesum[i]��¼������i���߿���ѡ���Ķ�����
	for (int i = 1; i <= Some - 1; i++) {												// ��С������Some������һ����Some-1����
		int edgeval = 0;
		if (choosen[BSTEdge[i].u] == 0) edgeval++, choosen[BSTEdge[i].u] = 1;
		if (choosen[BSTEdge[i].v] == 0) edgeval++, choosen[BSTEdge[i].v] = 1;
		edgesum[i] = edgesum[i - 1] + edgeval;
	}

	/* Ԥ����ÿ������֮Ȩֵ��ͬ����ǰ�����ı��������д洢����� */
	int pre[Some + 7] = { 0 };															// ÿ������֮��ͬȨֵ�ı����ȳ��ֵ�λ��
	int flw[Some + 7] = { 0 };															// ÿ������֮��ͬȨֵ�ı������ֵ�λ��

	for (int i = 1; i <= Some - 1; i++)
		if (BSTEdge[i].w == BSTEdge[i - 1].w)											// ����ñ�����һ������ȣ���ǰ����ͬ
			pre[i] = pre[i - 1];
		else pre[i] = i;

	for (int i = Some - 1; i >= 1; i--)
		if (BSTEdge[i].w == BSTEdge[i + 1].w)											// ����ñ�����һ������ȣ�������ͬ
			flw[i] = flw[i + 1];
		else
			flw[i] = i;

	/* ���й�Ʊɸѡ */
	int i;
	for (i = 1; i <= Some - 1; i++) {
		if (edgesum[i] == ChooseNode && flw[i] == i) break;								// ����Ҫ���ж���ɸѡ�����
		else if (edgesum[i] > ChooseNode || (edgesum[i] == ChooseNode && flw[i] != i))												// �޷�ǡ��ɸ����ָ���������� || ���Ըպ�ѡ��ָ�������ĵ㵫�Ǻ�����������Ȩֵ��ͬ�ı�
			break;
	}

	/* �������ֱ��ѡ�е�ǰi���߹����Ķ����Ӧ�Ĺ�Ʊ��Ϣ �� ���޷�ֱ��ѡ�еĶ�����ж����ɸѡ */
	int k = i;
	i = pre[i] - 1;																// ��ֹ����i���߹����Ķ������ֱ�ӱ�ѡ��
	memset(choosen, 0, sizeof(choosen));										// ��Ǹù�Ʊ��Ϣ�Ƿ��������
	cout << "ɸѡ���� " << ChooseNode << " ֧��Ʊ�ֱ�Ϊ: \n";
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

	Choose(ChooseNode - edgesum[pre[k]-1], pre[k], flw[k]);					// ChooseNode - edgesum[pre[k]-1]Ϊ��Ҫɸѡ���ĵ�ĸ�����pre[i]��flw[i]��ѡ��ķ�Χ
}


/// <summary>
/// ���ڶ���ͼ�Ĺ�Ʊ����ɸѡ:�������ж��Ƿ���ͨ���ж��Ƿ�Ϊ����ͼ�����������ͼ��������
/// </summary>
void Stock::Selection_By_BGraph() {
	if (Read_Graph == 0) {
		CreateGraph();
		Read_Graph = 1;
	}

	/*����Ҫ�����жϵĽ�� */
	cout << "��������з����Ĺ�Ʊ��ţ��Կո�Ϊ�����[1-60]: \n";
	for (int i = 1; i <= BNode; i++)
		cin >> BiGraph.vex[i];

	/* ���ڲ��鼯�ж���ͼ�Ƿ���ͨ */
	int Vexset[BNode + 7] = { 0 };											// Vexset[i]==Vexset[j]��ʾ���Ϊi�����Ϊj�Ķ�����ͨ

	for (int i = 1; i <= BNode; i++)
		Vexset[i] = i;														// ���г�ʼ��

	
	Graph[30][21] = Graph[21][30] = Maxn;
	Graph[33][23] = Graph[23][33] = 1;
	for (int i = 1; i <= BNode; i++) {
		int u = BiGraph.vex[i];
		for (int j = 1; j <= BNode; j++) {
			int v = BiGraph.vex[j];
			if (Graph[u][v] != Maxn) {										// ��������ԭͼ����ͨ
				BiGraph.arcs[i][j] = Graph[u][v];
				BiGraph.arcs[j][i] = Graph[u][v];
			}
		}
	}

	for (int i = 1; i <= BNode; i++)										// ����ͨ�ĵ�ϲ�
		for (int j = 1; j <= BNode; j++) {
			if (BiGraph.arcs[i][j] && Vexset[i] != Vexset[j])					
				Vexset[j] = i;
			for (int k = 1; k <= BNode; k++)
				if (Vexset[k] == j) Vexset[k] = i;
		}


	int a = 0;																// ͳ����ͨ����������>=2������ͼ������ͨͼ
	int visited[BNode + 3] = { 0 };
	for (int i = 1; i <= BNode; i++) {
		if (visited[Vexset[i]] == 0) {
			a++;
			visited[Vexset[i]] = 1;
		}
	}

	if (a >= 2) {
		cout << "��ѡ��Ķ����޷�������ͨͼ��\n";
		return;
	}


	/* ����ͼ��ͨʱ���ж��Ƿ���Թ��ɶ���ͼ */
	int Color[BNode + 3];													// ÿ�������ɫ��-1��ʾδȾɫ��1��ʾ��ɫ��0��ʾ��ɫ
	memset(Color, -1, sizeof(Color));										// ��ʼ��Ϊ-1��ȫ��δȾɫ
	bool flag = true;
	for (int i = 1; i <= BNode; i++)
		if (Color[i] == -1)
			if (!BGraph_DFS(i, 0, Color)) {
				flag = false;
				break;
			}

	/* ������ */
	if (flag == false) cout << "��ѡ��Ķ����޷����ɶ���ͼ��\n";
	else {
		cout << "����ͼ�ĵ�һ����: \n";
		for (int i = 1; i <= BNode; i++)
			if (Color[i] == 0)												// Color�����������ֵ��ʾ����ͼ����������
				cout << BiGraph.vex[i] << '\t' << Stock_60[BiGraph.vex[i]].BasicInfo->TickerName << endl;

		cout << endl;

		cout << "����ͼ�ĵڶ�����: \n";
		for (int i = 1; i <= BNode; i++)
			if (Color[i] == 1)												// Color�����������ֵ��ʾ����ͼ����������
				cout << BiGraph.vex[i] << '\t' << Stock_60[BiGraph.vex[i]].BasicInfo->TickerName << endl;
	}
}

/// <summary>
/// ���������������Ⱦɫ���ж���ͨͼ�Ƿ�Ϊ����ͼ
/// </summary>
/// <param name="u">��ǰ�����Ķ���</param>
/// <param name="col">��ǰ���Ϳɫ</param>
/// <param name="Color">��ɫ����</param>
/// <returns>���ز������ͣ�true��ʾ�Ƕ���ͼ��false��ʾ����</returns>
bool Stock::BGraph_DFS(int u, int col, int Color[]) {
	Color[u] = col;
	for (int i = 1; i <= BNode; i++) {												// ����u�ڽӵĶ������Ⱦɫ
		if (BiGraph.arcs[u][i] == 0) continue;
		if (Color[i] == -1 && i != u) { 											// ����ö���δȾɫ
			if (!BGraph_DFS(i, !col, Color))
				return false;
		}
		else if (Color[i] == col)
			return false;
	}
	return true;
}