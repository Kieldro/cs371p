
#ifndef FredkinCell_h
#define FredkinCell_h

#include "AbstractCell.h"

class FredkinCell : AbstractCell{
	public:
	
	int age;
	
	bool update(int neighbors){
			if(age >= 0) {
				if(neighbors == 0 or neighbors == 2 or neighbors == 4) {
					return false;}
				else {
					return true;}}
			
			return neighbors == 1 or neighbors == 3;
		}
	
};
#endif // FredkinCell_h