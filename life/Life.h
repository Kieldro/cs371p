
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

// ------
// macros
#define DEBUG !true
#define BOOYAKASHA	if(DEBUG) cerr << "BOOYAKASHA!" <<  endl; else;

#include "ConwayCell.h"


/**
	
	
*/
template <typename T>
class Life{
	private:
		
		int nRows() const{return _g.size();}
		int nCols() const{return _g.size() ? _g[0].size() : 0;}
		
	public:
		vector< vector<T> > _g;
		
		Life(int rows, int cols)
		: _g(rows, vector<T>(cols))
		{
			
			
		}
		
		
		
		
		
		void simulate(int turns, int j, ostream& out = cout);
		void print(ostream& out = cout);
};


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
	if(DEBUG) system("clear");
	out << "Generation = " << -1 << ", ";
	out << "Population = " << -1 << endl;
	out << "  ";
	for(int c = 0; c < nCols(); ++c)
		out << c % 10;
	out << endl;
	for(int r = 0; r < nRows(); ++r){
		out << r % 10 << " ";
		for(int c = 0; c < nCols(); ++c){
			if(_g[r][c] == NULL)
				out << ".";
			else
				out << *_g[r][c];
		}
		out << endl;
	}
	out << endl;
	//if(DEBUG) sleep(1/2);
}
	
	
	
	
	

#endif //Life_h
