#include "chooserulescene.h"

ChooseRuleScene::ChooseRuleScene(QWidget *parent)
    : QMainWindow{parent}
{
    //设置固定尺寸
    this->setFixedSize(WINDOWWIDTH,WINDOWHEIGHT);
    //设置标题
    this->setWindowTitle("选择游戏规则");
    //设置图标
    this->setWindowIcon(QIcon(":/icon/res/icon/mainwindowicon.png"));

    //返回按钮
    MyPushButton * backBtn = new MyPushButton(this);
    backBtn->setBtnImg(":/btn/res/btn/back.png",":/btn/res/btn/back2.png");
    backBtn->setRank(MyPushButton::Rank_3);
    backBtn->setBtnArea(this->width(),this->height());

    //跑的快按钮
    MyPushButton * rule1Btn = new MyPushButton(this);
    rule1Btn->setBtnImg(":/btn/res/btn/rule1_1.png",":/btn/res/btn/rule1_2.png");
    rule1Btn->setRank(MyPushButton::Rank_1);
    rule1Btn->setBtnArea(this->width(),this->height());

    //二十一点模式按钮
    MyPushButton * rule2Btn = new MyPushButton(this);
    rule2Btn->setBtnImg(":/btn/res/btn/rule2_1.png",":/btn/res/btn/rule2_2.png");
    rule2Btn->setRank(MyPushButton::Rank_2);
    rule2Btn->setBtnArea(this->width(),this->height());

    connect(rule1Btn,&MyPushButton::clicked,[=](){
        //延时 后发送一个点击了返回按钮的信号
        QTimer::singleShot(500,this,[=](){
            emit this->chooseRule0();
        });
    });
    connect(rule2Btn,&MyPushButton::clicked,[=](){
        //延时 后发送一个点击了返回按钮的信号
        QTimer::singleShot(500,this,[=](){
            emit this->chooseRule1();
        });
    });
    //返回按钮功能
    connect(backBtn,&MyPushButton::clicked,[=](){
        //延时 后发送一个点击了返回按钮的信号
        QTimer::singleShot(500,this,[=](){
            emit this->ruleSeceneBack();
        });
    });
}

void ChooseRuleScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/scene/res/background/menuscene.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}
