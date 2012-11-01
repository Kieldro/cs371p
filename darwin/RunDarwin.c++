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
		Grid g(8, 8);
		g.place(FOOD  , 'e', 0, 0);
		g.place(HOPPER, 'n', 3, 3);
		g.place(HOPPER, 'e', 3, 4);
		g.place(HOPPER, 's', 4, 4);
		g.place(HOPPER, 'w', 4, 3);
		g.place(FOOD  , 'n', 7, 7);
		
		g.simulate(5, 1);
		
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
		Grid g(7, 9);
		g.place(TRAP,   's', 0, 0);
		g.place(HOPPER, 'e', 3, 2);
		g.place(ROVER,  'n', 5, 4);
		g.place(TRAP,   'w', 6, 8);
		
		g.run(5, 1);
		
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
		/*
		Grid g(72, 72);
		g.place(Food  ('s'), 0, 0);
		g.place(Hopper('e'), 3, 2);
		g.place(Rover ('n'), 5, 4);
		g.place(Trap  ('w'), 6, 8);
		
		g.run(1000, 100);*/
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

/*
*** Darwin 8x8 ***
Turn = 0.
  01234567
0 f.......
1 ........
2 ........
3 ...hh...
4 ...hh...
5 ........
6 ........
7 .......f

Turn = 1.
  01234567
0 f.......
1 ........
2 ...h....
3 .....h..
4 ..h.....
5 ....h...
6 ........
7 .......f

Turn = 2.
  01234567
0 f.......
1 ...h....
2 ........
3 ......h.
4 .h......
5 ........
6 ....h...
7 .......f

Turn = 3.
  01234567
0 f..h....
1 ........
2 ........
3 .......h
4 h.......
5 ........
6 ........
7 ....h..f

Turn = 4.
  01234567
0 f..h....
1 ........
2 ........
3 .......h
4 h.......
5 ........
6 ........
7 ....h..f

Turn = 5.
  01234567
0 f..h....
1 ........
2 ........
3 .......h
4 h.......
5 ........
6 ........
7 ....h..f

*** Darwin 7x9 ***
Turn = 0.
  012345678
0 t........
1 .........
2 .........
3 ..h......
4 .........
5 ....r....
6 ........t

Turn = 1.
  012345678
0 t........
1 .........
2 .........
3 ...h.....
4 ....r....
5 .........
6 ........t

Turn = 2.
  012345678
0 t........
1 .........
2 .........
3 ....r....
4 ....r....
5 .........
6 ........t

Turn = 3.
  012345678
0 t........
1 .........
2 .........
3 ....rr...
4 .........
5 .........
6 ........t

Turn = 4.
  012345678
0 t........
1 .........
2 ....r....
3 ......r..
4 .........
5 .........
6 ........t

Turn = 5.
  012345678
0 t........
1 ....r....
2 .........
3 .......r.
4 .........
5 .........
6 ........t

*** Darwin 72x72 without Best ***
...

*** Darwin 72x72 with Best ***
...
*/
