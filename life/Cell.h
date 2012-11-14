
#ifndef Cell_h
#define Cell_h

#include "ConwayCell.h"
#include "FredkinCell.h"

class Cell : public AbstractCell {
	public:
	//FredkinCell* cell;
	AbstractCell* cell;
	
	Cell(){
		//if(DEBUG) cerr <<  "Cell() BOOM " << endl;
		cell = new FredkinCell; 
	}
	Cell(const Cell& c){
		//if(DEBUG) cerr <<  "Cell(const Cell&) BOOM " << endl;
		cell = c.cell->clone();
	}
	bool readChar(char c) { return cell->readChar(c); }
	bool isNeighbor() { return cell->isNeighbor(); }
	void update(int neighbors, unsigned* population) {
		cell->update(neighbors, population);
	}
	~Cell() { //delete aCell; 
		//if(DEBUG) cerr <<  "~Cell() BOOM " << endl;
		delete cell;
	}
	
	friend ostream& operator<< (ostream &strm, const Cell& c) {
		return strm << c.cell;
	}
};
#endif // Cell_h
