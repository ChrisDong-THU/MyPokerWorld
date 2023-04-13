#ifndef CARDSPANEL_H
#define CARDSPANEL_H

#include <QWidget>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QVector>
#include <QMap>
#include <QDebug>

#include "cardpanel.h"
#include "player.h"
#include "cards.h"
#include "config.h"

class CardsPanel : public QWidget
{
    Q_OBJECT
public:
    explicit CardsPanel(QWidget *parent = nullptr);

    void initCardpanel();

    void drawPanels(bool HorV, QRect rect, bool isfront);

    void initPlayHand();

    void onDrawPlayHand(bool HorV, QRect rect);

    //目前牌群区域
    QRect nowrect;

    //玩家牌群
    Cards m_cards;
    //玩家归属
    Player *m_player;

    /***对象内容器申请的内存一定要在更新时处理掉***/

    //map容器 绑定卡牌与位置rect
    QMap<CardPanel *, QRect *> m_panelPosList;
    //被选中的卡牌
    CardPanel *m_selectedPanel;
    //被选中的卡牌模块群
    //到下一出牌阶段时需clear()
    QSet<CardPanel*> m_selectedPanels;
    //出牌的绘制
    QVector<CardPanel*> m_playHandPanels;
    //被选中的卡牌群m_selectedCards.m_cards
    Cards m_selectedCards;
    //包含的多个卡牌板块容器 必须为有序容器
    QVector<CardPanel *> m_panels;

    //出牌绘制指针
    bool drawPlayHandFlag;

    //槽函数
    //牌选中
    void onCardSelected(Qt::MouseButton button);

    //获取玩家所有牌和出的牌
    Cards getMyCards();
    Cards getMyPlayHandCards();

protected:
    void mouseMoveEvent(QMouseEvent* ev);

private:
    //将牌群有序化存入数组容器CardList
    CardList m_cardvct;
    //将被选中牌群有序化存入容器
    CardList m_cardvct2;

    //卡牌间距
    int hSpace = POKER_W/4;
    int vSpace = POKER_H/10;


signals:
    void updateSelectedCards();
};

#endif // CARDSPANEL_H
