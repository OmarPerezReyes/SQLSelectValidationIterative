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
#include "clause.h"
using namespace std;

// Constructor
Window::Window(QWidget *parent)
: QWidget(parent) {
	clauses = {
		//SELECT
		new Clause("SELECT",		"CLAUSE",	1,	20,		20),
		new Clause("DISTINCT",		"CLAUSE",	2,	140,	60),
		new Clause("ALL",			"CLAUSE",	2,	140,	100),		
		new Clause("column",		"COLUMN",	3,	260,	20),		
		//FROM
		new Clause("FROM", 			"CLAUSE",	4,	40,		200),
		new Clause("table-or_subq", "TABLE" ,	5,	160,	200),
		//JOIN
		new Clause("join-clause", 	"TABLE",	6,	160, 	250 ),
		//WHERE
		new Clause("WHERE",			"CLAUSE",	6,	40,		300),
		new Clause("expr",			"COLUMN",	7,	160,	300),
		//ORDER BY
		new Clause("ORDER",			"CLAUSE",	8,	40,		400),
		new Clause("BY",			"CLAUSE",	9,	160,	400),
		new Clause("ordering-term",	"COLUMN",	10,	280,	400),
		//LIMIT - OFFSET
		new Clause("LIMIT",			"CLAUSE",	11,	40,		500),
		new Clause("expr",			"COLUMN",	12,	160,	500),
		new Clause("OFFSET",		"CLAUSE",	13,	280,	500),
		new Clause("expr",			"COLUMN",	14,	400,	500),
		//GROUP BY - HAVING
		new Clause("GROUP", 		"CLAUSE" ,	15,	40,		600),
		new Clause("BY",			"CLAUSE",	16,	160,	600),
		new Clause("expr",			"COLUMN",	17,	280,	600),
		new Clause("HAVING",		"CLAUSE",	18,	400,	600),
		new Clause("expr",			"COLUMN",	19,	520,	600)
	};
	
	arrows = {
		//INICIO
		new Arrow(QPoint(0,35), QPoint(20,35), 0, 1),
		//SELECT -> COLUMN
		new Arrow(QPoint(120, 35), QPoint(260, 35), 1, 1),
		//SELECT -> (DISTINCT | ALL)
		new Arrow(QPoint(125, 35), QPoint(125, 120), 1, 0),
		//SELECT -> DISTINCT
		new Arrow(QPoint(125, 70), QPoint(140, 70), 1, 1),
		//SELECT -> ALL
		new Arrow(QPoint(125, 120), QPoint(140, 120), 2, 1),
		//COLUMN -> FROM
		new Arrow(QPoint(360, 35), QPoint(400, 35), 3, 0),
		new Arrow(QPoint(400, 35), QPoint(400, 160), 3, 0),
		new Arrow(QPoint(400, 160), QPoint(20, 160), 3, 0),
		new Arrow(QPoint(20, 160), QPoint(20, 215), 3, 0),
		new Arrow(QPoint(20, 215), QPoint(40, 215), 3, 1),
		//FROM -> TABLE
		new Arrow(QPoint(140, 215), QPoint(160, 215), 2, 1),
		//TABLE -> JOIN
		new Arrow(QPoint(260, 215), QPoint(400, 215), 2, 0),
		new Arrow(QPoint(360, 35), QPoint(400, 35), 2, 0),
	};
		
	changeColor = {
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20
	};
	
	timerID = startTimer(10);
	
} //Fin constructor

//Destructor - Eliminar memoria de los objetos
Window::~Window() {
	for(auto& c: clauses) {
		delete c;
	}
	clauses.clear();
	for(auto& a: arrows) {
		delete a;
	}
	arrows.clear();
	changeColor.clear();
} //Fin destructor

// Método de bucle del programa
void Window::paintEvent(QPaintEvent *e) {   
	Q_UNUSED(e);
	doPainting();
} //Fin funcion paintEvent

//Función de dibujado
void Window::doPainting() {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

	//Dibujar CLAUSES Y COLUMNS
	for(auto& c: clauses) {
		QRectF rectangle(c->getX(), c->getY(), 100, 30);
		
		if( !changeColor.empty() ) {
			if( c->getID() == changeColor.front() ) {
				painter.setPen(QPen(Qt::green, 2));
			}
			else painter.setPen(QPen(Qt::black, 2));
		}				
			
		if( c->getType() == "CLAUSE" )    	
		    painter.drawRoundedRect(rectangle, 10, 10);
		else
		    painter.drawRoundedRect(rectangle, 0, 0);		    		    		
		
		//Dibujar texto
	    txt = QRect(c->getX(), c->getY(), 100, 30);
        painter.drawText(txt, Qt::AlignCenter, c->getClause() );
	}
	painter.setPen(QPen(Qt::black, 2));
	for(auto& a: arrows) {
		if( !changeColor.empty() ) {
			if( a->getID() == changeColor.front() ) {
				painter.setPen(QPen(Qt::green, 2));
			}
			else painter.setPen(QPen(Qt::black, 2));			
		}				
		drawArrow(painter, a->getStart(), a->getEnd(), a->getPoint());
	}		
	
	killTimer(timerID);
	timerID = startTimer(500);					    
	
	if( !changeColor.empty()  )
		changeColor.pop_front();			   			
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
void Window::drawArrow(QPainter& painter, QPoint start, QPoint end, bool point) {
	//Tamaño de la punta de la flecha
	qreal arrowSize = 10;

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
	if( !point ) return;
	painter.setBrush(QColor(255,255,255));
	QPolygonF arrowHead;
	arrowHead.clear();
	arrowHead << line.p1() 
		    << arrowP1 
		    << arrowP2;
	painter.drawPolygon(arrowHead);
} // Fin funcion drawArrow
