QT       += core widgets
TARGET = minesweeper
TEMPLATE = app 

CONFIG += c++11

SOURCES += \
    main.cpp \
    MineButton.cpp \
    ButtonGrid.cpp
    qrightclickbutton.cpp

HEADERS += \
    MineButton.h \
    ButtonGrid.h
    qrightclickbutton.h
