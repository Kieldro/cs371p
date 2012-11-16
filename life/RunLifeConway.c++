/*
Ian Buitrago
Graham Benevelli
11-28-2012
CS 371p
project 6 - Life
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
// 
/*

*/
void test1() {
	try {
		cout << "*** Life<Cell> 20x20 ***" << endl;
		Life<ConwayCell> game("acceptancetests/RunConway1.in");
		
		game.simulate(500, 1);
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
