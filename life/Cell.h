
#ifndef Cell_h
#define Cell_h

//#include "AbstractCell.h"
#include "ConwayCell.h"
#include "FredkinCell.h"

class Cell : public AbstractCell {
	public:
		Cell(bool a = false) { cell = new FredkinCell(a); }
		Cell(const Cell& c) { cell = c.cell->clone(); }
		Cell(AbstractCell* c) { cell = c; }		// for unit tests
		~Cell() { delete cell; }
		bool isNeighbor() { return cell->isNeighbor(); }
		void addAdj() { cell->addAdj(); }
		void addDiag() { cell->addDiag(); }
		Cell& operator= (const Cell& c);
		bool readChar(char c);
		void update(int , int , unsigned*);
		
		friend ostream& operator<< (ostream &strm, const Cell& c) {
			return strm << *(c.cell);
		}
	private:
		AbstractCell* cell;
};

Cell& Cell::operator= (const Cell& c) {
	delete cell;
	cell = c.cell->clone();
	return *this;
}

bool Cell::readChar(char c) {
	if(c == '*' or c == '.') {
		delete cell;
		cell = new ConwayCell();
	}
	bool ret = cell->readChar(c); 
	assert(cell->print() == '-' || cell->print() == '*' 
		|| cell->print() == '0' || cell->print() == '1' || cell->print() == '.');
	return ret;
}

void Cell::update(int neighborsAdj, int neighborsDiag, unsigned int* population) {
	cell->update(neighborsAdj, neighborsDiag, population);
	if(cell->transform()) {
		delete cell;
		cell = ConwayCell(true).clone();
	}
}
#endif // Cell_h
