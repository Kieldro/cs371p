/*
Ian Buitrago
Jonathan Chen
11-7-2012
CS 371p
project 5 - Darwin

compile:
	$ g++ -std=c++0x -ldl TestDarwin.c++ -lcppunit -o TestDarwin.c++.app
execute:
	$ valgrind ./TestDarwin.c++.app 2>&1 | tee TestDarwin.out
*/

// --------
// includes
#include "cppunit/extensions/HelperMacros.h"	// CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"				// TestFixture
#include "cppunit/TextTestRunner.h"				// TestRunner

#define private public
#include "Darwin.h"

// ----------
// TestDarwin
struct TestDarwin : CppUnit::TestFixture {
	// --------
	// testGrid
	void testGrid0 () {
		Grid g(2, 2);
		
		CPPUNIT_ASSERT(g.nRows() == 2);
		CPPUNIT_ASSERT(g.nCols() == 2);
		CPPUNIT_ASSERT(g.turn == 0);
		CPPUNIT_ASSERT(g.creatureStash.size() == 0);
	}
	
	// --------
	// testPlace
	void testPlace0 () {
		Grid g(3, 3);
		int r = 1;
		int c = 1;
		
		g.place(HOPPER, NORTH, r, c);
		CPPUNIT_ASSERT(g.creatureStash.size() == 1);
		CPPUNIT_ASSERT(g._g[r][c] !=  NULL);
	}
	
	void testPlace1 () {
		Grid g(3, 3);
		int r = -1;
		int c = -1;
		try{
			g.place(HOPPER, NORTH, r, c);
			CPPUNIT_ASSERT(false);
		}catch(...){
			CPPUNIT_ASSERT(true);
		}			
	}
	
	void testPlace2 () {
		Grid g(3, 3);
		int r = 3;
		int c = 3;
		try{
			g.place(HOPPER, NORTH, r, c);
			CPPUNIT_ASSERT(false);
		}catch(...){
			CPPUNIT_ASSERT(true);
		}			
	}
	// --------
	// testCreature
	void testCreature0 () {
		Grid g(3, 3);
		g.place(HOPPER, SOUTH, 0, 1);
		g.simulate(3, 1);
	}
	
	
	
	// --------
	// testHop
	void testHop0 () {
		Grid g(3, 3);
		g.place(HOPPER, SOUTH, 0, 1);
		g.simulate(3, 1);
	}
	// hop into each other
	void testHop1 () {
		Grid g(3, 3);
		g.place(HOPPER, EAST, 1, 1);
		g.place(HOPPER, WEST, 1, 2);
		
		g.simulate(2, 1);
	}
	
	// --------
	// testFood
	void testFood0 () {
		Grid g(2, 2);
		
		g.place(FOOD, SOUTH, 0, 0);
		g.simulate(2, 1);
	}
	
	// --------
	// testTrap
	void testTrap0 () {
		Grid g(2, 2);
		
		g.place(TRAP, SOUTH, 0, 0);
		g.simulate(2, 1);
	}
	void testTrap1 () {
		Grid g(3, 3);
		
		g.place(TRAP, EAST, 1, 1);
		g.place(FOOD, SOUTH, 1, 2);
		g.simulate(2, 1);
	}
	
	// --------
	// testRover
	void testRover0 () {
		Grid g(4, 4);
		srand(0);
		
		g.place(ROVER , EAST, 1, 1);
		g.place(FOOD  , SOUTH, 1, 3);
		g.place(HOPPER, EAST, 2, 2);
		g.simulate(6, 1);
	}
	
	// --------
	// testBest
	void testBest0 () {
		Grid g(5, 5);
		srand(0);
		
		g.place(BEST  , EAST, 0, 0);
		g.place(ROVER , EAST, 1, 1);
		g.place(FOOD  , SOUTH, 1, 3);
		g.place(HOPPER, EAST, 2, 2);
		g.simulate(10, 1);
	}
	
	// --------
	// testBest
	void testBest1 () {
		Grid g(50, 50);
		srand(0);
		
		g.randPlace(BEST  , 5);
		g.randPlace(ROVER , 5);
		g.randPlace(FOOD  , 5);
		g.randPlace(HOPPER, 5);
		g.randPlace(TRAP  , 5);
		g.simulate(500, 50);
	}
	void testBest2 () {
		Grid g(80, 80);
		srand(0);
		
		g.randPlace(BEST  , 13);
		g.randPlace(ROVER , 13);
		g.randPlace(FOOD  , 13);
		g.randPlace(HOPPER, 13);
		g.randPlace(TRAP  , 13);
		g.simulate(1000, 500);
	}
	
	// -----
	// suite
	CPPUNIT_TEST_SUITE(TestDarwin);
	
	CPPUNIT_TEST(testGrid0);
	CPPUNIT_TEST(testPlace0);
	CPPUNIT_TEST(testPlace1);
	CPPUNIT_TEST(testPlace2);
	CPPUNIT_TEST(testHop0);
	CPPUNIT_TEST(testHop1);
	CPPUNIT_TEST(testFood0);
	CPPUNIT_TEST(testTrap0);
	CPPUNIT_TEST(testTrap1);
	CPPUNIT_TEST(testRover0);
	CPPUNIT_TEST(testBest0);
	CPPUNIT_TEST(testBest1);
	CPPUNIT_TEST(testBest2);
	
	CPPUNIT_TEST_SUITE_END();
};

// ----
// main
int main () {
	using namespace std;
	ios_base::sync_with_stdio(false);	// turn off synchronization with C I/O
	cout << "TestDarwin.c++" << endl;

	CppUnit::TextTestRunner tr;
	tr.addTest(TestDarwin::suite());
	tr.run();

	cout << "Done." << endl;
	return 0;
}
