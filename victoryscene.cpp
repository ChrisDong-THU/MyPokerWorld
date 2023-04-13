#include "victoryscene.h"
#include "ui_victoryscene.h"

VictoryScene::VictoryScene(QWidget *parent)
    : QWidget{parent},
      ui(new Ui::VictoryScene)

{
    ui->setupUi(this);

    this->setWindowTitle("胜利！");

    connect(ui->restart,&QPushButton::clicked,this,&VictoryScene::restartMSG);
    connect(ui->restart,&QPushButton::clicked,this,[=](){
        this->hide();
    });
    connect(ui->quit,&QPushButton::clicked,this,&VictoryScene::quitMSG);
    connect(ui->quit,&QPushButton::clicked,this,[=](){
        this->hide();
    });
}

VictoryScene::~VictoryScene()
{
    delete ui;
}

bool VictoryScene::judgeWinner(Cards cards)
{
    if(cards.isEmpty()){
        return true;
    }else{
        return false;
    }
}

void VictoryScene::sendWinnerInf(int i)
{
    QString dir;
    switch(i){
    case 0: dir = QString("左方机器人"); break;
    case 1: dir = QString("右方机器人"); break;
    case 2: dir = QString("上方机器人"); break;
    case 3: dir = QString("你"); break;
    }

    winnerText=QString("恭喜%1获胜！").arg(dir);
    ui->winnerText->setText(winnerText);
}

void VictoryScene::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
//    QPainter p(ui->widget);

//    victoryBackGround.load(":/scene/res/background/victoryscene.jpg");
//    p.drawPixmap((WINDOWWIDTH-VICTORY_W)/2,(WINDOWHEIGHT-VICTORY_H)/2,victoryBackGround);

//    //创建QPixmap对象
//    QPixmap pix;
//    //加载标题资源
//    pix.load(":/icon/res/icon/gametitle.png");
//    //绘制标题
//    p.drawPixmap(486,145,pix);
}

