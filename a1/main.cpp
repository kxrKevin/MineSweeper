/*
Kevin Li - 251172272 - kli575@uwo.ca - Feb 07 2024

Main Class

Description: This class icalls the buttongrid class to generate the game GUI and set up mechanics

*/

#include <QApplication>
#include "ButtonGrid.h"

int main(int argc, char *argv[])
{
    QApplication apps(argc, argv);

    ButtonGrid buttonGrid;
    buttonGrid.resize(800, 600); // Set the initial size of the window

    buttonGrid.show();

    return apps.exec();
}
