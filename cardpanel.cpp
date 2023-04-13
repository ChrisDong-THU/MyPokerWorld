#include "cardpanel.h"

#include <QMouseEvent>
#include <QPainter>
#include <QDebug>

/***单张牌绘制***/
CardPanel::CardPanel(QWidget *parent) : QWidget(parent)
{
    //以图像大小设定卡牌窗口大小
    m_cardSize.setWidth(POKER_W);
    m_cardSize.setHeight(POKER_H);

    //设定单张卡牌窗口QWidget大小
    this->setFixedSize(m_cardSize);
}

void CardPanel::setCardImg(Card card)
{
    QString totalLoadPath = ":/card/res/card/";
    QString loadPath;
    char suit2path = 'C';

    switch(card.suit()){
    case Card::Club:
        suit2path = 'C'; break;
    case Card::Diamond:
        suit2path = 'D'; break;
    case Card::Heart:
        suit2path = 'H'; break;
    case Card::Spade:
        suit2path = 'S'; break;
    default:
        //qDebug()<<"未知花色!";
        suit2path = 'C';
        break;
    }
    loadPath = QString("%1%2%3.png").arg(totalLoadPath).arg(card.point()+2).arg(suit2path);

    m_front.load(loadPath);

    m_back.load(CARDBACKIMG);

    //每次重设 更新窗口部件
    update();
}

QPixmap CardPanel::getImage()
{
    return m_front;
}

void CardPanel::setFrontSide(bool flag)
{
    m_isfront = flag;
}

bool CardPanel::isFrontSide()
{
    return m_isfront;
}

void CardPanel::setSeclected(bool flag)
{
    m_isSelect = flag;
}

bool CardPanel::isSelected()
{
    return m_isSelect;
}

void CardPanel::setCard(const Card &card)
{
    m_card = card;
}

Card CardPanel::getCard()
{
    return m_card;
}

void CardPanel::setOwner(Player *player)
{
    m_owner = player;
}

Player *CardPanel::getOwner()
{
    return m_owner;
}

void CardPanel::clicked()
{
    //左键点击触发卡牌被选择
    emit cardSelected(Qt::LeftButton);
}

void CardPanel::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter p(this);
    /* 矩形尺寸QWidget::rect()
     * 小部件 内部几何图形
     * 无参默认全窗口大小
     * QRect(x,y,width,height)
     * return QRect(0,0,data->crect.width(),data->crect.height())
     * (x, y) as its top-left corner and the given width and height
     */
    if(m_isfront)
    {
        p.drawPixmap(rect(), m_front);
    }
    else
    {
        p.drawPixmap(rect(), m_back);
    }
}

void CardPanel::mousePressEvent(QMouseEvent *event)
{
    //将触发信号与鼠标联系
    emit cardSelected(event->button());
}
