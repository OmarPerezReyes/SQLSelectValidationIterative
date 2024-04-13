#include <QGridLayout>
#include <QLineEdit>
#include <QString>
#include <QMessageBox>
#include <QFileDialog>
#include <QPixmap>
#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QWheelEvent>
#include <QSlider>
#include <QtCore/qmath.h>
#include <QHeaderView>

#include "grid.h"
#include "window.h"
#include <iostream>
using namespace std;

Grid::Grid(QWidget *parent)
    : QWidget(parent) {
    
    //Variable para modificar o llamar funciones de window.cpp
    window = new Window(this);

	//GRID PRINCIPAL
    auto *grid = new QGridLayout(this);
    grid->setVerticalSpacing(15);
    grid->setHorizontalSpacing(10);
    
    //Layouts divisirios
    QHBoxLayout *rightLayout = new QHBoxLayout();
    QHBoxLayout *leftLayout = new QHBoxLayout();   

	//Botones
    btnTest = new QPushButton("Abrir ventana flotante", this);   

	//Añadir al GRID
	rightLayout->addWidget(btnTest);
    grid->addLayout(rightLayout, 0, 0);
    grid->addLayout(leftLayout, 0, 1);

	//Añadir el GRID principal a la ventana
    setLayout(grid);

	//Conexión de botones
    connect(btnTest, &QPushButton::clicked, this, &Grid::openFloatWindow);        
}

void Grid::openFloatWindow() {

    QHBoxLayout *layout = new QHBoxLayout();

    // Crear un diálogo para mostrar el nuevo layout flotante
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("Ventana flotante");
    dialog->setLayout(layout);
    dialog->setMinimumWidth(400);
    dialog->setMinimumHeight(400);
    dialog->show();
    dialog->exec();
}
