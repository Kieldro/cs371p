
#ifndef Cell_h
#define Cell_h

#include "AbstractCell.h"

class Cell : public AbstractCell{
	public:
	
	int age;
	
	int update(int neighbors){
			if(age >= 0) {
				if(neighbors == 0 or neighbors == 2 or neighbors == 4) {
					return -1;}
				else {
					return age+1;}}
			
			if (neighbors == 1 or neighbors == 3) {
				return 0;	
			} else {
				return -1;	
			}
		}
		
	bool readChar(char c) {
		if(c == '+') 
			age = 10;
		else if(c - '0' >= 0 and c -'0' <= 9) age = (int) c - '0';
		else age = -1;
		return age >= 0;
	}
	
	bool isAlive() {
		return age >= 0;	
	}
	
	void ageCell(int inc) {
		age = inc;	
	}
	
	friend ostream& operator<< (ostream &strm, const Cell& c){
			if (c.age < 0)
				return strm << "-";
			if (c.age < 10)
				return strm << c.age;
			return strm << "+";
		}
	
};
#endif // Cell_h