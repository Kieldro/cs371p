// -----------------------------
// projects/darwin/RunDarwin.c++
// Copyright (C) 2012
// Glenn P. Downing
/*
To run the program:
	% g++ -pedantic -std=c++0x -Wall RunCollatz.c++ -o RunCollatz.c++.app
	% valgrind RunDarwin.c++.app > RunDarwin.out
*/

// --------
// includes
#include <cassert>		// assert
#include <cstdlib>		// rand, srand
#include <iostream>		// cout, endl
#include <stdexcept>	// invalid_argument, out_of_range

#include "Darwin.h"

// ----
// main
int main () {
	using namespace std;
	ios_base::sync_with_stdio(false);	// turn off synchronization with C I/O

	// ----------
	// darwin 8x8
	try {
		cout << "*** Darwin 8x8 ***" << endl;
		/*
		8x8 Darwin
		Food,   facing east,  at (0, 0)
		Hopper, facing north, at (3, 3)
		Hopper, facing east,  at (3, 4)
		Hopper, facing south, at (4, 4)
		Hopper, facing west,  at (4, 3)
		Food,   facing north, at (7, 7)
		Simulate 5 moves.
		Print every grid.
		*/
		}
	catch (const invalid_argument&) {
		assert(false);}
	catch (const out_of_range&) {
		assert(false);}

	// ----------
	// darwin 7x9
	try {
		cout << "*** Darwin 7x9 ***" << endl;
		/*
		7x9 Darwin
		Trap,   facing south, at (0, 0)
		Hopper, facing east,  at (3, 2)
		Rover,  facing north, at (5, 4)
		Trap,   facing west,  at (6, 8)
		Simulate 5 moves.
		Print every grid.
		*/
		}
	catch (const invalid_argument&) {
		assert(false);}
	catch (const out_of_range&) {
		assert(false);}

	// ------------
	// darwin 72x72
	// without best
	try {
		cout << "*** Darwin 72x72 without Best ***" << endl;
		srand(0);
		/*
		Randomly place the following creatures facing randomly.
		Call rand(), mod it with 5184 (72x72), and use that for the position
		in a row-major order grid.
		Call rand() again, mod it with 4 and use that for it's direction with
		the ordering: west, north, east, south.
		Do that for each kind of creature.
		10 Food
		10 Hopper
		10 Rover
		10 Trap
		Simulate 1000 moves.
		Print every 100th grid.
		*/
		}
	catch (const invalid_argument&) {
		assert(false);}
	catch (const out_of_range&) {
		assert(false);}

	// ------------
	// darwin 72x72
	// with best
	try {
		cout << "*** Darwin 72x72 with Best ***" << endl;
		srand(0);
		/*
		Randomly place the following creatures facing randomly.
		Call rand(), mod it with 5184 (72x72), and use that for the position
		in a row-major order grid.
		Call rand() again, mod it with 4 and use that for it's direction with
		the ordering: west, north, east, south.
		Do that for each kind of creature.
		10 Food
		10 Hopper
		10 Rover
		10 Trap
		10 Best
		Simulate 1000 moves.
		Best MUST outnumber ALL other species for the bonus pts.
		Print every 100th grid.
		*/
		}
	catch (const invalid_argument&) {
		assert(false);}
	catch (const out_of_range&) {
		assert(false);}

	return 0;
}
