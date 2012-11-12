
#ifndef Cell_h
#define Cell_h

#include "AbstractCell.h"

class Cell : public AbstractCell {
	public:
	FredkinCell cell;
	AbstractCell* aCell;
	
	Cell(){ aCell = new FredkinCell; }
	bool readChar(char c) { return cell.readChar(c); }
	bool isNeighbor() { return cell.isNeighbor(); }
	void update(int neighbors, unsigned* population) {
		cell.update(neighbors, population);
	}
	~Cell() { delete aCell; }
	
	friend ostream& operator<< (ostream &strm, const Cell& c) {
		return strm << c.cell;
	}
};
#endif // Cell_h