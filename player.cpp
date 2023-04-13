#include "player.h"

Player::Player(QObject *parent) : QObject(parent)
{
}

Player::Player(QString name, QObject *parent) : Player(parent)
{
    m_name = name;
}

void Player::setName(QString name)
{
    m_name = name;
}

QString Player::getName()
{
    return m_name;
}

void Player::setDirection(Direction direction)
{
    m_direction = direction;
}

Player::Direction Player::getDirection()
{
    return m_direction;
}

void Player::setType(PlayerType type)
{
    m_type = type;
}

Player::PlayerType Player::getType()
{
    return m_type;
}

void Player::setScore(int score)
{
    m_score = score;
}

int Player::getScore()
{
    return m_score;
}

void Player::preparePlayHand()
{

}

void Player::thinkPlayHand()
{

}
