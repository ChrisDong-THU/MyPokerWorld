#ifndef CARDS_H
#define CARDS_H
#include "card.h"

#include <QSet>

class Cards
{
public:
    //搜索结果枚举值
    enum SortType{Asc, Desc, NoSort};
    //构造
    Cards();
    //有参重载 初始化一个类card
    explicit Cards(const Card& card);

    //都是对 <核心容器> QSet<card>操作
    //牌组增加一个类card
    void add(const Card& card);
    //add重载 与形参cards比较 查找缺失单位类并补齐
    void add(const Cards& cards);
    //add重载 对Qvector这一类cards的数组遍历 对QVector中每个元素cards进行unite查缺工作
    void add(const QVector<Cards>& cards);
    void add(const QSet<Card>& cards);

    //操作符重载 <<添加的card或cards类并返回当前使用对象
    Cards& operator <<(const Card& card);
    Cards& operator <<(const Cards& cards);

    //牌组移除一个类card 其他类比add
    void remove(const Card& card);
    void remove(const Cards& cards);
    void remove(const QVector<Cards>& cards);
    void remove(const QSet<Card>& cards);

    //QSet m_cards的大小
    int cardCount();
    bool isEmpty();
    bool isEmpty() const;//获取空状态 更健壮

    //清空QSet m_cards
    void clear();

    //遍历寻找m_Cards各card中最小、最大值，返回其在m_Cards中位置
    Card::CardPoint maxPoint();
    Card::CardPoint minPoint();

    //某点数同点数牌数
    int pointCount(Card::CardPoint point);

    //是否包含card或cards
    bool contains(const Card& card);
    bool contains(const Cards& cards);

    //随即发牌获取card
    Card takeRandomCard();

    /* QVector排序算法
     * 将QSet容器转化为排好序的CardList数组容器
     */
    CardList toCardList(SortType type = Desc);

    //打印牌信息 仅调试用
    void printAllCardInfo();

    //Qset对card类提供容器 集合 同理QVector
    QSet<Card> m_cards;

private:
};

#endif // CARDS_H
