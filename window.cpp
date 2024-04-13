#include <QPainter>
#include <QTimer>
#include <QTextStream>
#include <QtWidgets>
#include <QTimer>
#include <QObject>
#include <QColor>
#include <QMenu>
#include <QAction>
#include <QCursor>
#include <QPolygon>
#include <iostream>

#include "window.h"
using namespace std;

// Constructor
Window::Window(QWidget *parent)
: QWidget(parent) {
	timerID = startTimer(10);	
} //Fin constructor

//Destructor - Eliminar memoria de los objetos
Window::~Window() {

} //Fin destructor

// Método de bucle del programa
void Window::paintEvent(QPaintEvent *e) {   
	Q_UNUSED(e);
	doPainting();
} //Fin funcion paintEvent

//Función de dibujado
void Window::doPainting() {
    
} //Fin función de dibujado

// Repaint de la ventana
void Window::timerEvent(QTimerEvent *e) {   
	Q_UNUSED(e);  
	repaint();
} //Fin funcion timerEvent

//DETECTAR CLICK EN EL MOUSE
void Window::mousePressEvent(QMouseEvent* event)
{
	//Detectar lado del mouse
    if(event->button() == Qt::LeftButton) {  }
    else if (event->button() == Qt::RightButton) {}
}

//Función para dibujar una flecha
void Window::drawArrow(QPainter& painter, QPoint start, QPoint end) {
	painter.setRenderHint(QPainter::Antialiasing, true);

	//Tamaño de la punta de la flecha
	qreal arrowSize = 20;

	//Linea de la flecha
	QLineF line(end, start);

	//Angulo de la flecha
	double angle = atan2(-line.dy(), line.dx());
	QPointF arrowP1 = line.p1() + QPointF(sin(angle + M_PI / 3) * arrowSize,
		                                cos(angle + M_PI / 3) * arrowSize);
	QPointF arrowP2 = line.p1() + QPointF(sin(angle + M_PI - M_PI / 3) * arrowSize,
		                                cos(angle + M_PI - M_PI / 3) * arrowSize);

	//Dibujar linea de la flecha
	painter.drawLine(start, end);
	//Dibujar punta de la flecha
	QPolygonF arrowHead;
	arrowHead.clear();
	arrowHead << line.p1() 
		    << arrowP1 
		    << arrowP2;
	painter.drawPolygon(arrowHead);
} // Fin funcion drawArrow
