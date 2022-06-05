/// <summary>
/// ʵ�ֲ�ѯ����
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
/// ���ڹ�ϣ��Ĺ�Ʊ������Ϣ��ѯ�������Ʊ����������ơ����롢һ����ҵ��������ҵ����Ӫҵ�񣬲�����ASL
/// </summary>
void Stock::Search_By_Hash() {
	if (Hashed == 0) {
		CreateHash();
		Hashed = 1;
	}

	string Code;
	cout << "�������Ʊ�����ѯ��Ʊ��Ϣ: ";
	cin >> Code;													// ��������Ĺ�Ʊ�����ѯ��Ʊ��Ϣ

	int key = Hash_Key(Code);										// �����������Ĺ�ϣ����ֵ

	LinkList p = H.H[key];											// ���幤��������ָ����Ʊ
	int asl = 0;													// ���ڼ�����ҳɹ���ASLֵ

	if (p == NULL) {
		cout << "����ʧ�ܣ�δ��¼������Ʊ��Ϣ��\n";
	}
	else {
		p = p->next;
		while (p != NULL) {
			asl++;
			if (p->Data->TickerSymbol == Code && p->Data->Del_flag==0) {// �ҵ�Ŀ���Ʊ��δ��֮ǰ�Ĳ����б�ɾ��,��������Ϣ
				cout << "��Ʊ����:" << p->Data->TickerName << endl;
				cout << "��Ʊ����:" << p->Data->TickerSymbol << endl;
				cout << "����һ����ҵ:" << p->Data->PriClass << endl;
				cout << "����������ҵ:" << p->Data->SecClass << endl;
				cout << "��Ӫҵ��:" << p->Data->MainBusiness << endl;
				cout << "���ҳɹ���ASLֵΪ:" << GetASL_Hash() << endl;
				return;
			}
			p = p->next;
		}
	}
	cout << "����ʧ�ܣ�δ��¼������Ʊ��Ϣ!\n";
}


/// <summary>
/// ����KMP�Ĺ�Ʊ��ַ��ѯ��������ַ�ַ����Ӵ�����ѯ���й�Ʊ�ġ���ַ���ֶ�
/// </summary>
void Stock::Search_By_KMP() {
	cout << "�������ѯ��Ʊ��ַ�ַ������Ӵ�: ";
	string t;																	// ģʽ��t
	cin >> t;
	
	int k, infonum = 0;
	for (k = 0; k < ST.length; k++) {
		if (ST.Data[k].Del_flag == 1) continue;									// ������Ʊ��Ϣ����֮ǰ�Ĳ����б�ɾ��
		int nextval[100] = { 0 };												// ģʽ����next��������ֵ
		nextval[0] = -1;
		string s = ST.Data[k].WebAddress;										// ��Ʊ����ַ�ֶ���Ϊ����
		/* ��nextval����*/
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

		/* KMP�㷨 */
		i = 0, j = 0;
		while (i < s.size()) {													// ��������δ�Ƚϵ���β
			if (j == -1 || s[i] == t[j])
				i++, j++;														// �����ȽϺ����ַ�
			else j = nextval[j];												// ģʽ������ƶ�

			if (j == t.size()) {												// ƥ��ɹ�
				infonum++;
				cout << ST.Data[k].TickerName << '\t' << ST.Data[k].TickerSymbol <<endl;
				break;
			}
		}
	}
	cout << "����ѯ�� " << infonum << " ����Ϣ\n";
}

/// <summary>
/// ���ڶ����������Ĺ�Ʊ������Ϣ���ǵ���Ϣ��ѯ
/// </summary>
void Stock::Search_By_BST() {
	cout << "�������Ʊ�����ѯ��Ʊ��Ϣ: ";
	string Code;
	cin >> Code;													// ��������Ĺ�Ʊ�����ѯ��Ʊ��Ϣ

	if (T == NULL) {
		cout << "����ʧ�ܣ�δ��¼������Ʊ��Ϣ��\n";
		return;
	}

	BSTree f = NULL;
	BSTree q = T;													// ��ʱ����ָ��
	int asl = 0;													// ���ڼ�����ҳɹ���ASLֵ
	while (q != NULL) {
		asl++;
		if (q->Data->TickerSymbol == Code&&!q->Data->Del_flag) {	// ����ҵ���֧��Ʊ�������ϸ��Ϣ
			cout << "��Ʊ����: " << q->Data->TickerSymbol << endl;
			cout << "��Ʊ����: " << q->Data->TickerName << endl;
			cout << "��������: " << q->Data->UDInfo[1].Date << endl;
			cout << "���̼�:   " << q->Data->UDInfo[1].OpenPrice << endl;
			cout << "���̼�:   " << q->Data->UDInfo[1].ClosingPrice << endl;
			cout << "�ǵ���:   " << fixed << setprecision(2) << q->Data->UDInfo[1].FluctuationRange <<'%'<< endl;
			cout << "���ҳɹ���ASLֵΪ: " << GetASL_BST()<< endl;
			return;
		}
		f = q;
		if (Code < q->Data->TickerSymbol) q = q->lchild;			// С�ڵ�ǰֵ��ָ��ָ��������
		else q = q->rchild;											// ���ڵ�ǰֵ��ָ��ָ��������
	}

	cout << "����ʧ�ܣ�δ��¼������Ʊ��Ϣ��\n";
	return;
}

