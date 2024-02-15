/*
Kevin Li - 251172272 - kli575@uwo.ca - Feb 07 2024

MineButton Class

Description: This class contains all required attributes of a minesweeper grid button

*/

// QT Libraries
#include <QApplication>
#include <QPushButton>
#include <QtWidgets>
// HeaderFiles
#include "MineButton.h"

using namespace std;

MineButton::MineButton(QWidget* parent) : QPushButton(parent){
    isBomb = false;
    isFlag = false;
    isClicked = false;
    bombCount = 0;
    x = 0;
    y = 0;
} 

// Getter Methods for instance Variables
bool MineButton::checkBomb() {
    return isBomb;
}

bool MineButton::checkClicked(){
    return isClicked;
}

bool MineButton::checkFlag(){
    return isFlag;
}

int MineButton::bombCounter(){
    return bombCount;
}

int MineButton::getX(){
    return x;
}

int MineButton::getY(){
    return y;
}


// Setter Methods for Instance Variables
void MineButton::addBomb(){
    bombCount += 1;
}

void MineButton::isaBomb(){
    isBomb = true;
}

void MineButton::clickIt(){
    isClicked = true;
}

void MineButton::setFlag(){
    isFlag = true;
}

void MineButton::setX(int n){
    x = n;
}

void MineButton::setY(int n){
    y = n;
}

// Method that responds to Mouse Clicks and emits the appropriate signal
void MineButton::mousePressEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton){
        QPushButton::mousePressEvent(event);
    }
    else if(event->button() == Qt::RightButton){
        emit rightClicked();
    }
    
}





