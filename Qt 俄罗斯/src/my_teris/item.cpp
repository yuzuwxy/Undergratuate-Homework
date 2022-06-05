#include "item.h"
#include "mainwindow.h"
#include "gamearea.h"
#include "nextarea.h"
#include "QRandomGenerator"
#include <QTime>
#include <QPainter>

Item::Item(SHAPE t, int dir)
{
    mpos=QPoint(0,0);

    InitItem(t,dir);
}

Item::~Item(void) {

}


void Item::InitNew(){
    SHAPE t=(SHAPE)(QRandomGenerator::global()->bounded(999999)%7);
    int dir=QRandomGenerator::global()->bounded(999999)%4;
    InitItem(t,dir);
    //qDebug()<<t<<' '<<dir;
}

void Item::InitItem(SHAPE _t, int _dir)
{
    mpoints.clear();

    t=_t;
    dir=_dir;
    switch(t) {
    case SHAPE1 :
    {
        if(dir==0||dir==2) {
            for(int i=0;i<4;i++) mpoints.append(mpos+QPoint(0,i));
        }
        else {
            for(int i=0;i<4;i++) mpoints.append(mpos+QPoint(i,0));
        }
        break;
    }
    case SHAPE2 :
    {
        for(int i=0;i<2;i++) {
            for(int j=0;j<2;j++)
                mpoints.append(mpos+QPoint(i,j));
        }
        break;
    }
    case SHAPE3_1:
    {
        if(dir==0||dir==2) {
            mpoints.append(mpos+QPoint(0,0));
            mpoints.append(mpos+QPoint(1,0));
            mpoints.append(mpos+QPoint(1,1));
            mpoints.append(mpos+QPoint(2,1));
        }
        if(dir==1||dir==3) {
            mpoints.append(mpos+QPoint(0,1));
            mpoints.append(mpos+QPoint(0,2));
            mpoints.append(mpos+QPoint(1,0));
            mpoints.append(mpos+QPoint(1,1));
        }
        break;
    }
    case SHAPE3_2:
    {
        if(dir==0||dir==2){
            mpoints.append(mpos+QPoint(1,0));
            mpoints.append(mpos+QPoint(2,0));
            mpoints.append(mpos+QPoint(0,1));
            mpoints.append(mpos+QPoint(1,1));
        }
        else {
            mpoints.append(mpos+QPoint(0,0));
            mpoints.append(mpos+QPoint(0,1));
            mpoints.append(mpos+QPoint(1,1));
            mpoints.append(mpos+QPoint(1,2));
        }
        break;
    }
    case SHAPE4_1:
    {
        if(dir==0){
            mpoints.append(mpos+QPoint(0,0));
            mpoints.append(mpos+QPoint(0,1));
            mpoints.append(mpos+QPoint(0,2));
            mpoints.append(mpos+QPoint(1,2));
        }
        if(dir==1) {
            mpoints.append(mpos+QPoint(2,0));
            mpoints.append(mpos+QPoint(0,1));
            mpoints.append(mpos+QPoint(1,1));
            mpoints.append(mpos+QPoint(2,1));
        }
        if(dir==2) {
            mpoints.append(mpos+QPoint(0,0));
            mpoints.append(mpos+QPoint(1,0));
            mpoints.append(mpos+QPoint(1,1));
            mpoints.append(mpos+QPoint(1,2));
        }
        if(dir==3) {
            mpoints.append(mpos+QPoint(0,0));
            mpoints.append(mpos+QPoint(1,0));
            mpoints.append(mpos+QPoint(2,0));
            mpoints.append(mpos+QPoint(2,1));
        }
        break;
    }
    case SHAPE4_2:
    {
        if(dir==0){
            mpoints.append(mpos+QPoint(0,2));
            mpoints.append(mpos+QPoint(1,0));
            mpoints.append(mpos+QPoint(1,1));
            mpoints.append(mpos+QPoint(1,2));
        }
        if(dir==1){
            mpoints.append(mpos+QPoint(0,0));
            mpoints.append(mpos+QPoint(1,0));
            mpoints.append(mpos+QPoint(2,0));
            mpoints.append(mpos+QPoint(2,1));
        }
        if(dir==2){
            mpoints.append(mpos+QPoint(0,0));
            mpoints.append(mpos+QPoint(0,1));
            mpoints.append(mpos+QPoint(1,1));
            mpoints.append(mpos+QPoint(2,1));
        }
        if(dir==3){
            mpoints.append(mpos+QPoint(0,0));
            mpoints.append(mpos+QPoint(0,1));
            mpoints.append(mpos+QPoint(0,2));
            mpoints.append(mpos+QPoint(1,0));
        }
        break;
    }
    case SHAPE5:
    {
        if(dir==0) {
            mpoints.append(mpos+QPoint(0,1));
            mpoints.append(mpos+QPoint(1,0));
            mpoints.append(mpos+QPoint(1,1));
            mpoints.append(mpos+QPoint(2,1));
        }
        if(dir==1){
            mpoints.append(mpos+QPoint(0,1));
            mpoints.append(mpos+QPoint(1,0));
            mpoints.append(mpos+QPoint(1,1));
            mpoints.append(mpos+QPoint(1,2));
        }
        if(dir==2) {
            mpoints.append(mpos+QPoint(0,0));
            mpoints.append(mpos+QPoint(1,0));
            mpoints.append(mpos+QPoint(2,0));
            mpoints.append(mpos+QPoint(1,1));
        }
        if(dir==3) {
            mpoints.append(mpos+QPoint(0,0));
            mpoints.append(mpos+QPoint(0,1));
            mpoints.append(mpos+QPoint(0,2));
            mpoints.append(mpos+QPoint(1,1));
        }
        break;
    }
    default:
        break;
    }
}

