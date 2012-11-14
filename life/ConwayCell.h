
#ifndef ConwayCell_h
#define ConwayCell_h

#include "AbstractCell.h"

class ConwayCell : public AbstractCell
{
	public:
		ConwayCell(){ alive = false; }
		explicit ConwayCell(bool a){ alive = a; } // Why do we want it to be explicit?
		ConwayCell(const ConwayCell &other) { alive = other.alive; }
		bool isNeighbor() const { return alive; }
		bool readChar(char c) { return alive = c == '*'; }
		void update(int neighborsAdj,  int neighborsDiag, unsigned* population) {		// input params then output params.
			int neighbors = neighborsAdj + neighborsDiag;
			assert(neighbors >= 0 and neighbors <= 8);
			if(alive) {
				if(neighbors == 2 or neighbors == 3)
					alive = true;
				else 
					alive = false;
			} else
				alive = neighbors == 3;
			
			if(alive)
				++*population;
		}
		
		AbstractCell* clone() {
			return new ConwayCell(this);
		}
		
		friend ostream& operator<< (ostream &strm, const ConwayCell& c){
			if (!c.alive)
				return strm << ".";
			
			return strm << "*";
		}
	private:
		bool alive;
};
#endif // ConwayCell_h
