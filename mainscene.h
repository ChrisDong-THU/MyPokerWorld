#ifndef MAINSCENE_H
#define MAINSCENE_H

#include "config.h"
#include "choosemodescene.h"
#include "playscene.h"
#include "chooserulescene.h"

#include <QMainWindow>
#include <QSound>

QT_BEGIN_NAMESPACE
namespace Ui { class MainScene; }
QT_END_NAMESPACE

class MainScene : public QMainWindow
{
    Q_OBJECT

public:
    MainScene(QWidget *parent = nullptr);
    ~MainScene();

    //背景音乐
    QSound * mainbackground = new QSound(":/sound/res/sound/MainBackground.wav",this);

    //绘图事件
    void paintEvent(QPaintEvent *);

    //维护游戏模式场景的指针
    ChooseModeScene * chooseScene;

    //维护玩法规则指针
    ChooseRuleScene * ruleScene;

    //维护游玩场景的指针
    PlayScene * pScene;

    //窗口大小配置信息
    int windowh = WINDOWHEIGHT;
    int windoww = WINDOWWIDTH;

    //设置单人0/联机1记录
    int gameMode = 0;
    //设置跑0/二1规则
    int gameRule = 0;

private:
    Ui::MainScene *ui;
};
#endif // MAINSCENE_H
