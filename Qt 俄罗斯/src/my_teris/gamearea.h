#ifndef GAMEAREA_H
#define GAMEAREA_H

#include <QWidget>
#include <time.h>
#include <QTimer>
#include <QPainter>
#include <QDebug>
#include "mainwindow.h"
#include "nextarea.h"
#include "item.h"

class GameArea : public QWidget
{
    Q_OBJECT
public:
    explicit GameArea(QWidget *parent = nullptr);

    void DrawBkg();         //背景
    void DrawCurItem();     //正在下落的方块
    void DrawFixedItem();   //已经落下的方块
    void DrawWillItem();

    void NewGame(); //新游戏初始化
    void KeyPressed(int k);

    //bool Will_Coin();   //即将落下的位置左右移动后有重合
    bool HitSide();         //检查是否到达边界
    bool HitBottom();
    bool HitTop();          //到达顶部游戏结束
    void AddToFixed();      //把刚刚落下的这块加入到已经落下的方块里
    void DelFullRow();      //删除一整行

    int GetTimer(int level);    //通过关卡设置下落速度

signals:
    void NextItem(SHAPE t,int dir);         //当前方块出现的时候发信号改变左边下一个方块的图案
    void UpdateScores(int scores);          //消除一行就把7
    void UpdateLevel(int level);

private:
    Item Cur_Item;
    Item Next_Item;
    Item Fixed_Item;
    Item Will_Item;
    int scores;
    int level;
    int timer;      //计时器，确定下落速度

    bool flag;

protected:
    void paintEvent(QPaintEvent *);
    void timerEvent(QTimerEvent *);

};

#endif // GAMEAREA_H
