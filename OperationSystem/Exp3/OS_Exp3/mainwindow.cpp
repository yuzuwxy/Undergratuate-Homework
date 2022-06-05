#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "assignwin.h"

extern vector<Progress> prog;
extern vector<Progress> hangProg;
extern vector<Unused> UnusedTable;
extern vector<Used> UsedTable;

//extern int usedMem = 131072;
//extern int unusedMem = 383216;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("动态分区分配模拟");

    connect(ui->AddProg, &QPushButton::released,this,&MainWindow::AddProg);
    connect(ui->CreateRand, &QPushButton::released, this, &MainWindow::CreateRand);
    connect(ui->Clear, &QPushButton::released, this, &MainWindow::Clear);
    connect(ui->ok, &QPushButton::released, this, &MainWindow::Assigh);

    ui->ProgList->setColumnCount(4);
    ui->ProgList->horizontalHeader()->setStretchLastSection(true);
    QStringList header;
    header<<tr("PID")<<tr("到达时间")<<tr("运行时间")<<tr("占用内存(KB)");
    ui->ProgList->setHorizontalHeaderLabels(header);

    this->setStyleSheet("QLineEdit{font:20px}");
    ui->ProgList->setFont(QFont("song", 12));

    srand((unsigned int)time(NULL));

    Progress OS;		// 始终存在的操作系统进程
    OS.PID = 0;
    OS.arrive = 0;
    OS.time = 0;
    OS.state = 1;
    OS.memory = 131072;
    OS.endtime = 0;
    prog.push_back(OS);

    int row_count = ui->ProgList->rowCount();
    ui->ProgList->insertRow(row_count);

    QTableWidgetItem *PID=new QTableWidgetItem();
    QTableWidgetItem *arrive=new QTableWidgetItem();
    QTableWidgetItem *time=new QTableWidgetItem();
    QTableWidgetItem *Mem=new QTableWidgetItem();

    PID->setText(QString::fromStdString(to_string(OS.PID)));
    arrive->setText(QString::fromStdString(to_string(OS.arrive)));
    time->setText(QString::fromStdString(to_string(OS.time)));
    Mem->setText(QString::fromStdString(to_string(OS.memory) +"(操作系统进程)"));

    ui->ProgList->setItem(row_count,0,PID);
    ui->ProgList->setItem(row_count,1,arrive);
    ui->ProgList->setItem(row_count,2,time);
    ui->ProgList->setItem(row_count,3,Mem);

    Used OS_MEM = { 0, 0, 131071 };				// 操作系统进程永不回收
    UsedTable.push_back(OS_MEM);

    Unused Avai = { 0, 131072,524287 };			// 初始空闲分区
    UnusedTable.push_back(Avai);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::AddProg(){
    Progress newOne;
    newOne.PID = ui->PID->text().toInt();
    newOne.time = ui->Time->text().toInt();
    newOne.memory = ui->Memeory->text().toInt();
    newOne.arrive = ui->Arrive->text().toInt();
    prog.push_back(newOne);
    int row_count = ui->ProgList->rowCount();
    ui->ProgList->insertRow(row_count);

    QTableWidgetItem *PID=new QTableWidgetItem();
    QTableWidgetItem *arrive=new QTableWidgetItem();
    QTableWidgetItem *time=new QTableWidgetItem();
    QTableWidgetItem *Mem=new QTableWidgetItem();

    PID->setText(QString::fromStdString(to_string(newOne.PID)));
    arrive->setText(QString::fromStdString(to_string(newOne.arrive)));
    time->setText(QString::fromStdString(to_string(newOne.time)));
    Mem->setText(QString::fromStdString(to_string(newOne.memory)));

    ui->ProgList->setItem(row_count,0,PID);
    ui->ProgList->setItem(row_count,1,arrive);
    ui->ProgList->setItem(row_count,2,time);
    ui->ProgList->setItem(row_count,3,Mem);
}

void MainWindow::CreateRand(){
    int base = prog[prog.size()-1].PID;
    for (int i = 1; i <= 10; i++) {
        Progress newOne;
        newOne.PID = base + i;
        newOne.arrive = rand() % 100;			// 随机生成的进程到达时间为[0, 100)以内的随机数
        newOne.time = rand() % 30 + 1;			// 运行时间为[1, 30]之间的随机数
        newOne.memory = rand() % 393216 + 1;	// 可分配内存最大值为393216KB
        newOne.endtime = newOne.arrive + newOne.time;
        int row_count = ui->ProgList->rowCount();
        ui->ProgList->insertRow(row_count);

        QTableWidgetItem *PID=new QTableWidgetItem();
        QTableWidgetItem *arrive=new QTableWidgetItem();
        QTableWidgetItem *time=new QTableWidgetItem();
        QTableWidgetItem *Mem=new QTableWidgetItem();

        PID->setText(QString::fromStdString(to_string(newOne.PID)));
        arrive->setText(QString::fromStdString(to_string(newOne.arrive)));
        time->setText(QString::fromStdString(to_string(newOne.time)));
        Mem->setText(QString::fromStdString(to_string(newOne.memory)));

        ui->ProgList->setItem(row_count,0,PID);
        ui->ProgList->setItem(row_count,1,arrive);
        ui->ProgList->setItem(row_count,2,time);
        ui->ProgList->setItem(row_count,3,Mem);
        prog.push_back(newOne);
    }
}

void MainWindow::Clear() {
    for(int i=1;i<prog.size();i++) {
        prog.erase(prog.begin()+i);
    }
    ui->ProgList->setRowCount(0);
    int row_count = ui->ProgList->rowCount();
    ui->ProgList->insertRow(row_count);

    QTableWidgetItem *PID=new QTableWidgetItem();
    QTableWidgetItem *arrive=new QTableWidgetItem();
    QTableWidgetItem *time=new QTableWidgetItem();
    QTableWidgetItem *Mem=new QTableWidgetItem();

    PID->setText(QString::fromStdString(to_string(prog[0].PID)));
    arrive->setText(QString::fromStdString(to_string(prog[0].arrive)));
    time->setText(QString::fromStdString(to_string(prog[0].time)));
    Mem->setText(QString::fromStdString(to_string(prog[0].memory) +"(操作系统进程)"));

    ui->ProgList->setItem(row_count,0,PID);
    ui->ProgList->setItem(row_count,1,arrive);
    ui->ProgList->setItem(row_count,2,time);
    ui->ProgList->setItem(row_count,3,Mem);

    Used OS_MEM = { 0, 0, 131071 };				// 操作系统进程永不回收
    UsedTable.push_back(OS_MEM);

    Unused Avai = { 0, 131072,524287 };			// 初始空闲分区
    UnusedTable.push_back(Avai);
}

void MainWindow::Assigh(){
    assignWin = new AssignWin();
    assignWin->show();
    assignWin->Partition();
}
