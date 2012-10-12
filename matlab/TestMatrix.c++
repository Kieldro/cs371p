// ------------------------------
// projects/matlab/TestMatrix.c++
// Copyright (C) 2012
// Glenn P. Downing
// ------------------------------

/**
 * To test the program:
 *		g++ -ansi -pedantic -lcppunit -ldl -Wall TestMatrix.c++ -o TestMatrix.app
 *		valgrind TestMatrix.app >& TestMatrix.out
 */

// --------
// includes
#include "cppunit/extensions/HelperMacros.h"	// CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"				// TestFixture
#include "cppunit/TextTestRunner.h"				// TestRunner

#include "Matrix.h"

// ----------
// TestMatrix
struct TestMatrix : CppUnit::TestFixture {
	// ----------------
	// test_constructor
	void test_constructor () {
		Matrix<int> x;
		Matrix<int> y(2);
		Matrix<int> z(2, 3);
		Matrix<int> t(2, 3, 4);
		CPPUNIT_ASSERT(x.size() == 0);
		
		CPPUNIT_ASSERT(y.size() == 2);
		
		CPPUNIT_ASSERT(z.size() == 2);
		CPPUNIT_ASSERT(z[0].size() == 3);
		
		CPPUNIT_ASSERT(t.size() == 2);
		CPPUNIT_ASSERT(t[0].size() == 3);
		CPPUNIT_ASSERT(t[0][0] == 4);
		CPPUNIT_ASSERT(t[1][2] == 4);
	}

	// ----------
	// test_index
	void test_index () {
		const Matrix<int> x(1, 1);
		
		CPPUNIT_ASSERT(x[0][0] == 0);
	}

	// -----------
	// test_equals
	void test_equals () {
		Matrix<int> x;
		Matrix<int> y;
		CPPUNIT_ASSERT(  x == y);
		CPPUNIT_ASSERT(!(x != y));
	}

	// --------------
	// test_less_than
	void test_less_than () {
		Matrix<int> x;
		Matrix<int> y;
		CPPUNIT_ASSERT(  x == y);
		CPPUNIT_ASSERT(!(x != y));
	}

	// ---------
	// test_plus
	void test_plus () {
		Matrix<int> x;
		Matrix<int> y;
		Matrix<int> z;
		x += 0;
		CPPUNIT_ASSERT(x == z);
		x += y;
		CPPUNIT_ASSERT(x == z);
	}

	// ----------
	// test_minus
	void test_minus () {
		Matrix<int> x;
		Matrix<int> y;
		Matrix<int> z;
		x -= 0;
		CPPUNIT_ASSERT(x == z);
		x -= y;
		CPPUNIT_ASSERT(x == z);
	}

	// ---------------
	// test_multiplies
	void test_multiplies () {
		Matrix<int> x;
		Matrix<int> y;
		Matrix<int> z;
		x *= 0;
		CPPUNIT_ASSERT(x == z);
		x *= y;
		CPPUNIT_ASSERT(x == z);
	}

	// -------------
	// test_iterator
	void test_iterator () {
		Matrix<int> x;
		Matrix<int>::iterator b = x.begin();
		Matrix<int>::iterator e = x.end();
		CPPUNIT_ASSERT(b == e);
	}

	// -------------------
	// test_const_iterator
	void test_const_iterator () {
		const Matrix<int> x;
		Matrix<int>::const_iterator b = x.begin();
		Matrix<int>::const_iterator e = x.end();
		CPPUNIT_ASSERT(b == e);
	}

	// -----
	// suite
	CPPUNIT_TEST_SUITE(TestMatrix);
	
	CPPUNIT_TEST(test_constructor);
	CPPUNIT_TEST(test_index);
	CPPUNIT_TEST(test_equals);
	CPPUNIT_TEST(test_less_than);
	CPPUNIT_TEST(test_plus);
	CPPUNIT_TEST(test_minus);
	CPPUNIT_TEST(test_multiplies);
	CPPUNIT_TEST(test_iterator);
	CPPUNIT_TEST(test_const_iterator);
	
	CPPUNIT_TEST_SUITE_END();
};

// ----
// main
int main () {
	using namespace std;
	ios_base::sync_with_stdio(false); // turn off synchronization with C I/O
	cout << "TestMatrix.c++" << endl;

	CppUnit::TextTestRunner tr;
	tr.addTest(TestMatrix::suite());
	tr.run();

	cout << "Done." << endl;
	return 0;
}
