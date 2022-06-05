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
/// �����Ʊ�࣬��װ�������ͺͲ���
/// </summary>

class Stock
{
private:
	map<string, DateLink> L;					// ���嵥���������ǵ���Ϣ��ѯ,�������ڴ洢��ʹ��mapӳ��
	Hash H;										// �����ϣ�����ڻ�����Ϣ��ѯ�����ݹ�Ʊ����
	BSTree T;									// ������������������ǵ���Ϣ��ѯ�����ݹ�Ʊ����
	STable ST;									// ����˳������ڿ�������ʹ洢��Ϣ
	SixtyStock Stock_60[70];					// ����ṹ������洢��ʮ֧��Ʊ�������Ϣ
	int Graph[Some+7][Some+7] = { 0 };			// �洢�ļ��ж����ͼ
	int Compt_Graph[Some + 7][Some + 7] = { 0 };// �洢����Floyed֮�����ɵ���ȫͼ
	int Path[Some + 7][Some + 7] = { 0 };		// �洢Floyd�㷨�õ����������������·��
	BSTedge BSTEdge[Some + 7];					// �洢��С�������ı�
	BGraph BiGraph;								// �洢��ͼ


	KruscalEdge Krus_Edge[Some*Some/2];			// Kruscal�㷨ʹ�õĸ����ṹ������
	PrimEdge Prim_Closedge[Some + 7];			// Prim�㷨ʹ�õĸ������飬ͬ����¼Ȩֵ��С�ı�
	int Hashed = 0;								// Hashed==1ʱ��ʾ�Ѿ���������ϣ���ڷ��������ж�ȡ60֧��Ʊ��Ϣʱ����ͨ����ϣ���ѯ����Ӧ��Ϣ
	int Del_Mark = 0;							// Del_Mark==1ʱ��ʾ�Ѿ����й�ɾ����������Ҫ���˳�ϵͳʱ��д�ļ�
	int Sixty_Read = 0;							// Sixty_Read==1ʱ��ʾ�Ѿ������60֧��Ʊ��Ϣ������ʹ��ʱ����Ҫ�ٶ���
	int Read_Graph = 0;							// Read_Grah==1��ʾ�Ѿ����ļ��ж���ͼ
	int Floyded = 0;							// Floyded==1��ʾ�Ѿ�ʹ��Floyd�㷨�õ�����ȫͼ

	string line_Basic;							// �洢������Ϣ���ļ���ͷ
	string line_UDInfo;							// �洢�ǵ���Ϣ���ļ���ͷ
	string line_SixtyScr;						// �洢��ʮ֧��Ʊ���ֵ��ļ���ͷ
	string line_Graph;							// �洢ͼ���ļ���ͷ

protected:


public:
	// ������г�ʼ�����������ݴ洢�ڵ�������
	Stock();
	
	void Insert_BasicInfo(istringstream& ss, basicinfo BasicInfo[], int sum);	// �������һ�л�����Ϣͨ���ַ������洢��������
	int Insert_UDInfo(ifstream&, udinfo UDInfo[]);								// ��������ǵ���Ϣ�洢��������
	int  Hash_Key(string const&);												// ���ϣ����ֵ
	void InsertBST(BSTree&,int);												// ͨ���ݹ���뽨��������
	void PrintBST(BSTree);														// ����������Ƿ����ɹ��Ĳ������
	void Read_SixtyStock();														// ���ļ��ж���60֧��Ʊ��Ϣ
	basicinfo* Search60_InAll(string);											// ������ʮ֧��Ʊ�����ƺʹ����Ѱ����������Ϣ
	udinfo* GetMaxFlutuation(basicinfo*);										// �ҵ�ĳֻ��Ʊ����ǵ���
	void QSort(int, int,int);													// �Դ洢60֧��Ʊ��Ϣ��������п�������
	int Partition(int, int,int);												// ���������һ�����򣬷�������λ�� 
	void Relevance_Floyd();														// ʹ��Floyd�㷨�������·��������Է���
	void Prim();																// ʹ��Prim�㷨����ͨͼ����С������
	void Kruscal();																// ʹ��Kruscal�㷨����ͨͼ����С������
	void Choose(int ,int ,int );												// ��С������ɸѡ����ʱ���ֱ�Ȩ�ظ����޷�ǡ��ѡ��ʱ����Ҫ�������ɸѡ
	bool BGraph_DFS(int, int, int[]);											// ���������������Ⱦɫ���ж��Ƿ�Ϊ����ͼ


	void CreateHash();															// ������ϣ��
	void CreateList();															// ����������
	void CreateBST();															// ����������
	void CreateGraph();															// ���ļ��ж�����Ϣ������Ȩͼ



	void Search_By_Hash();														// ���ڹ�ϣ��Ĺ�Ʊ������Ϣ��ѯ
	void Search_By_KMP();														// ����KMP�Ĺ�Ʊ��ַ��ѯ
	void Search_By_BST();														// ���ڶ������Ĺ�Ʊ������Ϣ��ѯ
	void Delete_By_BST();														// ���ڶ����������Ĺ�Ʊ������Ϣɾ��
	void Search_By_List();														// ���ڵ�����Ĺ�Ʊ�۸���Ϣ��ѯ



	void InsertionSort();													
	void QuickSort_Sixty();														// ���60֧��Ʊ��Ϣ���ڿ�������Ĺ�Ʊ�۸����
	void SelectionSort_By_Scr();												// ���60֧��Ʊ��Ϣ���ڼ�ѡ������Ĺ�Ʊ�۸����(������������
	void SelectionSort_By_CloPrice();											// ���60֧��Ʊ��Ϣ���ڼ�ѡ������Ĺ�Ʊ�۸����(�������һ�����̼�����
	void ShortestPath_By_Floyd();												// ����Floyd�Ĺ�Ʊ����Լ��㣨�������������·����
	void Selection_By_BST();													// ����Prim��С�������Ĺ�Ʊ����ɸѡ
	void Selection_By_BGraph();													// ���ڶ���ͼ�Ĺ�Ʊ����ɸѡ

	double GetASL_Hash();														// ����ʹ�ù�ϣ����ҵ�ƽ�����ҳ���
	double GetASL_BST();														// ����ʹ�ö�����������ƽ�����ҳ���

	BSTree ReturnBST();															// �������ж���Ķ���������
	
	void Write_File();															// �˳�ϵͳʱ�������ܣ��޸Ĺ�������д��

	~Stock() {};

};