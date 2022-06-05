#include "assignwin.h"
#include "ui_assignwin.h"
#include "structure.h"

extern vector<Progress> prog;
extern vector<Progress> hangProg;
extern vector<Unused> UnusedTable;
extern vector<Used> UsedTable;

extern int usedMem = 131072;
extern int unusedMem = 383216;

AssignWin::AssignWin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AssignWin)
{
    ui->setupUi(this);

    this->setWindowTitle("内存分配结果");

    ui->Events->setColumnCount(4);
//    ui->Events->setRowCount(0);
    ui->Events->horizontalHeader()->setStretchLastSection(true);
    QStringList header1;
    header1<<tr("时刻")<<tr("PID")<<tr("内存")<<tr("事件");
    ui->Events->setHorizontalHeaderLabels(header1);
    ui->Events->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->Used->setColumnCount(3);
//    ui->Used->setRowCount(0);
    QStringList header2;
    header2<<tr("PID")<<tr("起始地址")<<tr("大小(KB)");
    ui->Used->setHorizontalHeaderLabels(header2);
    ui->Used->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->Unused->setColumnCount(2);
//    ui->Used->setRowCount(0);
    QStringList header3;
    header3<<tr("起始地址")<<tr("大小(KB)");
    ui->Unused->setHorizontalHeaderLabels(header3);
    ui->Unused->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

}

AssignWin::~AssignWin()
{
    delete ui;
}

bool cmp1(Progress& a, Progress& b) {
    return a.arrive < b.arrive;
}

bool cmp2(Unused& a, Unused& b) {
    return a.endd - a.start + 1 < b.endd - b.start + 1;
}

bool cmp3(Used& a, Used& b) {
    return a.start < b.start;
}

void AssignWin::printUsedTable(int t) {
//    printf("=========已分配分区============\n");
//    printf("   PID     start     end   \n");
    int row_count = ui->Used->rowCount();
    ui->Used->insertRow(row_count);
    QString Mes = QString::fromStdString("时刻" + to_string(t));
    ui->Used->setSpan(row_count, 0, 1, 3);
    ui->Used->setItem(row_count,0,new QTableWidgetItem(Mes));
    for (int i = 0; i < UsedTable.size(); i++) {
        //printf("%9d%9d%9d\n", UsedTable[i].JobID, UsedTable[i].start, UsedTable[i].endd);
        row_count = ui->Used->rowCount();
        ui->Used->insertRow(row_count);

        QTableWidgetItem *PID=new QTableWidgetItem();
        QTableWidgetItem *start=new QTableWidgetItem();
        QTableWidgetItem *Mem=new QTableWidgetItem();

        PID->setText(QString::fromStdString(to_string(UsedTable[i].JobID)));
        start->setText(QString::fromStdString(to_string(UsedTable[i].start)));
        Mem->setText(QString::fromStdString(to_string(UsedTable[i].endd - UsedTable[i].start + 1)));

        ui->Used->setItem(row_count,0,PID);
        ui->Used->setItem(row_count, 1, start);
        ui->Used->setItem(row_count,2,Mem);
    }
    //printf("=============================");
}

void AssignWin::printUnusedTable(int t) {
//    printf("===========空闲分区============\n");
//    printf("  start     end   \n");
    int row_count = ui->Unused->rowCount();
    cout<<row_count<<'\n';
    ui->Unused->insertRow(row_count);
    QString Mes = QString::fromStdString("时刻" + to_string(t));
    ui->Unused->setSpan(row_count, 0, 1, 2);
    ui->Unused->setItem(row_count,0,new QTableWidgetItem(Mes));
    for (int i = 0; i < UnusedTable.size(); i++){
//        printf("%9d%9d\n", UnusedTable[i].start, UnusedTable[i].endd);
//        cout<<UnusedTable[i].start;
        row_count = ui->Unused->rowCount();
        ui->Unused->insertRow(row_count);

//        QTableWidgetItem *PID=new QTableWidgetItem();
        QTableWidgetItem *start=new QTableWidgetItem();
        QTableWidgetItem *Mem=new QTableWidgetItem();

//        PID->setText(QString::fromStdString(to_string(UnusedTable[i].JobID)));
        start->setText(QString::fromStdString(to_string(UnusedTable[i].start)));
        Mem->setText(QString::fromStdString(to_string(UnusedTable[i].endd - UnusedTable[i].start + 1)));

//        ui->Unused->setItem(row_count,0,PID);
        ui->Unused->setItem(row_count, 0, start);
        ui->Unused->setItem(row_count,1,Mem);
    }
//    printf("=============================\n");
}

