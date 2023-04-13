#include "playscene.h"
#include "config.h"
#include <QPainter>
#include <QMenuBar>
#include <QTimer>
#include <QTime>
#include <QThread>

void PlayScene::setModeandRule(int mode, int rule)
{
    gameMode = mode;
    gameRule = rule;
}

PlayScene::PlayScene(QWidget *parent)
    : QMainWindow{parent}
{
    //设置固定尺寸
    this->setFixedSize(WINDOWWIDTH,WINDOWHEIGHT);
    //设置标题
    this->setWindowTitle("Enjoy Your Poker World !");
    //设置图标
    this->setWindowIcon(QIcon(":/icon/res/icon/mainwindowicon.png"));

    /* 创建牌堆绘画内存
     * 需绑定中央窗口centralwidget父类widget对象
     * 参考：btnGroup = new ButtonGroup(centralwidget);
     */
    //直接绑定父mainwindow
    //覆盖菜单栏 需另转移到CardsPanel中

    //申请游戏控制模块内存
    m_control = new GameControl(this);
    //申请机器人策略内存
    m_robots = new RobotStrategy();
    //申请出牌判断内存
    m_playhand = new PlayHand();
    //申请延时内存
    m_time = new QThread();
    //申请胜利场景内存
    m_vic = new VictoryScene();

    //牌堆绘制环境配置初始化
    initContexRef();

    //角色图片
    loadRolesImg();

    //初始化四个牌群
    for(int i=0; i<4; i++){
        CardsPanel *panels = new CardsPanel(this);

        panels->m_player = new Player(this);

        panels->m_player->setDirection(Player::Direction(i));

        connect(panels, &CardsPanel::updateSelectedCards, this, &PlayScene::onUpdate4CardsPanel);

        m_4panels.push_back(panels);
        m_playerList.push_back(panels->m_player);
    }

    m_control->playerInit(Player::Down);

    initMenubar();

    initBtnGroup();
    initVicScene();
}

void PlayScene::onUpdate4CardsPanel()
{
    for(int i=0; i<4; i++){
        bool HorV = (i==2||i==3) ? true : false;
        if(m_4panels[i]->m_panels.size()!=0){
            m_4panels[i]->drawPanels(HorV, m_contextRef[Player::Direction(i)].cardsRect, m_contextRef[Player::Direction(i)].isFront);
        }
        qDebug()<<i<<"m_4panels[i]->m_cards.size():"<<m_4panels[i]->m_cards.m_cards.size();
    }
}

void PlayScene::onUpdatePlayHand()
{
    for(int i=0; i<4; i++){
        bool HorV = (i==2||i==3) ? true : false;
        if(m_4panels[i]->m_selectedCards.m_cards.size()!=0){
            m_4panels[i]->initPlayHand();
            m_4panels[i]->onDrawPlayHand(HorV, m_contextRef[Player::Direction(i)].playHandRect);
        }
    }
}

void PlayScene::onPlayHand()
{
    //上家,当前家方向对应的序号
    int prev_i, now_i;

    now_i=m_control->getSeqI(m_control->getNowPlayerDir());
    prev_i = m_control->getSeqI(m_control->getPrevPlayerDir());

    if(0/*非游戏阶段*/){
        return;
    }
    qDebug()<<"T1";

    //上家打出的牌
    PlayHand pre_cards(m_4panels[prev_i]->m_selectedCards);
    PlayHand now_cards(m_4panels[now_i]->m_selectedCards);
    qDebug()<<"DOWN selected"<<m_4panels[3]->m_selectedCards.m_cards.size();
    qDebug()<<"prev selected"<<m_4panels[prev_i]->m_selectedCards.m_cards.size();
    if(m_playhand->canBeat(pre_cards,now_cards))
    {
        qDebug()<<"T3";
        //玩家轮回推移
        m_control->setPrevPlayerDir(m_control->getNowPlayerDir());
        m_control->setNowPlayerDir(m_control->getNextPlayerDir());
        m_control->setNextPlayerDir(m_control->getNextDir(m_control->getNextPlayerDir()));
        qDebug()<<"T4"<<m_control->getNowPlayerDir();


        //<出牌者>更新自己的牌群 但不更新被选中的牌群
        m_4panels[now_i]->m_cards.remove(m_4panels[now_i]->m_selectedCards);

        //内存管理
        manegeMemory(now_i);

        m_4panels[now_i]->initCardpanel();
        onUpdate4CardsPanel();

        //<上家>出牌绘制内存管理
        for(auto it=m_4panels[prev_i]->m_playHandPanels.begin();it!=m_4panels[prev_i]->m_playHandPanels.end(); ++it){
            delete *it;
        }
        m_4panels[prev_i]->m_playHandPanels.clear();
        m_4panels[prev_i]->m_selectedCards.clear();

        //绘制各Cardspanel选中且已出的牌
        onUpdatePlayHand();

        m_btngroup->setStakeWidget(1);
        if(m_control->getNowPlayerDir()==Player::Down){
            //按钮翻页
            m_btngroup->setStakeWidget(2);
        }

        if(m_vic->judgeWinner(m_4panels[now_i]->m_cards)){
            qDebug()<<"有人胜利了";
            m_vic->show();
            m_vic->raise();
            m_vic->sendWinnerInf(now_i);
        }

        return;
    }
    //管理内存
    manegeMemory(now_i);
    m_4panels[now_i]->m_selectedCards.clear();
    //panels绘制内存均被清除，需要通过initCardpanel初始化new出新的panel群
    m_4panels[now_i]->initCardpanel();
    onUpdate4CardsPanel();
}

