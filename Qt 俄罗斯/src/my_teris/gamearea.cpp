#include "gamearea.h"

#include <QString>
#include <qstring.h>
#include <QTime>
#include <time.h>
#include <QTimerEvent>
#include <QMessageBox>
#include <qmessagebox.h>
#include <QKeyEvent>

#define GAMECOLUMN 10
#define GAMEROW 20
#define WIDTH 40
#define HEIGHT 40

#define DEFAULT (GAMECOLUMN/2)

GameArea::GameArea(QWidget *parent) : QWidget(parent)
{
    scores=0;
    level=1;

    setMinimumSize(500,880);
}

void GameArea::DrawBkg()
{
    QPainter painter(this);

    painter.setBrush(QColor(141,117,115));
    painter.setPen(Qt::NoPen);

    painter.drawRect(0,0,480,40);
    painter.drawRect(0,0,40,880);
    painter.drawRect(440,0,40,880);
    painter.drawRect(0,840,480,40);
}

void GameArea::DrawCurItem(){
    QPainter p(this);
    p.setBrush(QColor(249,166,171));
    p.setPen(QPen(QColor(Qt::black),1));

    Cur_Item.Draw(p,0,0,WIDTH,HEIGHT);
}

void GameArea::DrawFixedItem(){
    QPainter p(this);
    p.setBrush(QColor(103,62,55));
    p.setPen(QPen(QColor(Qt::black),1));

    Fixed_Item.Draw(p,0,0,WIDTH,HEIGHT);
}

void GameArea::DrawWillItem(){
    QPainter p(this);
    p.setBrush(QColor(221,185,209));
    p.setPen(1);
    p.setBrush(QBrush(Qt::Dense7Pattern));
    Will_Item.Draw(p,0,0,WIDTH,HEIGHT);
}

void GameArea::NewGame(){       //对一系列值进行初始化
    Fixed_Item.mpoints.clear();

    Cur_Item.InitNew();
    Cur_Item.MoveTo(DEFAULT,1);

    Will_Item.InitWill(Cur_Item,Fixed_Item);

    Next_Item.InitNew();
    emit NextItem(Next_Item.t,Next_Item.dir);

    scores=0;
    level=1;
    emit UpdateLevel(level);
    emit UpdateScores(scores);

    timer=startTimer(GetTimer(level));
}

void GameArea::KeyPressed(int k){
    //是从mainwindow里调用过来的
    int x=0,y=0;
    //int flag=0;
    //qDebug()<<(int)Qt::Key_Enter;
    switch (k) {
    case Qt::Key_Left:
    {
        x=-1;
        break;  //这里出去搞叭
    }
    case Qt::Key_Right:
    {
        x=1;
        break;
    }
    case Qt::Key_Down:
    {
        y=1;
        break;
    }
    case Qt::Key_Up:
    {
        if(HitBottom()) break;
        Cur_Item.ChangeDir();
        Will_Item.InitWill(Cur_Item,Fixed_Item);
        while(HitSide()||HitBottom()) {
            Cur_Item.ChangeDir();
            Will_Item.InitWill(Cur_Item,Fixed_Item);
        }
        return;
    }
    //那就不搞直接下落了
    case Qt::Key_Space:
    {
        killTimer(timer);
        if(flag) return;
        int ret=QMessageBox::question(NULL,"Pause","要回到游戏吗？",QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
        if(ret==QMessageBox::Yes)
            timer=startTimer(GetTimer(level));
        else exit(0);
    }
    }

    //没有重载=，如果搞一个temp出来试试能不能移就有点麻烦了
    Cur_Item.Move(x,y);
    //Will_Item.Move(x,0);
    if(HitSide()||HitBottom()) {
        Cur_Item.Move(-x,-y);
//        Will_Item.Move(-x,0);
    }

    Will_Item.InitWill(Cur_Item,Fixed_Item);
}

//确实如果边框和方块的长宽不等就会很麻烦，看起来也有点奇怪
bool GameArea::HitTop(){
    for(int i=0;i<Fixed_Item.mpoints.size();i++) {
        QPoint temp=Fixed_Item.mpoints[i];
        if(temp.y()<=1) return true;
    }
    return false;
}

bool GameArea::HitSide(){
    for(int i=0;i<Cur_Item.mpoints.size();i++) {
        QPoint temp=Cur_Item.mpoints[i];
        if(temp.x()<=0||temp.x()>GAMECOLUMN){
            //这里边界情况有点迷糊，说不定到时候要改
            return true;
        }
    }
    return false;
}

bool GameArea::HitBottom(){
    for(int i=0;i<Cur_Item.mpoints.size();i++) {
        if(Fixed_Item.mpoints.contains(Cur_Item.mpoints[i])) return true;
        if(Cur_Item.mpoints[i].y()>GAMEROW) return true;
    }
    return false;
}

void GameArea::AddToFixed(){
    //这个函数就相当于是接口了，加点是Item里的操作
    Fixed_Item.addPoints(Cur_Item.mpoints);
}

void GameArea::DelFullRow() {
    int delrow[25]={0};
    for(int i=0;i<Fixed_Item.mpoints.size();i++) {
        QPoint temp=Fixed_Item.mpoints[i];
        delrow[temp.y()]++;
    }

    int addscore=0;
    for(int i=0;i<=20;i++) {
        if(delrow[i]==10) {
            Fixed_Item.DelRow(i);
            Fixed_Item.MoveDown(i,1);
            addscore++;
        }
    }

    scores+=addscore*addscore;

    emit UpdateScores(scores);

    if(scores>=level*10) {
        level++;

        killTimer(timer);
        timer=startTimer(GetTimer(level));  //加快定时器
        emit UpdateLevel(level);
    }
}

int GameArea::GetTimer(int level) {
    if(level>=5) return 200;
    else return 1000-(level-1)*200;
}

void GameArea::paintEvent(QPaintEvent *){
    //绘画事件，有变化就要更新
    DrawBkg();
    DrawCurItem();
    DrawFixedItem();
    DrawWillItem();

    update();
}

void GameArea::timerEvent(QTimerEvent *Timer){
    //在这个时间内，要对方块进行移动
    //qDebug()<<Timer->timerId();
    if(Timer->timerId() == timer){
        Cur_Item.Move(0,1);
        if(HitBottom()){
            Cur_Item.Move(0,-1);     //先移过去，如果发现已经不能移了，就回来
            AddToFixed();
            DelFullRow();   //落下去就判断能不能消去一行

            if(HitTop()){
                killTimer(timer);
                int ret=QMessageBox::question(NULL, "GAME OVER", "GAME OVER!\n再来一局吗？", QMessageBox::Yes|QMessageBox::No , QMessageBox::Yes);
                if(ret==QMessageBox::Yes) {
                    NewGame();
                    return;
                }
                else exit(0);
            }

            Cur_Item=Next_Item;
            Cur_Item.MoveTo(DEFAULT,1);     //感觉我的坐标有一点混乱呢

            Will_Item.InitWill(Cur_Item,Fixed_Item);

            Next_Item.InitNew();
            emit NextItem(Next_Item.t,Next_Item.dir);
        }
    }
}
//好多函数，好像是完了
