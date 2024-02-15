/*
Kevin Li - 251172272 - kli575@uwo.ca - Feb 07 2024

MineButton HeaderFile

Description: This headerfile declares all required attributes/functions for the minebutton class

*/

#ifndef MINEBUTTON_H
#define MINEBUTTON_H

#include <QPushButton>
#include <QtWidgets>
#include <QMouseEvent>

class MineButton : public QPushButton{
    Q_OBJECT

public:
    // Constructor 
    explicit MineButton(QWidget*parent = nullptr);
    bool checkBomb();
    bool checkClicked();
    bool checkFlag();
    int bombCounter();
    int getX();
    int getY();
    void addBomb();
    void isaBomb();
    void setFlag();
    void clickIt();
    void setX(int n);
    void setY(int n);

signals:
    void leftClicked();
    void rightClicked();

private slots:
    void mousePressEvent(QMouseEvent *event);

private:
    int bombCount;
    int x;
    int y;
    bool isBomb;
    bool isClicked;
    bool isFlag;


//protected:
    // void mousePressEvent(QMouseEvent *event) override;
};

#endif // MINEBUTTON_H
