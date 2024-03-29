/*
Ian Buitrago
Graham Benevelli
11-28-2012
CS 371p
project 6 - Life
*/
#ifndef Life_h
#define Life_h

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
#include <sstream>		// stringstreams
#include <iostream>		// cout, endl

using namespace std;

/**
Life class.
*/
template <typename T>
class Life {
	typedef vector< vector<T> > Tvector2D;
	public:
		Life(string);
		Life(int rows = 0, int cols = 0);
		void simulate(int turns, int j, ostream& out = cout);
		void place(int r, int c);
		~Life();
	private:
		unsigned generation;
		unsigned population;
		Tvector2D* _g;	// pointer to the grids
		allocator<Tvector2D> _x;
		
		int nRows() const{return _g->size();}
		int nCols() const{return _g->size() ? (*_g)[0].size() : 0;}
		void runTurn();
		void updateCell(int r, int c);
		int countNeighborsAdjacent(int row, int col);
		int countNeighborsDiag(int row, int col);
		void setNeighbors(int r, int c);
		void print(ostream& out = cout);
		void constructGrids(int, int);
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
	constructGrids(rows, cols);		// TODO Construct on the fly
	
	for(int r = 0; r < rows; ++r) {
		for(int c = 0; c < cols; ++c) {
			inFile >> inChar;
			if(_g[0][r][c].readChar(inChar))
				++population;
		}
	}
	inFile.close();
}

template <typename T>
Life<T>::Life(int rows, int cols)
: _g(_x.allocate(2))
{
	constructGrids(rows, cols);
}

/**
Constructor helper function. Allocates and constructs 2 grids.
@param rows The number of rows in the grids.
@param cols The number of columns in the grids.
*/
template <typename T>
void Life<T>::constructGrids(int rows, int cols) {
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

// ---------
// runTurn
/**
Runs a turn, updating every cell.
*/
template <typename T>
void Life<T>::runTurn() {
	population = 0;
	/*
	// distribute neigbors algorithm
	for(int r = 0; r < nRows(); ++r) {
		for(int c = 0; c < nCols(); ++c) {
			setNeighbors(r, c);
		}
	}
	*/
	
	for(int r = 0; r < nRows(); ++r) {
		for(int c = 0; c < nCols(); ++c) {
			updateCell(r, c);
		}
	}
	++generation;
}

/**
Updates cell to next generation and increment population accordingly.
@param r The row in the grid.
@param c The column in the grid.
*/
template <typename T>
void Life<T>::updateCell(int r, int c) {
	auto& current = _g[generation % 2];
	auto& next = _g[(generation + 1) % 2];
	
	int neighborsAdj = countNeighborsAdjacent(r, c);
	int neighborsDiag = countNeighborsDiag(r, c);
	next[r][c] = current[r][c];
	next[r][c].update(neighborsAdj, neighborsDiag, &population);
}

/**
Counts the diagonal neighbors of a cell.
@param r The row in the grid.
@param c The column in the grid.
*/
template <typename T>
int Life<T>::countNeighborsDiag(int r, int c) {
	int neighbors = 0;
	Tvector2D& grid = _g[generation % 2];
	
	if(r - 1 >= 0 and c - 1 >= 0 and grid[r-1][c-1].isNeighbor())
		++neighbors;
	if(r - 1 >= 0 and c + 1 < nCols() and grid[r-1][c+1].isNeighbor())
		++neighbors;
	if(r + 1 < nRows() and c - 1 >= 0 and grid[r+1][c-1].isNeighbor())
		++neighbors;
	if(r + 1 < nRows() and c + 1 < nCols() and grid[r+1][c+1].isNeighbor())
		++neighbors;
		
	//if(DEBUG) cerr << r << " " << c << " " << neighbors << endl;
	assert(neighbors >= 0 and neighbors <= 8);
	return neighbors;
}

/**
Counts the adjecent neighbors of a cell.
@param r The row in the grid.
@param c The column in the grid.
*/
template <typename T>
int Life<T>::countNeighborsAdjacent(int r, int c) {
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
Simulates the game.
@param turns the total number turns to run the game.
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
Set a cell in the current generation.
@param r row of the grid.
@param c column of the grid.
*/
template <typename T>
void Life<T>::place(int r, int c) {
	_g[generation % 2][r][c] = T(true);
}

/**
Prints the grid and turn number.
@param out Specifies which ostream to print to. Defaults to cout.
*/
template <typename T>
void Life<T>::print(ostream& out) {
	Tvector2D& grid = _g[generation % 2];
	
	//if(DEBUG) system("clear");
	out << "Generation = " << generation << ", ";
	out << "Population = " << population << "." << endl;
	
	for(int r = 0; r < nRows(); ++r) {
		for(int c = 0; c < nCols(); ++c) {
			out << grid[r][c];
		}
		out << endl;
	}
	out << endl;
	//if(DEBUG) usleep(100000);		// micro seconds
}
#endif // Life_h
