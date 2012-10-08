// ------------------------------------
// projects/allocator/TestAllocator.c++
// Copyright (C) 2011
// Glenn P. Downing
// ------------------------------------

/**
 * To test the program:
 *	g++ -ansi -pedantic -lcppunit -ldl -Wall TestAllocator.c++ -o TestAllocator.app
 *	valgrind TestAllocator.app >& TestAllocator.out
 */

// --------
// includes
#include <algorithm>	// count
#include <memory>		// allocator

#include "cppunit/extensions/HelperMacros.h"	// CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"				// TestFixture
#include "cppunit/TextTestRunner.h"				// TestRunner

#include "Allocator.h"

// -------------
// TestAllocator
template <typename A>
struct TestAllocator : CppUnit::TestFixture {
	// --------
	// typedefs
	typedef typename A::value_type		value_type;
	typedef typename A::difference_type	difference_type;
	typedef typename A::pointer			pointer;
	
	// -----
	// test0
	void test0 () {
		A x;
	}
	
	// -----
	// test1
	void test1 () {
		A x;
		x.allocate(6);
	}
	
	// --------
	// test_one
	void test_one () {
		A x;
		const difference_type	s = 1;
		const value_type		v = 2;
		const pointer			p = x.allocate(s);
		x.construct(p, v);
		
		CPPUNIT_ASSERT(*p == v);
		CPPUNIT_ASSERT(x == A());
		CPPUNIT_ASSERT(not (x != A()) );
		x.destroy(p);
		x.deallocate(p, s);
	}

	// --------
	// test_ten
	void test_ten () {
		A x;
		const difference_type	s = 10;
		const value_type		v = 2;
		const pointer			b = x.allocate(s);
			pointer				e = b + s;
			pointer				p = b;
		try {
		while (p != e) {
			x.construct(p, v);
			++p;}}
		catch (...) {
		while (b != p) {
			--p;
			x.destroy(p);}
		x.deallocate(b, s);
		throw;}
		CPPUNIT_ASSERT(std::count(b, e, v) == s);
		while (b != e) {
		--e;
		x.destroy(e);}
		x.deallocate(b, s);
	}

	// -----
	// suite
	CPPUNIT_TEST_SUITE(TestAllocator);
	
	CPPUNIT_TEST(test0);
	CPPUNIT_TEST(test1);
	//CPPUNIT_TEST(test_one);
	//CPPUNIT_TEST(test_ten);
	
	CPPUNIT_TEST_SUITE_END();
};

// ----
// main
int main () {
	using namespace std;
	ios_base::sync_with_stdio(false);		// turn off synchronization with C I/O
	cout << "TestAllocator.c++" << endl;

	CppUnit::TextTestRunner tr;
	
	if(DEBUG) cerr << "Testing std::allocator<int>... " << endl;
	tr.addTest(TestAllocator< std::allocator<int> >::suite());
	if(DEBUG) cerr << "Testing Allocator<int, 100>... " << endl;
	tr.addTest(TestAllocator< Allocator<int, 100> >::suite());	// uncomment!

	//if(DEBUG) cerr << "Testing std::allocator<int>... " << endl;
//	tr.addTest(TestAllocator< std::allocator<double> >::suite());
	//if(DEBUG) cerr << "Testing std::allocator<int>... " << endl;
//	tr.addTest(TestAllocator< Allocator<double, 100> >::suite());	// uncomment!

	tr.run();

	cout << "Done." << endl;
	return 0;
}
