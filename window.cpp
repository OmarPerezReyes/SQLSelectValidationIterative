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
#include <QMessageBox>

#include <list>
#include <vector>
#include <iostream>
#include <regex>

#include "window.h"
#include "clause.h"
using namespace std;

// Constructor
Window::Window(QWidget *parent)
: QWidget(parent) {
	error = "";
	setStatements(statements);

	// new Clause( texto, tipo, orden_railway, x, y)
	clauses = {
		//SELECT
		new Clause("SELECT",		"CLAUSE",	1,	20,		20),
		new Clause("DISTINCT",		"CLAUSE",	5,	140,	60),
		new Clause("ALL",			"CLAUSE",	7,	140,	100),		
		new Clause("column",		"COLUMN",	12,	280,	20),		
		//FROM
		new Clause("FROM", 			"CLAUSE",	13,	40,		200),
		new Clause("table", 		"TABLE" ,	13,	160,	200),
		//JOIN
		new Clause("JOIN", 			"TABLE",	15,	280, 	200 ),
		//WHERE
		new Clause("WHERE",			"CLAUSE",	18,	40,		300),
		new Clause("expr",			"COLUMN",	18,	160,	300),
		//ORDER BY
		new Clause("ORDER",			"CLAUSE",	20,	40,		400),
		new Clause("BY",			"CLAUSE",	20,	160,	400),
		new Clause("expr",			"COLUMN",	20,	280,	400),
		//LIMIT - OFFSET
		new Clause("LIMIT",			"CLAUSE",	22,	40,		500),
		new Clause("expr",			"COLUMN",	22,	160,	500),
		new Clause("OFFSET",		"CLAUSE",	24,	280,	500),
		new Clause("expr",			"COLUMN",	24,	400,	500),
		//GROUP BY - HAVING
		new Clause("GROUP", 		"CLAUSE" ,	28,	40,		600),
		new Clause("BY",			"CLAUSE",	28,	160,	600),
		new Clause("expr",			"COLUMN",	28,	280,	600),
		new Clause("HAVING",		"CLAUSE",	30,	400,	600),
		new Clause("expr",			"COLUMN",	30,	520,	600)
	};
	
	// new Arrow( punto_inicio, punto_fin, orden_railway, tiene:punta )
	arrows = {		
		//INICIO		
		new Arrow(QPoint(0,35), QPoint(20,35), 0, 1),
		
		//SELECT -> DIS | ALL | COL
		new Arrow(QPoint(120, 35), QPoint(125, 35), 2, 1), // COL | DIS | ALL	
		new Arrow(QPoint(120, 35), QPoint(260, 35), 3, 1), // SEL -> COL
		
		//SELECT -> DISTINCT
		new Arrow(QPoint(125, 35), QPoint(125, 70), 4, 1), // LINEA
		new Arrow(QPoint(125, 70), QPoint(140, 70), 5, 1), // FLECHA
						
		//SELECT -> ALL		
		new Arrow(QPoint(125, 35), QPoint(125, 120), 6, 1), //LINEA
		new Arrow(QPoint(125, 120), QPoint(140, 120), 7, 1), //FLECHA
		
		//DISTINCT -> COLUMN
		new Arrow(QPoint(240, 70), QPoint(260, 70), 8, 1),
		new Arrow(QPoint(260, 70), QPoint(260, 35), 9, 1),
		
		// ALL -> COLUMN		
		new Arrow(QPoint(240, 120), QPoint(260, 120), 10, 1),
		new Arrow(QPoint(260, 120), QPoint(260, 70), 11, 1),
		
		//SELECT (OPC) -> COLUMN
		new Arrow(QPoint(260, 35), QPoint(280, 35), 12, 1),	
		new Arrow(QPoint(380, 35), QPoint(400, 35), 12, 0),
		new Arrow(QPoint(400, 35), QPoint(400, 160), 12, 0),
		new Arrow(QPoint(400, 160), QPoint(20, 160), 12, 0),
		new Arrow(QPoint(20, 160), QPoint(20, 215), 12, 0),
		new Arrow(QPoint(20, 215), QPoint(40, 215), 12, 1),
		
		//FROM -> TABLE
		new Arrow(QPoint(140, 215), QPoint(160, 215), 13, 1),
		
		//FROM TABLE -> JOIN
		new Arrow(QPoint(260, 215), QPoint(270, 215), 14, 1),
		new Arrow(QPoint(270, 215), QPoint(280, 215), 15, 1),
		
		//FROM -> WHERE
		new Arrow(QPoint(270, 215), QPoint(270, 260), 16, 0),	

		// JOIN -> WHERE		
		new Arrow(QPoint(380, 215), QPoint(400, 215), 15, 0),
		new Arrow(QPoint(400, 215), QPoint(400, 260), 15, 0),
		new Arrow(QPoint(400, 260), QPoint(270, 260), 15, 1),		
		
		// -> WHERE
		new Arrow(QPoint(270, 260), QPoint(20, 260), 17, 1),
		new Arrow(QPoint(20, 260), QPoint(20, 315), 17, 1),
		new Arrow(QPoint(20, 315), QPoint(40, 315), 17, 1),
		
		//WHERE -> EXPR
		new Arrow(QPoint(140, 315), QPoint(160, 315), 18, 1),
		
		//WHERE EXPR -> ORDER BY
		new Arrow(QPoint(260, 315), QPoint(400, 315), 18, 0),
		new Arrow(QPoint(400, 315), QPoint(400, 360), 18, 0),
		new Arrow(QPoint(400, 360), QPoint(20, 360), 18, 1),
		new Arrow(QPoint(20, 360), QPoint(20, 415), 19, 1),	//v 		
				
		//ORDER BY -> ordering-term
		new Arrow(QPoint(20, 415), QPoint(40, 415), 20, 1), //->
		new Arrow(QPoint(140, 415), QPoint(160, 415), 20, 1), // ->
		new Arrow(QPoint(260, 415), QPoint(280, 415), 20, 1), // ->
		
		//ORDER BY orderint-term -> LIMIT
		new Arrow(QPoint(380, 415), QPoint(400, 415), 20, 0),
		new Arrow(QPoint(400, 415), QPoint(400, 460), 20, 0),
		new Arrow(QPoint(400, 460), QPoint(20, 460), 20, 0),
		new Arrow(QPoint(20, 460), QPoint(20, 515), 21, 1),
		new Arrow(QPoint(20, 515), QPoint(40, 515), 22, 1),
		
		//LIMIT -> COUNT
		new Arrow(QPoint(140, 515), QPoint(160, 515), 22, 1),
		
		//LIMIT -> OFFSET
		new Arrow(QPoint(260, 515), QPoint(270, 515), 23, 1),
		new Arrow(QPoint(270, 515), QPoint(280, 515), 24, 1),
		
		//LIMIT count OFFSET expr
		new Arrow(QPoint(380, 515), QPoint(400, 515), 24, 1),
		
		//LIMIT -> GROUP BY DIRECTO
		new Arrow(QPoint(270, 515), QPoint(270, 560), 25, 1),
		
		//LIMIT .. OFFSET -> GROUP
		new Arrow(QPoint(500, 515), QPoint(600, 515), 24, 0),
		new Arrow(QPoint(600, 515), QPoint(600, 560), 24, 0),
		new Arrow(QPoint(600, 560), QPoint(270, 560), 24, 1),
		
		new Arrow(QPoint(270, 560), QPoint(20, 560), 26, 1),
		new Arrow(QPoint(20, 560), QPoint(20, 615), 27, 1),
		new Arrow(QPoint(20, 615), QPoint(40, 615), 28, 1),
		
		//GROUP -> BY
		new Arrow(QPoint(140, 615), QPoint(160, 615), 28, 1),
		
		//GROUP BY -> expr
		new Arrow(QPoint(260, 615), QPoint(280, 615), 28, 1),
		
		//GROUP BY expr -> HAVING 
		new Arrow(QPoint(380, 615), QPoint(390, 615), 29, 1), //->
		new Arrow(QPoint(390, 615), QPoint(400, 615), 30, 1), //->
		new Arrow(QPoint(500, 615), QPoint(520, 615), 30, 1), //->
		
		//GROUP BY -> END DIRECTO
		new Arrow(QPoint(390, 615), QPoint(390, 660), 31, 1), //v		
		
		//FROM -> END	
		new Arrow(QPoint(20, 315), QPoint(20,360), 33, 1),
		
		// FLECHAS ABAJO
		new Arrow(QPoint(20, 415), QPoint(20, 460), 34, 1),
		new Arrow(QPoint(20, 515), QPoint(20, 560), 35, 1),
		new Arrow(QPoint(20, 615), QPoint(20, 660), 36, 1),
		
		//FLECHAS DER ->
		new Arrow(QPoint(20, 660), QPoint(390, 660), 36, 1),
		new Arrow(QPoint(390, 660), QPoint(650, 660), 32, 1),
		new Arrow(QPoint(570, 630), QPoint(570, 660), 40, 1)
	};
	
	//Railway - Orden de la consulta
	//changeColor = { 0, 1, 2, 3, 12, 13, 14, 15, 17, 33, 19, 34, 21, 35, 27, 28, 31, 32 };
	
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
	
		//Establecer el color del painter dependiendo...			
		painter.setPen(QPen(Qt::black, 2));
		if( !changeColor.empty() ) {
			if( c->getID() == changeColor.front() ) {
				painter.setPen(QPen(Qt::green, 2));
			}
		}
			
		if( c->getType() == "CLAUSE" )    	
		    painter.drawRoundedRect(rectangle, 10, 10);
		else
		    painter.drawRoundedRect(rectangle, 0, 0);		    		    		
		
		//Dibujar texto
	    txt = QRect(c->getX(), c->getY(), 100, 30);
        painter.drawText(txt, Qt::AlignCenter, c->getClause() );
	}
	for(auto& a: arrows) {		
		painter.setPen(QPen(Qt::black, 2));
		if( !changeColor.empty() ) {			
			if( a->getID() == changeColor.front() ) {
				painter.setPen(QPen(Qt::green, 2));
			}
		}						
		drawArrow(painter, a->getStart(), a->getEnd(), a->getPoint());
	}
	
	//Si hay algún error lo imprime por mientras xd
	if( !isValid && error != "") {
		cout << error << endl;
		QMessageBox::information(nullptr, "¡Consulta SELECT no válida!", QString::fromStdString(error) );
		error = "";
	}		    
	
	if( !changeColor.empty() ) {
		cout << changeColor.front() << endl;
		changeColor.pop_front();
	}	
	
	killTimer(timerID);
	timerID = startTimer(500);	
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

