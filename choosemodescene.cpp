#include "choosemodescene.h"
#include "config.h"
#include "mypushbutton.h"

#include <QPainter>
#include <QPixmap>
#include <QTimer>

ChooseModeScene::ChooseModeScene(QWidget *parent)
    : QMainWindow{parent}
{
    //设置固定尺寸
    this->setFixedSize(WINDOWWIDTH,WINDOWHEIGHT);
    //设置标题
    this->setWindowTitle("选择游戏模式");
    //设置图标
    this->setWindowIcon(QIcon(":/icon/res/icon/mainwindowicon.png"));

    //返回按钮
    MyPushButton * backBtn = new MyPushButton(this);
    backBtn->setBtnImg(":/btn/res/btn/back.png",":/btn/res/btn/back2.png");
    backBtn->setRank(MyPushButton::Rank_3);
    backBtn->setBtnArea(this->width(),this->height());

    //单人模式按钮
    MyPushButton * singleBtn = new MyPushButton(this);
    singleBtn->setBtnImg(":/btn/res/btn/single.png",":/btn/res/btn/single2.png");
    singleBtn->setRank(MyPushButton::Rank_1);
    singleBtn->setBtnArea(this->width(),this->height());

    //局域网联机模式按钮
    MyPushButton * onlineBtn = new MyPushButton(this);
    onlineBtn->setBtnImg(":/btn/res/btn/online.png",":/btn/res/btn/online2.png");
    onlineBtn->setRank(MyPushButton::Rank_2);
    onlineBtn->setBtnArea(this->width(),this->height());

    connect(singleBtn,&MyPushButton::clicked,[=](){
        //延时 后发送一个点击了返回按钮的信号
        QTimer::singleShot(500,this,[=](){
            emit this->chooseMode0();
        });
    });
    connect(onlineBtn,&MyPushButton::clicked,[=](){
        //延时 后发送一个点击了返回按钮的信号
        QTimer::singleShot(500,this,[=](){
            emit this->chooseMode1();
        });
    });
    //返回按钮功能
    connect(backBtn,&MyPushButton::clicked,[=](){
        //延时 后发送一个点击了返回按钮的信号
        QTimer::singleShot(500,this,[=](){
            emit this->chooseSeceneBack();
        });
    });
}

void ChooseModeScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/scene/res/background/modescene.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //加载标题 未设置
}
