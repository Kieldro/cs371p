
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
		
		
		Life(int rows = 0, int cols = 0)
		: _g(x.allocate(2))
		{
			if (rows < 0 or cols < 0)
				throw logic_error("Negative dimensions.");
			//x.construct();
		}
		
		~Life(){
			//x.destroy();
			//x.deallocate(_g);
		}
		
		
		
		void input(string file);
		void simulate(int turns, int j, ostream& out = cout);
		void print(ostream& out = cout);
	private:
		allocator<Tvector2D> x;
		
		int nRows() const{return _g.size();}
		int nCols() const{return _g.size() ? _g[0].size() : 0;}
		
};

/**
@param file
*/
template <typename T>
void Life<T>::input(string file){
	ifstream inFile(file);
	string s;
	int rows, cols;
	char c;
	
	getline(inFile, s);
	rows = atoi(s.c_str());
	getline(inFile, s);
	cols = atoi(s.c_str());
	
	if(DEBUG) cerr << rows << endl;
	if(DEBUG) cerr << cols << endl;
	for(int i = 0; i < rows; ++i){
		for(int j = 0; j < cols; ++j){
			inFile >> c;
			if(DEBUG) cerr << c;
			
		}
		if(DEBUG) cerr << endl;
	}
	
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
	Tvector2D& grid = *_g[generation % 2];
	
	if(DEBUG) system("clear");
	out << "Generation = " << generation << ", ";
	out << "Population = " << -1 << endl;
	
	for(int r = 0; r < nRows(); ++r){
		out << r % 10 << " ";
		for(int c = 0; c < nCols(); ++c){
			out << grid[r][c];
		}
		out << endl;
	}
	out << endl;
	//if(DEBUG) sleep(1/2);
}
	
	
	
	
	

#endif //Life_h
