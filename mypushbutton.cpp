#include "mypushbutton.h"

#include <QDebug>
#include <QPropertyAnimation>
#include <QPushButton>
#include <QMouseEvent>
#include <QSound>
#include <QTimer>

//定义和声明不能同时出现默认参数
MyPushButton::MyPushButton(QWidget *parent) : QPushButton(parent)
{
    //默认构造设定父类
}

void MyPushButton::setBtnImg(QString normalImg, QString pressImg)
{
    this->normalPath = normalImg;
    this->pressPath = pressImg;

    //创建QPixmap对象
    QPixmap pix;
    bool ret = pix.load(this->normalPath);
    if(!ret){
        QString str = QString("路径%1图标加载失败！").arg(this->normalPath);
        qDebug() << str;
    }

    /*特殊形状图片按钮*/
    //设置按钮固定尺寸
    this->setFixedSize(pix.width(),pix.height());
    //设置不规则样式 边框透明去除
    this->setStyleSheet("QPushButton{border:0px;}");
    //设置图标
    this->setIcon(pix);
    //设置图标大小
    this->setIconSize(QSize(pix.width(),pix.height()));
}

void MyPushButton::zoom1()
{
    //创建动画对象
    QPropertyAnimation * animation = new QPropertyAnimation(this,"geometry");
    //设置动画间隔
    animation->setDuration(200);
    //设置起始位置
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //设置结束位置 下沉3像素
    animation->setEndValue(QRect(this->x(),this->y()+3,this->width(),this->height()));
    //设置动画曲线
    animation->setEasingCurve(QEasingCurve::Linear);

    //执行动画
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void MyPushButton::zoom2()
{
    //创建动画对象
    QPropertyAnimation * animation = new QPropertyAnimation(this,"geometry");
    //设置动画间隔
    animation->setDuration(200);
    //设置起始位置
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //设置结束位置 上升3像素
    animation->setEndValue(QRect(this->x(),this->y()-3,this->width(),this->height()));
    //设置动画曲线
    animation->setEasingCurve(QEasingCurve::Linear);

    //执行动画
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void MyPushButton::mousePressEvent(QMouseEvent *e)
{
    //按下路径不为空说明要切换路径

    //设置播放音效
    if(m_type == TYPE_Main){
        clicksound->play();
    }

    if(this->pressPath != "")
    {
        //创建QPixmap对象
        QPixmap pix;
        bool ret = pix.load(this->pressPath);
        if(!ret){
            QString str = QString("路径%1图标加载失败！").arg(this->pressPath);
            qDebug() << str;
        }

        /*特殊形状图片按钮*/
        //设置按钮固定尺寸
        this->setFixedSize(pix.width(),pix.height());
        //设置不规则样式 边框透明去除
        this->setStyleSheet("QPushButton{border:0px;}");
        //设置图标
        this->setIcon(pix);
        //设置图标大小
        this->setIconSize(QSize(pix.width(),pix.height()));
    }

    //其他事情交给父类处理
    QPushButton::mousePressEvent(e);
}

void MyPushButton::mouseReleaseEvent(QMouseEvent *e)
{
    //按下路径不为空说明要还原正常显示路径
    if(this->normalPath != "")
    {
        //创建QPixmap对象
        QPixmap pix;
        bool ret = pix.load(this->normalPath);
        if(!ret){
            QString str = QString("路径%1图标加载失败！").arg(this->normalPath);
            qDebug() << str;
        }

        /*特殊形状图片按钮*/
        //设置按钮固定尺寸
        this->setFixedSize(pix.width(),pix.height());
        //设置不规则样式 边框透明去除
        this->setStyleSheet("QPushButton{border:0px;}");
        //设置图标
        this->setIcon(pix);
        //设置图标大小
        this->setIconSize(QSize(pix.width(),pix.height()));
    }

    //其他事情交给父类处理
    QPushButton::mouseReleaseEvent(e);
}

void MyPushButton::setBtnArea(int windoww, int windowh)
{
    switch(this->m_btnRank){
    case Rank_1: this->move(windoww*0.5 - this->width()*0.5,windowh*0.40); break;
    case Rank_2: this->move(windoww*0.5 - this->width()*0.5,windowh*0.52); break;
    case Rank_3: this->move(windoww*0.5 - this->width()*0.5,windowh*0.64); break;
    case Rank_4: this->move(windoww*0.5 - this->width()*0.5,windowh*0.76); break;
    }
}

void MyPushButton::setRank(ButtonRank rank)
{
    this->m_btnRank = rank;
}

void MyPushButton::setType(BtnType type)
{
    this->m_type = type;
}
