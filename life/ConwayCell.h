
#ifndef ConwayCell_h
#define ConwayCell_h

#include "AbstractCell.h"

class ConwayCell : public AbstractCell
{
	public:
		ConwayCell(){ alive = false; }
		bool isAlive() const { return alive; }
		bool readChar(char c) { return alive = c == '*'; }
		void update(int neighbors, unsigned* population) {		// input params then output params.
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
		
		friend ostream& operator<< (ostream &strm, const ConwayCell& c){
			if (!c.alive)
				return strm << ".";
			
			return strm << "*";
		}
	private:
		bool alive;
};
#endif // ConwayCell_h