void Item::InitWill(const Item & Cur,const Item & Fixed)
{
    this->mpos=Cur.mpos;
    this->t=Cur.t;
    this->dir=Cur.dir;
    this->mpoints=Cur.mpoints;
    while(1) {
        //qDebug()<<1;
        Move(0,1);
        bool flag=0;
        for(int i=0;i<mpoints.size();i++) {
            if(Fixed.mpoints.contains(mpoints[i])||mpoints[i].y()>20) {
                Move(0,-1);
                flag=1;
                break;
            }
        }
        if(flag) break;
    }
    //qDebug()<<mpos.x();
}

void Item::ChangeDir(){
    dir=(dir+1)%4;
    InitItem(t,dir);
}

void Item::Draw(QPainter & painter, int sx, int sy, int w, int h){
    for(int i=0;i<mpoints.size();i++){
        QPoint temp=mpoints[i];
        painter.drawRect(sx+temp.x()*w,sy+temp.y()*h,w,h);
    }
}

void Item::Move(int x,int y) {
    for(int i=0;i<mpoints.size();i++){
        int tempx=mpoints[i].x()+x;
        int tempy=mpoints[i].y()+y;
        mpoints[i].setX(tempx);
        mpoints[i].setY(tempy);
    }
    mpos+=QPoint(x,y);
}

void Item::MoveTo(int x, int y){
    for(int i=0;i<mpoints.size();i++) {
        int tempx=mpoints[i].x()+x-mpos.x();
        int tempy=mpoints[i].y()+y-mpos.y();
        mpoints[i].setX(tempx);
        mpoints[i].setY(tempy);
    }
    mpos=QPoint(x,y);
}

void Item::addPoints(QVector<QPoint> &points){
    for(int i=0;i<points.size();i++) {
        if(!mpoints.contains(points[i]))
            mpoints.append(points[i]);
    }
}

void Item::MoveDown(int row, int n){
    for(int i=0;i<mpoints.size();i++) {
        if(mpoints[i].y()<row) {
            int tempy=mpoints[i].y()+n;
            mpoints[i].setY(tempy);
        }
    }
}

void Item::DelRow(int row){
    QVector<QPoint> temp;
    for(int i=0;i<mpoints.size();i++) {
        if(mpoints[i].y()!=row) {
            temp.append(mpoints[i]);
        }
    }
    mpoints=temp;
}
