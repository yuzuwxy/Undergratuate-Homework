/// <summary>
/// 实现查询功能
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
/// 基于哈希表的股票基本信息查询，输入股票代码输出名称、代码、一级行业、二级行业、主营业务，并计算ASL
/// </summary>
void Stock::Search_By_Hash() {
	if (Hashed == 0) {
		CreateHash();
		Hashed = 1;
	}

	string Code;
	cout << "请输入股票代码查询股票信息: ";
	cin >> Code;													// 根据输入的股票代码查询股票信息

	int key = Hash_Key(Code);										// 计算输入代码的哈希函数值

	LinkList p = H.H[key];											// 定义工作结点查找指定股票
	int asl = 0;													// 用于计算查找成功的ASL值

	if (p == NULL) {
		cout << "查找失败！未收录该条股票信息！\n";
	}
	else {
		p = p->next;
		while (p != NULL) {
			asl++;
			if (p->Data->TickerSymbol == Code && p->Data->Del_flag==0) {// 找到目标股票且未在之前的操作中被删除,输出相关信息
				cout << "股票名称:" << p->Data->TickerName << endl;
				cout << "股票代码:" << p->Data->TickerSymbol << endl;
				cout << "所属一级行业:" << p->Data->PriClass << endl;
				cout << "所属二级行业:" << p->Data->SecClass << endl;
				cout << "主营业务:" << p->Data->MainBusiness << endl;
				cout << "查找成功的ASL值为:" << GetASL_Hash() << endl;
				return;
			}
			p = p->next;
		}
	}
	cout << "查找失败！未收录该条股票信息!\n";
}


/// <summary>
/// 基于KMP的股票网址查询，输入网址字符串子串，查询所有股票的“网址”字段
/// </summary>
void Stock::Search_By_KMP() {
	cout << "请输入查询股票网址字符串的子串: ";
	string t;																	// 模式串t
	cin >> t;
	
	int k, infonum = 0;
	for (k = 0; k < ST.length; k++) {
		if (ST.Data[k].Del_flag == 1) continue;									// 该条股票信息已在之前的操作中被删除
		int nextval[100] = { 0 };												// 模式串的next函数修正值
		nextval[0] = -1;
		string s = ST.Data[k].WebAddress;										// 股票的网址字段作为主串
		/* 求nextval数组*/
		int i = -1, j = 0;
		while (j < t.size()) {
			if (i == -1 || t[j] == t[i]) {
				j++, i++;
				if (t[j] != t[i])
					nextval[j] = i;
				else nextval[j] = nextval[i];
			}
			else
				i = nextval[i];
		}

		/* KMP算法 */
		i = 0, j = 0;
		while (i < s.size()) {													// 两个串均未比较到串尾
			if (j == -1 || s[i] == t[j])
				i++, j++;														// 继续比较后续字符
			else j = nextval[j];												// 模式串向后移动

			if (j == t.size()) {												// 匹配成功
				infonum++;
				cout << ST.Data[k].TickerName << '\t' << ST.Data[k].TickerSymbol <<endl;
				break;
			}
		}
	}
	cout << "共查询到 " << infonum << " 条信息\n";
}

/// <summary>
/// 基于二叉排序树的股票基本信息和涨跌信息查询
/// </summary>
void Stock::Search_By_BST() {
	cout << "请输入股票代码查询股票信息: ";
	string Code;
	cin >> Code;													// 根据输入的股票代码查询股票信息

	if (T == NULL) {
		cout << "查找失败！未收录该条股票信息！\n";
		return;
	}

	BSTree f = NULL;
	BSTree q = T;													// 临时工作指针
	int asl = 0;													// 用于计算查找成功的ASL值
	while (q != NULL) {
		asl++;
		if (q->Data->TickerSymbol == Code&&!q->Data->Del_flag) {	// 如果找到该支股票，输出详细信息
			cout << "股票代码: " << q->Data->TickerSymbol << endl;
			cout << "股票名称: " << q->Data->TickerName << endl;
			cout << "最新日期: " << q->Data->UDInfo[1].Date << endl;
			cout << "开盘价:   " << q->Data->UDInfo[1].OpenPrice << endl;
			cout << "收盘价:   " << q->Data->UDInfo[1].ClosingPrice << endl;
			cout << "涨跌幅:   " << fixed << setprecision(2) << q->Data->UDInfo[1].FluctuationRange <<'%'<< endl;
			cout << "查找成功的ASL值为: " << GetASL_BST()<< endl;
			return;
		}
		f = q;
		if (Code < q->Data->TickerSymbol) q = q->lchild;			// 小于当前值，指针指向左子树
		else q = q->rchild;											// 大于当前值，指针指向右子树
	}

	cout << "查找失败！未收录该条股票信息！\n";
	return;
}

