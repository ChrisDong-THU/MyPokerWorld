#ifndef VICTORYSCENE_H
#define VICTORYSCENE_H

#include "cards.h"
#include "config.h"
#include <QPainter>
#include <QWidget>
#include <QPaintEvent>

namespace Ui {
class VictoryScene;
}

class VictoryScene : public QWidget
{
    Q_OBJECT
public:
    explicit VictoryScene(QWidget *parent = nullptr);
    ~VictoryScene();

    bool judgeWinner(Cards cards);
    void sendWinnerInf(int i);

signals:
    void restartMSG();
    void quitMSG();

protected:
    void paintEvent(QPaintEvent *);

private:
    QPixmap victoryBackGround;
    QString winnerText;

    Ui::VictoryScene *ui;

};

#endif // VECTORYSCENE_H
