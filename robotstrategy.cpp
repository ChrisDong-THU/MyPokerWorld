#include "robotstrategy.h"
#include "qobject.h"

RobotStrategy::RobotStrategy()
{

}
Cards RobotStrategy::point2Card(Cards cards,Card::CardPoint point,int num)
{
    Cards outcards;
    int outnum=0;

    for(auto it=cards.m_cards.begin(); it!=cards.m_cards.end(); it++)
    {
        if((*it).point()==point){
            outcards.add(*it);
            outnum++;
        }
        if(outnum==num){
            return outcards;
        }
    }
    return outcards;
}
Cards RobotStrategy::robot_ifcanbeat(Cards pre_cards, Cards now_cards)
{
    //机器人策略
    //机器人策略（game_mode1）
    // 首先讲机器人手里牌按照数量输入值，用playhand里面的m_oneCard、、几个QVector
    //然后get上家牌的type，是否炸弹，炸弹则判断手中m_fourCard是否有值且大于上家的m_pt
    //之后判断上家出的牌长度如果大于手牌且手中无炸弹，则直接pass，否则继续判断
    //不是的话则首先一个个比较逻辑，该比extra的比extra，先比m_xxxxCard,再比m_pt，最后比extra
    //如果手牌逻辑比较有比上家大的牌则出牌，否则pass
    //逻辑设置中机器人默认出比上家大的最小的牌

    PlayHand pre_hand(pre_cards);
    PlayHand now_hand(now_cards);
    Cards selected_cards;

    //qDebug()<<"pre_hand.getHandType()"<<pre_hand.getHandType();
    //如果上家出牌是未定义或者pass,出最小的一张牌
    if(pre_hand.getHandType()==pre_hand.HandType::Hand_Unknown || pre_hand.getHandType()==pre_hand.HandType::Hand_Pass)
    {
        if(now_hand.m_oneCard.size()!=0)
        {
            selected_cards.add(point2Card(now_cards,now_hand.m_oneCard[0],1));
            return selected_cards;
        }

        if(now_hand.m_twoCard.size()!=0)
        {
            selected_cards.add(point2Card(now_cards,now_hand.m_twoCard[0],2));
            return selected_cards;
        }
        if(now_hand.m_threeCard.size()!=0)
        {
            selected_cards.add(point2Card(now_cards,now_hand.m_threeCard[0],3));
            return selected_cards;
        }
        if(now_hand.m_fourCard.size()!=0)
        {
            selected_cards.add(point2Card(now_cards,now_hand.m_fourCard[0],4));
            return selected_cards;
        }
        if(now_hand.m_fiveCard.size()!=0)
        {
            selected_cards.add(point2Card(now_cards,now_hand.m_fiveCard[0],5));
            return selected_cards;
        }
        if(now_hand.m_sixCard.size()!=0)
        {
            selected_cards.add(point2Card(now_cards,now_hand.m_sixCard[0],6));
            return selected_cards;
        }
        if(now_hand.m_sevenCard.size()!=0)
        {
            selected_cards.add(point2Card(now_cards,now_hand.m_sevenCard[0],7));
            return selected_cards;
        }
        if(now_hand.m_eightCard.size()!=0)
        {
            selected_cards.add(point2Card(now_cards,now_hand.m_eightCard[0],8));
            return selected_cards;
        }
        return selected_cards;
    }

    //如果上家出炸弹，判断手中炸弹是否存在和大小
    if(pre_hand.getHandType()==pre_hand.HandType::Hand_8Bomb)
    {
        if(now_hand.m_eightCard.size()!=0)
        {
            if(now_hand.m_eightCard[0]>pre_hand.m_pt)
            {
                selected_cards.add(point2Card(now_cards,now_hand.m_eightCard[0],8));
            }
        }
        return selected_cards;
    }
    if(pre_hand.getHandType()==pre_hand.HandType::Hand_7Bomb)
    {
        if(now_hand.m_sevenCard.size()!=0)
        {
            if(now_hand.m_sevenCard[0]>pre_hand.m_pt)
            {
                selected_cards.add(point2Card(now_cards,now_hand.m_sevenCard[0],7));
                return selected_cards;
            }
        }

        if(now_hand.m_eightCard.size()!=0)
        {
            selected_cards.add(point2Card(now_cards,now_hand.m_eightCard[0],8));
            return selected_cards;
        }
        return selected_cards;
    }
    if(pre_hand.getHandType()==pre_hand.HandType::Hand_6Bomb)
    {
        if(now_hand.m_sixCard.size()!=0)
        {
            if(now_hand.m_sixCard[0]>pre_hand.m_pt)
            {
                selected_cards.add(point2Card(now_cards,now_hand.m_sixCard[0],6));
                return selected_cards;
            }
        }

        if(now_hand.m_sevenCard.size()!=0)
        {
            selected_cards.add(point2Card(now_cards,now_hand.m_sevenCard[0],7));
            return selected_cards;
        }
        if(now_hand.m_eightCard.size()!=0)
        {
            selected_cards.add(point2Card(now_cards,now_hand.m_eightCard[0],8));
            return selected_cards;
        }
        return selected_cards;
    }
    if(pre_hand.getHandType()==pre_hand.HandType::Hand_5Bomb)
    {
        if(now_hand.m_fiveCard.size()!=0)
        {
            if(now_hand.m_fiveCard[0]>pre_hand.m_pt)
            {
                selected_cards.add(point2Card(now_cards,now_hand.m_fiveCard[0],5));
                return selected_cards;
            }
        }

        if(now_hand.m_sixCard.size()!=0)
        {
            selected_cards.add(point2Card(now_cards,now_hand.m_sixCard[0],6));
            return selected_cards;
        }
        if(now_hand.m_sevenCard.size()!=0)
        {
            selected_cards.add(point2Card(now_cards,now_hand.m_sevenCard[0],7));
            return selected_cards;
        }
        if(now_hand.m_eightCard.size()!=0)
        {
            selected_cards.add(point2Card(now_cards,now_hand.m_eightCard[0],8));
            return selected_cards;
        }
        return selected_cards;
    }
    if(pre_hand.getHandType()==pre_hand.HandType::Hand_Bomb)
    {
        if(now_hand.m_fourCard.size()!=0)
        {
            if(now_hand.m_fourCard[0]>pre_hand.m_pt)
            {
                selected_cards.add(point2Card(now_cards,now_hand.m_fourCard[0],4));
                return selected_cards;
            }
        }
        if(now_hand.m_fiveCard.size()!=0)
        {
            selected_cards.add(point2Card(now_cards,now_hand.m_fiveCard[0],5));
            return selected_cards;
        }
        if(now_hand.m_sixCard.size()!=0)
        {
            selected_cards.add(point2Card(now_cards,now_hand.m_sixCard[0],6));
            return selected_cards;
        }
        if(now_hand.m_sevenCard.size()!=0)
        {
            selected_cards.add(point2Card(now_cards,now_hand.m_sevenCard[0],7));
            return selected_cards;
        }
        if(now_hand.m_eightCard.size()!=0)
        {
            selected_cards.add(point2Card(now_cards,now_hand.m_eightCard[0],8));
            return selected_cards;
        }
        return selected_cards;
    }

    //如果上家出牌长度大于手牌长度，且手牌无炸弹
    else if(pre_cards.cardCount() > now_cards.cardCount() && now_hand.m_fourCard.size() == 0 && now_hand.m_fiveCard.size() == 0
            && now_hand.m_sixCard.size() == 0 && now_hand.m_fourCard.size() == 0 && now_hand.m_fourCard.size() == 0)
        return selected_cards;
    //其他情况
    else
    {
        //如果上家出单
        if(pre_hand.getHandType()==pre_hand.HandType::Hand_Single)
        {
            for(int i = 0; i < now_hand.m_oneCard.size(); i++)
            {
                if(now_hand.m_oneCard[i]>pre_hand.m_pt)
                {
                    selected_cards.add(point2Card(now_cards,now_hand.m_oneCard[i],1));
                    return selected_cards;
                }
            }
            for(int i = 0; i < now_hand.m_twoCard.size(); i++)
            {
                if(now_hand.m_twoCard[i]>pre_hand.m_pt)
                {
                    selected_cards.add(point2Card(now_cards,now_hand.m_twoCard[i],1));
                    return selected_cards;
                }
            }
            for(int i = 0; i < now_hand.m_threeCard.size(); i++)
            {
                if(now_hand.m_threeCard[i]>pre_hand.m_pt)
                {
                    selected_cards.add(point2Card(now_cards,now_hand.m_threeCard[i],1));
                    return selected_cards;
                }
            }
            if(now_hand.m_fourCard.size()!=0)
            {
                selected_cards.add(point2Card(now_cards,now_hand.m_fourCard[0],4));
                return selected_cards;
            }
            if(now_hand.m_fiveCard.size()!=0)
            {
                selected_cards.add(point2Card(now_cards,now_hand.m_fiveCard[0],5));
                return selected_cards;
            }
            if(now_hand.m_sixCard.size()!=0)
            {
                selected_cards.add(point2Card(now_cards,now_hand.m_sixCard[0],6));
                return selected_cards;
            }
            if(now_hand.m_sevenCard.size()!=0)
            {
                selected_cards.add(point2Card(now_cards,now_hand.m_sevenCard[0],7));
                return selected_cards;
            }
            if(now_hand.m_eightCard.size()!=0)
            {
                selected_cards.add(point2Card(now_cards,now_hand.m_eightCard[0],8));
                return selected_cards;
            }
        }
        //如果上家出对
        if(pre_hand.getHandType()==pre_hand.HandType::Hand_Pair)
        {
            for(int i = 0; i < now_hand.m_twoCard.size(); i++)
            {
                if(now_hand.m_twoCard[i]>pre_hand.m_pt)
                {
                    selected_cards.add(point2Card(now_cards,now_hand.m_twoCard[i],2));
                    return selected_cards;
                }
            }
            for(int i = 0; i < now_hand.m_threeCard.size(); i++)
            {
                if(now_hand.m_threeCard[i]>pre_hand.m_pt)
                {
                    selected_cards.add(point2Card(now_cards,now_hand.m_threeCard[i],2));
                    return selected_cards;
                }
            }
            if(now_hand.m_fourCard.size()!=0)
            {
                selected_cards.add(point2Card(now_cards,now_hand.m_fourCard[0],4));
                return selected_cards;
            }
            if(now_hand.m_fiveCard.size()!=0)
            {
                selected_cards.add(point2Card(now_cards,now_hand.m_fiveCard[0],5));
                return selected_cards;
            }
            if(now_hand.m_sixCard.size()!=0)
            {
                selected_cards.add(point2Card(now_cards,now_hand.m_sixCard[0],6));
                return selected_cards;
            }
            if(now_hand.m_sevenCard.size()!=0)
            {
                selected_cards.add(point2Card(now_cards,now_hand.m_sevenCard[0],7));
                return selected_cards;
            }
            if(now_hand.m_eightCard.size()!=0)
            {
                selected_cards.add(point2Card(now_cards,now_hand.m_eightCard[0],8));
                return selected_cards;
            }
        }
        //如果上家出三张，三带一，三带二
        if(pre_hand.getHandType()==pre_hand.HandType::Hand_Triple)
        {
            for(int i = 0; i < now_hand.m_threeCard.size(); i++)
            {
                if(now_hand.m_threeCard[i]>pre_hand.m_pt)
                {
                    selected_cards.add(point2Card(now_cards,now_hand.m_threeCard[i],3));
                    return selected_cards;
                }
            }
            if(now_hand.m_fourCard.size()!=0)
            {
                selected_cards.add(point2Card(now_cards,now_hand.m_fourCard[0],4));
                return selected_cards;
            }
            if(now_hand.m_fiveCard.size()!=0)
            {
                selected_cards.add(point2Card(now_cards,now_hand.m_fiveCard[0],5));
                return selected_cards;
            }
            if(now_hand.m_sixCard.size()!=0)
            {
                selected_cards.add(point2Card(now_cards,now_hand.m_sixCard[0],6));
                return selected_cards;
            }
            if(now_hand.m_sevenCard.size()!=0)
            {
                selected_cards.add(point2Card(now_cards,now_hand.m_sevenCard[0],7));
                return selected_cards;
            }
            if(now_hand.m_eightCard.size()!=0)
            {
                selected_cards.add(point2Card(now_cards,now_hand.m_eightCard[0],8));
                return selected_cards;
            }
            return selected_cards;
        }
        if(pre_hand.getHandType()==pre_hand.HandType::Hand_Triple_Single)
        {
            int i;
            for(i = 0; i < now_hand.m_threeCard.size(); i++)
            {
                if(now_hand.m_threeCard.size()!=0)
                {
                    if(now_hand.m_threeCard[i]>pre_hand.m_pt)
                    {
                        selected_cards.add(point2Card(now_cards,now_hand.m_threeCard[i],3));
                        if(now_hand.m_oneCard.size()!=0)
                        {
                            selected_cards.add(point2Card(now_cards,now_hand.m_oneCard[0],1));
                            return selected_cards;
                        }

                        if(now_hand.m_twoCard.size()!=0)
                        {
                            selected_cards.add(point2Card(now_cards,now_hand.m_twoCard[0],1));
                            return selected_cards;
                        }
                        if(now_hand.m_threeCard.size()!=1)
                        {
                            if(i==0)
                            selected_cards.add(point2Card(now_cards,now_hand.m_threeCard[1],1));
                            else
                            selected_cards.add(point2Card(now_cards,now_hand.m_threeCard[0],1));

                            return selected_cards;
                        }
                    }
                }
                selected_cards.clear();

            }
            if(now_hand.m_fourCard.size()!=0)
            {
                selected_cards.add(point2Card(now_cards,now_hand.m_fourCard[0],4));
                return selected_cards;
            }
            if(now_hand.m_fiveCard.size()!=0)
            {
                selected_cards.add(point2Card(now_cards,now_hand.m_fiveCard[0],5));
                return selected_cards;
            }
            if(now_hand.m_sixCard.size()!=0)
            {
                selected_cards.add(point2Card(now_cards,now_hand.m_sixCard[0],6));
                return selected_cards;
            }
            if(now_hand.m_sevenCard.size()!=0)
            {
                selected_cards.add(point2Card(now_cards,now_hand.m_sevenCard[0],7));
                return selected_cards;
            }
            if(now_hand.m_eightCard.size()!=0)
            {
                selected_cards.add(point2Card(now_cards,now_hand.m_eightCard[0],8));
                return selected_cards;
            }
            return selected_cards;
        }
        if(pre_hand.getHandType()==pre_hand.HandType::Hand_Triple_Pair)
        {
            int i;
            for(i = 0; i < now_hand.m_threeCard.size(); i++)
            {
                if(now_hand.m_threeCard.size()!=0)
                {
                    if(now_hand.m_threeCard[i]>pre_hand.m_pt)
                    {
                        selected_cards.add(point2Card(now_cards,now_hand.m_threeCard[i],3));

                        if(now_hand.m_twoCard.size()!=0)
                        {
                            selected_cards.add(point2Card(now_cards,now_hand.m_twoCard[0],2));
                            return selected_cards;
                        }
                        if(now_hand.m_threeCard.size()!=1)
                        {
                            if(i==0)
                            selected_cards.add(point2Card(now_cards,now_hand.m_threeCard[1],2));
                            else
                            selected_cards.add(point2Card(now_cards,now_hand.m_threeCard[0],2));

                            return selected_cards;
                        }
                    }
                }
                selected_cards.clear();

            }
            if(now_hand.m_fourCard.size()!=0)
            {
                selected_cards.add(point2Card(now_cards,now_hand.m_fourCard[0],4));
                return selected_cards;
            }
            if(now_hand.m_fiveCard.size()!=0)
            {
                selected_cards.add(point2Card(now_cards,now_hand.m_fiveCard[0],5));
                return selected_cards;
            }
            if(now_hand.m_sixCard.size()!=0)
            {
                selected_cards.add(point2Card(now_cards,now_hand.m_sixCard[0],6));
                return selected_cards;
            }
            if(now_hand.m_sevenCard.size()!=0)
            {
                selected_cards.add(point2Card(now_cards,now_hand.m_sevenCard[0],7));
                return selected_cards;
            }
            if(now_hand.m_eightCard.size()!=0)
            {
                selected_cards.add(point2Card(now_cards,now_hand.m_eightCard[0],8));
                return selected_cards;
            }
            return selected_cards;
        }

    }
    return selected_cards;
}
