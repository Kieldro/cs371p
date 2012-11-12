/*
Ian Buitrago
Graham Benevelli
11-28-2012
CS 371p
project 6 - Life

compile:
	$ g++ -std=c++0x -ldl TestLife.c++ -lcppunit -o TestLife.c++.app
execute:
	$ valgrind ./TestLife.c++.app 2>&1 | tee TestLife.out
*/

// --------
// includes
#include "cppunit/extensions/HelperMacros.h"	// CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"				// TestFixture
#include "cppunit/TextTestRunner.h"				// TestRunner
#include <sstream>

#define private public
#include "Life.h"

using std::ostringstream;
unsigned dummy = 0;

// --------
// TestLife
struct TestLife : CppUnit::TestFixture {
	// --------
	// testLife
	void testLife0 () {
		Life<ConwayCell> game("RunLifeConway.in");
		
		CPPUNIT_ASSERT(game.generation == 0);
		CPPUNIT_ASSERT(game.population == 35);
		CPPUNIT_ASSERT(game.nRows() == 109);
		CPPUNIT_ASSERT(game.nCols() == 69);
	}
	void testLife1 () {
		Life<FredkinCell> game(5, 5);
		
		CPPUNIT_ASSERT(game.generation == 0);
		CPPUNIT_ASSERT(game.population == 0);
		CPPUNIT_ASSERT(game.nRows() == 5);
		CPPUNIT_ASSERT(game.nCols() == 5);
	}
	
	void testUpdate0() {
		Life<ConwayCell> game(7, 5);
		game._g[0][2][1].alive = true;
		game._g[0][3][1].alive = true;
		game._g[0][4][1].alive = true;
		game._g[0][5][1].alive = true;
		
		CPPUNIT_ASSERT(game.countNeighbors(game._g[0][1][1], 1, 1) == 1);
		CPPUNIT_ASSERT(game.countNeighbors(game._g[0][2][1], 2, 1) == 1);
		CPPUNIT_ASSERT(game.countNeighbors(game._g[0][3][1], 3, 1) == 2);
		CPPUNIT_ASSERT(game.countNeighbors(game._g[0][3][2], 3, 2) == 3);
		CPPUNIT_ASSERT(game.countNeighbors(game._g[0][0][0], 0, 0) == 0);
	}
	
	void testRunTurn0() {
		Life<ConwayCell> game(3, 3);
		game.runTurn();
		//game.print();
		CPPUNIT_ASSERT(1);		
	}
	
	void testSimulateTurn0() {
		Life<ConwayCell> game(3, 3);
		//game.simulate(5, 1);
		CPPUNIT_ASSERT(1);		
	}
	
	// ------------------
	// testUpdateCell
	void testUpdateCell0 () {
		Life<ConwayCell> game(3, 3);
		int r = 0, c = 0;
		game._g[0][r][c].alive = true;
		game.updateCell(r, c);
		
		CPPUNIT_ASSERT(!game._g[0][r][c].alive);
	}
	
	// ------------------
	// testConwayReadChar
	void testConwayReadChar0 () {
		ConwayCell c;
		CPPUNIT_ASSERT(c.readChar('*'));
		CPPUNIT_ASSERT(c.alive);
	}
	void testConwayReadChar1 () {
		ConwayCell c;
		CPPUNIT_ASSERT(!c.readChar('.'));
		CPPUNIT_ASSERT(!c.alive);
	}
	void testConwayReadChar2 () {
		ConwayCell c;
		CPPUNIT_ASSERT(!c.readChar('0'));
		CPPUNIT_ASSERT(!c.alive);
	}
	
	// ------------------
	// testFredkinReadChar
	void testFredkinReadChar0 () {
		FredkinCell c;
		CPPUNIT_ASSERT(!c.readChar('.'));
		CPPUNIT_ASSERT(c.age < 0);
	}
	void testFredkinReadChar1 () {
		FredkinCell c;
		CPPUNIT_ASSERT(c.readChar('+'));
		CPPUNIT_ASSERT(c.age >= 10);
	}
	void testFredkinReadChar2 () {
		FredkinCell c;
		CPPUNIT_ASSERT(c.readChar('0'));
		CPPUNIT_ASSERT(c.age == 0);
	}
	void testFredkinReadChar3 () {
		FredkinCell c;
		CPPUNIT_ASSERT(c.readChar('7'));
		CPPUNIT_ASSERT(c.age == 7);
	}
	
