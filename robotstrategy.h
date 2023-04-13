#ifndef ROBOTSTRATEGY_H
#define ROBOTSTRATEGY_H

#include <QObject>
#include "card.h"
#include "cards.h"
#include "playhand.h"

class RobotStrategy
{
public:
    explicit RobotStrategy();

    Cards point2Card(Cards cards,Card::CardPoint point, int num);
    Cards robot_ifcanbeat(Cards pre_cards, Cards now_cards);

private:


};

#endif // ROBOTSTRATEGY_H