//Incluye en el vector todos los estados de una consulta SQL en SQLite
void Window::setStatements( vector<tuple<string,string,int>>& statements ) {
	string IDENTIFIER = "\\w+";
	string POSITIVE_NUMBER = "\\b\\d+\\b";
	string SPACE = "\\s+";
	
	// ID = y || ID != y || ID > y ...
	string COMPARATION = "(=|>|<|!=|<>)" + SPACE + "\\b\\d+\\b";
	// BETWEEN x AND y
	string BETWEEN = "BETWEEN" + SPACE + POSITIVE_NUMBER + SPACE + "AND" + SPACE + POSITIVE_NUMBER;
	
	//EXPRESIONES DEL HAVING
	string COUNT = 	"COUNT\\(" 	+ IDENTIFIER + "\\)" + SPACE + "(" + COMPARATION + "|"+ BETWEEN +")";
	string AVG = 	"AVG\\(" 	+ IDENTIFIER + "\\)" + SPACE + "(" + COMPARATION + "|"+ BETWEEN +")";
	string SUM = 	"SUM\\(" 	+ IDENTIFIER + "\\)" + SPACE + "(" + COMPARATION + "|"+ BETWEEN +")";
	string _MAX = 	"MAX\\(" 	+ IDENTIFIER + "\\)" + SPACE + "(" + COMPARATION + "|"+ BETWEEN +")";
	string _MIN = 	"MIN\\(" 	+ IDENTIFIER + "\\)" + SPACE + "(" + COMPARATION + "|"+ BETWEEN +")";
	string LENGTH = "LENGTH\\(" + IDENTIFIER + "\\)" + SPACE + "(" + COMPARATION + "|"+ BETWEEN +")";
	
	//Expresiones de SQLite
	string SELECT = "^SELECT";
	string SELECT_OPT = "\\s+(?:(?:DISTINCT|ALL)\\s+)?";
	string COLUMNS = "(?:\\*|\\b\\w+\\b(?:,\\s*\\b\\w+\\b)*)";
	//string FROM = "\\sFROM\\s\\w+(\\s\\w+)?";
	string FROM = "FROM\\s+\\b(?!SELECT\\b|ALL\\b|DISTINCT\\b|FROM\\b|WHERE\\b|GROUP\\sBY\\b|HAVING\\b|ORDER\\sBY\\b|LIMIT\\b|OFFSET\\b|INNER\\sJOIN\\b|LEFT\\sJOIN\\b|RIGHT\\sJOIN\\b|FULL\\sJOIN\\b|CROSS\\sJOIN\\b|BY\\b|ON\\b|AND\\b|OR\\b|NOT\\b|IN\\b|BETWEEN\\b|LIKE\\b|IS\\b|NULL\\b|AS\\b|ASC\\b|DESC\\b|USING\\b)\\w+(?:\\.\\w+)?\\b";
	string JOIN = "\\s(JOIN|LEFT\\sJOIN|RIGHT\\sJOIN|FULL\\sJOIN)\\s\\w+\\sON\\s\\w+\\.\\w+\\s=\\s\\w+\\.\\w+";
	string WHERE = "\\sWHERE\\s\\w+\\s=\\s\\w+";
	string ORDER_BY = "\\sORDER\\sBY\\s\\w+";
	string LIMIT = "\\sLIMIT\\s\\b\\d+\\b(?:\\sOFFSET\\s\\b\\d+\\b)?";
	string HAVING = "(?:\\sHAVING"+ SPACE +"(" + COUNT + "|" + AVG + "|" + SUM + "|" + "|" + _MAX + "|" + "|" + _MIN + "|" + "|" + LENGTH + ")" + ")?";
	string GROUP_BY = "\\sGROUP" + SPACE + "BY" + SPACE + "(" + IDENTIFIER + "\\." + IDENTIFIER + "|" + IDENTIFIER + ")" + HAVING;

	statements = {
        make_tuple(SELECT, "SELECT", 1),       
        make_tuple(SELECT_OPT, "SELECT_OPT", 3),
        make_tuple(COLUMNS, "COLUMNS", 12),        
        make_tuple(FROM, "FROM", 13),                
        make_tuple(JOIN, "JOINS", 15),
        make_tuple(WHERE, "WHERE", 18),
        make_tuple(ORDER_BY, "ORDER_BY", 20),
        make_tuple(LIMIT, "LIMIT-OFFSET", 22),
        make_tuple(GROUP_BY, "GROUP_BY", 28)
    };
} // Fin setStatements

