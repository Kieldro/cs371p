
#ifndef Cell_h
#define Cell_h

#include "ConwayCell.h"
#include "FredkinCell.h"

class Cell : public AbstractCell {
	public:
		Cell() {
			//if(DEBUG) cerr <<  "Cell() BOOM " << endl;
			cell = new FredkinCell;
		}
		Cell(AbstractCell* c) {
			cell = c;
		}
		Cell(const Cell& c) {
			cell = c.cell->clone();
			//if(DEBUG) cerr <<  "Cell(const Cell&) BOOM " << endl;
		}
		~Cell() { 
			//if(DEBUG) cerr <<  "~Cell() BOOM " << endl;
			delete cell;
		}
		Cell& operator= (const Cell& c) {
			delete cell;
			cell = c.cell->clone();
			return *this;
		}
		bool readChar(char c) { 
			//BOOYAKASHA
			//if(DEBUG) cerr <<  "readChar() cell " << cell << endl;
			if(c == '*') {
				delete cell;
				cell = new ConwayCell();
			}
			bool ret = cell->readChar(c); 
			assert(cell->print() == '-' || cell->print() == '*' || cell->print() == '0' || cell->print() == '1');
			return ret;
		}
		bool isNeighbor() { return cell->isNeighbor(); }
		void update(int neighborsAdj, int neighborsDiag, unsigned* population) {
			cell->update(neighborsAdj, neighborsDiag, population);
			/*if(cell->transform()) {
				delete cell;
				cell = new ConwayCell(true);
			}*/
		}
		
		friend ostream& operator<< (ostream &strm, const Cell& c) {
			return strm << *(c.cell);
		}
	
	private:
		AbstractCell* cell;
};
#endif // Cell_h