void PlayScene::onPass()
{
    /* 跳过处理
     * 上家不变，当前、下家向后推移
     */
    qDebug()<<"T5";
    if(m_control->getPrevPlayerDir()==m_control->getNextDir(m_control->getNowPlayerDir())){
        //<上家>出牌绘制内存管理
        qDebug()<<"T6";
        int prev_i;
        prev_i = m_control->getSeqI(m_control->getPrevPlayerDir());

        for(auto it=m_4panels[prev_i]->m_playHandPanels.begin();it!=m_4panels[prev_i]->m_playHandPanels.end(); ++it){
            delete *it;
        }
        m_4panels[prev_i]->m_playHandPanels.clear();
        m_4panels[prev_i]->m_selectedCards.clear();
        m_4panels[prev_i]->m_selectedPanels.clear();

        m_control->setPrevPlayerDir(m_control->getNowPlayerDir());
        qDebug()<<"prev_i"<<prev_i<<"m_4panels[prev_i]->m_selectedCards:"<<m_4panels[prev_i]->m_selectedCards.m_cards.size();
    }

    int now_i=m_control->getSeqI(m_control->getNowPlayerDir());

    //管理内存
    manegeMemory(now_i);
    m_4panels[now_i]->m_selectedCards.clear();
    //panels绘制内存均被清除，需要通过initCardpanel初始化new出新的panel群
    m_4panels[now_i]->initCardpanel();
    onUpdate4CardsPanel();

    m_control->setNowPlayerDir(m_control->getNextPlayerDir());
    m_control->setNextPlayerDir(m_control->getNextDir(m_control->getNextPlayerDir()));
    m_btngroup->setStakeWidget(1);
    if(m_control->getNowPlayerDir()==Player::Down){
        //按钮翻页
        m_btngroup->setStakeWidget(2);
    }
}

void PlayScene::initBtnGroup()
{
    m_btngroup = new ButtonGroup(this);

    m_btngroup->move(0,BTNS_TOP);

    m_btngroup->setStakeWidget(0);

    connect(m_btngroup,&ButtonGroup::startGame,this, [=](){
        if(gameRule==0){
            dispatchCardsMode1();
        }else if(gameRule==1){
            dispatchCardsMode2();
        }

        for(int i=0; i<4; i++){
            m_4panels[i]->initCardpanel();
        }
        //提取cardspanel中m_cards信息并重画
        onUpdate4CardsPanel();

        m_btngroup->setStakeWidget(2);
    });
    connect(m_btngroup,&ButtonGroup::pass,this,[=](){
        onPass();
        robotsPlayHand();
    });

    connect(m_btngroup,&ButtonGroup::playHand,this,[=](){
        onPlayHand();
        robotsPlayHand();
    });
}

void PlayScene::initVicScene()
{
    connect(m_vic,&VictoryScene::restartMSG,this,[=](){
        deleteALL();
        m_btngroup->setStakeWidget(0);
        QTimer::singleShot(500,this,[=](){
            emit this->playSceneBack();
        });
    });
    connect(m_vic,&VictoryScene::quitMSG,this,[=](){
        exit(0);
    });
}

