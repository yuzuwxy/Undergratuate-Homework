#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

protected:
    //键盘事件是对mainwindow的
    void keyPressEvent(QKeyEvent *e);        //忘了消息对话框咋用

public slots:
    //两个槽函数，更新分数和关卡，是两个widget的，得从mainwindow里过一下
    void slotupdatescores(int CurScore);
    void slotupdatelevel(int CurLevel);
};
#endif // MAINWINDOW_H