void AssignWin::printHangProg(int i, int t) {
//    cout << t << "时刻: \n";
//    cout << "进程" << prog[i].PID << "到达，空闲内存不足，挂起\n";
//    cout << "进程所需内存" << prog[i].memory << "KB\n";
    int row_count = ui->Events->rowCount();
    ui->Events->insertRow(row_count);
    QTableWidgetItem *PID=new QTableWidgetItem();
    QTableWidgetItem *time=new QTableWidgetItem();
    QTableWidgetItem *Mem=new QTableWidgetItem();
    QTableWidgetItem *eve=new QTableWidgetItem();

    PID->setText(QString::fromStdString(to_string(prog[i].PID)));
    time->setText(QString::fromStdString(to_string(t)));
    Mem->setText(QString::fromStdString(to_string(prog[i].memory)));
    eve->setText(QString::fromStdString("进程挂起"));

    ui->Events->setItem(row_count,0,time);
    ui->Events->setItem(row_count, 1, PID);
    ui->Events->setItem(row_count,2,Mem);
    ui->Events->setItem(row_count,3,eve);

    printUsedTable(t);
    printUnusedTable(t);
}

void AssignWin::printAssign(int i, int t) {
//    cout << t << "时刻: \n";
//    cout << "为进程" << prog[i].PID << "分配内存\n";
//    cout << "分配地址区间为: " << "[" << UsedTable[UsedTable.size() - 1].start << ", " << UsedTable[UsedTable.size() - 1].endd << "]\n";
    int row_count = ui->Events->rowCount();
    ui->Events->insertRow(row_count);
    cout<<row_count<<" ";
    QTableWidgetItem *PID=new QTableWidgetItem();
    QTableWidgetItem *time=new QTableWidgetItem();
    QTableWidgetItem *Mem=new QTableWidgetItem();
    QTableWidgetItem *eve=new QTableWidgetItem();

    PID->setText(QString::fromStdString(to_string(prog[i].PID)));
    time->setText(QString::fromStdString(to_string(t)));
    Mem->setText(QString::fromStdString(to_string(prog[i].memory)));
    eve->setText(QString::fromStdString("分配内存"));

    ui->Events->setItem(row_count,0,time);
    ui->Events->setItem(row_count, 1, PID);
    ui->Events->setItem(row_count,2,Mem);
    ui->Events->setItem(row_count,3,eve);

    printUsedTable(t);
    printUnusedTable(t);
}

void AssignWin::printJointAssign(int i, int t) {
//    cout << t << "时刻: \n";
//    cout << "为进程" << prog[i].PID << "拼接分配内存\n";

    int row_count = ui->Events->rowCount();
    ui->Events->insertRow(row_count);
    QTableWidgetItem *PID=new QTableWidgetItem();
    QTableWidgetItem *time=new QTableWidgetItem();
    QTableWidgetItem *Mem=new QTableWidgetItem();
    QTableWidgetItem *eve=new QTableWidgetItem();

    PID->setText(QString::fromStdString(to_string(prog[i].PID)));
    time->setText(QString::fromStdString(to_string(t)));
    Mem->setText(QString::fromStdString(to_string(prog[i].memory)));
    eve->setText(QString::fromStdString("拼接分配内存"));

    ui->Events->setItem(row_count,0,time);
    ui->Events->setItem(row_count, 1, PID);
    ui->Events->setItem(row_count,2,Mem);
    ui->Events->setItem(row_count,3,eve);

    printUsedTable(t);
    printUnusedTable(t);
}