void PlayScene::delayMsec(int msec)
{
    QTime n=QTime::currentTime();
    QTime now;
    do{
        now=QTime::currentTime();
    }while (n.msecsTo(now)<=msec);
}

void PlayScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/scene/res/background/playscene.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    drawRoles(painter);
}

//按左、右、上、下进行配置
void PlayScene::initContexRef()
{
    const QRect cardsRect[]={
        QRect(VERTICAL_biEDGE,VERTICAL_topEDGE,POKER_W,this->height()-VERTICAL_topEDGE*2),
        QRect(rect().right()-VERTICAL_biEDGE-POKER_W,VERTICAL_topEDGE,POKER_W,this->height()-VERTICAL_topEDGE*2),
        QRect(HORIZON_biEDGE,HORIZON_topEDGE,this->width()-HORIZON_biEDGE*2,POKER_H),
        QRect(HORIZON_biEDGE,rect().bottom()-HORIZON_topEDGE-POKER_H,this->width()-HORIZON_biEDGE*2,POKER_H)
    };
    //出牌区配置
    const QRect playHandRect[]={
        QRect(VERTICAL_biEDGE*2+POKER_W,VERTICAL_topEDGE,POKER_W,this->height()-VERTICAL_topEDGE*2),
        QRect(rect().right()-VERTICAL_biEDGE*2-POKER_W*2,VERTICAL_topEDGE,POKER_W,this->height()-VERTICAL_topEDGE*2),
        QRect(HORIZON_biEDGE,HORIZON_topEDGE*2+POKER_H,this->width()-HORIZON_biEDGE*2,POKER_H),
        QRect(HORIZON_biEDGE,rect().bottom()-HORIZON_topEDGE-BTNS_H-POKER_H*2,this->width()-HORIZON_biEDGE*2,POKER_H)
    };
    //角色头像绘制配置
    const QPoint roleImgPos[]={
        QPoint(cardsRect[0].left()-ROLE_W-ROLE_biEDGE,(WINDOWHEIGHT-ROLE_H)/2),
        QPoint(cardsRect[1].right()+ROLE_biEDGE,(WINDOWHEIGHT-ROLE_H)/2),
        QPoint(cardsRect[2].left()-ROLE_biEDGE,cardsRect[2].top()+(cardsRect[2].height()-ROLE_H)/2),
        QPoint(cardsRect[3].left()-ROLE_biEDGE,cardsRect[3].top()+(cardsRect[3].height()-ROLE_H)/2)
    };
    for(int i=0; i<4; i++){
        Player::Direction dir;
        dir = Player::Direction(i);
        PlayerContext context;
        context.align = (dir==Player::Down||dir==Player::Up) ? Horizontal : Vertical;
        context.cardsRect = cardsRect[i];
        context.playHandRect = playHandRect[i];
        context.roleImgPos = roleImgPos[i];
        context.isFront = (dir==Player::Down) ? true : false;

        m_contextRef.insert(dir, context);
    }

}

void PlayScene::initALLCardMode1()
{
    //将所有Card对象存入m_allcards
    for(int deck=Card::Deck_1; deck<=Card::Deck_2; ++deck){
        for(int suit=Card::Suit_Begin+1; suit<Card::Suit_End; ++suit){
            for(int pt=Card::Card_Begin+1; pt<Card::Card_SJ; ++pt){
               Card card((Card::CardDeck)deck, (Card::CardPoint)pt, (Card::CardSuit)suit);
               m_allCard.add(card);
            }
        }
    }
}

void PlayScene::initALLCardMode2()
{
    //将所有Card对象存入m_allcards
    for(int suit=Card::Suit_Begin+1; suit<Card::Suit_End; ++suit){
        for(int pt=Card::Card_Begin+1; pt<Card::Card_SJ; ++pt){
           Card card(Card::Deck_1, (Card::CardPoint)pt, (Card::CardSuit)suit);
           m_allCard.add(card);
        }
    }

    //大小王（可选）
//    Card card1(Card::Deck_1, Card::CardPoint::Card_SJ, Card::CardSuit::Club);
//    m_allCard.add(card1);
//    Card card2(Card::Deck_1, Card::CardPoint::Card_BJ, Card::CardSuit::Club);
//    m_allCard.add(card2);

}

void PlayScene::dispatchCardsMode1()
{
    //初始化牌 104张
    initALLCardMode1();

    //开始发牌
    for(int loop=0; loop<26; loop++){
        for(int i=0; i<4; i++){
            takeOneCard(i);
        }
    }
}

