#pragma once

#include <QString>

class Clause {
	public:
		Clause(QString clause, QString type, int id, int x, int y) {
			this->clause = clause;
			this->type = type;
			this->id = id;
			this->x = x;
			this->y = y;
		}

		QString getClause() { return clause; }
		QString getType() { return type; }
		int getX() { return x; }
		int getY() { return y; }		
		int getID() { return id; }	
	private:
		QString clause;
		QString type;
		int id;
		int x;
		int y;
};
