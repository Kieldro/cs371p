// ------------------------------
// projects/matlab/TestMatrix.c++
// Copyright (C) 2012
// Glenn P. Downing
// ------------------------------

/**
 * To test the program:
 *		make test
 *		g++ -std=c++0x -ansi -pedantic -lcppunit -ldl -Wall TestMatrix.c++ -o TestMatrix.app
 *		valgrind TestMatrix.app >& TestMatrix.out
 */

// --------
// includes
#include "cppunit/extensions/HelperMacros.h"	// CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"				// TestFixture
#include "cppunit/TextTestRunner.h"				// TestRunner

#include "Matrix.h"

using std::exception;

// ----------
// TestMatrix
struct TestMatrix : CppUnit::TestFixture {
	// ----------------
	// test_constructor
	void test_constructor0 () {
		Matrix<int> x;
		Matrix<int> y(2);
		Matrix<int> z(2, 3);
		Matrix<int> t(2, 3, 4);
		CPPUNIT_ASSERT(x.size() == 0);
	}

	void test_constructor1 () {
		;
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
		Matrix<bool> z;
		Matrix<bool> t;
		
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
	
	void test_relEqual4 () {
		Matrix<int>  x(5, 0);
		Matrix<int>  y(5, 0);
		//if(DEBUG)Matrix<int>(0, 5).printMatrix();
		Matrix<bool> z;
		Matrix<bool> t(5, 0);	// answer must have same dimensions
		z = (x == y);
		
		CPPUNIT_ASSERT(z.eq(t));
	}
	
	void test_relEqual5 () {
		Matrix<int>  x(5, 5);
		Matrix<int>  y(4, 5);
		//auto s = Matrix<int>::eq;
		
		try{
			// exception must be thrown
			x == y;
		}catch(exception& e){
			CPPUNIT_ASSERT(true);
			return;
		}
		CPPUNIT_ASSERT(false);
	}
	
	void test_relEqual6 () {
		assert(testMethod());
	}
	
	bool testMethod(){
		Matrix<int> x(5, 5);
		Matrix<int> y(5, 4);
		//Matrix<bool> (*op)(const Matrix<int>&, const Matrix<int>&) = Matrix<int>::operator==;
		//auto f= operator==;
		try{
			// exception must be thrown
			operator==(x, y);
		}catch(exception& e){
			return true;
		}
		
		return false;
	 }

	// ---------
	// test_less
	void test_less0 () {
		Matrix<int>  x;
		Matrix<int>  y;
		Matrix<bool> z;
		Matrix<bool> t;
		z = (x < y);
		
		CPPUNIT_ASSERT(z.eq(t));
	}
	
	void test_less1 () {
		Matrix<int>  x(2, 2, 5);
		Matrix<int>  y(2, 2, 5);
		Matrix<bool> z;
		Matrix<bool> t(2, 2, false);
		z = (x < y);
		
		CPPUNIT_ASSERT(z.eq(t));
	}
	
	void test_less2 () {
		Matrix<int>  x(2, 2, 5);
		Matrix<int>  y(2, 2, 7);
		Matrix<bool> z;
		Matrix<bool> t(2, 2, true);
		z = (x < y);
		
		CPPUNIT_ASSERT(z.eq(t));
	}
	
	void test_less3 () {
		Matrix<int>  x(2, 2, 5);
		Matrix<int>  y(2, 2, 5);
		Matrix<bool> z;
		Matrix<bool> t(2, 2, false);
		x[1][1] = 3;
		t[1][1] = true;
		z = (x < y);
		
		CPPUNIT_ASSERT(z.eq(t));
	}
	
	void test_less4 () {
		Matrix<int>  x(5, 0);
		Matrix<int>  y(5, 0);
		Matrix<bool> z;
		Matrix<bool> t(5, 0);	// answer must have same dimensions
		z = (x < y);
		
		CPPUNIT_ASSERT(z.eq(t));
	}
	
	void test_less5 () {
		Matrix<int>  x(5, 0);
		Matrix<int>  y(5, 0);
		Matrix<bool> z;
		Matrix<bool> t(5, 0);	// answer must have same dimensions
		z = (x < y);
		
		CPPUNIT_ASSERT(z.eq(t));
	}

	// --------------
	// test_less_equal
	void test_less_equal0 () {
		Matrix<int>  x;
		Matrix<int>  y;
		Matrix<bool> z;
		Matrix<bool> t;
		z = (x <= y);
		
		CPPUNIT_ASSERT(z.eq(t));
	}
	
	void test_less_equal1 () {
		Matrix<int>  x(2, 2, 7);
		Matrix<int>  y(2, 2, 5);
		Matrix<bool> z;
		Matrix<bool> t(2, 2, false);
		z = (x <= y);
		
		CPPUNIT_ASSERT(z.eq(t));
	}
	
	void test_less_equal2 () {
		Matrix<int>  x(2, 2, 5);
		Matrix<int>  y(2, 2, 7);
		Matrix<bool> z;
		Matrix<bool> t(2, 2, true);
		z = (x <= y);
		
		CPPUNIT_ASSERT(z.eq(t));
	}
	
	void test_less_equal3 () {
		Matrix<int>  x(2, 2, 5);
		Matrix<int>  y(2, 2, 5);
		Matrix<bool> z;
		Matrix<bool> t(2, 2, true);
		x[1][1] = 7;
		t[1][1] = false;
		z = (x <= y);
		
		CPPUNIT_ASSERT(z.eq(t));
	}
	
	void test_less_equal4 () {
		Matrix<int>  x(5, 0);
		Matrix<int>  y(5, 0);
		Matrix<bool> z;
		Matrix<bool> t(5, 0);	// answer must have same dimensions
		z = (x <= y);
		
		CPPUNIT_ASSERT(z.eq(t));
	}

	// --------------
	// test_ne
	void test_ne0 () {
		Matrix<int>  x;
		Matrix<int>  y;
		Matrix<bool> z;
		Matrix<bool> t;
		z = (x != y);
		
		CPPUNIT_ASSERT(z.eq(t));
	}
	
	void test_ne1 () {
		Matrix<int>  x(2, 2, 3);
		Matrix<int>  y(2, 2, 3);
		Matrix<bool> z;
		Matrix<bool> t(2, 2, false);
		z = (x != y);
		
		CPPUNIT_ASSERT(z.eq(t));
	}
	
	void test_ne2 () {
		Matrix<int>  x(2, 2, 3);
		Matrix<int>  y(2, 2, 5);
		Matrix<bool> z;
		Matrix<bool> t(2, 2, true);
		z = (x != y);
		
		CPPUNIT_ASSERT(z.eq(t));
	}
	
	void test_ne3 () {
		Matrix<int>  x(2, 2, 3);
		Matrix<int>  y(2, 2, 3);
		Matrix<bool> z;
		Matrix<bool> t(2, 2, false);
		x[1][1] = 5;
		t[1][1] = true;
		z = (x != y);
		
		CPPUNIT_ASSERT(z.eq(t));
	}
	
	void test_ne4 () {
		Matrix<int>  x(2, 0);
		Matrix<int>  y(2, 0);
		Matrix<bool> z;
		Matrix<bool> t(2, 0);
		z = (x != y);
		
		CPPUNIT_ASSERT(z.eq(t));
	}

	// --------------
	// test_greater
	void test_greater0 () {
		Matrix<int>  x;
		Matrix<int>  y;
		Matrix<bool> z;
		Matrix<bool> t;
		z = (x > y);
		
		CPPUNIT_ASSERT(z.eq(t));
	}
	
	void test_greater1 () {
		Matrix<int>  x(2, 2, 3);
		Matrix<int>  y(2, 2, 3);
		Matrix<bool> z;
		Matrix<bool> t(2, 2, false);
		z = (x > y);
		
		CPPUNIT_ASSERT(z.eq(t));
	}
	
	void test_greater2 () {
		Matrix<int>  x(2, 2, 3);
		Matrix<int>  y(2, 2, 5);
		Matrix<bool> z;
		Matrix<bool> t(2, 2, false);
		z = (x > y);
		
		CPPUNIT_ASSERT(z.eq(t));
	}
	
	void test_greater3 () {
		Matrix<int>  x(2, 2, 3);
		Matrix<int>  y(2, 2, 3);
		Matrix<bool> z;
		Matrix<bool> t(2, 2, false);
		x[1][1] = 5;
		t[1][1] = true;
		z = (x > y);
		
		CPPUNIT_ASSERT(z.eq(t));
	}
	
	void test_greater4 () {
		Matrix<int>  x(2, 0);
		Matrix<int>  y(2, 0);
		Matrix<bool> z;
		Matrix<bool> t(2, 0);
		z = (x > y);
		
		CPPUNIT_ASSERT(z.eq(t));
	}

	// --------------
	// test_greater_equal
	void test_greater_equal0 () {
		Matrix<int>  x;
		Matrix<int>  y;
		Matrix<bool> z;
		Matrix<bool> t;
		z = (x >= y);
		
		CPPUNIT_ASSERT(z.eq(t));
	}
	
	void test_greater_equal1 () {
		Matrix<int>  x(2, 2, 3);
		Matrix<int>  y(2, 2, 3);
		Matrix<bool> z;
		Matrix<bool> t(2, 2, true);
		z = (x >= y);
		
		CPPUNIT_ASSERT(z.eq(t));
	}
	
	void test_greater_equal2 () {
		Matrix<int>  x(2, 2, 3);
		Matrix<int>  y(2, 2, 5);
		Matrix<bool> z;
		Matrix<bool> t(2, 2, false);
		z = (x >= y);
		
		CPPUNIT_ASSERT(z.eq(t));
	}
	
	void test_greater_equal3 () {
		Matrix<int>  x(2, 2, 3);
		Matrix<int>  y(2, 2, 3);
		Matrix<bool> z;
		Matrix<bool> t(2, 2, true);
		x[1][1] = 5;
		t[1][1] = true;
		z = (x >= y);
		
		CPPUNIT_ASSERT(z.eq(t));
	}
	
	void test_greater_equal4 () {
		Matrix<int>  x(2, 0);
		Matrix<int>  y(2, 0);
		Matrix<bool> z;
		Matrix<bool> t(2, 0);
		z = (x >= y);
		
		CPPUNIT_ASSERT(z.eq(t));
	}
	
	// --------------------
	// test_scalar_addition
	void test_scalar_addition0() {
		Matrix<int> x(2, 2, 0);
		Matrix<int> z(2, 2, 1);
		x += 1;
		CPPUNIT_ASSERT(z.eq(x));
	}
	void test_scalar_addition1() {
		Matrix<int> x(2, 2, 0);
		Matrix<int> z(2, 2, -1);
		x += -1;
		CPPUNIT_ASSERT(z.eq(x));
	}
	void test_scalar_addition2() {
		Matrix<int> x(2, 2, 2);
		x[1][0] = 4;
		Matrix<int> z(2, 2, 7);
		z[1][0] = 9;
		x += 5;
		CPPUNIT_ASSERT(z.eq(x));
	}
	void test_scalar_addition3() {
		Matrix<int> x;
		Matrix<int> z;
		x += 1123;
		CPPUNIT_ASSERT(z.eq(x));
	}
	
	// -----------------------
	// test_scalar_subtraction
	void test_scalar_subtraction0() {
		Matrix<int> x(2, 2, 0);
		Matrix<int> z(2, 2, -1);
		x -= 1;
		CPPUNIT_ASSERT(z.eq(x));
	}
	void test_scalar_subtraction1() {
		Matrix<int> x(2, 2, 0);
		Matrix<int> z(2, 2, +1);
		x -= -1;
		CPPUNIT_ASSERT(z.eq(x));
	}
	void test_scalar_subtraction2() {
		Matrix<int> x(2, 2, 2);
		x[1][0] = 4;
		Matrix<int> z(2, 2, -3);
		z[1][0] = -1;
		x -= 5;
		CPPUNIT_ASSERT(z.eq(x));
	}
	void test_scalar_subtraction3() {
		Matrix<int> x;
		Matrix<int> z;
		x -= 1123;
		CPPUNIT_ASSERT(z.eq(x));
	}
	
	// -----------------------
	// test_scalar_multiplication
	void test_scalar_multiplication0() {
		Matrix<int> x(2, 2, 1);
		Matrix<int> z(2, 2, 3);
		x *= 3;
		CPPUNIT_ASSERT(z.eq(x));
	}
	void test_scalar_multiplication1() {
		Matrix<int> x(2, 2, -3);
		Matrix<int> z(2, 2, 15);
		x *= -5;
		CPPUNIT_ASSERT(z.eq(x));
	}
	void test_scalar_multiplication2() {
		Matrix<int> x(2, 2, 2);
		x[1][0] = 4;
		Matrix<int> z(2, 2, 10);
		z[1][0] = 20;
		x *= 5;
		CPPUNIT_ASSERT(z.eq(x));
	}
	
	// ---------
	// test_plus
	void test_plus0 () {
		Matrix<int> x;
		Matrix<int> y;
		Matrix<int> z;
		x += y;
		CPPUNIT_ASSERT(x.eq(z));
	}

	void test_plus1 () {
		Matrix<int> x(2, 2, 0);
		Matrix<int> y(2, 2, 1);
		Matrix<int> z(2, 2, 2);
		//x[0].push_back(7); 	// will invalidate a matrix
		
		x += 1;
		CPPUNIT_ASSERT(x.eq(y));
		y += x;
		CPPUNIT_ASSERT(y.eq(z));
	}
	
	void test_plus2 () {
		Matrix<int> x(2, 2, 0);
		Matrix<int> y(7, 7, 1);
		
		try{
			x += y;
		}catch(std::exception& e){
			CPPUNIT_ASSERT(true);
			return;
		}
		// no exception was thrown
		CPPUNIT_ASSERT(false);
	}
	
	void test_plus3 () {
		Matrix<int> x(2, 2, 0);
		Matrix<int> y(2, 7, 1);
		
		try{
			x += y;
		}catch(std::exception& e){
			CPPUNIT_ASSERT(true);
			return;
		}
		// no exception was thrown
		CPPUNIT_ASSERT(false);
	}


	// ----------
	// test_minus
	void test_minus0 () {
		Matrix<int> x;
		Matrix<int> y;
		Matrix<int> z;
		x -= y;
		CPPUNIT_ASSERT(x.eq(z));
	}
	
	void test_minus1 () {
		Matrix<int> x(3, 3, 5);
		Matrix<int> y(3, 3, 2);
		Matrix<int> z(3, 3, 0);
		
		x -= 3;
		CPPUNIT_ASSERT(x.eq(y));
		x -= y;
		CPPUNIT_ASSERT(x.eq(z));
	}

	// ---------------
	// test_multiplies
	void test_multiplies0 () {
		Matrix<int> x;
		Matrix<int> y;
		Matrix<int> z;
		
		x *= y;
		CPPUNIT_ASSERT(x.eq(z));
	}

	void test_multiplies1 () {
		const int innerD = 5;
		Matrix<int> x(3, innerD);
		Matrix<int> y(innerD, 0);
		Matrix<int> z(3, 0);
		
		x *= y;
		// must return a 3x0
		CPPUNIT_ASSERT(x.eq(z));
	}

	void test_multiplies2 () {
		const int innerD = 3;
		Matrix<int> x(3, innerD, 11);
		Matrix<int> y(innerD, 5, 7);
		Matrix<int> z(3, 5, 11*7*innerD);
		
		x *= y;
		//if(DEBUG)x.printMatrix();
		CPPUNIT_ASSERT(x.eq(z));
	}

	void test_multiplies3 () {
		const int innerD = 1;
		Matrix<int> x(3, innerD, 11);
		Matrix<int> y(innerD, 5, 7);
		Matrix<int> z(3, 5, 11*7*innerD);
		
		x *= y;
		//if(DEBUG)x.printMatrix();
		CPPUNIT_ASSERT(x.eq(z));
	}

	void test_multiplies4 () {
		Matrix<int> x(0, 0);
		Matrix<int> y(1, 0);
		
		try{
			x *= y;
		}catch(std::exception& e){
			CPPUNIT_ASSERT(true);
			return;
		}
		// no exception was thrown
		CPPUNIT_ASSERT(false);
	}

	void test_multiplies5 () {
		const int innerD = 0;
		Matrix<int> x(3, innerD);
		Matrix<int> y(innerD, 0);
		Matrix<int> z(3, 0);
		
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

	// ---
	// empty
	void test_empty () {
		Matrix<int> x;
		Matrix<int> y(0, 3);
		Matrix<int> z(5, 0);
		Matrix<int> w(5, 0, 3);
		
		CPPUNIT_ASSERT(x.empty());
		CPPUNIT_ASSERT(y.empty());
		CPPUNIT_ASSERT(z.empty());
		CPPUNIT_ASSERT(w.empty());
	}

	// -----
	// suite
	CPPUNIT_TEST_SUITE(TestMatrix);
	
	CPPUNIT_TEST(test_constructor0);
	CPPUNIT_TEST(test_constructor1);
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
	CPPUNIT_TEST(test_relEqual4);
	CPPUNIT_TEST(test_relEqual5);
	CPPUNIT_TEST(test_relEqual6);
	CPPUNIT_TEST(test_scalar_addition0);
	CPPUNIT_TEST(test_scalar_addition1);
	CPPUNIT_TEST(test_scalar_addition2);
	CPPUNIT_TEST(test_scalar_addition3);
	CPPUNIT_TEST(test_scalar_subtraction0);
	CPPUNIT_TEST(test_scalar_subtraction1);
	CPPUNIT_TEST(test_scalar_subtraction2);
	CPPUNIT_TEST(test_scalar_subtraction3);
	CPPUNIT_TEST(test_scalar_multiplication0);
	CPPUNIT_TEST(test_scalar_multiplication1);
	CPPUNIT_TEST(test_scalar_multiplication2);
	CPPUNIT_TEST(test_less0);
	CPPUNIT_TEST(test_less1);
	CPPUNIT_TEST(test_less2);
	CPPUNIT_TEST(test_less3);
	CPPUNIT_TEST(test_less4);
	CPPUNIT_TEST(test_less_equal0);
	CPPUNIT_TEST(test_less_equal1);
	CPPUNIT_TEST(test_less_equal2);
	CPPUNIT_TEST(test_less_equal3);
	CPPUNIT_TEST(test_less_equal4);
	CPPUNIT_TEST(test_ne0);
	CPPUNIT_TEST(test_ne1);
	CPPUNIT_TEST(test_ne2);
	CPPUNIT_TEST(test_ne3);
	CPPUNIT_TEST(test_greater0);
	CPPUNIT_TEST(test_greater1);
	CPPUNIT_TEST(test_greater2);
	CPPUNIT_TEST(test_greater3);
	CPPUNIT_TEST(test_greater4);
	CPPUNIT_TEST(test_greater_equal0);
	CPPUNIT_TEST(test_greater_equal1);
	CPPUNIT_TEST(test_greater_equal2);
	CPPUNIT_TEST(test_greater_equal3);
	CPPUNIT_TEST(test_greater_equal4);
	CPPUNIT_TEST(test_plus0);
	CPPUNIT_TEST(test_plus1);
	CPPUNIT_TEST(test_plus2);
	CPPUNIT_TEST(test_plus3);
	CPPUNIT_TEST(test_minus0);
	CPPUNIT_TEST(test_minus1);
	CPPUNIT_TEST(test_multiplies0);
	CPPUNIT_TEST(test_multiplies1);
	CPPUNIT_TEST(test_multiplies2);
	CPPUNIT_TEST(test_multiplies3);
	CPPUNIT_TEST(test_multiplies4);
	CPPUNIT_TEST(test_multiplies5);
	CPPUNIT_TEST(test_iterator);
	CPPUNIT_TEST(test_const_iterator);
	CPPUNIT_TEST(test_empty);
	
	CPPUNIT_TEST_SUITE_END();
};

// ----
// main
int main () {
	using namespace std;
	ios_base::sync_with_stdio(false);	// turn off synchronization with C I/O
	cout << "TestMatrix.c++" << endl;

	CppUnit::TextTestRunner tr;
	tr.addTest(TestMatrix::suite());
	tr.run();

	cout << "Done." << endl;
	return 0;
}
