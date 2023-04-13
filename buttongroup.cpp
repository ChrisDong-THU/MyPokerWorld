#include "buttongroup.h"
#include "ui_buttongroup.h"

ButtonGroup::ButtonGroup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ButtonGroup)
{
    ui->setupUi(this);

    initBtns();
}

ButtonGroup::~ButtonGroup()
{
    delete ui;
}

void ButtonGroup::initBtns()
{
    ui->start->setBtnImg(":/btn/res/btn/fapai.png",":/btn/res/btn/fapai.png");
    ui->pass->setBtnImg(":/btn/res/btn/buyao.png",":/btn/res/btn/buyao.png");
    ui->playhand->setBtnImg(":/btn/res/btn/chupai.png",":/btn/res/btn/chupai.png");

    //设置尺寸 由button自身根据图片大小完成，this则在ui文件中完成

    //连接信号和槽
    connect(ui->start,&MyPushButton::clicked,this,&ButtonGroup::startGame);
    connect(ui->pass,&MyPushButton::clicked,this,&ButtonGroup::pass);
    connect(ui->playhand,&MyPushButton::clicked,this,&ButtonGroup::playHand);

}

void ButtonGroup::setStakeWidget(int i)
{
    ui->stackedWidget->setCurrentIndex(i);
}
