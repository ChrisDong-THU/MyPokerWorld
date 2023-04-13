#include "playhand.h"

PlayHand::PlayHand()
{

}

PlayHand::PlayHand(Cards &cards)
{
    classify(cards);
    judgeCardType();
}

PlayHand::PlayHand(HandType type, Card::CardPoint pt, int extra)
{
    m_type = type;
    m_pt = pt;
    m_extra = extra;
}

void PlayHand::classify(Cards &cards)
{
    CardList list = cards.toCardList();
    int cardRecord[Card::Card_End];
    memset(cardRecord, 0, sizeof(int) * Card::Card_End);

    for(int i=0; i<list.size(); ++i)
    {
        Card c = list.at(i);
        cardRecord[c.point()] ++;
    }

    m_oneCard.clear();
    m_twoCard.clear();
    m_threeCard.clear();
    m_fourCard.clear();
    m_fiveCard.clear();
    m_sixCard.clear();
    m_sevenCard.clear();
    m_eightCard.clear();

    for(int i=0; i<Card::Card_End; ++i)
    {
        if(cardRecord[i] == 1)
        {
            m_oneCard.push_back((Card::CardPoint)i);
        }
        else if(cardRecord[i] == 2)
        {
            m_twoCard.push_back((Card::CardPoint)i);
        }
        else if(cardRecord[i] == 3)
        {
            m_threeCard.push_back((Card::CardPoint)i);
        }
        else if(cardRecord[i] == 4)
        {
            m_fourCard.push_back((Card::CardPoint)i);
        }
        else if(cardRecord[i] == 5)
        {
            m_fiveCard.push_back((Card::CardPoint)i);
        }
        else if(cardRecord[i] == 6)
        {
            m_sixCard.push_back((Card::CardPoint)i);
        }
        else if(cardRecord[i] == 7)
        {
            m_sevenCard.push_back((Card::CardPoint)i);
        }
        else if(cardRecord[i] == 8)
        {
            m_eightCard.push_back((Card::CardPoint)i);
        }

    }

}

void PlayHand::judgeCardType()
{
    m_type = Hand_Unknown;
    m_pt = Card::Card_Begin;
    m_extra = 0;

    //qDebug()<<"m_oneCard[0]:"<<*m_oneCard.begin();
    //qDebug()<<"m_twoCard[0]:"<<*m_twoCard.begin();
    //qDebug()<<"m_threeCard[0]:"<<*m_threeCard.begin();
    //qDebug()<<"m_fourCard[0]:"<<*m_fourCard.begin();

    if(isPass())
    {
        m_type = Hand_Pass;
    }
    if(isSingle())
    {
        m_type = Hand_Single;
        m_pt = m_oneCard[0];
    }
    else if(isPair())
    {
        m_type = Hand_Pair;
        m_pt = m_twoCard[0];
    }
    else if(isTriple())
    {
        m_type = Hand_Triple;
        m_pt = m_threeCard[0];
    }
    else if(isTripleSingle())
    {
        m_type = Hand_Triple_Single;
        m_pt = m_threeCard[0];
    }
    else if(isTriplePair())
    {
        m_type = Hand_Triple_Pair;
        m_pt = m_threeCard[0];
    }
    else if(isBomb())
    {
        m_type = Hand_Bomb;
        m_pt = m_fourCard[0];
    }
    else if(is5Bomb())
    {
        m_type = Hand_5Bomb;
        m_pt = m_fiveCard[0];
    }
    else if(is6Bomb())
    {
        m_type = Hand_6Bomb;
        m_pt = m_sixCard[0];
    }
    else if(is7Bomb())
    {
        m_type = Hand_7Bomb;
        m_pt = m_sevenCard[0];
    }
    else if(is8Bomb())
    {
        m_type = Hand_8Bomb;
        m_pt = m_eightCard[0];
    }
    return;
}

bool PlayHand::isPass()
{
    if(m_oneCard.size() == 0 && m_twoCard.isEmpty() && m_threeCard.isEmpty() && m_fourCard.isEmpty() &&
            m_fiveCard.size() == 0 && m_sixCard.isEmpty() && m_sevenCard.isEmpty() && m_eightCard.isEmpty())
    {
        return true;
    }
    return false;
}

PlayHand::HandType PlayHand::getHandType()
{
    return m_type;
}

Card::CardPoint PlayHand::getCardPoint()
{
    return m_pt;
}

int PlayHand::getExtra()
{
    return m_extra;
}

