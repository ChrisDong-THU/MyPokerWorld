QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    buttongroup.cpp \
    card.cpp \
    cardpanel.cpp \
    cards.cpp \
    cardspanel.cpp \
    choosemodescene.cpp \
    chooserulescene.cpp \
    gamecontrol.cpp \
    main.cpp \
    mainscene.cpp \
    mypushbutton.cpp \
    player.cpp \
    playhand.cpp \
    playscene.cpp \
    robotplayhand.cpp \
    robotstrategy.cpp \
    victoryscene.cpp

HEADERS += \
    buttongroup.h \
    card.h \
    cardpanel.h \
    cards.h \
    cardspanel.h \
    choosemodescene.h \
    chooserulescene.h \
    config.h \
    gamecontrol.h \
    mainscene.h \
    mypushbutton.h \
    player.h \
    playhand.h \
    playscene.h \
    robotplayhand.h \
    robotstrategy.h \
    victoryscene.h

FORMS += \
    buttongroup.ui \
    mainscene.ui \
    victoryscene.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