/// <summary>
/// 基于二叉树的股票基本信息删除，删除后输出此位置新节点的信息和左右孩子信息
/// </summary>
void Stock::Delete_By_BST() {
	string Code;
	cout << "请输入待删除股票信息的股票代码: ";
	cin >> Code;																// 输入待删除的股票代码
	getchar();

	BSTree p = T, f = NULL;														// 初始化
	/* 从根节点开始寻找目标结点 */
	while (p != NULL) {
		if (p->Data->TickerSymbol == Code && !p->Data->Del_flag)				// 找到目标结点并且该节点未在之前的操作中被删除
			break;																// 退出循环

		f = p;																	// f时p的父节点
		if (p->Data->TickerSymbol > Code) p = p->lchild;						// 在左子树中继续查找
		else p = p->rchild;														// 在右子树中继续查找
	}

	if (p == NULL) {
		cout << "很抱歉！未收录该条股票信息！\n";
		return;																	// 找不到被删除结点，输出提示信息后返回
	}

	cout << "查询结果: \n";
	cout << p->Data->TickerSymbol << '\t' << p->Data->TickerName << endl;
	char flag = ' ';
	while (flag != 'y' && flag != 'n') {
		cout << "您确定要删除该条信息吗？[y/n]  ";
		flag = getchar();
		if (flag == 'n') return;
	}

	p->Data->Del_flag = 1;														// 被删标志置为1
	Del_Mark = 1;																// 进行过信息删除，需要在退出系统时重新写入
																				
	/* 考虑三种情况实现p所指子树内部的处理：p左右子树均不空，p的左子树为空，p的右子树为空 */
	BSTree q=new BSTNode(), s;
	if (p->rchild != NULL && p->lchild != NULL) {								// 左右子树均不空
		q = p, s = p->lchild;
		while (s->rchild != NULL) {												// 在左子树中继续查找其前驱结点，即最右下结点
			q = s;
			s = s->rchild;														// 向右到尽头
		}

		p->Data = s->Data;														// s指向被删结点的”前驱“
		if (q != p) q->rchild = s->lchild;										// 重接q的右子树
		else q->lchild = s->lchild;												// 重接q的左子树
		//delete s;
		//return;
	}
	else if (p->rchild == NULL) {												// 被删结点无右子树，只需重接其左子树
		q = p;
		p = p->lchild;
	}
	else if (p->lchild == NULL) {												// 无左子树，只需重接其右子树
		q = p;
		p = p->rchild;
	}

	/* 将p所指的子树挂到其双亲结点f的相应位置*/
	if (f == NULL) T = p;														// 被删结点为根节点
	else if (q == f->lchild) f->lchild = p;										// 挂接到f的左子树位置
	else f->rchild = p;															// 挂接到f的右子树位置

	cout << "成功删除！\n";


	/* 输出原来结点所在位置的新结点及其左右孩子信息 */
	if (p != NULL) {
		cout << "新结点信息 \n";
		cout << "股票名称: " << p->Data->TickerName << endl;
		cout << "股票代码: " << p->Data->TickerSymbol << endl;
		cout << "日期:    " << p->Data->UDInfo->Date << endl;
		cout << "开盘价:   " << p->Data->UDInfo->OpenPrice << endl;
		cout << "收盘价:   " << p->Data->UDInfo->ClosingPrice << endl;
		cout << "涨跌幅:   " << fixed << setprecision(2)<<fixed<<setprecision(2) <<p->Data->UDInfo->FluctuationRange <<'%'<< endl;
	}
	cout << '\n';
	if (p&&p->lchild != NULL) {
		cout << "左孩子信息 \n";
		cout << "股票名称: " << p->lchild->Data->TickerName << endl;
		cout << "股票代码: " << p->lchild->Data->TickerSymbol << endl;
		cout << "日期:    " << p->lchild->Data->UDInfo->Date << endl;
		cout << "开盘价:   " << p->lchild->Data->UDInfo->OpenPrice << endl;
		cout << "收盘价:   " << p->lchild->Data->UDInfo->ClosingPrice << endl;
		cout << "涨跌幅:   " << fixed << setprecision(2) << p->lchild->Data->UDInfo->FluctuationRange <<'%'<< endl;
	}

	cout << '\n';
	if (p&&p->rchild != NULL) {
		cout << "右孩子信息 \n";
		cout << "股票名称: " << p->rchild->Data->TickerName << endl;
		cout << "股票代码: " << p->rchild->Data->TickerSymbol << endl;
		cout << "日期:    " << p->rchild->Data->UDInfo->Date << endl;
		cout << "开盘价:   " << p->rchild->Data->UDInfo->OpenPrice << endl;
		cout << "收盘价:   " << p->rchild->Data->UDInfo->ClosingPrice << endl;
		cout << "涨跌幅:   " << fixed << setprecision(2) << p->rchild->Data->UDInfo->FluctuationRange<<'%' << endl;
	}
}


