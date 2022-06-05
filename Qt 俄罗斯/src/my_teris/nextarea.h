#ifndef NEXTAREA_H
#define NEXTAREA_H

#include <QWidget>
#include "item.h"
#include <QPainter>

class NextArea : public QWidget
{
    Q_OBJECT
public:
    explicit NextArea(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);

public slots:
    //当前这个一出现，就发出信号改变这个里面的块
    void slotNextRect(SHAPE t,int dir);

private:
    Item nItem;

};

#endif // NEXTAREA_H
