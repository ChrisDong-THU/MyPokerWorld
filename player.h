#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include "cards.h"

class Player : public QObject
{
    Q_OBJECT
public:
    // 头像的显示方位
    enum Direction{
        Left,
        Right,
        Up,
        Down
    };

    // 玩家的类型
    enum PlayerType{
        Robot,
        User,
        UnKnow
    };

    explicit Player(QObject *parent = nullptr);
    explicit Player(QString name, QObject *parent = nullptr);

    void setName(QString name);
    QString getName();

    void setDirection(Direction direction);
    Direction getDirection();

    void setType(PlayerType type);
    PlayerType getType();

    void setScore(int score);
    int getScore();

    void setWin(bool flag);
    bool isWin();

    //设置出牌前后顺序玩家
    //逆时针left->down->right->up
    void setPrevPlayer(Player* player);
    void setNextPlayer(Player* player);
    Player* getPrevPlayer();
    Player* getNextPlayer();

    void storeDispatchCard(const Card& card);
    void storeDispatchCard(const Cards& cards);

    Cards getCards();
    void clearCards();

    void playHand(const Cards& cards);

    Player* getPendPlayer();
    Cards getPendCards();

    //储存挂起的玩家和卡牌
    void storePendingInfo(Player* player, const Cards& cards);

    virtual void preparePlayHand();
    virtual void thinkPlayHand();

signals:
    void notifyPlayHand(Player* player, const Cards& card);
    //信号 传递玩家和其挂起的牌m_pendCards
    void notifyPickCards(Player* player, const Cards& cards);

//子类可直接访问父类protected成员变量
protected:
    int m_score = 0;
    QString m_name;
    Direction m_direction;
    PlayerType m_type;

};

#endif // PLAYER_H
