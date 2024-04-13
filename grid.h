#pragma once

#include <QWidget>
#include <QCheckBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QCheckBox>
#include "window.h"

class Grid : public QWidget {

  public:
    Grid(QWidget *parent = nullptr);

    private:
    Window *window;
    
    //Formularios (Inputs, botones, etc)
    QLabel* lblOrigen;
    QLineEdit* txtDestino;
    QCheckBox* check;
    QPushButton* btnTest;
    
    void openFloatWindow();
};
