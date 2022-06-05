#include "mainwindow.h"
#include "assignwin.h"

#include <QApplication>

vector<Progress> prog;
vector<Progress> hangProg;
vector<Unused> UnusedTable;
vector<Used> UsedTable;

//int usedMem = 131072;
//int unusedMem = 383216;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
