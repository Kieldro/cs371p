
#ifndef ConwayCell_h
#define ConwayCell_h

#include "AbstractCell.h"

class ConwayCell : AbstractCell
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
		bool update(int neighbors){
			if(alive) {
				if(neighbors == 2 or neighbors == 3) {
					return true;}
				else {
					return false;}}
			
			return neighbors == 3;
		}
		
		friend ostream& operator<< (ostream &strm, const ConwayCell& c){
			if (!c.alive)
				return strm << ".";
			
			return strm << "*";
		}
	private:
		
};
#endif // ConwayCell_h
