#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QKeyEvent"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowIcon(QIcon("app.ico"));
    setWindowTitle("Teris");

    setFixedSize(930,880);

    connect(ui->GameArea,&GameArea::NextItem,ui->Shape,&NextArea::slotNextRect);
    connect(ui->GameArea,&GameArea::UpdateLevel,this,&MainWindow::slotupdatelevel);
    connect(ui->GameArea,&GameArea::UpdateScores,this,&MainWindow::slotupdatescores);

    ui->GameArea->NewGame();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent * e){
    //qDebug()<<"我按键盘啦！！";
    ui->GameArea->KeyPressed(e->key());
    QMainWindow::keyPressEvent(e);      //放在这一直监测键盘事件的意思吧应该是……？知道单词的意思这也看不懂啊
}

void MainWindow::slotupdatelevel(int CurLevel) {
    ui->Level->setText(QString::number(CurLevel));
}

void MainWindow::slotupdatescores(int CurScores) {
    ui->Scores->setText(QString::number(CurScores));
}
