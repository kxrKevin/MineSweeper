#include "qrightclickbutton.h"
#include <QMouseEvent>
#include <QPushButton>

QRightClickButton::QRightClickButton(QWidget *parent) : QPushButton(parent){
}

void QRightClickButton::mousePressEvent(QMouseEvent *e)
{
    if(e->button()==Qt::RightButton)

    
        emit rightClicked();
    mousePressEvent(QMouseEvent *e)
}