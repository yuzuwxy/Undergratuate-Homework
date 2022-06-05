#ifndef ASSIGNWIN_H
#define ASSIGNWIN_H

#include <QWidget>
#include "structure.h"

namespace Ui {
class AssignWin;
}

class AssignWin : public QWidget
{
    Q_OBJECT

public:
    explicit AssignWin(QWidget *parent = nullptr);
    ~AssignWin();

    void printUsedTable(int t);
    void printUnusedTable(int t);
    void Partition();

    void Recover(int ,int);
    void Assign(int i, int t);
    void jointAssign(int i, int t);
    void printProg();
    void printRecover(int i, int t);
    void printJointAssign(int i, int t);
    void printAssign(int i, int t);
    void printHangProg(int i, int t);



private:
    Ui::AssignWin *ui;

};

#endif // ASSIGNWIN_H
