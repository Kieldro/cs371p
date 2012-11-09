// -------------------------
// projects/life/RunLife.c++
// Copyright (C) 2012
// Glenn P. Downing
// -------------------------

/*
To run the program:
	% g++ -pedantic -std=c++0x -Wall RunLife.c++ -o RunLife.c++.app
	% valgrind RunLife.c++.app > RunLife.out
*/

// --------
// includes
#include <iostream>  // cout, endl

#include "Life.h"


// ----
// main
int main () {
	using namespace std;
	ios_base::sync_with_stdio(false); // turn off synchronization with C I/O

	// ------------------
	// Conway Cell 109x69
	try {
		cout << "*** Life<ConwayCell> 109x69 ***" << endl;
		/*
		read RunLifeConway.in // assume all Conway cells
		Print grid.
		Simulate 283 moves.
		Print grid.
		Simulate 40 moves.
		Print grid.
		Simulate 2500 moves.
		Print grid.
		*/
		//Life<ConwayCell> game = input<ConwayCell>("RunLifeConway.in");
		//game.simulate(283,  2500);
		//game.simulate(40,   2500);
		//game.simulate(2500-40-283, 2500);
		
		}
	catch (const invalid_argument&) {
		assert(false);}
	catch (const out_of_range&) {
		assert(false);}

	// ------------------
	// Fredkin Cell 20x20
	try {
		cout << "*** Life<FredkinCell> 20x20 ***" << endl;
		/*
		read RunLifeFredkin.in // assume all Fredkin cells
		Print grid.
		Simulate 2 moves.
		Print every grid.
		*/
		Life<FredkinCell> game = input<FredkinCell>("RunLife.in");
		game.simulate(2, 1);
		
		}
	catch (const invalid_argument&) {
		assert(false);}
	catch (const out_of_range&) {
		assert(false);}

	// ----------
	// Cell 20x20
	try {
		cout << "*** Life<Cell> 20x20 ***" << endl;
		/*
		read RunLife.in // assume all Fredkin cells
		Print grid.
		Simulate 5 moves.
		Print every grid.
		*/
		//Life<Cell> game(20, 20);
		//game.simulate(5, 1);
		
		}
	catch (const invalid_argument&) {
		assert(false);}
	catch (const out_of_range&) {
		assert(false);}

	return 0;
}
