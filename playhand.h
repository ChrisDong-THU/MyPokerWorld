#ifndef PLAYHAND_H
#define PLAYHAND_H

#include "card.h"
#include "cards.h"
#include <QDebug>

class PlayHand
{
public:
    // 出牌组合或者方式
    enum HandType
    {
        Hand_Unknown,               // 未知
        Hand_Pass,                  // 过

        Hand_Single,                // 单
        Hand_Pair,                  // 对

        Hand_Triple,                // 三个
        Hand_Triple_Single,         // 三带一
        Hand_Triple_Pair,           // 三带二

        Hand_Plane,                 // 飞机，555_666
        Hand_Plane_Two_Single,      // 飞机带单，555_666_3_4
        Hand_Plane_Two_Pair,        // 飞机带双，555_666_33_44

        Hand_Seq_Pair,              // 连对，33_44_55(_66...)
        Hand_Seq_Single,            // 顺子，34567(8...)

        Hand_Bomb,                  // 4张的炸弹
        Hand_5Bomb,                  // 5张的炸弹
        Hand_6Bomb,                  // 6张的炸弹
        Hand_7Bomb,                  // 7张的炸弹
        Hand_8Bomb,                  // 8张的炸弹

    };

    PlayHand();
    explicit PlayHand(Cards& cards);
    PlayHand(HandType type, Card::CardPoint pt, int extra);


    HandType getHandType();
    Card::CardPoint getCardPoint();
    int getExtra();
    //模式1（跑得快）大小判断标准
    bool canBeat(const PlayHand& pre_cards,const PlayHand& now_cards);

    HandType m_type;
    Card::CardPoint m_pt;
    int m_extra;
    QVector<Card::CardPoint> m_oneCard;
    QVector<Card::CardPoint> m_twoCard;
    QVector<Card::CardPoint> m_threeCard;
    QVector<Card::CardPoint> m_fourCard;
    QVector<Card::CardPoint> m_fiveCard;
    QVector<Card::CardPoint> m_sixCard;
    QVector<Card::CardPoint> m_sevenCard;
    QVector<Card::CardPoint> m_eightCard;


private:
    void classify(Cards& cards);
    void judgeCardType();
    bool isPass();
    bool isSingle();
    bool isPair();
    bool isTriple();
    bool isTripleSingle();
    bool isTriplePair();
    bool isBomb();
    bool is5Bomb();
    bool is6Bomb();
    bool is7Bomb();
    bool is8Bomb();

private:

};

#endif // PLAYHAND_H
