
/*
Kevin Li - 251172272 - kli575@uwo.ca - Feb 07 2024

MineButton HeaderFile

Description: This headerfile declares all required attributes/functions for the buttonfrid class

*/

#ifndef BUTTONGRID_H
#define BUTTONGRID_H
// QT Libraries
#include <iostream>
#include <random>
#include <QApplication>
#include <QWidget>
#include <QtWidgets>
#include <QPushButton>
#include <QGridLayout>
#include <QPixmap>
#include <QIcon>
#include <QMouseEvent>
// HeaderFiles
#include "minebutton.h"

class ButtonGrid : public QWidget{
    Q_OBJECT

public:
    ButtonGrid(QWidget *parent = nullptr);


private slots:
    void itsabomb();
    void notabomb();
    void flagIt();
    void expand(int x, int y);

private:
    int rows;
    int cols;
    MineButton* mminebuttons[16][30];
};

#endif // BUTTONGRID_H
