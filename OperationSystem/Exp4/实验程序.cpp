#include<iostream>
#include<cstdio>
#include<vector>
#include<cstring>
#include<string>
#include<cmath>
#include<ctime>
#include<cstdlib>
#include<windows.h>

using namespace std;

/** ҳ��������ݽṹ **/
struct PageItem{
    bool status;            // ҳ��״̬�� true��ʾ���ڴ棬false��ʾ�����
    int block_num;          // ҳ�����ڵ��ڴ���
    int visit_num;          // ��ҳ��ķ��ʴ���
    bool changed;           // �����Ƿ���������
    double firstTime;       // �״η���ʱ��
    double lastTime;        // ������ʱ��
};

/** ���̿��ƿ� **/
struct PCB{
    string name;            // ������
    int blockNum;           // ��Ҫ�ڴ����
    vector<PageItem> page;  // ҳ��
};

const int BlockNum = 8;     // �ڴ�����
const double BlockSize = 1; // ҳ���С���ڴ���С),��λΪMB
vector<PCB> all;            // �洢���н��̵���Ϣ
bool M[BlockNum + 3];       // ����8���ڴ��
int occupy;                 // �ڴ��ռ��״̬
vector<int> list;           // ���̵��ڴ��������
clock_t startTime;          // ҳ�������ʱ��

void showStorage() {
    cout<<"�ڴ�ռ���������:\n";
    cout<<"������, ռ���ڴ����\n";

    for(vector<PCB>::iterator it = all.begin();it != all.end(); it ++)
        cout<<it->name<<", "<<it->blockNum;
    cout<<"\n";
}

/**
 * LRU: ���ȵ������δʹ�õ�ҳ��
 * ��������ҳ�����������ҳ��
 * Ѱ�����н��̼��ص��ڴ����ʹ��ʱ����С��ҳ��
 */
void LRU(vector<PageItem> &page, PageItem &pageitem) {
    int proceid, pageid;
    double currtime = (double) clock() / CLOCKS_PER_SEC;
    for(int i = 0; i < all.size(); i ++) {      // �������еĽ���
        PCB tmp = all[i];
        for(int j = 0; j < tmp.page.size(); j ++) {    // �������̵������б���
            if(tmp.page[j].status)
                if(tmp.page[j].lastTime < currtime) {
                    currtime = tmp.page[j].lastTime;
                    proceid = i;
                    pageid = j;
                }
        }
    }
    // ��ҳ�滻��
    pageitem.status = 1;
    pageitem.block_num = all[proceid].page[pageid].block_num;
    currtime = clock() / CLOCKS_PER_SEC;
    pageitem.lastTime = currtime;
    pageitem.firstTime = currtime;
    pageitem.visit_num = 1;
    // ��ҳ�滻��
    all[proceid].page[pageid].status = 0;

    // ����û���Ϣ
    cout<<"����� " << all[proceid].name << " ��ҳ�� " << pageid << " �û�\n";
    return;
}

/**
 * FIFO: �ҳ�������ص��ڴ��ҳ�����û�
 * ��������ҳ�����������ҳ��
 * Ѱ�Ҽ��ص��ڴ����ʱ�������ҳ��
 */
void FIFO(vector<PageItem> &page, PageItem &pageitem) {
    int proceid, pageid;
    double currtime = (double) clock() / CLOCKS_PER_SEC;
    for(int i = 0; i < all.size(); i ++) {      // �������еĽ���
        PCB tmp = all[i];
        for(int j = 0; j < tmp.page.size(); j ++) {    // �������̵������б���
            if(tmp.page[j].status)
                if(tmp.page[j].firstTime < currtime) {
                    currtime = tmp.page[j].firstTime;
                    proceid = i;
                    pageid = j;
            }
        }
    }
    // ��ҳ�滻��
    pageitem.status = 1;
    pageitem.block_num = all[proceid].page[pageid].block_num;
    currtime = clock() / CLOCKS_PER_SEC;
    pageitem.lastTime = currtime;
    pageitem.firstTime = currtime;
    pageitem.visit_num = 1;
    // ��ҳ�滻��
    all[proceid].page[pageid].status = 0;

    // ����û���Ϣ
    cout<<"����� " << all[proceid].name << " ��ҳ�� " << pageid << " �û�\n";
    return;
}

/**
 * OPT: ����û��㷨
 * ��������ҳ��������ҳ��ҳ����������е��������������еĳ��ȣ�������Ҫ���ڴ����
 * �û�δ�������õ�
 */
void OPT(vector<PageItem> &page, PageItem &pageitem, int pos, int p_size) {
    vector<int> note(p_size);               // ��¼ҳ���Ԥ���ʴ���
    for(int i = 0; i < p_size; i ++)
        note[i] = 0;
    
    // ��ǰ�Ѵ����ڴ��еĽ���ҳ���¼��ʼ��
    int i = 0;
    for(vector<PageItem>::iterator it = page.begin(); it != page.end(); it ++, i ++) 
        if(it->status) 
            note[i] = 0;
    
    // ��������������
    for(int i = pos; i < list.size(); i ++) 
        if(note[list[i]] != -1)
            note[list[i]] ++;

    // �û������������õ���ҳ��
    int leastid, minn = 9999999;
    for(i = 0; i <p_size; i ++)
        if(note[i] != -1 && note[i] < minn)
            minn = note[i], leastid = i;
    
    // ��ҳ�滻��
    pageitem.status = 1;
    pageitem.block_num = page[leastid].block_num;
    double currtime = clock() / CLOCKS_PER_SEC;
    pageitem.lastTime = currtime;
    pageitem.firstTime = currtime;
    pageitem.visit_num = 1;
    // ��ҳ�滻��
    page[leastid].status = 0;

    // ����û���Ϣ
    cout<<"��ҳ�� " << leastid << " �û�\n";
    return;
}


