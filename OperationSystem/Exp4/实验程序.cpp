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

/** 页表项的数据结构 **/
struct PageItem{
    bool status;            // 页面状态， true表示在内存，false表示在外存
    int block_num;          // 页面所在的内存块号
    int visit_num;          // 该页面的访问次数
    bool changed;           // 内容是否做过更改
    double firstTime;       // 首次访问时间
    double lastTime;        // 最后访问时间
};

/** 进程控制块 **/
struct PCB{
    string name;            // 进程名
    int blockNum;           // 需要内存块数
    vector<PageItem> page;  // 页表
};

const int BlockNum = 8;     // 内存块个数
const double BlockSize = 1; // 页面大小（内存块大小),单位为MB
vector<PCB> all;            // 存储所有进程的信息
bool M[BlockNum + 3];       // 共有8个内存块
int occupy;                 // 内存的占用状态
vector<int> list;           // 进程的内存访问序列
clock_t startTime;          // 页面载入的时间

void showStorage() {
    cout<<"内存占用情况如下:\n";
    cout<<"进程名, 占据内存块数\n";

    for(vector<PCB>::iterator it = all.begin();it != all.end(); it ++)
        cout<<it->name<<", "<<it->blockNum;
    cout<<"\n";
}

/**
 * LRU: 优先调出最久未使用的页面
 * 请求调入的页表项和所属的页表
 * 寻找所有进程加载到内存最后使用时间最小的页面
 */
void LRU(vector<PageItem> &page, PageItem &pageitem) {
    int proceid, pageid;
    double currtime = (double) clock() / CLOCKS_PER_SEC;
    for(int i = 0; i < all.size(); i ++) {      // 遍历所有的进程
        PCB tmp = all[i];
        for(int j = 0; j < tmp.page.size(); j ++) {    // 遍历进程的所有列表项
            if(tmp.page[j].status)
                if(tmp.page[j].lastTime < currtime) {
                    currtime = tmp.page[j].lastTime;
                    proceid = i;
                    pageid = j;
                }
        }
    }
    // 新页面换入
    pageitem.status = 1;
    pageitem.block_num = all[proceid].page[pageid].block_num;
    currtime = clock() / CLOCKS_PER_SEC;
    pageitem.lastTime = currtime;
    pageitem.firstTime = currtime;
    pageitem.visit_num = 1;
    // 旧页面换出
    all[proceid].page[pageid].status = 0;

    // 输出置换信息
    cout<<"与进程 " << all[proceid].name << " 的页面 " << pageid << " 置换\n";
    return;
}

/**
 * FIFO: 找出最早加载到内存的页面来置换
 * 请求调入的页表项和所属的页表
 * 寻找加载到内存进入时间最早的页面
 */
void FIFO(vector<PageItem> &page, PageItem &pageitem) {
    int proceid, pageid;
    double currtime = (double) clock() / CLOCKS_PER_SEC;
    for(int i = 0; i < all.size(); i ++) {      // 遍历所有的进程
        PCB tmp = all[i];
        for(int j = 0; j < tmp.page.size(); j ++) {    // 遍历进程的所有列表项
            if(tmp.page[j].status)
                if(tmp.page[j].firstTime < currtime) {
                    currtime = tmp.page[j].firstTime;
                    proceid = i;
                    pageid = j;
            }
        }
    }
    // 新页面换入
    pageitem.status = 1;
    pageitem.block_num = all[proceid].page[pageid].block_num;
    currtime = clock() / CLOCKS_PER_SEC;
    pageitem.lastTime = currtime;
    pageitem.firstTime = currtime;
    pageitem.visit_num = 1;
    // 旧页面换出
    all[proceid].page[pageid].status = 0;

    // 输出置换信息
    cout<<"与进程 " << all[proceid].name << " 的页面 " << pageid << " 置换\n";
    return;
}

/**
 * OPT: 最佳置换算法
 * 请求调入的页表项所属页表，页表项，访问序列的索引，访问序列的长度，进程需要的内存块数
 * 置换未来最少用的
 */
