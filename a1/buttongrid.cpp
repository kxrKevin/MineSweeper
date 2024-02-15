/*
Kevin Li - 251172272 - kli575@uwo.ca - Feb 07 2024

ButtonGrid Class

Description: This class contains all required attributes of the minesweeper button grid, along with game mechanics

*/

//QT Libraries
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
#include <QMessageBox>
#include <QTimer>
#include <QObject>
#include <cstdlib>
//Header Files
#include "ButtonGrid.h"
#include "MineButton.h"


/*
The Constructor method is responsible for generating the button grid and assigning mines for the game.
After placing the bombs, the method reiterates through all buttons to assign the appropriate number values to buttons without a mine
*/
ButtonGrid::ButtonGrid(QWidget *parent) : QWidget(parent), rows(16), cols(30){
        
    QGridLayout *gridLayout = new QGridLayout(this);

    // MineButton *mminebuttons[rows][cols];
    
    // For Loop that randomly places the bombs
    for(int row = 0; row < rows; ++row){
        for(int col = 0; col < cols; ++col){

            // Create Button 
            MineButton *mbutton = new MineButton();

            mbutton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            mbutton->setMinimumSize(40, 40);  // Adjust the size as needed
            mbutton->setMaximumSize(40, 40);

            // minebuttons[row][col] = button;
            mminebuttons[row][col] = mbutton;
            mminebuttons[row][col]->setX(col);
            mminebuttons[row][col]->setY(row);

            // sweeperminebuttons[row][col] = mbutton;

            gridLayout->addWidget(mbutton, row, col);

            // Generate Random Number
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> distrib(1, 3);
            int randomInt = distrib(gen);

            if(randomInt == 1){
                mminebuttons[row][col]->isaBomb();
                connect(mminebuttons[row][col], &MineButton::clicked, this, &ButtonGrid::itsabomb);
                connect(mminebuttons[row][col], &MineButton::rightClicked, this, &ButtonGrid::flagIt);
            }
            else{
                connect(mminebuttons[row][col], &MineButton::clicked, this, &ButtonGrid::notabomb); 
                connect(mminebuttons[row][col], &MineButton::rightClicked, this, &ButtonGrid::flagIt);
            }

        }
    }
    setLayout(gridLayout);

    for(int row = 0; row < rows; row++){
        for(int col = 0; col < cols; col++){
            // Looks for Mine Squares
            if(mminebuttons[row][col]->checkBomb() == true){

                // Update Bomb Counter to Surrounding Squares
                
                // Left
                if(col - 1 >= 0){
                    // LeftTop
                    if(row - 1 >= 0){
                        if(mminebuttons[row - 1][col - 1]->checkBomb() == false){mminebuttons[row - 1][col - 1]->addBomb();}
                    }
                    // LeftBottom
                    if(row + 1 < rows){
                        if(mminebuttons[row + 1][col - 1]->checkBomb() == false){mminebuttons[row + 1][col - 1]->addBomb();}
                    }
                    // LeftMiddle
                    if(mminebuttons[row][col - 1]->checkBomb() == false){mminebuttons[row][col - 1]->addBomb();} 
                }

                // Center Top
                if(row - 1 >= 0){
                    if(mminebuttons[row - 1][col]->checkBomb() == false){mminebuttons[row - 1][col]->addBomb();}
                }
                // Center Bottom
                if(row + 1 < rows){
                    if(mminebuttons[row + 1][col]->checkBomb() == false){mminebuttons[row + 1][col]->addBomb();}
                }

                // Right
                if(col + 1 < cols){
                    // LeftTop
                    if(row - 1 >= 0){
                        if(mminebuttons[row - 1][col + 1]->checkBomb() == false){mminebuttons[row - 1][col + 1]->addBomb();}
                    }
                    // LeftBottom
                    if(row + 1 < rows){
                        if(mminebuttons[row + 1][col + 1]->checkBomb() == false){mminebuttons[row + 1][col + 1]->addBomb();}
                    }
                    // LeftMiddle
                    if(mminebuttons[row][col + 1]->checkBomb() == false){mminebuttons[row][col + 1]->addBomb();} 
                }
            }
        }
    } 
}

/*
Slot Method that reacts to clicking on a mine button.
This causes the button to display a bomb icon and initiate a pop up window that gives the user a choice to replay or close the program
*/

void ButtonGrid::itsabomb() {
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if(button){

        button->setIcon(QIcon("bomb.png"));
        button->setIconSize(QSize(32, 32)); 

        for(int row = 0; row < rows; ++row){
            for(int col = 0; col < cols; ++col){
                if(mminebuttons[row][col]->checkBomb()){
                    mminebuttons[row][col]->setIcon(QIcon("bomb_explode.png"));
                    mminebuttons[row][col]->setIconSize(QSize(32, 32)); 
                }
                else{
                    if(mminebuttons[row][col]->bombCounter() > 0){
                        mminebuttons[row][col]->setText(QString::number(mminebuttons[row][col]->bombCounter()));
                    }
                    else{
                        mminebuttons[row][col]->setIcon(QIcon("grey.png"));
                        mminebuttons[row][col]->setIconSize(QSize(40, 40)); 
                    }
                }
            }
        }

        QMessageBox::StandardButton reply = QMessageBox::question(nullptr, "GameOver", "Game Over!! Do you want to retry?", QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            qApp->quit(); // Quit the application
            QProcess::startDetached(qApp->arguments()[0], qApp->arguments()); // Restart the application
        } else {
            qApp->quit(); // Quit the application
            exit(EXIT_SUCCESS);
        } 
    }
}

/*
Slot Method that reacts to clicking on a non mine button
Everytime a non-mine button is clicked this method must check if there are no more remaining unclicked non-mine buttons(which leads to the game win)
Clicking an Empty slot initiates the recursive "expand" method. More on this below
*/

