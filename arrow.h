#pragma once

#include <QString>
#include <QPoint>

class Arrow {
	public:
		Arrow(QPoint start, QPoint end, int id, bool point) {
			this->start = start;
			this->end = end;
			this->id = id;
			this->point = point;
		}
		
		QPoint getStart() {
			return start;	
		}
		QPoint getEnd() {
			return end;
		}
		int getID() {
			return id;
		}
		bool getPoint() {
			return point;
		}
		
	private:
		QPoint start;
		QPoint end;
		bool point;
		int id;
};
