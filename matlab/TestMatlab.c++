// ------------------------------
// projects/matlab/TestMatlab.c++
// Copyright (C) 2012
// Glenn P. Downing
// ------------------------------

/**
 * To test the program:
 *		g++ -ansi -pedantic -lcppunit -ldl -Wall TestMatlab.c++ -o TestMatlab.app
 *		valgrind TestMatlab.app >& TestMatlab.out
 */

// --------
// includes
#include "cppunit/extensions/HelperMacros.h"	// CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"				// TestFixture
#include "cppunit/TextTestRunner.h"				// TestRunner

#include "Matrix.h"
#include "Matlab.h"

// ----------
// TestMatlab
struct TestMatlab : CppUnit::TestFixture {
	// --------
	// test_cat
	void test_horzcat0() {
		Matrix<int> x;
		Matrix<int> y;
		Matrix<int> z;
		x = horzcat(x, y);
		CPPUNIT_ASSERT(x.eq(z));
	}
	
	void test_horzcat1 () {
		Matrix<int> x(2, 2);
		Matrix<int> y(2, 3);
		Matrix<int> z(2, 5);
		x = horzcat(x, y);
		CPPUNIT_ASSERT(x.eq(z));
	}

	void test_vertcat0 () {
		Matrix<int> x;
		Matrix<int> y;
		Matrix<int> z;
		x = vertcat(x, y);
		CPPUNIT_ASSERT(x.eq(z));
	}

	void test_vertcat1 () {
		Matrix<int> x(3, 2);
		Matrix<int> y(5, 2);
		Matrix<int> z(8, 2);
		x = vertcat(x, y);
		CPPUNIT_ASSERT(x.eq(z));
	}

	// ---------
	// test_diag
	void test_diag0 () {
		Matrix<int> x;
		Matrix<int> y;
		x = diag(x);
		CPPUNIT_ASSERT(x.eq(y));
	}
	
	void test_diag1 () {
		Matrix<int> x(2, 2, 1);
		Matrix<int> y(2, 1, 1);
		x = diag(x);
		//if(DEBUG)x.printMatrix();
		CPPUNIT_ASSERT(x.eq(y));
	}
	// --------
	// test_dot
	void test_dot () {
		Matrix<int> x;
		Matrix<int> y;
		Matrix<int> z;
		x = dot(x, y);
		CPPUNIT_ASSERT(x.eq(z));
	}

	// --------
	// test_eye
	void test_eye () {
		Matrix<int> x;
		Matrix<int> y(2, 3);
		y[0][0] = 1;
		y[1][1] = 1;
		
		x = eye< Matrix<int> >(2, 3);
		CPPUNIT_ASSERT(x.eq(y));
	}

	// -------------
	// test_linsolve
	void test_linsolve () {
		Matrix<int> x;
		Matrix<int> y;
		Matrix<int> z;
		x = linsolve(x, y);
		CPPUNIT_ASSERT(x.eq(z));
	}

	// ---------
	// test_ones
	void test_ones () {
		Matrix<int> x;
		Matrix<int> y(2, 3, 1);
		x = ones< Matrix<int> >(2, 3);
		CPPUNIT_ASSERT(x.eq(y));
	}

	// ---------
	// test_rand
	void test_rand0 () {
		Matrix<int> x;
		Matrix<int> y;
		x = rand< Matrix<int> >(2, 3);
		
		CPPUNIT_ASSERT(x.size() == 2);
		CPPUNIT_ASSERT(x[0].size() == 3);
	}
	void test_rand1 () {
		Matrix<int> x;
		Matrix<int> y;
		x = rand< Matrix<int> >(2, 3);
		
		CPPUNIT_ASSERT(x.size() == 2);
		CPPUNIT_ASSERT(x[0].size() == 3);
	}

	// --------------
	// test_transpose
	void test_transpose0 () {
		Matrix<int> x;
		Matrix<int> y;
		x = transpose(x);
		CPPUNIT_ASSERT(x.eq(y));
	}
	
	void test_transpose1 () {
		Matrix<int> x(2, 3);
		Matrix<int> y(3, 2);
		x = transpose(x);
		CPPUNIT_ASSERT(x.eq(y));
	}

	// ---------
	// test_tril
	void test_tril0 () {
		Matrix<int> x;
		Matrix<int> y;
		x = tril(x);
		CPPUNIT_ASSERT(x.eq(y));
	}
	
	void test_tril1 () {
		Matrix<int> x(2, 2, 1);
		Matrix<int> y(2, 2, 1);
		y[0][1] = 0;
		x = tril(x);
		
		CPPUNIT_ASSERT(x.eq(y));
	}

	// ---------
	// test_triu
	void test_triu0 () {
		Matrix<int> x;
		Matrix<int> y;
		x = triu(x);
		CPPUNIT_ASSERT(x.eq(y));
	}
	
	void test_triu1 () {
		Matrix<int> x(2, 2, 1);
		Matrix<int> y(2, 2, 1);
		y[1][0] = 0;
		x = triu(x);
		
		CPPUNIT_ASSERT(x.eq(y));
	}

	// ----------
	// test_zeros
	void test_zeros () {
		Matrix<int> x;
		Matrix<int> y(2, 3, 0);
		x = zeros< Matrix<int> >(2, 3);
		CPPUNIT_ASSERT(x.eq(y));
	}

	// -----
	// suite
	CPPUNIT_TEST_SUITE(TestMatlab);
	
	CPPUNIT_TEST(test_horzcat0);
	CPPUNIT_TEST(test_horzcat1);
	CPPUNIT_TEST(test_vertcat0);
	CPPUNIT_TEST(test_vertcat1);
	CPPUNIT_TEST(test_diag0);
	CPPUNIT_TEST(test_diag1);
	CPPUNIT_TEST(test_eye);
	CPPUNIT_TEST(test_linsolve);
	CPPUNIT_TEST(test_ones);
	CPPUNIT_TEST(test_rand0);
	CPPUNIT_TEST(test_rand1);
	CPPUNIT_TEST(test_transpose0);
	CPPUNIT_TEST(test_transpose1);
	CPPUNIT_TEST(test_tril0);
	CPPUNIT_TEST(test_tril1);
	CPPUNIT_TEST(test_triu0);
	CPPUNIT_TEST(test_triu1);
	CPPUNIT_TEST(test_zeros);
	
	CPPUNIT_TEST_SUITE_END();
};

// ----
// main
int main () {
	using namespace std;
	ios_base::sync_with_stdio(false);	// turn off synchronization with C I/O
	cout << "TestMatlab.c++" << endl;

	CppUnit::TextTestRunner tr;
	tr.addTest(TestMatlab::suite());
	tr.run();

	cout << "Done." << endl;
	return 0;
}
