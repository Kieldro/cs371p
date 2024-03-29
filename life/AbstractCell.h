
#ifndef AbstractCell_h
#define AbstractCell_h

#include "Life.h"

class AbstractCell {
	public:
		virtual bool readChar(char c) { return 0; }
		virtual void update(int, int, unsigned*) {}
		virtual AbstractCell* clone() { return NULL; }
		virtual bool transform () { return false; }
		virtual char print () const { return 'F'; }
		bool isNeighbor() { return alive; }
		friend ostream& operator<< (ostream &strm, const AbstractCell& c) {
			return strm << c.print();
		}
	protected:
		bool alive;
};
#endif // AbstractCell_h