void PlayScene::dispatchCardsMode2()
{
    //初始化牌 54张
    initALLCardMode2();

    //开始发牌
    for(int loop=0; loop<13; loop++){
        for(int i=0; i<4; i++){
            takeOneCard(i);
        }
    }
}

void PlayScene::robotsPlayHand()
{
    int now_i, prev_i;

    while((m_control->getNowPlayerDir())!=Player::Down)
    {
        now_i = m_control->getSeqI(m_control->getNowPlayerDir());
        prev_i = m_control->getSeqI(m_control->getPrevPlayerDir());

        qDebug()<<"now_i"<<now_i;
        qDebug()<<"prev_i"<<prev_i;

        Cards robotplayhand;
        robotplayhand = m_robots->robot_ifcanbeat(m_4panels[prev_i]->m_selectedCards,m_4panels[now_i]->m_cards);

        m_4panels[now_i]->m_selectedCards=robotplayhand;

        if(robotplayhand.isEmpty()){
            onPass();
        }else{
            onPlayHand();
        }

        //延时（待用）
//        for(int k=0; k<100; k++){
//            delayMsec(10);
//            bool HorV = (prev_i==2||prev_i==3) ? true : false;
//            m_4panels[prev_i]->onDrawPlayHand(HorV, m_contextRef[Player::Direction(prev_i)].playHandRect);
//        }
    }
    this->m_btngroup->setStakeWidget(2);
}

//第i位玩家抽取一张牌（左、右、上、下）
void PlayScene::takeOneCard(int i)
{
    Card card = m_allCard.takeRandomCard();
    m_4panels[i]->m_cards.add(card);
}

void PlayScene::loadRolesImg()
{
    for(int i=0; i<4; i++){
        QPixmap *roleimg = new QPixmap;
        QString totalLoadPath = ":/role/res/role/";
        QString loadPath;

        loadPath = QString("%1role%2.png").arg(totalLoadPath).arg(i);
        roleimg->load(loadPath);

        m_roleImgs.insert(roleimg);
    }
}

void PlayScene::drawRoles(QPainter &painter)
{
    auto it = m_roleImgs.begin();
    for(int i=0; i<4; i++, it++){
        QPoint point = m_contextRef[Player::Direction(i)].roleImgPos;
        painter.drawPixmap(point.x(),point.y(),ROLE_W,ROLE_H,*(*it));
    }
}

void PlayScene::manegeMemory(int i)
{
    //管理内存 仅用erase无法清除原来绘制的卡牌
    for(auto it=m_4panels[i]->m_panelPosList.begin();it!=m_4panels[i]->m_panelPosList.end(); ++it){
        delete *it;
    }
    for(auto it=m_4panels[i]->m_panels.begin();it!=m_4panels[i]->m_panels.end(); ++it){
        delete *it;
    }
    m_4panels[i]->m_panels.clear();
    m_4panels[i]->m_panelPosList.clear();
    m_4panels[i]->m_selectedPanels.clear();
}

void PlayScene::deleteALL()
{
    for(int i=0; i<4; i++){
        manegeMemory(i);
        for(auto it=m_4panels[i]->m_playHandPanels.begin();it!=m_4panels[i]->m_playHandPanels.end(); ++it){
            delete *it;
        }
        m_4panels[i]->m_playHandPanels.clear();
        m_4panels[i]->m_selectedCards.clear();
        m_4panels[i]->m_selectedPanels.clear();
        m_4panels[i]->m_cards.clear();
    }
    m_allCard.clear();
}

void PlayScene::initMenubar()
{
    /***建议菜单***/
    //创建菜单栏（借助代码的方式，而非ui界面）
    QMenuBar * bar = menuBar();
    this->setMenuBar(bar);
    bar->raise();
    //创建菜单
    QMenu* startMenu = bar->addMenu("选项");

    //创建菜单项
    QAction * backAction = startMenu->addAction("返回主选单");
    //监听退出
    connect(backAction,&QAction::triggered,[=](){
        deleteALL();
        m_btngroup->setStakeWidget(0);
        QTimer::singleShot(500,this,[=](){
            emit this->playSceneBack();
        });
    });

    //创建菜单项
    QAction * quitAction = startMenu->addAction("退出至桌面");
    //监听退出
    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });
}