/** �������̣��û�����������ʹ�С��������ɷ������� **/
void createProcess() {
    // �û��������
    string name;
    int size;
    cout<<"���������: ";
    cin>>name;
    cout<<"������̴�С(MB): ";
    cin>>size;
    
    // ���ɶ�Ӧ�Ľ��̿��ƿ�
    PCB process;
    process.name = name;
    process.blockNum = ceil(size/BlockSize);
    cout<<"���� " << name << " �����ɹ�, �� " << process.blockNum << " ҳ\n";

    // ������ɷ�������, ����5-15
    srand((unsigned)time(NULL));
    int len = rand() % 11 + 6;
    for(int i = 0; i < len; i++)
        list.push_back(rand() % process.blockNum);
    cout<<"�������ҳ���������: \n";
    for(int i = 0; i < len; i ++) {
        if(i != 0) cout<<", ";
        cout<<list[i];
    }
    cout<<"\n";

    // ��ʼ�����̵�ҳ��
    vector<PageItem> page;
    for(int i = 0; i < process.blockNum; i ++) {
        PageItem tmp;
        tmp.status = 0;                     // �½��̵�ÿһ��ҳ�涼��δ������
        page.push_back(tmp);
    }
    process.page = page;

    // �����������У�ģ����������ڴ�
    for(int i = 0; i < len; i ++){
        clock_t cntTime = clock();          // ���ʵ�ǰҳ���ʱ��
        if(!process.page[list[i]].status) { // ҳ��δ�����ڴ�
            if(occupy == 8) {               // �����ڴ�鶼��ռ��
                cout<<"�ڴ�����, ҳ�� " << list[i] << " �������\n";
                cout << "��ѡ��ҳ���û��ĵ��ȷ�ʽ��" << endl;
                cout << "1.LRU(���ȵ������δʹ�õ�ҳ��)" << endl;
                cout << "2.FIFO(���ȵ�����������ڴ��ҳ��)" << endl;
                if( i != 0) 
                    cout << "3.OPT(���ȵ����Ժ������ʹ�õ�ҳ��)" << endl;
                char choice;
                cin >> choice;
                switch (choice)
                {
                case '1':
                    LRU(process.page, process.page[list[i]]);
                    cout << "�û��ɹ���\n" << endl;
                    break;
                case '2':
                    FIFO(process.page, process.page[list[i]]);
                    cout << "�û��ɹ���\n" << endl;
                    break;
                case '3':
                    OPT(process.page, process.page[list[i]], i, process.blockNum);
                    cout << "�û��ɹ���\n" << endl;
                    break;
                default:
                    cout << "�������󣬱�ҳ�����ʧ��" << endl;
                    break;
                }
            }
            else {                          // �п����ڴ��
                int initPos = rand() % BlockNum;
                int pos;
                for(int j = 0; j < BlockNum; j ++){// �ҵ�һ��δʹ�õ��ڴ��
                    pos = (initPos + j) % BlockNum;
                    if(M[pos]) {            // �ڴ��δ��ռ��
                        M[pos] = false;
                        occupy ++;
                        process.page[list[i]].status = 1;
                        process.page[list[i]].visit_num = 1;
                        process.page[list[i]].block_num = pos;
                        process.page[list[i]].firstTime = (double) cntTime / CLOCKS_PER_SEC;
                        process.page[list[i]].lastTime = process.page[list[i]].firstTime;
                        break;
                    }
                }
                cout<<"ҳ��"<<list[i]<<"���䵽�ڴ��" << pos<<"\n";
            }
        }
        else {                              // ҳ���������ڴ�
            // �޸ķ��ʴ�����ҳ�������ʵ�ʱ��
            process.page[list[i]].visit_num ++;
            process.page[list[i]].lastTime = (double) cntTime / CLOCKS_PER_SEC;
            cout<<"ҳ��"<<list[i]<<"�������ڴ�\n";
        }
        Sleep(200);                         // ���ߣ�ģ���ڴ����
    } 

    // �����ǰ���̵�ҳ����Ϣ
    cout<<"\n���ս��� " << process.name << " ��ҳ������:\n";
    int i = 0;
    cout<<"ҳ��, ��Ӧ��������, ���ʴ���, ������ʱ��\n";
    for(vector<PageItem>::iterator it = process.page.begin(); it != process.page.end(); it ++, i ++){
        cout << i;
        if(it->status) 
            cout<<", "<<it->block_num<<", "<<it->visit_num<<", "<<it->lastTime<<"\n";
        else 
            cout<<"δ��������\n";
    }
    cout<<"\n";
    all.push_back(process);
}
    

int main() {
    memset(M, 1, sizeof(M));
    occupy = 0;
    char choice;
    bool running = 1;
    while(running) { 
        cout<<"����Ҫ���еĲ���:\n";
        cout<<"1. �鿴��ǰ�ڴ��ռ�����;\n";
        cout<<"2. �����µĽ���;\n";
        cout<<"3. �˳�;\n";
        
        cin>>choice;

        if(choice == '1')
            showStorage();
        else if (choice == '2')
            createProcess();
        else if (choice == '3')
            running = 0;
        else
            continue;
    }
    return 0;
}