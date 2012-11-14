
#ifndef AbstractCell_h
#define AbstractCell_h

// ------
// macros
#define DEBUG true
#define BOOYAKASHA	if(DEBUG) cerr << "BOOYAKASHA!" <<  endl; else;

// --------
// includes
#include <cstdlib>
#include <cassert>		// assert
#include <vector>		// vector
#include <deque>
#include <typeinfo>		// typeid
#include <stdexcept>
#include <string>
#include <fstream>
#include <iostream>

using std::vector;
using std::deque;
using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::logic_error;
using std::out_of_range;
using std::ostream;
using std::ifstream;
using std::allocator;

class AbstractCell{
	public:
		virtual bool readChar(char c) { return 0; }
		virtual void update(int neighborsAdj, int neighborsDiag, unsigned int* population) {}
		virtual bool isNeighbor() { return 0; }
		virtual AbstractCell* clone() { return NULL; }
		virtual bool transform () { return false; }
		virtual char print () const { return 'F'; }
		friend ostream& operator<< (ostream &strm, const AbstractCell& c) {
			return strm << c.print();
		}
	protected:
		bool alive;
};
#endif // AbstractCell_h