/// <summary>
/// ���ڶ������Ĺ�Ʊ������Ϣɾ����ɾ���������λ���½ڵ����Ϣ�����Һ�����Ϣ
/// </summary>
void Stock::Delete_By_BST() {
	string Code;
	cout << "�������ɾ����Ʊ��Ϣ�Ĺ�Ʊ����: ";
	cin >> Code;																// �����ɾ���Ĺ�Ʊ����
	getchar();

	BSTree p = T, f = NULL;														// ��ʼ��
	/* �Ӹ��ڵ㿪ʼѰ��Ŀ���� */
	while (p != NULL) {
		if (p->Data->TickerSymbol == Code && !p->Data->Del_flag)				// �ҵ�Ŀ���㲢�Ҹýڵ�δ��֮ǰ�Ĳ����б�ɾ��
			break;																// �˳�ѭ��

		f = p;																	// fʱp�ĸ��ڵ�
		if (p->Data->TickerSymbol > Code) p = p->lchild;						// ���������м�������
		else p = p->rchild;														// ���������м�������
	}

	if (p == NULL) {
		cout << "�ܱ�Ǹ��δ��¼������Ʊ��Ϣ��\n";
		return;																	// �Ҳ�����ɾ����㣬�����ʾ��Ϣ�󷵻�
	}

	cout << "��ѯ���: \n";
	cout << p->Data->TickerSymbol << '\t' << p->Data->TickerName << endl;
	char flag = ' ';
	while (flag != 'y' && flag != 'n') {
		cout << "��ȷ��Ҫɾ��������Ϣ��[y/n]  ";
		flag = getchar();
		if (flag == 'n') return;
	}

	p->Data->Del_flag = 1;														// ��ɾ��־��Ϊ1
	Del_Mark = 1;																// ���й���Ϣɾ������Ҫ���˳�ϵͳʱ����д��
																				
	/* �����������ʵ��p��ָ�����ڲ��Ĵ���p�������������գ�p��������Ϊ�գ�p��������Ϊ�� */
	BSTree q=new BSTNode(), s;
	if (p->rchild != NULL && p->lchild != NULL) {								// ��������������
		q = p, s = p->lchild;
		while (s->rchild != NULL) {												// ���������м���������ǰ����㣬�������½��
			q = s;
			s = s->rchild;														// ���ҵ���ͷ
		}

		p->Data = s->Data;														// sָ��ɾ���ġ�ǰ����
		if (q != p) q->rchild = s->lchild;										// �ؽ�q��������
		else q->lchild = s->lchild;												// �ؽ�q��������
		//delete s;
		//return;
	}
	else if (p->rchild == NULL) {												// ��ɾ�������������ֻ���ؽ���������
		q = p;
		p = p->lchild;
	}
	else if (p->lchild == NULL) {												// ����������ֻ���ؽ���������
		q = p;
		p = p->rchild;
	}

	/* ��p��ָ�������ҵ���˫�׽��f����Ӧλ��*/
	if (f == NULL) T = p;														// ��ɾ���Ϊ���ڵ�
	else if (q == f->lchild) f->lchild = p;										// �ҽӵ�f��������λ��
	else f->rchild = p;															// �ҽӵ�f��������λ��

	cout << "�ɹ�ɾ����\n";


	/* ���ԭ���������λ�õ��½�㼰�����Һ�����Ϣ */
	if (p != NULL) {
		cout << "�½����Ϣ \n";
		cout << "��Ʊ����: " << p->Data->TickerName << endl;
		cout << "��Ʊ����: " << p->Data->TickerSymbol << endl;
		cout << "����:    " << p->Data->UDInfo->Date << endl;
		cout << "���̼�:   " << p->Data->UDInfo->OpenPrice << endl;
		cout << "���̼�:   " << p->Data->UDInfo->ClosingPrice << endl;
		cout << "�ǵ���:   " << fixed << setprecision(2)<<fixed<<setprecision(2) <<p->Data->UDInfo->FluctuationRange <<'%'<< endl;
	}
	cout << '\n';
	if (p&&p->lchild != NULL) {
		cout << "������Ϣ \n";
		cout << "��Ʊ����: " << p->lchild->Data->TickerName << endl;
		cout << "��Ʊ����: " << p->lchild->Data->TickerSymbol << endl;
		cout << "����:    " << p->lchild->Data->UDInfo->Date << endl;
		cout << "���̼�:   " << p->lchild->Data->UDInfo->OpenPrice << endl;
		cout << "���̼�:   " << p->lchild->Data->UDInfo->ClosingPrice << endl;
		cout << "�ǵ���:   " << fixed << setprecision(2) << p->lchild->Data->UDInfo->FluctuationRange <<'%'<< endl;
	}

	cout << '\n';
	if (p&&p->rchild != NULL) {
		cout << "�Һ�����Ϣ \n";
		cout << "��Ʊ����: " << p->rchild->Data->TickerName << endl;
		cout << "��Ʊ����: " << p->rchild->Data->TickerSymbol << endl;
		cout << "����:    " << p->rchild->Data->UDInfo->Date << endl;
		cout << "���̼�:   " << p->rchild->Data->UDInfo->OpenPrice << endl;
		cout << "���̼�:   " << p->rchild->Data->UDInfo->ClosingPrice << endl;
		cout << "�ǵ���:   " << fixed << setprecision(2) << p->rchild->Data->UDInfo->FluctuationRange<<'%' << endl;
	}
}


