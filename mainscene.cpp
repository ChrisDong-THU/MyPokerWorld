#include "mainscene.h"
#include "ui_mainscene.h"
#include <QPainter>
#include "mypushbutton.h"
#include <QDebug>
#include <QTimer>
#include <QSound>

MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)//private
    /* 冒号初始化
     * namespace Ui in ui_mainscene.h
     */
{
    ui->setupUi(this);

    //准备音效

    //设置固定尺寸
    this->setFixedSize(windoww,windowh);
    //设置标题
    this->setWindowTitle("My Poker World");
    //设置图标
    this->setWindowIcon(QIcon(":/icon/res/icon/mainwindowicon.png"));

    //播放初始背景音乐
    mainbackground->play();
    mainbackground->setLoops(-1);

    //new 创建选模式场景指针指向内存 保持不释放
    this->chooseScene = new ChooseModeScene;

    //new 创建选规则场景指针指向内存
    this->ruleScene = new ChooseRuleScene;

    //new 创建游玩界面指针指向内存
    this->pScene = new PlayScene;

    //创建开始按钮
    MyPushButton * startBtn = new MyPushButton(this);
    startBtn->setBtnImg(":/btn/res/btn/start.png",":/btn/res/btn/start2.png");
    startBtn->setRank(MyPushButton::Rank_1);
    startBtn->setBtnArea(this->width(),this->height());

    //创建游戏模式按钮
    MyPushButton * modeBtn = new MyPushButton(this);
    modeBtn->setBtnImg(":/btn/res/btn/mode.png",":/btn/res/btn/mode2.png");
    modeBtn->setRank(MyPushButton::Rank_2);
    modeBtn->setBtnArea(this->width(),this->height());

    //创建游戏玩法按钮
    MyPushButton * ruleBtn = new MyPushButton(this);
    ruleBtn->setBtnImg(":/btn/res/btn/rule.png",":/btn/res/btn/rule2.png");
    ruleBtn->setRank(MyPushButton::Rank_3);
    ruleBtn->setBtnArea(this->width(),this->height());

    //创建退出按钮
    MyPushButton * quitBtn = new MyPushButton(this);
    quitBtn->setBtnImg(":/btn/res/btn/quit.png",":/btn/res/btn/quit2.png");
    quitBtn->setRank(MyPushButton::Rank_4);
    quitBtn->setBtnArea(this->width(),this->height());

    //按钮功能实现
    connect(startBtn,&MyPushButton::clicked,[=](){
        //qDebug() << "进入开始界面";
        QTimer::singleShot(500,this,[=](){
            //游玩场景打开
            this->pScene->setModeandRule(gameMode,gameRule);
            this->pScene->show();
            //主菜单隐藏
            this->hide();
        });
    });
    connect(modeBtn,&MyPushButton::clicked,[=](){
        //延时进入下一场景
        QTimer::singleShot(500,this,[=](){
            //选模式场景打开
            this->chooseScene->show();
            //主菜单隐藏
            this->hide();
        });
    });
    connect(ruleBtn,&MyPushButton::clicked,[=](){
        //延时进入下一场景
        QTimer::singleShot(500,this,[=](){
            //选模式场景打开
            this->ruleScene->show();
            //主菜单隐藏
            this->hide();
        });
    });
    connect(quitBtn,&MyPushButton::clicked,[=](){
        QTimer::singleShot(500,this,[=](){
            this->close();
        });
    });

    //监听选模式场景信号
    connect(this->chooseScene,&ChooseModeScene::chooseSeceneBack,[=](){
        this->show();
        this->chooseScene->hide();
    });
    connect(this->chooseScene,&ChooseModeScene::chooseMode0,[=](){
        this->gameMode = 0;
    });
    connect(this->chooseScene,&ChooseModeScene::chooseMode1,[=](){
        this->gameMode = 1;
    });
    //监听选规则场景信号
    connect(this->ruleScene,&ChooseRuleScene::ruleSeceneBack,[=](){
        this->show();
        this->ruleScene->hide();
    });
    connect(this->ruleScene,&ChooseRuleScene::chooseRule0,[=](){
        this->gameRule = 0;
    });
    connect(this->ruleScene,&ChooseRuleScene::chooseRule1,[=](){
        this->gameRule = 1;
    });
    //监听游玩场景信号
    connect(this->pScene,&PlayScene::playSceneBack,[=](){
        this->show();
        this->pScene->hide();
    });

}

MainScene::~MainScene()
{
    delete ui;
}

void MainScene::paintEvent(QPaintEvent *)
{
    //创建画家对象
    QPainter painter(this);

    //创建QPixmap对象
    QPixmap pix;
    pix.load(":/scene/res/background/menuscene.png");

    //绘制背景
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    /*版权待用*/
    pix.load(":/icon/res/icon/mainwindowicon.png");
    //缩放图片
    pix = pix.scaled(pix.width()*0.15,pix.height()*0.15);
    //绘制标志
    painter.drawPixmap(400,150,pix);
    //加载标题资源
    pix.load(":/icon/res/icon/gametitle.png");
    //绘制标题
    painter.drawPixmap(486,145,pix);
}

