#ifndef ITEM_H
#define ITEM_H

#include <QPoint>
#include <QVector>
#include "QVector"
#include "QPainter"



enum SHAPE {
    SHAPE1=0,   //“一”字形
    SHAPE2,     //正方形
    SHAPE3_1,   //“之”字形——左
    SHAPE3_2,   //“之”字形——右
    SHAPE4_1,   //“L”形左
    SHAPE4_2,   //“L”形右
    SHAPE5,     //“凸”字形
};

class Item          //正在下落的方块，已经下落的方块，下一个出现的方块，都是Item类型
{
public:
    Item(){};
    Item(SHAPE,int s=0);
    ~Item(void);

    void InitNew();  //随机产生一个初始方块
    void InitItem(SHAPE t,int dir);     //对方块重新初始化
    void InitWill(const Item& ,const Item&);        //产生一个方块，同时要显示即将下落的位置
    void ChangeDir();   //改变方向
    void Draw(QPainter& painter,int,int,int,int);
    void Move(int x,int y); //移动x,y
    void MoveTo(int x,int y);   //移动到x,y
    void addPoints(QVector<QPoint> & points);   //在已经落下的方块里加入刚刚落下的方块
    void MoveDown(int row,int n);   //将已经落下的方块row以上的全部下落y行
    void DelRow(int row);   //移除已经满掉的这一行的全部格子

public:
    QVector<QPoint> mpoints;    //包含的点的坐标
    QPoint mpos;    //确定正在下落的方块的位置
    SHAPE t;    //方块的形状
    int dir;    //方块的方向
};

#endif // ITEM_H