/// <summary>
/// 基于单链表的股票信息查询，输入日期，输入当日的股票相关信息
/// </summary>
void Stock::Search_By_List() {
	string Date;
	cout << "请输入您要查询的日期: ";
	cin >> Date;																		// 输出要查询的日期

	map<string, DateLink>::iterator it = L.find(Date);
	int tot = 0;
	if (it != L.end()) {																// 输出该日的股票信息
		DateLink p = it->second->next;													// 定义工作指针
		while (p != NULL) {
			if (p->BasicInfo->Del_flag == 1) continue;
			else {
				tot++;
				cout << p->BasicInfo->TickerSymbol << '\t' << p->BasicInfo->TickerName << '\t' << p->UDInfo->OpenPrice << '\t' << p->UDInfo->ClosingPrice << '\t' << fixed << setprecision(2) << p->UDInfo->FluctuationRange <<'%'<< endl;
			}
			p = p->next;
		}
	}
	cout << "该日共查询到 " << tot << " 条信息\n";
}


/// <summary>
/// 计算链地址法哈希表的查找成功的平均查找长度，返回值在查找函数中输出
/// </summary>
/// <returns></returns>
double Stock::GetASL_Hash() {
	if (Hashed == 0) {
		CreateHash();
		Hashed = 1;
	}
	int del = 0;														// 统计被删除的顶点数
	int asl = 0;														// 用于计算查找成功的ASL值
	for (int i = 0; i < ST.length; i++) {
		string Code = ST.Data[i].TickerSymbol;
		if (ST.Data[i].Del_flag == 1) {
			del++;
			continue;
		}

		int key = Hash_Key(Code);										// 计算输入代码的哈希函数值

		LinkList p = H.H[key];											// 定义工作结点查找指定股票

		if (p == NULL) {
			continue;
		}
		else {
			p = p->next;
			while (p != NULL) {
				asl++;
				if (p->Data->TickerSymbol == Code)						// 找到目标股票
					break;
				p = p->next;
			}
		}
	}

	return (double)asl / (ST.length - del);
}


/// <summary>
/// 计算基于二叉排序树查找的查找成功的平均查找长度，返回值在查找函数中输出
/// </summary>
/// <returns></returns>
double Stock::GetASL_BST() {
	int del = 0;														// 统计被删除的顶点数
	int asl = 0;														// 用于计算查找成功的ASL值
	for (int i = 0; i < ST.length; i++) {
		string Code = ST.Data[i].TickerSymbol;

		if (ST.Data[i].Del_flag == 1) {
			del++;
			continue;
		}

		if (T == NULL) {
			return 0;
		}

		BSTree f = NULL;
		BSTree q = T;													// 临时工作指针
		while (q != NULL) {
			asl++;
			if (q->Data->TickerSymbol == Code)							// 如果找到该支股票，输出详细信息
				break;
			f = q;
			if (Code < q->Data->TickerSymbol) q = q->lchild;			// 小于当前值，指针指向左子树
			else q = q->rchild;											// 大于当前值，指针指向右子树
		}
	}
	return (double)asl / (ST.length - del);
}


