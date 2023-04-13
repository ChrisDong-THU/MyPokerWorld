#ifndef BUTTONGROUP_H
#define BUTTONGROUP_H

#include <QWidget>

namespace Ui {
class ButtonGroup;
}

class ButtonGroup : public QWidget
{
    Q_OBJECT

public:
    explicit ButtonGroup(QWidget *parent = nullptr);
    ~ButtonGroup();

    void initBtns();

    //QStakeWidget翻页到i
    void setStakeWidget(int i);

private:
    Ui::ButtonGroup *ui;

signals:
    //转接载体信号函数
    void startGame();//发牌
    void pass();//不要
    void playHand();//出牌
};

#endif // BUTTONGROUP_H
