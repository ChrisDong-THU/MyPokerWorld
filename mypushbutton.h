#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>
#include <QSound>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    explicit MyPushButton(QWidget *parent = nullptr);

    //设置音效
    QSound * clicksound = new QSound(":/sound/res/sound/click.wav",this);

    //参数1 正常图片路径 参数2 按下后切换图片路径
    void setBtnImg(QString normalImg, QString pressImg = " ");

    //枚举按钮等级
    enum ButtonRank{
        Rank_1,
        Rank_2,
        Rank_3,
        Rank_4,
    };

    //根据按钮类型确定播放音效
    enum BtnType{
        TYPE_Main,
        TYPE_Play
    };

    //向下跳跃
    void zoom1();

    //向上跳跃
    void zoom2();

    //鼠标按下事件
    void mousePressEvent(QMouseEvent *e);
    //鼠标释放事件
    void mouseReleaseEvent(QMouseEvent *e);

    //重设按钮高度
    void setBtnArea(int windoww, int windowh);

    void setRank(ButtonRank rank);
    void setType(BtnType type);

signals:

private:
    QString normalPath;
    QString pressPath;

    ButtonRank m_btnRank;
    BtnType m_type = TYPE_Main;
};

#endif // MYPUSHBUTTON_H