	// --------
	// testConwayUpdate
	void testConwayUpdate0 () {
		ConwayCell c;
		unsigned population = 0;
		c.update(2, &population);
		
		CPPUNIT_ASSERT(!c.alive);
		CPPUNIT_ASSERT(population == 0);
	}
	void testConwayUpdate1 () {
		ConwayCell c;
		unsigned population = 0;
		c.update(3, &population);
		
		CPPUNIT_ASSERT(c.alive);
		CPPUNIT_ASSERT(population == 1);
	}
	void testConwayUpdate2 () {
		ConwayCell c;
		c.alive= true;
		unsigned population = 0;
		
		c.update(3, &population);
		CPPUNIT_ASSERT(c.alive);
		CPPUNIT_ASSERT(population == 1);
		
		c.update(2, &population);
		CPPUNIT_ASSERT(c.alive);
		CPPUNIT_ASSERT(population == 2);
		
		c.update(1, &population);
		CPPUNIT_ASSERT(!c.alive);
		CPPUNIT_ASSERT(population == 2);
	}
	void testConwayUpdate3 () {
		ConwayCell c;
		c.alive= true;
		c.update(4, &dummy);
		
		CPPUNIT_ASSERT(!c.alive);
	}
	
	// --------
	// testFredkinUpdate
	void testFredKinUpdate0 () {
		FredkinCell f;
		f.alive= true;
		f.age = 10;
		f.update(0, &dummy);
		
		CPPUNIT_ASSERT(!f.alive);
		CPPUNIT_ASSERT(f.age == 10);
	}
	void testFredKinUpdate1 () {
		FredkinCell f;
		f.alive= true;
		f.age = 10;
		
		f.update(1, &dummy);
		CPPUNIT_ASSERT(f.age == 11);
		CPPUNIT_ASSERT(f.alive);
		
		f.update(3, &dummy);
		CPPUNIT_ASSERT(f.age == 12);
		CPPUNIT_ASSERT(f.alive);
	}
	void testFredKinUpdate2 () {
		FredkinCell f;
		
		CPPUNIT_ASSERT(!f.alive);
		CPPUNIT_ASSERT(f.age == 0);
		
		f.update(1, &dummy);
		CPPUNIT_ASSERT(f.alive);
		CPPUNIT_ASSERT(f.age == 0);
		
		f.update(3, &dummy);
		CPPUNIT_ASSERT(f.alive);
		CPPUNIT_ASSERT(f.age == 1);
	}
	void testFredKinUpdate3 () {
		FredkinCell f;
		
		f.update(0, &dummy);
		CPPUNIT_ASSERT(!f.alive);
		CPPUNIT_ASSERT(f.age == 0);
		
		f.update(2, &dummy);
		CPPUNIT_ASSERT(!f.alive);
		CPPUNIT_ASSERT(f.age == 0);
		
		f.update(4, &dummy);
		CPPUNIT_ASSERT(!f.alive);
		CPPUNIT_ASSERT(f.age == 0);
	}
	
	// -----
	// suite
	CPPUNIT_TEST_SUITE(TestLife);
	
	CPPUNIT_TEST(testLife0);
	CPPUNIT_TEST(testLife1);
	CPPUNIT_TEST(testUpdate0);
	CPPUNIT_TEST(testRunTurn0);
	CPPUNIT_TEST(testSimulateTurn0);
	CPPUNIT_TEST(testConwayReadChar0);
	CPPUNIT_TEST(testConwayReadChar1);
	CPPUNIT_TEST(testConwayReadChar2);
	CPPUNIT_TEST(testFredkinReadChar0);
	CPPUNIT_TEST(testFredkinReadChar1);
	CPPUNIT_TEST(testFredkinReadChar2);
	CPPUNIT_TEST(testFredkinReadChar3);
	CPPUNIT_TEST(testConwayUpdate0);
	CPPUNIT_TEST(testConwayUpdate1);
	CPPUNIT_TEST(testConwayUpdate2);
	CPPUNIT_TEST(testConwayUpdate3);
	CPPUNIT_TEST(testFredKinUpdate0);
	CPPUNIT_TEST(testFredKinUpdate1);
	CPPUNIT_TEST(testFredKinUpdate2);
	CPPUNIT_TEST(testFredKinUpdate3);
	
	CPPUNIT_TEST_SUITE_END();
};

// ----
// main
int main () {
	using namespace std;
	ios_base::sync_with_stdio(false);	// turn off synchronization with C I/O
	cout << "TestLife.c++" << endl;

	CppUnit::TextTestRunner tr;
	tr.addTest(TestLife::suite());
	tr.run();

	cout << "Done." << endl;
	return 0;
}
