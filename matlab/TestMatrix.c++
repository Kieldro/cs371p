// ------------------------------
// projects/matlab/TestMatrix.c++
// Copyright (C) 2012
// Glenn P. Downing
// ------------------------------

/**
 * To test the program:
 *		make test
 *		g++ -ansi -pedantic -lcppunit -ldl -Wall TestMatrix.c++ -o TestMatrix.app
 *		valgrind TestMatrix.app >& TestMatrix.out
 *		on g++ version 4.4.3
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
		Matrix<int> y(2);		// size 0 rows?
		Matrix<int> z(2, 3);
		Matrix<int> t(2, 3, 4);
		
		
		CPPUNIT_ASSERT(x.size() == 0);
		
		CPPUNIT_ASSERT(y.size() == 2);
		CPPUNIT_ASSERT(y[0].size() == 0);
		
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
		const Matrix<int> y(1, 0);
		
		CPPUNIT_ASSERT(y[0] == Matrix<int>::value_type(0) );
		CPPUNIT_ASSERT(x[0][0] == 0);
	}

	// -----------
	// test_equals
	void test_equals0 () {
		Matrix<int> x;
		Matrix<int> z;
		Matrix<int>& y = x;
		
		CPPUNIT_ASSERT(  x == x);
		CPPUNIT_ASSERT(  x == y);
		CPPUNIT_ASSERT(!(x != y));
		CPPUNIT_ASSERT(x == z);
		
	}
	
	void test_equals1 () {
		Matrix<int> x(1);
		Matrix<int> y(2);
		CPPUNIT_ASSERT(x != y);
		
		//if(DEBUG)cerr << "BOOM! " << NULL << endl;
		
		x = Matrix<int>(2, 2);		// original x GCed?
		y = Matrix<int>(2, 0);
		CPPUNIT_ASSERT(x != y);
	}
	
	void test_equals2 () {
		Matrix<int> x(2, 0);
		Matrix<int> y(2, 0);
		CPPUNIT_ASSERT(x == y);
		
		x = Matrix<int>(2, 2, 7);
		y = Matrix<int>(2, 2, 5);
		CPPUNIT_ASSERT(x != y);
		
		x = Matrix<int>(2, 2, 5);
		y = Matrix<int>(2, 2, 5);
		y[1][1] = 9;
		CPPUNIT_ASSERT(x != y);
		
	}

	// --------------
	// test_less_than
	void test_less_than () {
		Matrix<int> x;
		Matrix<int> y;
		CPPUNIT_ASSERT(!(x < y));
	}

	// ---------
	// test_plus
	void test_plus0 () {
		Matrix<int> x;
		Matrix<int> y;
		Matrix<int> z;
		
		x += 0;
		CPPUNIT_ASSERT(x == z);
		x += y;
		CPPUNIT_ASSERT(x == z);
	}

	void test_plus1 () {
		Matrix<int> x(2, 2, 0);
		Matrix<int> y(2, 2, 1);
		Matrix<int> z(2, 2, 2);
		//x[0].push_back(7); 	// will invalidate a matrix
		
		x += 1;
		CPPUNIT_ASSERT(x == y);
		y += x;
		CPPUNIT_ASSERT(y == z);
	}

	// ----------
	// test_minus
	void test_minus0 () {
		Matrix<int> x;
		Matrix<int> y;
		Matrix<int> z;
		
		x -= 0;
		CPPUNIT_ASSERT(x == z);
		x -= y;
		CPPUNIT_ASSERT(x == z);
	}
	
	void test_minus1 () {
		Matrix<int> x(3, 3, 5);
		Matrix<int> y(3, 3, 2);
		Matrix<int> z(3, 3, 0);
		
		x -= 3;
		CPPUNIT_ASSERT(x == y);
		x -= y;
		CPPUNIT_ASSERT(x == z);
	}

	// ---
	// dot
	void test_dot0 () {
		Matrix<int> x;
		Matrix<int> y;
		
		int i = x.dot(vector<int>() = {5, 3}, vector<int>() = {5, 3});
		
		CPPUNIT_ASSERT(i == 34);
	}

	// ---
	// empty
	void test_empty0 () {
		Matrix<int> x;
		Matrix<int> y(0, 3);
		Matrix<int> z(5, 0);
		Matrix<int> w(5, 0, 3);
		
		CPPUNIT_ASSERT(x.empty());
		CPPUNIT_ASSERT(y.empty());
		CPPUNIT_ASSERT(z.empty());
		CPPUNIT_ASSERT(w.empty());
	}

	// ---------------
	// test_multiplies
	void test_multiplies0 () {
		Matrix<int> x;
		Matrix<int> y;
		Matrix<int> z;
		
		x *= 0;
		CPPUNIT_ASSERT(x == z);
		x *= y;
		CPPUNIT_ASSERT(x == z);
	}

	void test_multiplies1 () {
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
	CPPUNIT_TEST(test_equals0);
	CPPUNIT_TEST(test_equals1);
	CPPUNIT_TEST(test_equals2);
	CPPUNIT_TEST(test_less_than);
	CPPUNIT_TEST(test_plus0);
	CPPUNIT_TEST(test_plus1);
	CPPUNIT_TEST(test_minus0);
	CPPUNIT_TEST(test_minus1);
	CPPUNIT_TEST(test_dot0);
	CPPUNIT_TEST(test_empty0);
	CPPUNIT_TEST(test_multiplies0);
	CPPUNIT_TEST(test_multiplies1);
	/*CPPUNIT_TEST(test_iterator);
	CPPUNIT_TEST(test_const_iterator);
	*/
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
