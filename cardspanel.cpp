#include "cardspanel.h"

CardsPanel::CardsPanel(QWidget *parent)
    : QWidget{parent}
{
    //自身作为父窗口设定
    this->setFixedSize(WINDOWWIDTH,WINDOWHEIGHT);
}

void CardsPanel::initCardpanel()
{
    //绘制m_cards中card对象
    m_cardvct = m_cards.toCardList();

    for(int num=0; num<m_cards.m_cards.size(); num++){
        CardPanel *panel = new CardPanel(this);

        panel->setCard(m_cardvct[num]);
        panel->setCardImg(panel->getCard());
        panel->setOwner(this->m_player);
        panel->hide();

        //信号由cardpanel传递到cardspanel槽函数
        connect(panel, &CardPanel::cardSelected, this, &CardsPanel::onCardSelected);

        m_panels.push_back(panel);
    }

    update();
}

//接受绘制区域 并show()
//手牌及选中但未打出的牌
void CardsPanel::drawPanels(bool HorV, QRect rect, bool isfront)
{
    qDebug()<<"m_panels.size():"<<m_panels.size();
    for(int i=0; i<m_panels.size(); i++){
        CardPanel *panel = m_panels[i];

        //显示卡牌 并提到最顶层
        panel->show();
        panel->raise();
        panel->setFrontSide(isfront);

        //水平排布
        if(HorV){
            int leftX = rect.left() + (rect.width() - (m_cardvct.size()-1)*hSpace - POKER_W)/2;
            int topY = rect.top() + (rect.height() - POKER_H)/2;
            if(panel->isSelected()){
                topY -= POKER_H/8;
            }
            panel->move(leftX + hSpace*i, topY);

            nowrect = QRect(leftX,topY,hSpace*i+POKER_W,POKER_H);

            //卡牌选中判定区域分配
            int curWidth = 0;
            if(i == m_panels.size()-1){
                curWidth = POKER_W;
            }else{
                curWidth = hSpace;
            }
            QRect *cardRect = new QRect(leftX+hSpace*i,topY,curWidth,POKER_H);
            m_panelPosList.insert(panel, cardRect);
        }
        else//竖直排布
        {
            int leftX = rect.left() + (rect.width()-POKER_W)/2;
            int topY = rect.top() + (rect.height() - (m_cardvct.size()-1)*vSpace-POKER_H)/2;
            panel->move(leftX,topY + i*vSpace);
        }
    }
}

void CardsPanel::initPlayHand()
{
    m_cardvct2 = m_selectedCards.toCardList();

    for(int num=0; num<m_cardvct2.size(); num++)
    {
        CardPanel *panel = new CardPanel(this);
        panel->setParent(this);
        panel->setCard(m_cardvct2[num]);
        panel->setCardImg(panel->getCard());
        panel->setOwner(this->m_player);

        panel->hide();

        m_playHandPanels.push_back(panel);
    }
}

//出牌响应绘制槽函数
void CardsPanel::onDrawPlayHand(bool HorV, QRect rect)
{
    for(int num=0; num<m_playHandPanels.size(); num++)
    {
        CardPanel *panel = m_playHandPanels[num];

        panel->show();
        panel->raise();
        panel->setFrontSide(true);

        if(HorV){
            int leftX = rect.left() + (rect.width() - (m_cardvct2.size()-1)*hSpace - POKER_W)/2;
            int topY = rect.top() + (rect.height() - POKER_H)/2;
            qDebug()<<"进入出牌绘制3！";
            panel->move(leftX + hSpace*num, topY);
        }else{
            int leftX = rect.left() + (rect.width()-POKER_W)/2;
            int topY = rect.top() + (rect.height() - (m_cardvct2.size()-1)*vSpace-POKER_H)/2;
            panel->move(leftX,topY + num*vSpace);
        }
    }
}

void CardsPanel::onCardSelected(Qt::MouseButton button)
{
    if(0/*非出牌阶段*/){
        return;
    }

    //发送被选中信号的卡牌
    m_selectedPanel = static_cast<CardPanel*>(sender());
    if(m_selectedPanel->getOwner()->getDirection() != Player::Down/*非下方玩家*/)
    {
        return;
    }
    if(button == Qt::LeftButton)
    {
        //选中状态反向转换
        m_selectedPanel->setSeclected(!m_selectedPanel->isSelected());

        //发出信号请求更新牌所有者及其所在容器信息
        emit updateSelectedCards();
        auto it = m_selectedPanels.find(m_selectedPanel);
        if(it == m_selectedPanels.constEnd())//未找到将返回Set末尾地址给迭代器
        {
            m_selectedCards.add(m_selectedPanel->getCard());
            m_selectedPanels.insert(m_selectedPanel);
        }
        else
        {
            m_selectedCards.remove(m_selectedPanel->getCard());
            m_selectedPanels.erase(it);
        }

        qDebug()<<"选中牌数"<<m_selectedPanels.size();

        //选中音乐
        //m_bgm->playAssistMusic(BGMControl::SelectCard);
    }
}

Cards CardsPanel::getMyCards()
{
    return m_cards;
}

Cards CardsPanel::getMyPlayHandCards()
{
    return m_selectedCards;
}

void CardsPanel::mouseMoveEvent(QMouseEvent *ev)
{
    Q_UNUSED(ev)
    if(ev->buttons() & Qt::LeftButton){
        QPoint pt = ev->pos();
        if(!nowrect.contains(pt)){
            m_selectedPanel = nullptr;
        }else{
            //list容器
            QList<CardPanel*> list = m_panelPosList.keys();
            for(int i=0; i<list.size(); ++i)
            {
                CardPanel* panel = list.at(i);
                if(m_panelPosList[panel]->contains(pt) && m_selectedPanel != panel)
                {
                    //发出选中卡牌信号
                    panel->clicked();
                    m_selectedPanel = panel;
                }
            }
        }
    }
}
