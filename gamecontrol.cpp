#include "gamecontrol.h"

GameControl::GameControl(QObject *parent): QObject(parent)
{

}

void GameControl::playerInit(Player::Direction dir)
{
    now.setDirection(dir);
    prev.setDirection(getPrevDir(dir));
    next.setDirection(getNextDir(dir));
}

int GameControl::getSeqI(Player::Direction dir)
{
    int i;

    switch(dir)
    {
    case Player::Left: i=0; break;
    case Player::Down: i=3; break;
    case Player::Right: i=1; break;
    case Player::Up: i=2; break;
    default:
        i=3;
        break;
    }

    return i;
}

Player::Direction GameControl::getNextDir(Player::Direction dir)
{
    Player::Direction i;

    switch(dir)
    {
    case Player::Left: i=Player::Down; break;
    case Player::Down: i=Player::Right; break;
    case Player::Right: i=Player::Up; break;
    case Player::Up: i=Player::Left; break;
    default:
        break;
    }

    return i;
}

Player::Direction GameControl::getPrevDir(Player::Direction dir)
{
    Player::Direction i;

    switch(dir)
    {
    case Player::Left: i=Player::Up; break;
    case Player::Down: i=Player::Left; break;
    case Player::Right: i=Player::Down; break;
    case Player::Up: i=Player::Right; break;
    default:
        break;
    }

    return i;
}

Player::Direction GameControl::getPrevPlayerDir()
{
    return prev.getDirection();
}

Player::Direction GameControl::getNowPlayerDir()
{
    return now.getDirection();
}

Player::Direction GameControl::getNextPlayerDir()
{
    return next.getDirection();
}

void GameControl::setPrevPlayerDir(Player::Direction dir)
{
    prev.setDirection(dir);
}

void GameControl::setNowPlayerDir(Player::Direction dir)
{
    now.setDirection(dir);
}

void GameControl::setNextPlayerDir(Player::Direction dir)
{
    next.setDirection(dir);
}
