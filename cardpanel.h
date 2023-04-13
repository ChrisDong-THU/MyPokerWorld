#ifndef CARDPANEL_H
#define CARDPANEL_H

#include <QWidget>
#include <QSize>
#include "card.h"
#include "player.h"
#include "config.h"

class CardPanel : public QWidget
{
    Q_OBJECT
public:
    //explicit使构造函数不能进行隐式转换
    explicit CardPanel(QWidget *parent = nullptr);

    //设置正、反面图像Qpixmap
    void setCardImg(Card card);

    //获取正面图像
    QPixmap getImage();

    //卡牌大小控制
    QSize m_cardSize;

    //设置显示正面or反面
    void setFrontSide(bool flag);
    //获取显示是否为正面 为正面bool值为true
    bool isFrontSide();

    //设置是否被选中
    void setSeclected(bool flag);
    //获取选中状态
    bool isSelected();

    //设置卡牌信息
    void setCard(const Card& card);
    //获取卡牌信息
    Card getCard();

    //设置卡牌所有者
    void setOwner(Player* player);
    //获取卡牌所有者 指针
    Player* getOwner();

    //左键点击卡牌事件
    void clicked();

protected:
    //链接绘图事件
    void paintEvent(QPaintEvent *event);
    //链接鼠标左键点击事件 event->button()
    void mousePressEvent(QMouseEvent* event);


signals:
    //卡牌被选取状态信号函数 无实现
    //通过鼠标点击按钮发送
    //枚举量左键点击型 形参 button
    void cardSelected(Qt::MouseButton button);

private:
    //卡牌正面、反面图像
    QPixmap m_front;
    QPixmap m_back;

    //当前绘制的卡牌
    Card m_card;

    //正面、选取状态 被选中状态变量
    bool m_isfront = true;
    bool m_isSelect = false;

    //待绘制卡片

    /* 卡牌所有者
     * 在cardpanel完成卡牌与玩家的组合
     * 于CardsPanel::disposeCard实现绑定
     */
    Player* m_owner = nullptr;
};

#endif // CARDPANEL_H
