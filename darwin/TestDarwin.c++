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
		Grid g(5, 5);
		
		g.print();
		CPPUNIT_ASSERT(true);
	}
	
	// --------
	// testHopper
	void testHopper0 () {
		//Grid g(5, 5);
		
		Hopper h;
		h.sigil = 'a';
		//if(DEBUG)cerr << "BOOM!: " << h << endl;
		//h.i = 2;
		
		//g.print();
		CPPUNIT_ASSERT(true);
	}
	
	// --------
	// testPlace
	void testPlace0 () {
		Grid g(5, 5);
		Creature x = Hopper();
		
		g.place(x, 2, 2);
		
		g.print();
		CPPUNIT_ASSERT(true);
	}

	// -----
	// suite
	CPPUNIT_TEST_SUITE(TestDarwin);
	
	CPPUNIT_TEST(testGrid0);
	CPPUNIT_TEST(testPlace0);
	CPPUNIT_TEST(testHopper0);
	
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
