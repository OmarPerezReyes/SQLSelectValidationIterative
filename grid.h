#pragma once

#include <QWidget>
#include <QCheckBox>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QCheckBox>
#include "window.h"

class Grid : public QWidget {

  public:
    Grid(QWidget *parent = nullptr);

    private:
    Window *window;
    
    //Formularios (Inputs, botones, etc)    
    QTextEdit* txtQuery;
    QPushButton* btnTest;    
    
    void openFloatWindow();
    void startRailway();
};
