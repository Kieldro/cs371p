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
void test9();

using namespace std;
// ----
// main
int main() {
	ios_base::sync_with_stdio(false); // turn off synchronization with C I/O
	
	test0();
	test1();
	test2();
	test9();

	return 0;
}

// ------------------
// 
/*


*/
void test0() {
	try {
		cout << "*** Life<Cell> 0x0 ***" << endl;
		Life<Cell> game(0, 0);
		
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
		cout << "*** Life<Cell> 1x1 ***" << endl;
		Life<Cell> game(1, 1);
		game.place(0, 0);
		
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
void test2() {
	try {
		cout << "*** Life<Cell> 2x2 ***" << endl;
		Life<Cell> game(1, 1);
		game.place(0, 0);
		
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
void test9() {
	try {
		cout << "*** Life<Cell> 20x20 ***" << endl;
		Life<Cell> game("RunLife.in");
		
		game.simulate(5, 1);	
	} catch (const invalid_argument&) {
		assert(false);
	} catch (const out_of_range&) {
		assert(false);
	}
}
