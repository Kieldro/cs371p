
#ifndef Cell_h
#define Cell_h

#include "AbstractCell.h"

class Cell : public AbstractCell{
	public:
	FredkinCell cell;
	AbstractCell* aCell;
	
	Cell(){
		aCell = new FredkinCell;
	}
	
	void update(int neighbors, unsigned* population){
		cell.update(neighbors, population);
	}
	
	bool readChar(char c) {
		return cell.readChar(c);
	}
	
	bool isAlive() {
		return cell.isAlive();
	}
	
	~Cell(){
		delete aCell;
	}
	
	friend ostream& operator<< (ostream &strm, const Cell& c){
		return strm << c.cell;
	}
};
#endif // Cell_h