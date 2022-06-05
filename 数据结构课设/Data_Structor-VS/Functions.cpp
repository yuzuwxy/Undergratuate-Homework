/// <summary>
/// ʵ�ֹ�Ʊ���ж���ķ���Ҫ����
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
/// ���ļ��ж�ȡA�ɻ�����Ϣ����������
/// </summary>
/// <param name="ss">����ĳһ����Ϣ���ַ�����</param>
/// <param name="BasicInfo">������Ϣ����</param>
/// <param name="sum">��ǰ��Ϣ�ı��</param>
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
/// ���ļ��ж����Ʊ���ǵ���Ϣ
/// </summary>
/// <param name="iFile">�ļ���</param>
/// <param name="UDInfo">�洢�ǵ���Ϣ����</param>
/// <param name="i">������</param>
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
/// �����ϣ����ֵ
/// </summary>
/// <param name="TickerSymbol">��Ʊ��Ϣ�д洢�Ĺ�Ʊ���벿��</param>
/// <returns>���ع�ϣ����ֵ</returns>
int Stock::Hash_Key(string const& TickerSymbol) {
	int len = TickerSymbol.size();
	int sum = 0;
	for (int i = 0; i < len; i++)
		sum += TickerSymbol[i];
	return sum % MOD;																	// ����Ĺ�ϣ����Ϊ��Ʊ������ַ�ֵ֮��%97
}


/// <summary>
/// �����½��ķ�ʽ���������
/// </summary>
/// <param name="T">��ǰ�ݹ鵽�Ķ��������</param>
/// <param name="i">����������˳����е�λ��</param>
void Stock::InsertBST(BSTree &T, int i) {
	if (T == NULL) {														// �ҵ�����λ�ã��ݹ����
		BSTree S = new BSTNode();											// �����½��
		S->Data = ST.Data + i;												// �½���������Ϊ������Ĺ�Ʊ��Ϣ
		S->lchild = NULL, S->rchild = NULL;									// ���½����ΪҶ�ӽ��
		T = S;																// ���½�����ӵ��Ѿ��ҵ��Ĳ���λ��
	}
	else if (ST.Data[i].TickerSymbol < T->Data->TickerSymbol)				// ���½��S����������
		InsertBST(T->lchild, i);
	else if (ST.Data[i].TickerSymbol > T->Data->TickerSymbol)				// ���½��S����������
		InsertBST(T->rchild, i);
}


/// <summary>
/// �����������������������Զ������������в������
/// </summary>
/// <param name="T">��������ǰ���</param>
void Stock::PrintBST(BSTree T) {
	if (T == NULL) return;
	PrintBST(T->lchild);
	if (T->Data->Del_flag == 0) {														// �жϽ���Ƿ��Ѿ��ڶ�������ɾ��
		cout << T->Data->TickerSymbol << endl;
		if (T->rchild == NULL && T->lchild == NULL) cout << "NULL\n";
	}
	PrintBST(T->rchild);
}


