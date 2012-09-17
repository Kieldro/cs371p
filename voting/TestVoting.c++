// includes
#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"			// TestFixture
#include "cppunit/TextTestRunner.h"			// TextTestRunner

#include "Voting.h"

// -----------
// TestVoting
struct TestVoting : CppUnit::TestFixture {
	// ----
	// read
	void test_read_0 () {
		istringstream r("1 10\n");
		int i;
		int j;
		const bool b = read(r, i, j);
		
		CPPUNIT_ASSERT(b == true);
		CPPUNIT_ASSERT(i ==	1);
		CPPUNIT_ASSERT(j == 10);
	}
	
	void test_solve_4 () {
		int t0 = clock();
		istringstream r("1 999999\n");
		ostringstream w;
		solve(r, w);
		if(DEBUG) cerr << "w.str(): " << w.str() << endl;
		CPPUNIT_ASSERT(w.str() == "1 999999 525\n");
		int t1 = clock();
		int i = 0; i++;
		if(DEBUG) cerr << "time: " << (t1 - t0) << endl;
		if(DEBUG) cerr << "clock per sec: " << CLOCKS_PER_SEC	 << endl;
		
	}

	// -----
	// suite
	CPPUNIT_TEST_SUITE(TestVoting);
	
	CPPUNIT_TEST(test_read_0);
	/*CPPUNIT_TEST(test_read_1);
	CPPUNIT_TEST(test_read_2);
	CPPUNIT_TEST(test_solve_0);
	CPPUNIT_TEST(test_solve_1);
	CPPUNIT_TEST(test_solve_2);
	CPPUNIT_TEST(test_solve_3);
	CPPUNIT_TEST(test_solve_4);
	*/
	CPPUNIT_TEST_SUITE_END();
};

// ----
// main
int main () {
	//using namespace std;
	//ios_base::sync_with_stdio(false);  // turn off synchronization with C I/O
	cout << "TestVoting.c++" << endl;

	CppUnit::TextTestRunner tr;
	tr.addTest(TestVoting::suite());
	tr.run();

	cout << "Done." << endl;
	return 0;
}
