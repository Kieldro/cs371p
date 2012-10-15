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
#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"		    // TestFixture
#include "cppunit/TextTestRunner.h"          // TestRunner

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
	}

	// ----------
	// test_index
	void test_index () {
		const Matrix<int> x(1, 1);
		const Matrix<int> y(1, 0);
		
		CPPUNIT_ASSERT(y[0] == Matrix<int>::value_type(0) );
		CPPUNIT_ASSERT(x[0][0] == 0);
	}

	// -----------
	// test_equals
	void test_equals0 () {
		//Matrix<int>  x;
		//Matrix<int>  y;
		Matrix<bool> z;
		Matrix<bool> t;
		//z = (x == y);
		
		CPPUNIT_ASSERT(z.eq(z));
		CPPUNIT_ASSERT(z.eq(t));
	}
	
	void test_equals1 () {
		Matrix<int> x(1, 2, 1);
		Matrix<int> y(2, 1, 1);
		
		CPPUNIT_ASSERT(!x.eq(y));
	}
	
	void test_equals2 () {
		Matrix<int> x(2, 2, -1);
		Matrix<int> y(2, 2, 343);
		CPPUNIT_ASSERT(!x.eq(y));
	}
	
	void test_equals3 () {
		Matrix<int> x(3, 3, 0);
		Matrix<int> y(3, 3, 0);
		x[2][2] = 1;
		CPPUNIT_ASSERT(!x.eq(y));
	}
	
	void test_equals4 () {
		Matrix<int> x(3, 0);
		Matrix<int> y(3, 0);
		
		CPPUNIT_ASSERT(x.eq(y));
	}

	// -----------
	// test_relEqual
	void test_relEqual0 () {
		Matrix<int>  x;
		Matrix<int>  y;
		Matrix<bool> z;
		Matrix<bool> t;
		z = (x == y);
		
		CPPUNIT_ASSERT(z.eq(t));
	}
	
	void test_relEqual1 () {
		Matrix<int>  x(2, 2, 1);
		Matrix<int>  y(2, 2, 0);
		Matrix<bool> z;
		Matrix<bool> t(2, 2, 0);
		z = (x == y);
		
		CPPUNIT_ASSERT(z.eq(t));
	}
	
	void test_relEqual2 () {
		Matrix<int>  x(2, 2, 7);
		Matrix<int>  y(2, 2, 7);
		Matrix<bool> z;
		Matrix<bool> t(2, 2, 1);
		z = (x == y);
		
		CPPUNIT_ASSERT(z.eq(t));
	}
	
	void test_relEqual3 () {
		Matrix<int>  x(2, 2, 7);
		Matrix<int>  y(2, 2, 7);
		Matrix<bool> z;
		Matrix<bool> t(2, 2, true);
		x[1][1] = 3;
		t[1][1] = false;
		z = (x == y);
		
		CPPUNIT_ASSERT(z.eq(t));
	}

	// --------------
	// test_less_than
	void test_less_than () {
		Matrix<int>  x;
		Matrix<int>  y;
		Matrix<bool> z;
		Matrix<bool> t;
		z = (x == y);
		CPPUNIT_ASSERT(z.eq(t));
	}

	// ---------
	// test_plus
	void test_plus () {
		Matrix<int> x;
		Matrix<int> y;
		Matrix<int> z;
		x += 0;
		CPPUNIT_ASSERT(x.eq(z));
		x += y;
		CPPUNIT_ASSERT(x.eq(z));
	}

	// ----------
	// test_minus
	void test_minus () {
		Matrix<int> x;
		Matrix<int> y;
		Matrix<int> z;
		x -= 0;
		CPPUNIT_ASSERT(x.eq(z));
		x -= y;
		CPPUNIT_ASSERT(x.eq(z));
	}

	// ---------------
	// test_multiplies
	void test_multiplies () {
		Matrix<int> x;
		Matrix<int> y;
		Matrix<int> z;
		x *= 0;
		CPPUNIT_ASSERT(x.eq(z));
		x *= y;
		CPPUNIT_ASSERT(x.eq(z));
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
	CPPUNIT_TEST(test_equals0);
	CPPUNIT_TEST(test_equals1);
	CPPUNIT_TEST(test_equals2);
	CPPUNIT_TEST(test_equals3);
	CPPUNIT_TEST(test_equals4);
	CPPUNIT_TEST(test_relEqual0);
	CPPUNIT_TEST(test_relEqual1);
	CPPUNIT_TEST(test_relEqual2);
	CPPUNIT_TEST(test_relEqual3);
	//CPPUNIT_TEST(test_less_than);
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
