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
	}
	
	// --------
	// testHopper
	void testHopper0 () {
		//Grid g(5, 5);
		
		//Hopper h('e', 0, 1, NULL);
		//h.test();
		//if(DEBUG)cerr << "BOOM!: " << h << endl;
	}
	
	// --------
	// testPlace
	void testPlace0 () {
		Grid g(3, 3);
		//Creature x = Hopper('n', 0, 1, &g);
		
		//g.place(HOPPER, 'n', 1, 1);
		
		//g.print();
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
/*	
	// --------
	// testRunTurn
	void testRunTurn0 () {
		Grid g(3, 3);
		g.place(HOPPER, 'n', 1, 1);
		
		g.print();
		g.runTurn();
		g.print();
	}
	
/*	void testRunTurn1 () {
		Grid g(3, 3);
		Creature x = Hopper('n');
		g.place(x, 1, 1);
		g.place(x, 1, 2);
		
		g.print();
		g.runTurn();
		g.print();
		g.runTurn();
		g.print();
	}
	
	// --------
	// testSimulate
	void testSimulate0 () {
		Grid g(3, 3);
		g.place(HOPPER, 'n', 0, 1);
		
		g.simulate(2, 1);
	}
	
	// --------
	// testCreatureProgram
	void testCreatureProgram0 () {
		Grid g(3, 3);
		Creature x = Hopper('n');
		
		//CPPUNIT_ASSERT(x.program[0].op == "hop");
		//CPPUNIT_ASSERT(x.program[0].line == -1);
	}
*/
	// -----
	// suite
	CPPUNIT_TEST_SUITE(TestDarwin);
	
	CPPUNIT_TEST(testGrid0);
	CPPUNIT_TEST(testPlace0);
	CPPUNIT_TEST(testHopper0);
	CPPUNIT_TEST(testHop0);
	CPPUNIT_TEST(testHop1);
// 	CPPUNIT_TEST(testRunTurn0);
/*	CPPUNIT_TEST(testRunTurn0);
	CPPUNIT_TEST(testRunTurn1);
	CPPUNIT_TEST(testCreatureProgram0);
	*/
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
