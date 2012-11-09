
#ifndef ConwayCell_h
#define ConwayCell_h

#include "AbstractCell.h"

class ConwayCell : public AbstractCell
{
	public:
		bool alive;
		
		ConwayCell(){
			
			alive = false;
		}
		
		void qux(){
			;
		}
		/**
		
		*/
		int update(int neighbors){
			if(alive) {
				if(neighbors == 2 or neighbors == 3) {
					return true;}
				else {
					return false;}}
			
			return (int) neighbors == 3;
		}
		
		bool readChar(char c) {
			if(c == '*') alive = true;	
			return alive;
		}
		
		bool isAlive() {
			return alive;	
		}
		
		void ageCell(int inc) {
			alive = inc == 1;	
		}
		
		friend ostream& operator<< (ostream &strm, const ConwayCell& c){
			if (!c.alive)
				return strm << ".";
			
			return strm << "*";
		}
	private:
		
};
#endif // ConwayCell_h