/// <summary>
/// ���ڵ�����Ĺ�Ʊ��Ϣ��ѯ���������ڣ����뵱�յĹ�Ʊ�����Ϣ
/// </summary>
void Stock::Search_By_List() {
	string Date;
	cout << "��������Ҫ��ѯ������: ";
	cin >> Date;																		// ���Ҫ��ѯ������

	map<string, DateLink>::iterator it = L.find(Date);
	int tot = 0;
	if (it != L.end()) {																// ������յĹ�Ʊ��Ϣ
		DateLink p = it->second->next;													// ���幤��ָ��
		while (p != NULL) {
			if (p->BasicInfo->Del_flag == 1) continue;
			else {
				tot++;
				cout << p->BasicInfo->TickerSymbol << '\t' << p->BasicInfo->TickerName << '\t' << p->UDInfo->OpenPrice << '\t' << p->UDInfo->ClosingPrice << '\t' << fixed << setprecision(2) << p->UDInfo->FluctuationRange <<'%'<< endl;
			}
			p = p->next;
		}
	}
	cout << "���չ���ѯ�� " << tot << " ����Ϣ\n";
}


/// <summary>
/// ��������ַ����ϣ��Ĳ��ҳɹ���ƽ�����ҳ��ȣ�����ֵ�ڲ��Һ��������
/// </summary>
/// <returns></returns>
double Stock::GetASL_Hash() {
	if (Hashed == 0) {
		CreateHash();
		Hashed = 1;
	}
	int del = 0;														// ͳ�Ʊ�ɾ���Ķ�����
	int asl = 0;														// ���ڼ�����ҳɹ���ASLֵ
	for (int i = 0; i < ST.length; i++) {
		string Code = ST.Data[i].TickerSymbol;
		if (ST.Data[i].Del_flag == 1) {
			del++;
			continue;
		}

		int key = Hash_Key(Code);										// �����������Ĺ�ϣ����ֵ

		LinkList p = H.H[key];											// ���幤��������ָ����Ʊ

		if (p == NULL) {
			continue;
		}
		else {
			p = p->next;
			while (p != NULL) {
				asl++;
				if (p->Data->TickerSymbol == Code)						// �ҵ�Ŀ���Ʊ
					break;
				p = p->next;
			}
		}
	}

	return (double)asl / (ST.length - del);
}


/// <summary>
/// ������ڶ������������ҵĲ��ҳɹ���ƽ�����ҳ��ȣ�����ֵ�ڲ��Һ��������
/// </summary>
/// <returns></returns>
double Stock::GetASL_BST() {
	int del = 0;														// ͳ�Ʊ�ɾ���Ķ�����
	int asl = 0;														// ���ڼ�����ҳɹ���ASLֵ
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
		BSTree q = T;													// ��ʱ����ָ��
		while (q != NULL) {
			asl++;
			if (q->Data->TickerSymbol == Code)							// ����ҵ���֧��Ʊ�������ϸ��Ϣ
				break;
			f = q;
			if (Code < q->Data->TickerSymbol) q = q->lchild;			// С�ڵ�ǰֵ��ָ��ָ��������
			else q = q->rchild;											// ���ڵ�ǰֵ��ָ��ָ��������
		}
	}
	return (double)asl / (ST.length - del);
}


