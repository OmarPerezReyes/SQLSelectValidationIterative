#pragma once

#include <QWidget>
#include <QRect>
#include <QMenu>
#include <QString>
#include <string>
#include <list>
#include <tuple>
#include <vector>
#include "clause.h"
#include "arrow.h"
using namespace std;

class Window : public QWidget {

    public:
        Window(QWidget *parent = 0);
        ~Window();
        void mousePressEvent(QMouseEvent* event);
        //Devuelve el railway o camino de la consulta
		list<int> returnRailway(const string& consulta, vector<tuple<string,string,int>>& statements);
		//Validar si la consulta es valida
		bool validateQuery(const string& consulta, vector<tuple<string,string,int>> statements);
		void setStatements(vector<tuple<string,string,int>>& statements);
		void checkQuery(string query);

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
    	bool isValid;
    	vector<tuple<string, string, int>> statements;    	
    	string error;
    	
    	//Metodos Window
    	void doPainting();
    	
    	//Metodos extras
        void drawArrow(QPainter& painter, QPoint start, QPoint end, bool point);                 
};
