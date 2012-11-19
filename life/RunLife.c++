/*
Ian Buitrago
Graham Benevelli
11-28-2012
CS 371p
project 6 - Life
*/

/*
To run the program:
	% g++ -pedantic -std=c++0x -Wall RunLife.c++ -o RunLife.c++.app
	% valgrind RunLife.c++.app > RunLife.out
*/

// --------
// includes
#include "Life.h"

using namespace std;

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
void testConway0() {
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


void testConway1() {
	try {
		cout << "*** Life<Cell> 20x20 ***" << endl;
		Life<ConwayCell> game("acceptancetests/RunConway1.in");
		
		game.simulate(90, 1);
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
void testConway2() {
	try {
		cout << "*** Life<Cell> 20x20 ***" << endl;
		Life<ConwayCell> game("acceptancetests/RunConway2.in");
		
		game.simulate(200, 1);
		
		
	} catch (const invalid_argument&) {
		assert(false);
	} catch (const out_of_range&) {
		assert(false);
	}
}

void testConway3() {
	try {
		cout << "*** Life<Cell> 20x20 ***" << endl;
		Life<ConwayCell> game("acceptancetests/RunConway3.in");
		
		game.simulate(9, 1);
		
		
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
void testFredkin0() {
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
void testCell0() {
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
void testCell1() {
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
void testCell2() {
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

void testCell3() {
	try {
		cout << "*** Life<Cell> 20x20 ***" << endl;
		Life<Cell> game("acceptancetests/RunLife3.in");
		
		game.simulate(10, 1);	
	} catch (const invalid_argument&) {
		assert(false);
	} catch (const out_of_range&) {
		assert(false);
	}
}

void testCell4() {
	try {
		cout << "*** Life<Cell> 20x20 ***" << endl;
		Life<Cell> game("acceptancetests/RunLife4.in");
		
		game.simulate(10, 1);	
	} catch (const invalid_argument&) {
		assert(false);
	} catch (const out_of_range&) {
		assert(false);
	}
}

void testCell5() {
	try {
		cout << "*** Life<Cell> 20x20 ***" << endl;
		Life<Cell> game("acceptancetests/RunLife5.in");
		
		game.simulate(70, 1);	
	} catch (const invalid_argument&) {
		assert(false);
	} catch (const out_of_range&) {
		assert(false);
	}
}

void testCell6() {
	try {
		cout << "*** Life<Cell> 20x20 ***" << endl;
		Life<Cell> game("acceptancetests/RunLife6.in");
		
		game.simulate(700, 1);	
	} catch (const invalid_argument&) {
		assert(false);
	} catch (const out_of_range&) {
		assert(false);
	}
}

void testCell7() {
	try {
		cout << "*** Life<Cell> 20x20 ***" << endl;
		Life<Cell> game("acceptancetests/RunLife7.in");
		
		game.simulate(100, 1);	
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
void testCell8() {
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

// ----
// main
int main() {
	ios_base::sync_with_stdio(false); // turn off synchronization with C I/O
	
	// Conway tests
	testConway0();
	testConway1();
	testConway2();
	testConway3();
	
	// Fredkin tests
	testFredkin0();
	
	// Cell tests
	testCell0();
	testCell1();
	testCell2();
	testCell3();
	testCell4();
	testCell5();
	testCell6();
	testCell7();
	testCell8();

	return 0;
}