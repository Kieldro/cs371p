
#ifndef Cell_h
#define Cell_h

#include "AbstractCell.h"

class Cell : public AbstractCell{
	public:
	FredkinCell cell;
	
	int update(int neighbors){
		return cell.update(neighbors);
	}
		
	bool readChar(char c) {
		return cell.readChar(c);
	}
	
	bool isAlive() {
		return cell.isAlive();	
	}
	
	void ageCell(int inc) {
		cell.ageCell(inc);	
	}
	
	friend ostream& operator<< (ostream &strm, const Cell& c){
		return strm << c.cell;
	}
	
};
#endif // Cell_h