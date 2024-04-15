#pragma once

#include <QWidget>
#include <QRect>
#include <QMenu>
#include <list>
#include <tuple>

#include "clause.h"
#include "arrow.h"

class Window : public QWidget {

    public:
        Window(QWidget *parent = 0);
        ~Window();
        void mousePressEvent(QMouseEvent* event);

    protected:
        void paintEvent(QPaintEvent *event);
        void timerEvent(QTimerEvent *event);

    private:
    	std::list<Clause*> clauses;
    	std::list<Arrow*> arrows;
    	std::list<int> changeColor;
    	//Atributos
    	int timerID;
    	QRect txt;
    	
    	//Metodos Window
    	void doPainting();
    	
    	//Metodos extras
        void drawArrow(QPainter& painter, QPoint start, QPoint end, bool point);                 
};
