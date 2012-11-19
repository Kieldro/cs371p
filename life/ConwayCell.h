
#ifndef ConwayCell_h
#define ConwayCell_h

#include "AbstractCell.h"

class ConwayCell : public AbstractCell
{
	public:
		//ConwayCell(){ alive = false; } // use delegation somehow?
		ConwayCell(bool a = false){ alive = a; adjNeighbors = 0; diagNeighbors = 0; }
		ConwayCell(const ConwayCell& other) { alive = other.alive; adjNeighbors = 0; diagNeighbors = 0; }
		bool readChar(char c) { return alive = c == '*'; }
		void update(int neighborsAdj,  int neighborsDiag, unsigned* population);
		ConwayCell* clone() { return new ConwayCell(*this); }
		bool transform() { return false; }
		char print() const {
			if(!alive)
				return '.';
			return '*';
		}
		friend ostream& operator<< (ostream &strm, const ConwayCell& c){
			return strm << c.print();
		}
};

// input params then output params.
void ConwayCell::update(int neighborsAdj,  int neighborsDiag, unsigned* population) {
	//int neighbors = neighborsAdj + neighborsDiag;
	int neighbors = adjNeighbors + diagNeighbors;
	
	/*if(DEBUG) cerr << "aneighbors: " << adjNeighbors << endl;
	if(DEBUG) cerr << "dneighbors: " << diagNeighbors << endl;
	if(DEBUG) cerr << "neighbors: " << neighbors << endl;
	assert(adjNeighbors == neighborsAdj);
	assert(diagNeighbors == neighborsDiag);
	*/
	assert(neighbors >= 0);
	assert(neighbors <= 8);
	if(alive) {
		alive = neighbors == 3 or neighbors == 2;
		++*population;
	} else
		alive = neighbors == 3;
	
	adjNeighbors = 0;
	diagNeighbors = 0;
}

#endif // ConwayCell_h

