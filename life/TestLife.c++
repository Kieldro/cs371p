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

//#define private public
#include "Life.h"

using std::ostringstream;

// --------
// TestLife
struct TestLife : CppUnit::TestFixture {
	// --------
	// testLife
	void testLife0 () {
		Life<ConwayCell> game = input<ConwayCell>("AcceptanceTest.in");
		game.print();
		CPPUNIT_ASSERT(1);
	}
	void testLife1 () {
		Life<ConwayCell> game(5, 5);
		
		game.print();
		CPPUNIT_ASSERT(1);
	}
	
	void testUpdate0() {
		Life<ConwayCell> game(7, 5);
		game._g[0][2][1].alive = true;
		game._g[0][3][1].alive = true;
		game._g[0][4][1].alive = true;
		game._g[0][5][1].alive = true;
		CPPUNIT_ASSERT(game.countNeighbors(game._g[0][1][1], 1, 1) == 1);
		cout << game.countNeighbors(game._g[0][2][1], 2, 1);
		CPPUNIT_ASSERT(game.countNeighbors(game._g[0][2][1], 2, 1) == 1);
		CPPUNIT_ASSERT(game.countNeighbors(game._g[0][3][1], 3, 1) == 2);
	}
	
	void testRunTurn0() {
		Life<ConwayCell> game = input<ConwayCell>("RunLifeConway.in");
		game.runTurn();
		game.print();
		CPPUNIT_ASSERT(1);		
	}
	
	void testSimulateTurn0() {
		Life<ConwayCell> game = input<ConwayCell>("RunLifeConway.in");
		game.simulate(5, 1);
		CPPUNIT_ASSERT(1);		
	}
	
	// --------
	// testConwayUpdate
	void testConwayUpdate0 () {
		ConwayCell c;
		CPPUNIT_ASSERT(!c.update(2));
	}
	void testConwayUpdate1 () {
		ConwayCell c;
		CPPUNIT_ASSERT(c.update(3));
	}
	void testConwayUpdate2 () {
		ConwayCell c;
		c.alive= true;
		CPPUNIT_ASSERT(c.update(3));
		CPPUNIT_ASSERT(c.update(2));
		CPPUNIT_ASSERT(!c.update(1));
	}
	void testConwayUpdate3 () {
		ConwayCell c;
		c.alive= true;
		CPPUNIT_ASSERT(!c.update(4));
	}
	
	// --------
	// testFredkinUpdate
	void testFredKinUpdate0 () {
		FredkinCell f;
		f.age = 10;
		CPPUNIT_ASSERT(!f.update(0));
		CPPUNIT_ASSERT(!f.update(2));
		CPPUNIT_ASSERT(!f.update(4));
	}
	void testFredKinUpdate1 () {
		FredkinCell f;
		f.age = 10;
		CPPUNIT_ASSERT(f.update(1));
		CPPUNIT_ASSERT(f.update(3));
		CPPUNIT_ASSERT(f.update(5));
	}
	void testFredKinUpdate2 () {
		FredkinCell f;
		f.age = -1;
		CPPUNIT_ASSERT(f.update(1));
		CPPUNIT_ASSERT(f.update(3));
	}
	void testFredKinUpdate3 () {
		FredkinCell f;
		f.age = -1;
		CPPUNIT_ASSERT(!f.update(0));
		CPPUNIT_ASSERT(!f.update(2));
		CPPUNIT_ASSERT(!f.update(4));
	}
	
	// -----
	// suite
	CPPUNIT_TEST_SUITE(TestLife);
	
	//CPPUNIT_TEST(testLife0);
	//CPPUNIT_TEST(testLife1);
	CPPUNIT_TEST(testUpdate0);
	//CPPUNIT_TEST(testRunTurn0);
	//CPPUNIT_TEST(testSimulateTurn0);
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