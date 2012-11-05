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

#include "Darwin.h"

// ----------
// TestDarwin
struct TestDarwin : CppUnit::TestFixture {
	// --------
	// testGrid
	void testGrid0 () {
		Grid g(2, 2);
		
		g.print();
	}
	
	// --------
	// testPlace
	void testPlace0 () {
		Grid g(3, 3);
		
		g.place(HOPPER, 'n', 1, 1);
		
		g.print();
	}
	
	// --------
	// testHop
	void testHop0 () {
		Grid g(3, 3);
		g.place(HOPPER, 's', 0, 1);
		
		g.simulate(3, 1);
	}
	// hop into each other
	void testHop1 () {
		Grid g(3, 3);
		g.place(HOPPER, 'e', 1, 1);
		g.place(HOPPER, 'w', 1, 2);
		
		g.simulate(2, 1);
	}
	
	// --------
	// testFood
	void testFood0 () {
		Grid g(2, 2);
		
		g.place(FOOD, 's', 0, 0);
		g.simulate(2, 1);
	}
	
	// --------
	// testTrap
	void testTrap0 () {
		Grid g(2, 2);
		
		g.place(TRAP, 's', 0, 0);
		g.simulate(2, 1);
	}
	void testTrap1 () {
		Grid g(3, 3);
		
		g.place(TRAP, 'e', 1, 1);
		g.place(FOOD, 's', 1, 2);
		g.simulate(2, 1);
	}
	
	// --------
	// testRover
	void testRover0 () {
		Grid g(4, 4);
		srand(0);
		
		g.place(ROVER , 'e', 1, 1);
		g.place(FOOD  , 's', 1, 3);
		g.place(HOPPER, 'e', 2, 2);
		g.simulate(6, 1);
	}
	
	// --------
	// testBest
	void testBest0 () {
		Grid g(5, 5);
		srand(0);
			
		g.place(BEST  , 'e', 0, 0);
		g.place(ROVER , 'e', 1, 1);
		g.place(FOOD  , 's', 1, 3);
		g.place(HOPPER, 'e', 2, 2);
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
