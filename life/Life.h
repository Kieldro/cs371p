
#ifndef Life_h
#define Life_h

// --------
// includes
#include <cstdlib>
#include <cassert>		// assert
#include <vector>		// vector
#include <deque>
#include <typeinfo>		// typeid
#include <stdexcept>
#include <string>

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

// ------
// macros
#define DEBUG true
#define BOOYAKASHA	if(DEBUG) cerr << "BOOYAKASHA!" <<  endl; else;

#include "ConwayCell.h"
#include "FredkinCell.h"


/**
	
	
*/
template <typename T>
class Life{
	typedef vector< vector<T> > Tvector2D;
	public:
		Tvector2D* _g;
		unsigned generation;
		unsigned population;
		
		Life(int rows = 0, int cols = 0);
		~Life();
		void simulate(int turns, int j, ostream& out = cout);
		void print(ostream& out = cout);
		friend Life<T> input();
	private:
		allocator<Tvector2D> _x;
		
		int nRows() const{return _g->size();}
		int nCols() const{return _g->size() ? (*_g)[0].size() : 0;}
		
};
		
// Constructor
template <typename T>
Life<T>::Life(int rows, int cols)
: _g(_x.allocate(2))
{
	//if(DEBUG) cerr << "CONSTRUCT LIFE!" << endl;
	
	if (rows < 0 or cols < 0)
		throw logic_error("Negative dimensions.");
	generation = 0;
	population = 0;
	
	_x.construct(_g, Tvector2D(rows, vector<T>(cols)));
	_x.construct(_g + 1, Tvector2D(rows, vector<T>(cols)));
}

// Destructor
template <typename T>
Life<T>::~Life(){
	_x.destroy(_g);
	_x.destroy(_g + 1);
	
	_x.deallocate(_g, 2);
}

/**
@param turns the number turns to run the game.
@param j print the grid every j turns.
*/
template <typename T>
void Life<T>::simulate(int turns, int j, ostream& out){
	print(out);
	for(int i = 1; i <= turns; ++i){
		//runTurn();
		if(i % j == 0)
			print(out);
	}
}

/**
Prints the grid and turn number.
*/
template <typename T>
void Life<T>::print(ostream& out){
	Tvector2D& grid = _g[generation % 2];
	
	//if(DEBUG) system("clear");
	out << "Generation = " << generation << ", ";
	out << "Population = " << population << "." << endl;
	
	for(int r = 0; r < nRows(); ++r){
		for(int c = 0; c < nCols(); ++c){
			out << grid[r][c];
		}
		out << endl;
	}
	out << endl;
	//if(DEBUG) sleep(1/2);
}

/**
@param file
*/
template <typename T>
Life<T> input(string file){
	ifstream inFile(file);
	string s;
	int rows, cols;
	char inChar;
	
	getline(inFile, s);
	rows = atoi(s.c_str());
	getline(inFile, s);
	cols = atoi(s.c_str());
	if(DEBUG) cerr << rows << endl;
	if(DEBUG) cerr << cols << endl;
	Life<T> result(rows, cols);
	
	for(int r = 0; r < rows; ++r){
		for(int c = 0; c < cols; ++c){
			inFile >> inChar;
			if(inChar == '*')
				result._g[0][r][c].alive = true;
			//if(DEBUG) cerr << inChar;
			
		}
		//if(DEBUG) cerr << endl;
	}
	
	//if(DEBUG) result.print();
	
	return result;
}
#endif // Life_h
