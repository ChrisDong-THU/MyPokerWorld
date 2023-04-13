#ifndef CARD_H
#define CARD_H

#include <QVector>

class Card
{
public:
    //牌的副数 两副牌 序号 0 1
    enum CardDeck
    {
        Deck_1,
        Deck_2
    };

    // 花色 枚举值1-4级对应花色大小（同点数也可比较，黑桃Spade最大）
    enum CardSuit
    {
        Suit_Begin,
        Diamond,
        Club,
        Heart,
        Spade,
        Suit_End
    };
    // 点数 枚举值1-15级对应3,4,5-A,2，常用1-13级
    enum CardPoint
    {
        Card_Begin,
        Card_3,
        Card_4,
        Card_5,
        Card_6,
        Card_7,
        Card_8,
        Card_9,
        Card_10,
        Card_J,
        Card_Q,
        Card_K,
        Card_A,
        Card_2,
        Card_SJ,    // small joker
        Card_BJ,     // big joker
        Card_End
    };

    //默认构造函数
    Card();

    //重载函数 设定单张卡牌状态
    Card(CardDeck deck, CardPoint point, CardSuit suit);

    //设定状态
    void setDeck(CardDeck deck);
    void setPoint(CardPoint point);
    void setSuit(CardSuit suit);

    //获取状态
    CardDeck deck() const;
    CardPoint point() const;
    CardSuit suit() const;

private:
    //卡牌Card主要信息 点数point 花色suit
    CardDeck m_deck;
    CardPoint m_point;
    CardSuit m_suit;

};

    //单张牌操作函数
    //less比较当c1<c2，返回bool值true
    bool lessSort(const Card& c1, const Card& c2);
    bool greaterSort(const Card& c1, const Card& c2);

    //操作符重载
    //重载便捷调用less，比较c1小于c2
    bool operator <(const Card& c1, const Card& c2);

    //c1和c2完全相同返回bool值true
    bool operator ==(const Card& left, const Card& right);

    //哈希函数 单张牌总值unsigned int 点数为主要比较依据
    uint qHash(const Card& card);

    //using相当于typedef QVector动态数组 元素类型Card 卡牌列表CardList
    //最后端添加元素append(Card)
    //访问总个数count()
    //删除元素remove(0,2) 从0元素开始删除2个元素
    //判断是否含有某元素 contains(Card)
    using CardList = QVector<Card>;

#endif // CARD_H