bool PlayHand::canBeat(const PlayHand &pre_cards,const PlayHand &now_cards)
{
    if(now_cards.m_type == Hand_Unknown)
    {
        return false;
    }
    if(pre_cards.m_type == Hand_Pass || pre_cards.m_type == Hand_Unknown)
    {
        return true;
    }
    if(now_cards.m_type >= Hand_Bomb && pre_cards.m_type < now_cards.m_type)
    {
        return true;
    }
    if(now_cards.m_type == pre_cards.m_type)
    {
        return now_cards.m_pt > pre_cards.m_pt;
    }
    return false;
}

bool PlayHand::isSingle()
{
    if(m_oneCard.size() == 1 && m_twoCard.isEmpty() && m_threeCard.isEmpty() && m_fourCard.isEmpty() &&
            m_fiveCard.isEmpty() && m_sixCard.isEmpty() && m_sevenCard.isEmpty() && m_eightCard.isEmpty())
    {
        return true;
    }
    return false;
}

bool PlayHand::isPair()
{
    if(m_oneCard.isEmpty() && m_twoCard.size() == 1 && m_threeCard.isEmpty() && m_fourCard.isEmpty() &&
            m_fiveCard.isEmpty() && m_sixCard.isEmpty() && m_sevenCard.isEmpty() && m_eightCard.isEmpty())
    {
        return true;
    }
    return false;
}

bool PlayHand::isTriple()
{
    if(m_oneCard.isEmpty() && m_twoCard.isEmpty() == 1 && m_threeCard.size() == 1 && m_fourCard.isEmpty() &&
            m_fiveCard.isEmpty() && m_sixCard.isEmpty() && m_sevenCard.isEmpty() && m_eightCard.isEmpty())
    {
        return true;
    }
    return false;
}

bool PlayHand::isTripleSingle()
{
    if(m_oneCard.size() == 1 && m_twoCard.isEmpty() && m_threeCard.size()== 1 && m_fourCard.isEmpty() &&
            m_fiveCard.isEmpty() && m_sixCard.isEmpty() && m_sevenCard.isEmpty() && m_eightCard.isEmpty())
    {
        return true;
    }
    return false;
}

bool PlayHand::isTriplePair()
{
    if(m_oneCard.isEmpty() && m_twoCard.size() == 1 && m_threeCard.size() == 1 && m_fourCard.isEmpty() &&
            m_fiveCard.isEmpty() && m_sixCard.isEmpty() && m_sevenCard.isEmpty() && m_eightCard.isEmpty())
    {
        return true;
    }
    return false;
}

bool PlayHand::isBomb()
{
    if(m_oneCard.isEmpty() && m_twoCard.isEmpty() && m_threeCard.isEmpty() && m_fourCard.size() == 1 &&
            m_fiveCard.isEmpty() && m_sixCard.isEmpty() && m_sevenCard.isEmpty() && m_eightCard.isEmpty())
    {
         return true;
    }
    return false;
}

bool PlayHand::is5Bomb()
{
    if(m_oneCard.isEmpty() && m_twoCard.isEmpty() && m_threeCard.isEmpty() && m_fourCard.isEmpty() &&
            m_fiveCard.size() == 1 && m_sixCard.isEmpty() && m_sevenCard.isEmpty() && m_eightCard.isEmpty())
    {
         return true;
    }
    return false;
}
bool PlayHand::is6Bomb()
{
    if(m_oneCard.isEmpty() && m_twoCard.isEmpty() && m_threeCard.isEmpty() && m_fourCard.isEmpty() &&
            m_fiveCard.isEmpty() && m_sixCard.size() == 1 && m_sevenCard.isEmpty() && m_eightCard.isEmpty())
    {
         return true;
    }
    return false;
}
bool PlayHand::is7Bomb()
{
    if(m_oneCard.isEmpty() && m_twoCard.isEmpty() && m_threeCard.isEmpty() && m_fourCard.isEmpty() &&
            m_fiveCard.size() == 1 && m_sixCard.isEmpty() && m_sevenCard.isEmpty() && m_eightCard.isEmpty())
    {
         return true;
    }
    return false;
}
bool PlayHand::is8Bomb()
{
    if(m_oneCard.isEmpty() && m_twoCard.isEmpty() && m_threeCard.isEmpty() && m_fourCard.isEmpty() &&
            m_fiveCard.isEmpty() && m_sixCard.isEmpty() && m_sevenCard.isEmpty() && m_eightCard.size() == 1)
    {
         return true;
    }
    return false;
}
