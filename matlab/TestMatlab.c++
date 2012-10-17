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
	// 2 0x0 matricies
	void test_dot0 () {
		Matrix<int> A;
		Matrix<int> B;
		Matrix<int> ans;
		A = dot(A, B);
		CPPUNIT_ASSERT(A.eq(ans));
	}
	
	// Any 2 empty matricies returns and empty result in this implementation.
	void test_dot1 () {
		Matrix<int> A(3, 0);
		Matrix<int> B(3, 0);
		Matrix<int> ans;
		A = dot(A, B);
		CPPUNIT_ASSERT(A.eq(ans));
	}
	
	// Allowing different dimensions if both empty, simplifies the logic.
	void test_dot2 () {
		Matrix<int> A(3, 0);
		Matrix<int> B(0, 0);
		Matrix<int> ans;
		A = dot(A, B);
		CPPUNIT_ASSERT(A.eq(ans));
	}
	
	// simple 1x1 vectors
	void test_dot3 () {
		Matrix<int> A(1, 1, 3);
		Matrix<int> B(1, 1, 5);
		Matrix<int> ans(1, 1, 15);
		A = dot(A, B);
		CPPUNIT_ASSERT(A.eq(ans));
	}
	
	// 2 column vectors
	void test_dot4 () {
		Matrix<int> A(2, 1, 3);
		Matrix<int> B(2, 1, 5);
		Matrix<int> ans(1, 1, 30);
		A = dot(A, B);
		CPPUNIT_ASSERT(A.eq(ans));
	}
	
	// 2 row vectors
	void test_dot5 () {
		Matrix<int> A(1, 2, 3);
		Matrix<int> B(1, 2, 5);
		Matrix<int> ans(1, 1, 30);
		A = dot(A, B);
		CPPUNIT_ASSERT(A.eq(ans));
	}
	
	// row and column vectors
	void test_dot6 () {
		Matrix<int> A(1, 2, 3);
		Matrix<int> B(2, 1, 5);
		Matrix<int> ans(1, 1, 30);
		A = dot(A, B);
		CPPUNIT_ASSERT(A.eq(ans));
	}
	
	// column and row vectors
	void test_dot7 () {
		Matrix<int> A(2, 1, 3);
		Matrix<int> B(1, 2, 5);
		Matrix<int> ans(1, 1, 30);
		A = dot(A, B);
		CPPUNIT_ASSERT(A.eq(ans));
	}
	
	// 2 matricies
	void test_dot8 () {
		Matrix<int> A(2, 2, 3);
		Matrix<int> B = horzcat(Matrix<int>(2, 1, 5), Matrix<int>(2, 1, 0));
		Matrix<int> ans = horzcat(Matrix<int>(1, 1, 30), Matrix<int>(1, 1, 0));
		A = dot(A, B);
		CPPUNIT_ASSERT(A.eq(ans));
	}

	// -------------
	// test_linsolve
	void test_linsolve0 () {
		Matrix<int> A;
		Matrix<int> B;
		A = linsolve(A, B);
		CPPUNIT_ASSERT(A.eq(B));
	}
	
	void test_linsolve1 () {
		Matrix<int> A(3, 0);
		Matrix<int> B(3, 0);
		Matrix<int> ans;
		A = linsolve(A, B);
		CPPUNIT_ASSERT(A.eq(ans));	// design choice to return []
	}
	
	void test_linsolve2 () {
		Matrix<int> A(3, 5);
		Matrix<int> B(3, 0);
		Matrix<int> ans;
		A = linsolve(A, B);
		CPPUNIT_ASSERT(A.eq(ans));	// design choice to return []
	}
	
	void test_linsolve3 () {
		Matrix<int> A(3, 0);
		Matrix<int> B(3, 5);
		Matrix<int> ans;
		A = linsolve(A, B);
		CPPUNIT_ASSERT(A.eq(ans));	// design choice to return []
	}
	
	void test_linsolve4 () {
		const int m = 1;
		const int n = 1;
		const int k = 1;
		Matrix<int> A(m, n, 2);
		Matrix<int> B(m, k, 6);
		Matrix<int> ans(n, k, 3);
		A = linsolve(A, B);
		//CPPUNIT_ASSERT(A.eq(ans));
	}
	
	void test_linsolve5 () {
		const int m = 1;
		const int n = 2;
		const int k = 1;
		Matrix<int> A(m, n, 2);
		Matrix<int> B(m, k, 16);
		Matrix<int> ans(n, k, 8);
		A = linsolve(A, B);
		//CPPUNIT_ASSERT(A.eq(ans));
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
	CPPUNIT_TEST(test_linsolve0);
	/*CPPUNIT_TEST(test_linsolve1);
	CPPUNIT_TEST(test_linsolve2);
	CPPUNIT_TEST(test_linsolve3);
	CPPUNIT_TEST(test_linsolve4);
	CPPUNIT_TEST(test_linsolve5);
	*/
	CPPUNIT_TEST(test_dot0);
	CPPUNIT_TEST(test_dot1);
	CPPUNIT_TEST(test_dot2);
	CPPUNIT_TEST(test_dot3);
	CPPUNIT_TEST(test_dot4);
	CPPUNIT_TEST(test_dot5);
	CPPUNIT_TEST(test_dot6);
	CPPUNIT_TEST(test_dot7);
	CPPUNIT_TEST(test_dot8);
	CPPUNIT_TEST(test_eye);
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
