#ifndef GAMECONTROL_H
#define GAMECONTROL_H

#include <QObject>
#include "cards.h"
#include "player.h"

/**********联系玩家对象和牌容器**********/
class GameControl:public QObject
{
    Q_OBJECT
public:
    GameControl();

    enum GameStatus
    {
        DispatchCard,
        PlayingHand
    };

    enum PlayerStatus
    {
        ThinkingForPlayHand,
        Winning
    };

    explicit GameControl(QObject *parent = nullptr);

    //受控制三玩家对象 当前、上家、下家
    //i刚开始出牌者
    void playerInit(Player::Direction dir);

    //得到方位对应的i值
    int getSeqI(Player::Direction dir);
    //获得当前方向的下一方向
    Player::Direction getNextDir(Player::Direction dir);
    Player::Direction getPrevDir(Player::Direction dir);

    Player::Direction getPrevPlayerDir();
    Player::Direction getNowPlayerDir();
    Player::Direction getNextPlayerDir();

    void setPrevPlayerDir(Player::Direction dir);
    void setNowPlayerDir(Player::Direction dir);
    void setNextPlayerDir(Player::Direction dir);

private:
    //当前玩家卡牌
    Player prev;
    Player now;
    Player next;

    Cards m_pendCards;

signals:
    void playerStatusChanged(Player* player, PlayerStatus status);
    void gameStatusChanged(GameStatus status);
    void notifyPlayHand(Player* player, const Cards& card);
    void pendingInfo(Player* player, const Cards& card);
};

#endif // GAMECONTROL_H