void OPT(vector<PageItem> &page, PageItem &pageitem, int pos, int p_size) {
    vector<int> note(p_size);               // 记录页面的预访问次数
    for(int i = 0; i < p_size; i ++)
        note[i] = 0;
    
    // 当前已处于内存中的进程页面记录初始化
    int i = 0;
    for(vector<PageItem>::iterator it = page.begin(); it != page.end(); it ++, i ++) 
        if(it->status) 
            note[i] = 0;
    
    // 遍历待访问序列
    for(int i = pos; i < list.size(); i ++) 
        if(note[list[i]] != -1)
            note[list[i]] ++;

    // 置换出将来最少用到的页面
    int leastid, minn = 9999999;
    for(i = 0; i <p_size; i ++)
        if(note[i] != -1 && note[i] < minn)
            minn = note[i], leastid = i;
    
    // 新页面换入
    pageitem.status = 1;
    pageitem.block_num = page[leastid].block_num;
    double currtime = clock() / CLOCKS_PER_SEC;
    pageitem.lastTime = currtime;
    pageitem.firstTime = currtime;
    pageitem.visit_num = 1;
    // 旧页面换出
    page[leastid].status = 0;

    // 输出置换信息
    cout<<"与页面 " << leastid << " 置换\n";
    return;
}


/** 创建进程，用户输入进程名和大小，随机生成访问序列 **/
void createProcess() {
    // 用户输入进程
    string name;
    int size;
    cout<<"输入进程名: ";
    cin>>name;
    cout<<"输入进程大小(MB): ";
    cin>>size;
    
    // 生成对应的进程控制块
    PCB process;
    process.name = name;
    process.blockNum = ceil(size/BlockSize);
    cout<<"进程 " << name << " 创建成功, 共 " << process.blockNum << " 页\n";

    // 随机生成访问序列, 长度5-15
    srand((unsigned)time(NULL));
    int len = rand() % 11 + 6;
    for(int i = 0; i < len; i++)
        list.push_back(rand() % process.blockNum);
    cout<<"随机产生页面访问序列: \n";
    for(int i = 0; i < len; i ++) {
        if(i != 0) cout<<", ";
        cout<<list[i];
    }
    cout<<"\n";

    // 初始化进程的页表
    vector<PageItem> page;
    for(int i = 0; i < process.blockNum; i ++) {
        PageItem tmp;
        tmp.status = 0;                     // 新进程的每一个页面都还未被载入
        page.push_back(tmp);
    }
    process.page = page;

    // 遍历访问序列，模拟进程载入内存
    for(int i = 0; i < len; i ++){
        clock_t cntTime = clock();          // 访问当前页面的时间
        if(!process.page[list[i]].status) { // 页面未载入内存
            if(occupy == 8) {               // 所有内存块都被占用
                cout<<"内存已满, 页面 " << list[i] << " 请求调入\n";
                cout << "请选择页面置换的调度方式：" << endl;
                cout << "1.LRU(优先调出最久未使用的页面)" << endl;
                cout << "2.FIFO(优先调出最早进入内存的页面)" << endl;
                if( i != 0) 
                    cout << "3.OPT(优先调出以后最不经常使用的页面)" << endl;
                char choice;
                cin >> choice;
                switch (choice)
                {
                case '1':
                    LRU(process.page, process.page[list[i]]);
                    cout << "置换成功！\n" << endl;
                    break;
                case '2':
                    FIFO(process.page, process.page[list[i]]);
                    cout << "置换成功！\n" << endl;
                    break;
                case '3':
                    OPT(process.page, process.page[list[i]], i, process.blockNum);
                    cout << "置换成功！\n" << endl;
                    break;
                default:
                    cout << "输入有误，本页面调入失败" << endl;
                    break;
                }
            }
            else {                          // 有空余内存块
                int initPos = rand() % BlockNum;
                int pos;
                for(int j = 0; j < BlockNum; j ++){// 找到一个未使用的内存块
                    pos = (initPos + j) % BlockNum;
                    if(M[pos]) {            // 内存块未被占用
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
                cout<<"页面"<<list[i]<<"分配到内存块" << pos<<"\n";
            }
        }
        else {                              // 页面已载入内存
            // 修改访问次数和页面最后访问的时间
            process.page[list[i]].visit_num ++;
            process.page[list[i]].lastTime = (double) cntTime / CLOCKS_PER_SEC;
            cout<<"页面"<<list[i]<<"已载入内存\n";
        }
        Sleep(200);                         // 休眠，模拟内存加载
    } 

    // 输出当前进程的页表信息
    cout<<"\n最终进程 " << process.name << " 的页表如下:\n";
    int i = 0;
    cout<<"页号, 对应的主存块号, 访问次数, 最后访问时间\n";
    for(vector<PageItem>::iterator it = process.page.begin(); it != process.page.end(); it ++, i ++){
        cout << i;
        if(it->status) 
            cout<<", "<<it->block_num<<", "<<it->visit_num<<", "<<it->lastTime<<"\n";
        else 
            cout<<"未载入主存\n";
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
        cout<<"输入要进行的操作:\n";
        cout<<"1. 查看当前内存的占用情况;\n";
        cout<<"2. 创建新的进程;\n";
        cout<<"3. 退出;\n";
        
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