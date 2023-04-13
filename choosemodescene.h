#ifndef CHOOSEMODESCENE_H
#define CHOOSEMODESCENE_H

#include <QMainWindow>

/***选择模式界面***/
class ChooseModeScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseModeScene(QWidget *parent = nullptr);

    //绘图事件
    void paintEvent(QPaintEvent *);

signals:
    //点击返回按钮backBtn自定义信号
    void chooseSeceneBack();

    //选择模式信号
    void chooseMode0();
    void chooseMode1();

};

#endif // CHOOSEMODESCENE_H
