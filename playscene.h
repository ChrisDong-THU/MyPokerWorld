#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include <QMap>
#include "cards.h"
#include "cardspanel.h"
#include "gamecontrol.h"
#include "player.h"
#include "playhand.h"
#include "buttongroup.h"
#include "robotstrategy.h"
#include "victoryscene.h"

/***游戏主场景***/
class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    //模式和规则控制
    int gameMode = 0;
    int gameRule = 0;

    void setModeandRule(int mode, int rule);

    //绘制环境坐标配置
    //卡牌排序方式
    //传入cardspanel时需转化为bool变量HorV true:Horizontal
    enum CardAlign{Horizontal, Vertical};
    //玩家手牌、出牌等位置
    struct PlayerContext{
        CardAlign align;
        QRect cardsRect;
        QRect playHandRect;
        bool isFront;
        QPoint roleImgPos;
    };
    //map容器 绑定玩家与环境配置 供查表
    QMap<Player::Direction, PlayerContext> m_contextRef;

    explicit PlayScene(QWidget *parent = nullptr);

    //槽函数
    //更新4个牌群
    void onUpdate4CardsPanel();
    //更新出牌绘制
    void onUpdatePlayHand();
    //出牌判定 提取选中的牌进入
    void onPlayHand();
    //跳过判定
    void onPass();

    //初始化按钮群
    void initBtnGroup();
    //初始化游戏场景
    void initVicScene();

    void delayMsec(int msec);

protected:
    //绘图事件
    void paintEvent(QPaintEvent *);

private:
    //维护牌堆容器
    Cards m_allCard;

    //维护各牌群绘画指针
    QVector<CardsPanel *> m_4panels;

    //维护游戏控制模块指针
    GameControl *m_control;

    //维护机器人策略指针
    RobotStrategy *m_robots;

    //维护延时指针
    QThread *m_time;

    //维护胜利场景指针
    VictoryScene *m_vic;

    //维护出牌判断指针
    PlayHand *m_playhand;

    //维护按钮群指针
    ButtonGroup * m_btngroup;

    //承接各cardspanel中的玩家对象
    QVector<Player *> m_playerList;

    //角色头像
    QSet<QPixmap *> m_roleImgs;

    //实现环境配置绑定 写表
    void initContexRef();

    //两副牌，无大小王，104张
    void initALLCardMode1();
    //一副牌，包含大小王，52+2张
    void initALLCardMode2();

    //需要重新发牌必须进行m_allCard.clear()
    //发牌方式1，一次性发完104张
    void dispatchCardsMode1();
    //发牌方式2，一次性发完52张
    void dispatchCardsMode2();

    //三个机器人出牌
    void robotsPlayHand();

    //i代表玩家序号0123,对应左右上下
    void takeOneCard(int i);

    void loadRolesImg();
    void drawRoles(QPainter &painter);

    //对第i模块的m_panels和Pos的内存管理函数
    //每次第iCardspanel重新调用init时都需先管理内存
    void manegeMemory(int i);

    //重新开始游戏管理内存
    void deleteALL();

    void initMenubar();

signals:
    //点击返回主选单菜单项信号
    void playSceneBack();

};

#endif // PLAYSCENE_H