list<int> Window::returnRailway(const string& consulta, vector<tuple<string,string,int>>& statements) {
	//Posible railway de la consulta
    list<int> railway;   
    
	//Busca cada parte del SELECT
    for (vector<tuple<string, string, int>>::iterator it = statements.begin(); it != statements.end();) {
		regex expresion(get<0>(*it)); 
		
		regex select_("^SELECT");
		if(!regex_search(consulta, select_)) {
			railway.push_back(0);
			railway.push_back(1);
			error = "¡La consulta debe empezar por un SELECT!";
			return railway;
		}			
		
		//regex from_("\\sFROM\\s\\w+(\\s\\w+)?");
		regex from_("FROM\\s+\\b(?!SELECT\\b|ALL\\b|DISTINCT\\b|FROM\\b|WHERE\\b|GROUP\\sBY\\b|HAVING\\b|ORDER\\sBY\\b|LIMIT\\b|OFFSET\\b|INNER\\sJOIN\\b|LEFT\\sJOIN\\b|RIGHT\\sJOIN\\b|FULL\\sJOIN\\b|CROSS\\sJOIN\\b|BY\\b|ON\\b|AND\\b|OR\\b|NOT\\b|IN\\b|BETWEEN\\b|LIKE\\b|IS\\b|NULL\\b|AS\\b|ASC\\b|DESC\\b|USING\\b)\\w+(?:\\.\\w+)?\\b");
		if(!regex_search(consulta, from_)) {
			railway.push_back(0);
			railway.push_back(1);
			railway.push_back(2);
			error = "¡Falta seleccionar la TABLA en el FROM (FROM table_name) o la tabla es una palabra reservada de SQL!";
			return railway;
		}
		
		// Buscar si hay alguna coincidencia de cada PARAMETRO del SELECT
		if (!regex_search(consulta, expresion))
		    it = statements.erase(it);
		else {
			//cout << get<1>(*it) << endl;
			
			regex opt("ORDER\\sBY");
			if( get<1>(*it) == "WHERE" ) {				
				if( !regex_search(consulta, opt) ) {
					railway.push_back(34);
				}
			} else if( get<1>(*it) == "ORDER_BY" ) {
				opt = regex("LIMIT");
				if( !regex_search(consulta, opt) ) {
					railway.push_back(35);
				}
			} else if( get<1>(*it) == "GROUP_BY" ) {
				opt = regex("GROUP\\sBY");
				if( !regex_search(consulta, opt) ) {
					railway.push_back(36);
				}
			}			
			
			//Si la consulta tiene DISTINCT o ALL
			if( get<1>(*it) == "SELECT_OPT" ) {
				//IDENTIFICAR PARAMETRO
				regex select_opts( "DISTINCT" );
				int CASE = 0;				
				if( regex_search(consulta, select_opts) ) CASE = 1;
				
				select_opts = regex("ALL");
				if( regex_search(consulta, select_opts) ) CASE = 2;
				
				switch( CASE ) {
					case 1: //DISTINCT
						railway.push_back(4);
						railway.push_back(5);
						railway.push_back(8);
						railway.push_back(9);					
						break;
					case 2: // ALL
						railway.push_back(4);
						railway.push_back(6);
						railway.push_back(7);
						railway.push_back(10);
						railway.push_back(11);
						railway.push_back(9);
						break;
					default: //"ALL"
						railway.push_back(3);
				} //Fin switch
				it++;
				continue;
			} //Fin if
			
			//Si la consulta tiene DISTINCT o ALL
			if( get<1>(*it) == "LIMIT-OFFSET" ) {
				//IDENTIFICAR PARAMETRO
				regex select_opts("OFFSET\\s\\b\\d+\\b");
				int CASE = 0;				
				if( regex_search(consulta, select_opts) ) CASE = 1;				

				railway.push_back(22);
				railway.push_back(23);				
				switch( CASE ) {
					case 1: //DISTINCT
						railway.push_back(24);
						railway.push_back(26);					
						break;
					default: // ALL
						railway.push_back(25);
						railway.push_back(26);
						break;
				} //Fin switch
				it++;
				continue;
			} //Fin if
			
			//Si la consulta tiene DISTINCT o ALL
			if( get<1>(*it) == "GROUP_BY" ) {
				//IDENTIFICAR PARAMETRO
				regex select_opts("HAVING\\s(?:COUNT\\(\\w+\\)\\s(?:=|>|<|!=|<>)\\s\\d+\\b|AVG\\(\\w+\\)\\s(?:=|>|<|!=|<>)\\s\\d+\\b|SUM\\(\\w+\\)\\s(?:=|>|<|!=|<>)\\s\\d+\\b|MAX\\(\\w+\\)\\s(?:=|>|<|!=|<>)\\s\\d+\\b|MIN\\(\\w+\\)\\s(?:=|>|<|!=|<>)\\s\\d+\\b|LENGTH\\(\\w+\\)\\s(?:=|>|<|!=|<>)\\s\\d+\\b)?");
				int CASE = 0;				
				if( regex_search(consulta, select_opts) ) CASE = 1;				

				railway.push_back(28);
				railway.push_back(29);				
				switch( CASE ) {
					case 1:
						railway.push_back(30);
						railway.push_back(40);
						break;
					default:
						railway.push_back(31);
						railway.push_back(32);
						break;
				} //Fin switch
				it++;
				continue;
			} //Fin if
			
			switch( get<2>(*it) ) {
				case 1:	//SELECT
					railway.push_back(1);
					railway.push_back(2);
					break;
				case 13: //FROM
					railway.push_back(13);
					railway.push_back(14);
					railway.push_back(16);
					railway.push_back(17);					
					break;
				case 15: //JOIN
					railway.pop_back();
					railway.pop_back();
					railway.push_back(15);
					railway.push_back(17);
					break;
				default:
					railway.push_back( get<2>(*it) );
			} //Fin switch
			++it;														
		} //Fin else
	} //Fin for	
	return railway;
} //Fin returnRailway()

//Valida el query
bool Window::validateQuery(const string& consulta, vector<tuple<string, string, int>> statements) {   
    //CADENA DEL REGEX - OBTIENE EL SELECT INICIAL DEL VECTOR
    string query = "";          
    // Iterar sobre cada parte de la consulta
    for(int i = 0; i < statements.size(); i++){
    	//CONCATENAR PARAMETROS QUERY
    	query = "";
    	for(int j = 0; j <= i; j++) {
    		query += get<0>( statements.at(j) );    		
    	}
    	if( i < statements.size() - 1 )    	           
	    	query += ".*";
    } //FIN FOR REGEX
    
    regex expresion(query); 
    if (regex_match(consulta, expresion))
    	return true;
    
    return false;
} // Fin validarConsulta()

void Window::checkQuery(string query) {
	changeColor.clear();
	changeColor = returnRailway(query, statements);
	isValid = validateQuery(query, statements);
}
