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

#include <QDebug>

#include "grid.h"
#include "window.h"
#include <iostream>
using namespace std;

Grid::Grid(QWidget *parent)
    : QWidget(parent) {        

	//GRID PRINCIPAL
    auto *grid = new QGridLayout(this);
    grid->setVerticalSpacing(15);
    grid->setHorizontalSpacing(10);
    
    //Variable para modificar o llamar funciones de window.cpp
    window = new Window(this);

	//Botones
    btnTest = new QPushButton("Ejecutar railway", this);   
    txtQuery = new QTextEdit("", this);
    txtQuery->setPlaceholderText("Ingrese una consulta SQL");	

	grid->addWidget(window);

	//Añadir el GRID principal a la ventana
    setLayout(grid);

	//Conexión de botones
    connect(btnTest, &QPushButton::clicked, this, &Grid::startRailway); 
}

void Grid::startRailway() {	
	QString consulta = txtQuery->toPlainText();
	txtQuery->setText("");
	
	qDebug() << consulta << "\n";
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