void ButtonGrid::notabomb() {
    MineButton *button = qobject_cast<MineButton*>(sender());
    button->clickIt();
    if(button->bombCounter() > 0){
        // Displays number of nearby bombs
        button->setText(QString::number(button->bombCounter()));
    }
    else{

        button->setIcon(QIcon("grey.png"));
        button->setIconSize(QSize(40, 40));  

        int xx = button->getX();
        int yy = button->getY();

        expand(xx, yy);

    }

    bool win = true;

    // Run a for loop to check if all non explosive boxes have been opened
    for(int row = 0; row < rows; row++){
        for(int col = 0; col < cols; col++){
            if(!mminebuttons[row][col]->checkBomb() && !mminebuttons[row][col]->checkClicked()){
                win = false;
            }
        }
    }

    if(win){
        QMessageBox::information(nullptr, "WinGame", "YOU WON!!");
        qApp->quit(); // Quit the application
        QProcess::startDetached(qApp->arguments()[0], qApp->arguments()); // Restart the application 
    }
}

/*
The expand method recursive explores neighboring buttons that do not have a mine
*/
void ButtonGrid::expand(int x, int y){

    // Update Bomb Counter to Surrounding Squares
    // Rows are y
    // Columns are X
    int col = x;
    int row = y;

    // Left 
    if(col - 1 >= 0){
        // LeftTop
        if(row - 1 >= 0){
            if(mminebuttons[row -1][col -1]->bombCounter() > 0 && !mminebuttons[row -1][col -1]->checkBomb()){
                mminebuttons[row -1][col -1]->clickIt();
                mminebuttons[row -1][col -1]->setText(QString::number(mminebuttons[row -1][col -1]->bombCounter()));
            }
            else{
                mminebuttons[row -1][col -1]->setIcon(QIcon("grey.png"));
                expand(x-1,y-1);
            }
        }
        // LeftBottom
        if(row + 1 < rows){
            if(mminebuttons[row +1][col -1]->bombCounter() > 0 && !mminebuttons[row +1][col -1]->checkBomb()){
                mminebuttons[row +1][col -1]->clickIt();
                mminebuttons[row +1][col -1]->setText(QString::number(mminebuttons[row +1][col -1]->bombCounter()));
            }
            else{
                mminebuttons[row +1][col -1]->setIcon(QIcon("grey.png"));
                expand(x-1, y+1);
            }
        }
        // LeftMiddle
        if(mminebuttons[row][col -1]->bombCounter() > 0 && !mminebuttons[row][col -1]->checkBomb()){
            mminebuttons[row][col -1]->clickIt();
            mminebuttons[row][col -1]->setText(QString::number(mminebuttons[row][col -1]->bombCounter()));            
        }
        else{
            mminebuttons[row][col -1]->setIcon(QIcon("grey.png"));
            expand(x-1, y);
        }
    }

    // Center Top
    if(row - 1 >= 0){
        if(mminebuttons[row -1][col]->bombCounter() > 0 && !mminebuttons[row -1][col]->checkBomb()){
            mminebuttons[row -1][col]->clickIt();
            mminebuttons[row -1][col]->setText(QString::number(mminebuttons[row -1][col]->bombCounter())); 
        }
        else{
            mminebuttons[row -1][col]->setIcon(QIcon("grey.png"));
            expand(x, y-1);
        }
    }
    // Center Bottom
    if(row + 1 < rows){
        if(mminebuttons[row +1][col]->bombCounter() > 0 && !mminebuttons[row +1][col]->checkBomb()){
            mminebuttons[row +1][col]->clickIt();
            mminebuttons[row +1][col]->setText(QString::number(mminebuttons[row +1][col]->bombCounter())); 
        }
        else{
            mminebuttons[row +1][col]->setIcon(QIcon("grey.png"));
            expand(x, y+1);
        }
    }

    // Right
    if(col + 1 < cols){
        // RightTop
        if(row - 1 >= 0){
            if(mminebuttons[row -1][col + 1]->bombCounter() > 0 && !mminebuttons[row -1][col +1]->checkBomb()){
                mminebuttons[row -1][col + 1]->clickIt();
                mminebuttons[row -1][col + 1]->setText(QString::number(mminebuttons[row -1][col + 1]->bombCounter()));  
            }
            else{
                mminebuttons[row -1][col + 1]->setIcon(QIcon("grey.png"));
                expand(x+1,y-1);
            }
        }
        // RightBottom
        if(row + 1 < rows){
            if(mminebuttons[row +1][col + 1]->bombCounter() > 0 && !mminebuttons[row -1][col +1]->checkBomb()){
                mminebuttons[row +1][col + 1]->clickIt();
                mminebuttons[row +1][col + 1]->setText(QString::number(mminebuttons[row -1][col + 1]->bombCounter()));  
            }
            else{
                mminebuttons[row +1][col + 1]->setIcon(QIcon("grey.png"));
                expand(x+1,y+1);
            }  
        }
        // RightMiddle
        if(mminebuttons[row][col +1]->bombCounter() > 0 && !mminebuttons[row][col +1]->checkBomb()){
            mminebuttons[row][col +1]->clickIt();
            mminebuttons[row][col +1]->setText(QString::number(mminebuttons[row][col +1]->bombCounter()));            
        }
        else{
            mminebuttons[row][col +1]->setIcon(QIcon("grey.png"));
            expand(x+1, y);
        }       
    }

}

/*
flag setter method that is triggered by the user's right-click on a button
*/
void ButtonGrid::flagIt() {
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if(button){
        button->setIcon(QIcon("mine_flag.png"));
        button->setIconSize(QSize(32, 32)); 
    }
}






