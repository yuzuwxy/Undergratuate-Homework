#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QFile>
#include <QMessageBox>
#include <QDebug>
#include "assignwin.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

//    void WriteInto(Progress newOne);

private:
    Ui::MainWindow *ui;
    AssignWin *assignWin;

public slots:
    void AddProg();
    void CreateRand();
    void Clear();
    void Assigh();

//    void assignToMain();
};
#endif // MAINWINDOW_H