/// <summary>
/// ��ȡ��ʮ֧��Ʊ�ļ�������Ϣ��������Ϣ+����ǵ���������ǵ���Ϣ���洢�ڽṹ��������
/// </summary>
void Stock::Read_SixtyStock() {
	if (Hashed == 0) {
		CreateHash();
		Hashed = 1;																		// ��ͨ����ϣ���ѯ����Ӧ��Ϣ
	}
	ifstream iFile;
	iFile.open("��Ʊ������Ϣ����/60֧��Ʊ��Ϣ2.csv", ios::in);								// ��������ļ����ļ���

	string line;
	iFile >> line_SixtyScr;																		// �����һ�б�ͷ

	while (!iFile.eof()) {
		int idx;																		// �ļ��еĹ�Ʊ���
		string idx_s, scr_s, name, code;												// ��Ʊ���ƺʹ���
		double scr;																		// ��Ʊ����
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
/// ��ȫ������Ϣ���ҵ�60֧��Ʊ��Ӧ����Ϣ
/// </summary>
/// <param name="Code">60֧��Ʊ����</param>
/// <returns>��Ʊ������Ϣ������</returns>
basicinfo* Stock::Search60_InAll(string Code) {
	int key = Hash_Key(Code);										// �����������Ĺ�ϣ����ֵ

	LinkList p = H.H[key];											// ���幤��������ָ����Ʊ

	if (p == NULL) {
		return NULL;
	}
	else {
		p = p->next;
		while (p != NULL) {
			if (p->Data->TickerSymbol == Code && p->Data->Del_flag == 0) {// �ҵ�Ŀ���Ʊ��δ��֮ǰ�Ĳ����б�ɾ��,��������Ϣ
				return p->Data;
			}
			p = p->next;
		}
	}
	return NULL;
}


/// <summary>
/// ������Ʊ�����ǵ���Ϣ��Ѱ������ǵ���
/// </summary>
/// <param name="Info">�洢ĳ֧��Ʊ��Ϣ�Ľṹ��ָ������</param>
/// <returns>ָ������ǵ����洢�ռ��ָ��</returns>
udinfo* Stock::GetMaxFlutuation(basicinfo* Info) {
	int days = Info->UDInfo_num;
	udinfo* max=new udinfo();
	max->FluctuationRange = -1;

	for (int i = 0; i < days; i++) {															// ���������ǵ���Ϣ��Ѱ������ǵ���
		if (Info->UDInfo[i].FluctuationRange > max->FluctuationRange)
			max = Info->UDInfo + i;
	}

	return max;
}


/// <summary>
/// �������low��highԪ�ؽ��п�������
/// </summary>
/// <param name="low">��߽�</param>
/// <param name="high">�ұ߽�</param>
/// <param name="way">����ʽ</param>
void Stock::QSort(int low, int high, int way) {
	if (low < high) {
		int piv = Partition(low, high,way);													// ����һ��Ϊ����piv������λ��
		QSort(low, piv - 1,way);															// �����ӱ�ݹ�����
		QSort(piv + 1, high,way);															// �����ӱ�ݹ�����
	}
}


/// <summary>
/// ������low��high��һ���ֽ���һ�����򣬷�������λ��
/// </summary>
/// <param name="low">��߽�</param>
/// <param name="high">�ұ߽�</param>
/// <param name="way">����ʽ</param>
/// <returns>����λ��</returns>
int Stock::Partition(int low, int high,int way) {
	Stock_60[0] = Stock_60[low];														// ������ĵ�һ��Ԫ���������¼
	double pivkey = Stock_60[low].MaxFluctuation->FluctuationRange;						// ����ؼ��ֱ���
	while (low < high) {																// �ӱ�����˽�������м�ɨ��
		while ((low < high && Stock_60[high].MaxFluctuation->FluctuationRange >= pivkey&&way==1)||
			   (low < high && Stock_60[high].MaxFluctuation->FluctuationRange <= pivkey && way == 2))
			--high;
		Stock_60[low] = Stock_60[high];													// ��������С�Ĺ�Ʊ��Ϣ�ƶ����Ͷ�

		while ((low < high && Stock_60[low].MaxFluctuation->FluctuationRange <= pivkey&&way==1)||
			   (low < high && Stock_60[low].MaxFluctuation->FluctuationRange >= pivkey && way == 2))
			++low;
		Stock_60[high] = Stock_60[low];													// ���������Ĺ�Ʊ��Ϣ�ƶ����߶�

	}
	Stock_60[low] = Stock_60[0];
	return low;
}


/// <summary>
/// ʹ��Floyd�������·���㼴��Ʊ����Է���
/// </summary>
void Stock::Relevance_Floyd() {
	if (Read_Graph == 0) {
		CreateGraph();
		Read_Graph = 1;
	}

	/* Floyd�㷨 */
	for (int i = 1; i <= Some; i++)
		for (int j = 1; j <= Some; j++) {
			Compt_Graph[i][j] = Graph[i][j];
			if (Compt_Graph[i][j] < Maxn) Path[i][j] = i;								// i��j֮���л�
			else Path[i][j] = -1;
		}

	for (int k = 1; k <= Some; k++)
		for (int i = 1; i <= Some; i++)
			for (int j = 1; j <= Some; j++)
				if (Compt_Graph[i][k] + Compt_Graph[k][j] < Compt_Graph[i][j]) {
					Compt_Graph[i][j] = Compt_Graph[i][k] + Compt_Graph[k][j];
					Path[i][j] = Path[k][j];
				}
	Floyded = 1;																		// ��־�Ѿ��õ���ȫͼ�����·��
}


/// <summary>
/// ʹ��sort����С�������еı߰���Ȩֵ��������
/// </summary>
bool cmp1(BSTedge a, BSTedge b) {
	return a.w < b.w;
}


/// <summary>
/// ʹ��Prim�㷨����Ѿ��õ�����ȫͼ����С���������洢���鰴��Ȩ��������
/// </summary>
void Stock::Prim() {
	int k = 1;																	// �����Ϊ1�Ľ�����������С������

	for (int j = 1; j <= Some; j++)												// ��ʼ��
		if (j != k) Prim_Closedge[j].adjvex = j, Prim_Closedge[j].lowcost = Compt_Graph[k][j];

	Prim_Closedge[k].lowcost = 0;													// ��ʼU={1}
	int edge = 0;																// �Ѿ����뵽��С�������еı���

	/* ѡ������Some-1�����㣬����Some-1���� */
	for (int i = 2; i <= Some; i++) {
		for (int j = 1; j <= Some; j++)											// �����С����������һ����㣬���Ϊk��Prim_Closedge[k]�д��е�ǰ��С��
			if (Prim_Closedge[j].lowcost != 0 && Prim_Closedge[j].lowcost < Maxn)
				k = j;

		int u0 = Prim_Closedge[k].adjvex;										// �ñ�����U�еĶ���
		int v0 = k;																// ��һ�����Ķ���Ϊ���Ϊk�Ķ���

		BSTEdge[++edge] = { u0,v0,Compt_Graph[u0][v0] };						// �ñ߼��뵽��С������

		Prim_Closedge[k].lowcost = 0;											// ��k�����㲢�뼯��
		for (int j = 1; j <= Some; j++)
			if (Compt_Graph[k][j] < Prim_Closedge[j].lowcost)					// �¶��㲢��������С��
				Prim_Closedge[j].adjvex = k, Prim_Closedge[j].lowcost = Compt_Graph[k][j];
	}

	sort(BSTEdge + 1, BSTEdge + edge + 1, cmp1);								// ����С�������ı߽������򣬱��ں���ɸѡ
}


/// <summary>
/// ʹ��sort��Kruscal��������
/// </summary>
bool cmp2(KruscalEdge a, KruscalEdge b) {
	return a.w < b.w;
}


/// <summary>
/// ʹ��Kruscal�㷨�õ���ȫͼ����С���������洢���鰴�ߵ�Ȩֵ��������
/// </summary>
void Stock::Kruscal() {
	/* ��ʼ���������� */
	int arcnum = 0;																// �洢�ߵ���Ϣ�������ߵ�����������Ϣ��Ȩֵ
	for (int i = 1; i <= Some; i++)
		for (int j = i + 1; j <= Some; j++)
			Krus_Edge[++arcnum] = { i,j,Compt_Graph[i][j] };

	int Vexset[Some + 7];														// ��ʶ����������������ͨ����

	sort(Krus_Edge + 1, Krus_Edge + arcnum + 1, cmp2);							// ��Ȩֵ��С��������
	for (int i = 1; i <= Some; i++)
		Vexset[i] = i;															// ��ʼ�������Գ�һ����ͨ����

	/* Kruscal�㷨 */
	int edge = 0;																// ��¼������С�������еı�
	for (int i = 1; i <= arcnum; i++) {											// ���β鿴��
		int v1 = Krus_Edge[i].u;
		int v2 = Krus_Edge[i].v;
		int v1_Cpnt = Vexset[v1];
		int v2_Cpnt = Vexset[v2];                                               // ��ǰ�߹����������������ڵ���ͨ����

		if (v1_Cpnt != v2_Cpnt) {												// �����㲻����ͬһ����ͨ����
			BSTEdge[++edge] = { v1,v2,Compt_Graph[v1][v2] };					// ���ñ߼�����С������
			for (int j = 1; j <= Some; j++)
				if (Vexset[j] == v2) Vexset[j] = v1;							// �ϲ�������ͨ����
		}
	}

	/* ����Krus_Edge�����ǰ�Ȩֵ����ģ����ռ��뵽��С�������еı�Ҳ���������� */
	sort(BSTEdge + 1, BSTEdge + edge + 1, cmp1);
}
		

/// <summary>
/// ��Ȩֵ��ȵı߹����Ķ����һ��ɸѡ���������֣�
/// </summary>
/// <param name="VNum">��Ҫѡ���ĵ�ĸ���</param>
/// <param name="l">��߽�</param>
/// <param name="r">�ұ߽�</param>
void Stock::Choose(int VNum, int l, int r) {
	int chosen[Some] = { 0 };															// �����ڴ�֮ǰ�Ѿ�ѡ�еĵ�

	/* ȥ���Ѿ���ֱ��ѡ�еĶ��� */
	for (int i = 1; i <= l-1; i++)
		chosen[BSTEdge[i].u] = 1, chosen[BSTEdge[i].v] = 1;

	int Node[Some] = { 0 };																// �洢��Ҫ��һ��ɸѡ�ĵ�ı��
	int tmp = 0;
	for (int i = l; i <= r; i++) {
		if (chosen[BSTEdge[i].u] == 0) Node[++tmp] = BSTEdge[i].u, chosen[BSTEdge[i].u] = 1;
		if (chosen[BSTEdge[i].v] == 0) Node[++tmp] = BSTEdge[i].v, chosen[BSTEdge[i].v] = 1;
	}

	for (int i = 1; i < tmp; i++) {
		int k = i;
		for (int j = i + 1; j <= tmp; j++) {
			//cout << Node[i] << ' ' << Node[j] << endl;
			if (Stock_60[Node[j]].BasicInfo->Score > Stock_60[Node[i]].BasicInfo->Score)// ��������kָ������������Ĺ�Ʊ��Ϣ
				k = j;
			if (k != i) {
				int tmp;
				tmp = Node[i];
				Node[i] = Node[k];
				Node[k] = tmp;
			}
		}
	}																			// �Խ�һ��ɸѡ�ĵ㰴��һ�������������

	for (int i = 1; i <= VNum; i++)
		cout << Stock_60[Node[i]].BasicInfo->TickerName<<'\t'<<Stock_60[Node[i]].BasicInfo->TickerSymbol << endl;
}


