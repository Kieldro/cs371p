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
#include "Life.h"

void test0();
void test1();
void test2();

using namespace std;
// ----
// main
int main() {
	ios_base::sync_with_stdio(false); // turn off synchronization with C I/O
	
	test0();
	//test1();
	//test2();

	return 0;
}

// ------------------
// Fredkin Cell 20x20
/*
read RunLifeFredkin.in // assume all Fredkin cells
Print grid.
Simulate 2 moves.
Print every grid.
*/
void test0() {
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

// ------------------
// 
/*


*/
void test1() {
	try {
		
		
	} catch (const invalid_argument&) {
		assert(false);
	} catch (const out_of_range&) {
		assert(false);
	}
}

// ----------
// 
/*


*/
void test2() {
	try {
			
	} catch (const invalid_argument&) {
		assert(false);
	} catch (const out_of_range&) {
		assert(false);
	}
}
