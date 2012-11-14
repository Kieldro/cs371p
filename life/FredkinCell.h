
#ifndef FredkinCell_h
#define FredkinCell_h

#include "AbstractCell.h"

class FredkinCell : public AbstractCell{
	public:
		FredkinCell() { alive = false; age = 0; }
		FredkinCell(bool a1, int a2 = 0) { alive = a1; age = a2; }
		FredkinCell(const FredkinCell& other) { alive = other.alive; age = other.age; }
		bool isNeighbor() { return alive; }
		void update(int neighborsAdj, int neighborsDiag, unsigned* population) {
			//if(DEBUG) cerr << "neighbors: " << neighbors << endl;
			int neighbors = neighborsAdj;
			assert(neighbors >= 0 and neighbors <= 4);
			
			if(alive) {
				if(neighbors == 0 or neighbors == 2 or neighbors == 4)
					alive = false;
				else
					++age;
			} else if (neighbors == 1 or neighbors == 3)
				alive = true;
			
			if(alive)
				++*population;
		}
		
		bool readChar(char c) {
			alive = true;
			
			if(c == '+') 
				age = 10;
			else if(c - '0' >= 0 and c -'0' <= 9)
				age = c - '0';
			else
				alive = false;
			
			return alive;
		}
		
		AbstractCell* clone() {
			return new FredkinCell(*this);
		}
		
		
		friend ostream& operator<< (ostream &strm, const FredkinCell& c) {
			if (!c.alive)
				return strm << "-";
			if (c.age < 10)
				return strm << c.age;
			else
				return strm << "+";
		}
	private:
		bool alive;
		int age;
};
#endif // FredkinCell_h
