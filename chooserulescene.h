#ifndef CHOOSERULESCENE_H
#define CHOOSERULESCENE_H

#include <QMainWindow>
#include <QPainter>
#include <QPixmap>
#include <QTimer>
#include "config.h"
#include "mypushbutton.h"

/***选择玩法界面***/
class ChooseRuleScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseRuleScene(QWidget *parent = nullptr);

    //绘图事件
    void paintEvent(QPaintEvent *);

signals:
    //点击返回按钮backBtn自定义信号
    void ruleSeceneBack();

    void chooseRule0();
    void chooseRule1();
};

#endif // CHOOSERULESCENE_H