void AssignWin::printRecover(int i, int t) {
//    cout << t << "时刻: \n";
//    cout << "结束进程" << prog[i].PID << "\n";
//    cout << "回收内存" << prog[i].memory << "KB\n";
    int row_count = ui->Events->rowCount();
    ui->Events->insertRow(row_count);
    QTableWidgetItem *PID=new QTableWidgetItem();
    QTableWidgetItem *time=new QTableWidgetItem();
    QTableWidgetItem *Mem=new QTableWidgetItem();
    QTableWidgetItem *eve=new QTableWidgetItem();

    PID->setText(QString::fromStdString(to_string(prog[i].PID)));
    time->setText(QString::fromStdString(to_string(t)));
    Mem->setText(QString::fromStdString(to_string(prog[i].memory)));
    eve->setText(QString::fromStdString("回收内存"));

    ui->Events->setItem(row_count,0,time);
    ui->Events->setItem(row_count, 1, PID);
    ui->Events->setItem(row_count,2,Mem);
    ui->Events->setItem(row_count,3,eve);


    printUsedTable(t);
    printUnusedTable(t);
}

void AssignWin::printProg() {
    int progNum = prog.size();
    for (int i = 0; i < progNum; i++)
        cout << prog[i].PID << ' ' << prog[i].arrive <<' '<<prog[i].time<< ' ' << prog[i].memory << ' ' << prog[i].state << '\n';
}

// 将回收的内存合并入空闲分区中
void AddToUnused(Unused tmp) {
//    int up = -1, down = -1;			// 记录可能存在的上相邻分区和下相邻分区的索引
    int unusedNum = UnusedTable.size();
    for (int i = 0; i < unusedNum; i++) {
        if (UnusedTable[i].start == tmp.endd + 1) {
            //down = i;
            tmp.endd = UnusedTable[i].endd;
            UnusedTable.erase(UnusedTable.begin() + i);
            break;
        }
    }
    unusedNum = UnusedTable.size();
    for (int i = 0; i < unusedNum; i++) {
        if (UnusedTable[i].endd + 1 == tmp.start) {
            tmp.start = UnusedTable[i].start;
            UnusedTable.erase(UnusedTable.begin() + i);
            break;
        }
    }
    UnusedTable.push_back(tmp);
}

// 对索引为i的进程进行内存拼接分配
void AssignWin::jointAssign(int i, int t) {
    sort(UsedTable.begin() + 1, UsedTable.end(), cmp3);		// 按照地址排序（操作系统进程始终在低128MB
    int usedNum = UsedTable.size();
    for (int j = 1; j < usedNum; j++) {						// 已分配分区
        int m = UsedTable[j].endd - UsedTable[j].start + 1;
        UsedTable[j].start = UsedTable[j - 1].endd + 1;
        UsedTable[j].endd = UsedTable[j].start + m - 1;
    }
    Unused avai = { 0, UsedTable[usedNum - 1].endd + 1,524287 };
    UnusedTable.clear();
    UnusedTable.push_back(avai);

    if (prog[i].memory < unusedMem) {
        prog[i].state = 1;				// 调入内存运行
        Used usedM = { prog[i].PID, UnusedTable[0].start, UnusedTable[0].start - 1 + prog[i].memory };
        unusedMem -= prog[i].memory;
        usedMem += prog[i].memory;
        UsedTable.push_back(usedM);
        UnusedTable[0].start = UnusedTable[0].start + prog[i].memory;
        printJointAssign(i, t);			// 输出内存拼接分配事件
    }
}

