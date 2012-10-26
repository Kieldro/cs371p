/**
 * To test the program:
 *		g++ -pedantic -lcppunit -ldl -Wall TestDarwin.c++ -o TestDarwin.app
 *		valgrind TestDarwin.app >& TestDarwin.out
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
		
		//g.print();
		CPPUNIT_ASSERT(true);
	}
	
	// --------
	// testHopper
	void testHopper0 () {
		//Grid g(5, 5);
		
		Hopper h('e');
		//h.test();
		//if(DEBUG)cerr << "BOOM!: " << h << endl;
		CPPUNIT_ASSERT(true);
	}
	
	// --------
	// testPlace
	void testPlace0 () {
		Grid g(3, 3);
		Creature x = Hopper('n');
		
		g.place(x, 1, 1);
		
		//g.print();
		CPPUNIT_ASSERT(true);
	}
	
	// --------
	// testrunTurn
	void testrunTurn0 () {
		Grid g(3, 3);
		Creature x = Hopper('n');
		g.place(x, 1, 1);
		
		g.print();
		g.runTurn();
		g.print();
		g.runTurn();
		g.print();
		CPPUNIT_ASSERT(true);
	}
	void testrunTurn1 () {
		Grid g(3, 3);
		Creature x = Hopper('n');
		g.place(x, 1, 1);
		g.place(x, 1, 2);
		
		g.print();
		g.runTurn();
		g.print();
		g.runTurn();
		g.print();
		CPPUNIT_ASSERT(true);
	}

	// -----
	// suite
	CPPUNIT_TEST_SUITE(TestDarwin);
	
	CPPUNIT_TEST(testGrid0);
	CPPUNIT_TEST(testPlace0);
	CPPUNIT_TEST(testHopper0);
	CPPUNIT_TEST(testrunTurn0);
	CPPUNIT_TEST(testrunTurn1);
	
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
