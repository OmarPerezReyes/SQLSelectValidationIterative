#pragma once

#include <QWidget>
#include <QMenu>

class Window : public QWidget {

    public:
        Window(QWidget *parent = 0);
        ~Window();
        void mousePressEvent(QMouseEvent* event);

    protected:
        void paintEvent(QPaintEvent *event);
        void timerEvent(QTimerEvent *event);

    private:
    	//Atributos
    	int timerID;
    	
    	//Metodos Window
    	void doPainting();
    	
    	//Metodos extras
        void drawArrow(QPainter& painter, QPoint start, QPoint end);
                
};
