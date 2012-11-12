
#ifndef FredkinCell_h
#define FredkinCell_h

#include "AbstractCell.h"

class FredkinCell : public AbstractCell{
	private:
		bool alive;
		int age;
	public:
		FredkinCell(){ alive = false; age = 0;}
		void update(int neighbors, unsigned* population){
			//if(DEBUG) cerr << "neighbors: " << neighbors << endl;
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
			if(c == '+') 
				age = 10;
			else if(c - '0' >= 0 and c -'0' <= 9) age = (int) c - '0';
			else age = -1;
			return age >= 0;
		}
		
		bool isAlive() {
			return alive;	
		}
		
		friend ostream& operator<< (ostream &strm, const FredkinCell& c){
			if (c.age < 0)
				return strm << "-";
			if (c.age < 10)
				return strm << c.age;
			return strm << "+";
		}
	
};
#endif // FredkinCell_h