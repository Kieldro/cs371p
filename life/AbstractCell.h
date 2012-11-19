
#ifndef AbstractCell_h
#define AbstractCell_h

#include "Life.h"

class AbstractCell{
	public:
		virtual bool readChar(char c) { return 0; }
		virtual void update(int, int, unsigned* ) {}
		virtual bool isNeighbor() { return 0; }
		virtual AbstractCell* clone() { return NULL; }
		virtual bool transform () { return false; }
		virtual char print () const { return 'F'; }
		//void incAdj() { return 'F'; }
		friend ostream& operator<< (ostream &strm, const AbstractCell& c) {
			return strm << c.print();
		}
	protected:
		bool alive;
		int adjNeighbors;
		int diagNeighbors;
};
#endif // AbstractCell_h
