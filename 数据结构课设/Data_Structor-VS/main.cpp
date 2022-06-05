#include<iostream>
#include<queue>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<string>
#include"Stock.h"

using namespace std;

/// <summary>
/// Ö÷º¯Êý
/// <summary>

int main() {
	Stock Info;

	/*Info.Search_By_KMP();
	Info.Search_By_Hash();
	Info.PrintBST(Info.ReturnBST());
	Info.Search_By_BST();
	Info.QuickSort_Sixty();
	Info.SelectionSort_By_Scr();
	Info.SelectionSort_By_CloPrice();
	Info.CreateGraph();
	Info.CreateHash();
	Info.Selection_By_BST();
	Info.Selection_By_BGraph();
	Info.Search_By_Hash();
	Info.Search_By_BST();
	Info.ShortestPath_By_Floyd();
	Info.CreateBST();
	Info.Delete_By_BST();
	Info.Write_File();
	Info.PrintBST(Info.ReturnBST());*/
	Info.CreateList();
	Info.InsertionSort();
	Info.Search_By_List();

	return 0;
}