
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
		Cell(const Cell& c) {
			cell = new FredkinCell;
			
			cell = c.cell->clone();	// FIXME
			//if(DEBUG) cerr <<  "Cell(const Cell&) BOOM " << endl;
		}
		~Cell() { //delete aCell; 
			//if(DEBUG) cerr <<  "~Cell() BOOM " << endl;
			delete cell;
		}
		bool readChar(char c) { 
			//BOOYAKASHA
			//if(DEBUG) cerr <<  "readChar() cell " << cell << endl;
			return cell->readChar(c); }
		bool isNeighbor() { return cell->isNeighbor(); }
		void update(int neighborsAdj, int neighborsDiag, unsigned* population) {
			cell->update(neighborsAdj, neighborsDiag, population);
		}
		
		
		friend ostream& operator<< (ostream &strm, const Cell& c) {
			return strm << c.cell;
		}
	
	private:
		AbstractCell* cell;
};
#endif // Cell_h
