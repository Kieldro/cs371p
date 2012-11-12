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
#include <fstream>

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
#include "Cell.h"

/**
Life class.
*/
template <typename T>
class Life {
	typedef vector< vector<T> > Tvector2D;
	public:
		unsigned generation;
		unsigned population;
		
		Life(string);
		Life(int rows = 0, int cols = 0);
		void simulate(int turns, int j, ostream& out = cout);
		void runTurn();
		void updateCell(int r, int c);
		int countNeighbors(ConwayCell, int row, int col);
		int countNeighbors(FredkinCell, int row, int col);
		void print(ostream& out = cout);
		int nRows() const{return _g->size();}
		int nCols() const{return _g->size() ? (*_g)[0].size() : 0;}
		~Life();
	private:
		Tvector2D* _g;	// pointer to the grids
		allocator<Tvector2D> _x;
		
		void allocateGrids(int, int);
};
		
// Constructors
/**
Initializes a grid based on the input file.
@param file The name of an input file.
*/
template <typename T>
Life<T>::Life(string file)
: _g(_x.allocate(2))
{
	ifstream inFile(file);
	string s;
	int rows, cols;
	char inChar;
	
	getline(inFile, s);
	rows = atoi(s.c_str());
	getline(inFile, s);
	cols = atoi(s.c_str());
	//if(DEBUG) cerr << rows << endl;
	//if(DEBUG) cerr << cols << endl;
	allocateGrids(rows, cols);
	
	for(int r = 0; r < rows; ++r) {
		for(int c = 0; c < cols; ++c) {
			inFile >> inChar;
			if(_g[0][r][c].readChar(inChar))
				++population;
		}
	}
}

template <typename T>
Life<T>::Life(int rows, int cols)
: _g(_x.allocate(2))
{
	allocateGrids(rows, cols);
}

/**
Constructor helper function. Allocates and constructs 2 grids.
@param rows The number of rows in the grids.
@param cols The number of columns in the grids.
*/
template <typename T>
void Life<T>::allocateGrids(int rows, int cols) {
	if (rows < 0 or cols < 0)
		throw logic_error("Negative dimensions.");
	generation = 0;
	population = 0;
	
	_x.construct(_g, Tvector2D(rows, vector<T>(cols)));
	_x.construct(_g + 1, Tvector2D(rows, vector<T>(cols)));
}

// Destructor
/**
Destructs then destroys both grids.
*/
template <typename T>
Life<T>::~Life() {
	_x.destroy(_g);
	_x.destroy(_g + 1);
	
	_x.deallocate(_g, 2);
}

/**
@param turns the number turns to run the game.
@param j print the grid every j turns.
*/
template <typename T>
void Life<T>::simulate(int turns, int j, ostream& out) {
	print(out);
	for(int i = 1; i <= turns; ++i) {
		runTurn();
		if(i % j == 0)
			print(out);
	}
}

/**
Runs a turn.
*/
template <typename T>
void Life<T>::runTurn() {
	population = 0;
	
	for(int r = 0; r < nRows(); ++r) {
		for(int c = 0; c < nCols(); ++c) {
			updateCell(r, c);
		}
	}
	++generation;
}

/**
Updates cell to next generation and increment population accordingly.
*/
template <typename T>
void Life<T>::updateCell(int r, int c) {
	auto& current = _g[generation % 2];
	auto& next = _g[(generation + 1) % 2];
	
	int neighbors = countNeighbors(current[r][c], r, c);
	next[r][c] = current[r][c];
	next[r][c].update(neighbors, &population);
}

/**
Counts the neighbors of a ConwayCell.
*/
template <typename T>		// TODO cell is never used
int Life<T>::countNeighbors(ConwayCell, int r, int c) {
	int neighbors = 0;
	Tvector2D& grid = _g[generation % 2];
	
	for(int i = r-1; i < r+2; ++i)
		for(int j = c-1; j < c+2; ++j) {
			if((i == r and j == c) or i < 0 or j < 0 or i >= nRows() or j >= nCols())
				continue;
			if(grid[i][j].isNeighbor())
				++neighbors;
		}
	//if(DEBUG) cerr << r << " " << c << " " << neighbors << endl;
	assert(neighbors >= 0 and neighbors <= 8);
	return neighbors;
}

/**
Counts the neighbors of a FredkinCell.
*/
template <typename T>
int Life<T>::countNeighbors(FredkinCell, int r, int c) {
	int neighbors = 0;
	Tvector2D& grid = _g[generation % 2];
	
	if(r - 1 >= 0 and grid[r - 1][c].isNeighbor())
		++neighbors;
	if(r + 1 < nRows() and grid[r + 1][c].isNeighbor())
		++neighbors;
	if(c - 1 >= 0 and grid[r][c - 1].isNeighbor())
		++neighbors;
	if(c + 1 < nCols() and grid[r][c + 1].isNeighbor())
		++neighbors;
	
	assert(neighbors >= 0 and neighbors <= 4);
	return neighbors;
}

/**
Prints the grid and turn number.
*/
template <typename T>
void Life<T>::print(ostream& out) {
	Tvector2D& grid = _g[generation % 2];
	
	if(DEBUG) system("clear");
	out << "Generation = " << generation << ", ";
	out << "Population = " << population << "." << endl;
	
	for(int r = 0; r < nRows(); ++r) {
		for(int c = 0; c < nCols(); ++c) {
			out << grid[r][c];
		}
		out << endl;
	}
	out << endl;
	if(DEBUG) usleep(100000);		// micros seconds
}
#endif // Life_h
