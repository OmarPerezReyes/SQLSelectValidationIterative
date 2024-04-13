#include <QApplication>
#include "grid.h"
using namespace std;

// COMPILAR Y EJECUTAR APP
// qmake -project && echo "QT += widgets" >> $(basename "$(pwd)").pro && qmake && make && ./$(basename "$(pwd)")

// Generar ventana principal
int main( int argc, char *argv[] ) {	
	QApplication app(argc, argv); 
	Grid window;
	window.setWindowTitle("SQL SELECT - RAILWAY");
	window.showMaximized();
	
	return app.exec();		
}
