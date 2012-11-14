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

void test0();
void test1();
void test2();

using namespace std;
// ----
// main
int main() {
	ios_base::sync_with_stdio(false); // turn off synchronization with C I/O
	
	//test0();
	test1();
	test2();

	return 0;
}

// ------------------
// Conway Cell 109x69
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
void test0() {
	try {
		cout << "*** Life<ConwayCell> 109x69 ***" << endl;
		Life<ConwayCell> game("RunLifeConway.in");
		game.simulate(283,  2500);
		game.simulate(40,   2500);
		game.simulate(2500, 2500);
	} catch (const invalid_argument&) {
		assert(false);
	} catch (const out_of_range&) {
		assert(false);
	}
}

// ------------------
// Fredkin Cell 20x20
/*
read RunLifeFredkin.in // assume all Fredkin cells
Print grid.
Simulate 2 moves.
Print every grid.
*/
void test1() {
	try {
		cout << "*** Life<FredkinCell> 20x20 ***" << endl;
		Life<FredkinCell> game("RunLifeFredkin.in");
		game.simulate(2, 1);
	} catch (const invalid_argument&) {
		assert(false);
	} catch (const out_of_range&) {
		assert(false);
	}
}

// ----------
// Cell 20x20
/*
read RunLife.in // assume all Fredkin cells
Print grid.
Simulate 5 moves.
Print every grid.
*/
void test2() {
	try {
		cout << "*** Life<Cell> 20x20 ***" << endl;
		Life<Cell> game("RunLife.in");
		//BOOYAKASHA
		game.simulate(5, 1);	
	} catch (const invalid_argument&) {
		assert(false);
	} catch (const out_of_range&) {
		assert(false);
	}
}