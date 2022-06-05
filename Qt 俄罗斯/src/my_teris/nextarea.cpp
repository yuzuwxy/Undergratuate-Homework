#include "nextarea.h"
#include "QPainter"
#include <QDebug>

NextArea::NextArea(QWidget *parent) : QWidget(parent)
{
    setFixedSize(260,260);
}

void NextArea::paintEvent(QPaintEvent * event) {       //也许应该不要参数也可以叭，要了再加
    QPainter p(this);
    p.setBrush(QColor(249,166,171));
    p.setPen(QPen(QColor(Qt::black),1));

    nItem.Draw(p,20,80,30,30);

    update();
}

void NextArea::slotNextRect(SHAPE t,int dir) {
    nItem.InitItem(t,dir);
}