// 为进程分配内存
void AssignWin::Assign(int i, int t) {
    // 为刚刚到达的进程分配内存
    if (prog[i].state == 0) {
        if (unusedMem < prog[i].memory) {		// 空闲分区内存总和小于该进程需要的内存，挂起
            prog[i].state = 3;
//            cout << "进程挂起事件\n";
            printHangProg(i, t);
            return;
        }
        else {
            int unusedNum = UnusedTable.size();
            sort(UnusedTable.begin(), UnusedTable.end(), cmp2);
            for (int j = 0; j < unusedNum; j++) {	// 找到最小可以分配给进程的空闲分区
                if (UnusedTable[j].endd - UnusedTable[j].start + 1 >= prog[i].memory) {
                    prog[i].state = 1;
                    Used cntUse = { prog[i].PID, UnusedTable[j].start, UnusedTable[j].start + prog[i].memory - 1 };
                    UsedTable.push_back(cntUse);
                    usedMem += cntUse.endd - cntUse.start + 1;
                    unusedMem -= cntUse.endd - cntUse.start + 1;
                    if (UnusedTable[j].start + prog[i].memory != UnusedTable[j].endd)			// 更新空闲分区表
                        UnusedTable[j].start = UnusedTable[j].start + prog[i].memory;
                    else
                        UnusedTable.erase(UnusedTable.begin() + j);
//                    cout << "进程创建, 内存分配事件\n";
                    printAssign(i, t);			// 输出t时刻为prog[i]进程分配内存
                    break;
                }
            }
            if (prog[i].state == 0) {		// 未找到可分配的空闲分区，考虑拼接
//                cout << "进程创建，拼接分配事件\n";
                jointAssign(i, t);			// 拼接分配
            }
        }
        return;
    }

    // 为挂起的进程分配内存
    if (prog[i].state == 3) {
        int unusedNum = UnusedTable.size();
        sort(UnusedTable.begin(), UnusedTable.end(), cmp2);
        for (int j = 0; j < unusedNum; j++) {	// 找到最小可以分配给进程的空闲分区
            if (UnusedTable[j].endd - UnusedTable[j].start + 1 >= prog[i].memory) {
                prog[i].state = 1;
                Used cntUse = { prog[i].PID, UnusedTable[j].start, UnusedTable[j].start + prog[i].memory - 1 };
                UsedTable.push_back(cntUse);
                usedMem += cntUse.endd - cntUse.start + 1;
                unusedMem -= cntUse.endd - cntUse.start + 1;
                if (UnusedTable[j].start + prog[i].memory != UnusedTable[j].endd)			// 更新空闲分区表
                    UnusedTable[j].start = UnusedTable[j].start + prog[i].memory;
                else
                    UnusedTable.erase(UnusedTable.begin() + j);
//                cout << "进程激活, 内存分配事件\n";
                prog[i].arrive = t;
                prog[i].endtime = t + prog[i].time;
                printAssign(i, t);			// 输出t时刻为prog[i]进程分配内存
            }
        }
        if (prog[i].state == 3) { 		// 需要拼接
//            cout << "进程激活，拼接分配事件\n";
            jointAssign(i, t);
        }
    }
}

// 回收内存
void AssignWin::Recover(int i, int t) {
    int usedNum = UsedTable.size();
    for (int j = 1; j < usedNum; j++) {
        if (UsedTable[j].JobID == prog[i].PID) {
            Unused cnt = UsedTable[j];
            usedMem -= cnt.endd - cnt.start + 1;
            unusedMem += cnt.endd - cnt.start + 1;
            AddToUnused(cnt);							// 将该分区合并入空闲分区中
            UsedTable.erase(UsedTable.begin() + j);
            prog[i].state = 2;
            break;
        }
    }
//    cout << "进程撤销, 内存回收事件\n";
    printRecover(i, t);

    // 判断是否有挂起的进程可以分配内存
    for (int j = 1; j < prog.size(); j++) {
        if (prog[j].state == 3 && unusedMem >= prog[j].memory)
            Assign(i, t);
    }
}

void AssignWin::Partition() {
    printUsedTable(0);
    printUnusedTable(0);
    sort(prog.begin() + 1, prog.end(), cmp1);
    int ProgNum = prog.size();
    int latest = 0;
    for (int i = 1; i < ProgNum; i++) {
        latest = max(latest, prog[i].endtime);
    }
    for (int t = 0; t <= latest; t++) {
        // 判断时刻t是否有进程到达
        for (int i = 1; i < ProgNum; i++)
            if (prog[i].arrive == t && !prog[i].state)	// 有进程到达，为其分配内存
                Assign(i, t);

        // 判断时刻t是否有进程结束
        for (int i = 1; i < ProgNum; i++) {
            if (prog[i].endtime == t && prog[i].state == 1) {		// 有进程结束，回收内存
                Recover(i, t);
            }
        }
    }
}
