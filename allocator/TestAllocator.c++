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
		//pointer p = 
		x.allocate(6);
		//if(DEBUG) cerr << endl << "p " << p << endl;
	}
	
	// -----
	// test2
	void test2 () {
		A x;
		
		try{
			x.allocate(100000000);
		}
		catch(...){
			//if(DEBUG) cerr << "CAUGHT!" << endl;
			CPPUNIT_ASSERT(true);
		}
	}
	
	// -----
	// test3
	void test3 () {
		A x;
		value_type v = 3;
		
		pointer p = x.allocate(5);
		x.construct(p, v);
		
		
		CPPUNIT_ASSERT(*p == v);
	}
	
	// -----
	// test4
	void test4 () {
		A x;
		value_type v = 7;
		int nElements = 5;
		
		pointer p = x.allocate(nElements);
		
		for(int i = 0; i < nElements; ++i, ++p){
			x.construct(p, v);
			CPPUNIT_ASSERT(*p == v);
		}
	}
	
	// -----
	// test5
	void test5 () {
		A x;
		int nElements = 5;
		
		pointer p = x.allocate(nElements);
		x.construct(p, 11);
		x.destroy(p);
		
		x.deallocate(p, nElements);
	}
	
	// -----
	// test6
	void test6 () {
		A x;
		int nElements = 4;
		
		pointer p0 = x.allocate(nElements);
		pointer p1 = x.allocate(nElements);
		
		x.deallocate(p0, nElements);
		x.deallocate(p1, nElements);
		x.allocate(2 * nElements);
		p0++;p1++;
		
	}

	void test7 () {
		A x;

		pointer p0 = x.allocate(7);
		pointer p1 = x.allocate(7);
		pointer p2 = x.allocate(5); //this should fill our allocator to maximum capacity

		try{
			pointer bad = x.allocate(1); // shouldn't work
			CPPUNIT_ASSERT(false);
		}
		catch(...){
			//if(DEBUG) cerr << "CAUGHT!" << endl;
			CPPUNIT_ASSERT(true);
		}

		x.construct(p0, 4);
		x.destroy(p0);

		x.deallocate(p0, 7);
		x.deallocate(p2, 7);
		x.deallocate(p1, 5);

		// should fill back up to maximum capacity if deallocate worked.
		pointer full_pointer = x.allocate(23);
		x.deallocate(full_pointer, 23); // restore to memory
	}

	void test8 () {
		A x;

		pointer p0 = x.allocate(5);
		pointer p1 = x.allocate(7);
		pointer p2 = x.allocate(7); //this should fill our allocator to maximum capacity

		try{
			pointer bad = x.allocate(1); // shouldn't work
			CPPUNIT_ASSERT(false);
		}
		catch(...){
			//if(DEBUG) cerr << "CAUGHT!" << endl;
			CPPUNIT_ASSERT(true);
		}

		x.construct(p0, 4);
		x.destroy(p0);

		x.deallocate(p0, 5); //different ordering
		x.deallocate(p1, 7);
		x.deallocate(p2, 7);

		// should fill back up to almost maximum capacity if deallocate worked.
		pointer full_pointer = x.allocate(22);
		x.deallocate(full_pointer, 22); // restore to memory
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
		CPPUNIT_ASSERT(x == A());		// operator == test
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
				++p;
			}
		}catch (...) {
			while (b != p) {
				--p;
				x.destroy(p);
			}
			x.deallocate(b, s);
			throw;
		}
		CPPUNIT_ASSERT(std::count(b, e, v) == s);
		while (b != e) {
			--e;
			x.destroy(e);
		}
		x.deallocate(b, s);
	}

	// -----
	// suite
	CPPUNIT_TEST_SUITE(TestAllocator);
	
	CPPUNIT_TEST(test0);
	CPPUNIT_TEST(test1);
	CPPUNIT_TEST(test2);
	CPPUNIT_TEST(test3);
	CPPUNIT_TEST(test4);
	CPPUNIT_TEST(test5);
	CPPUNIT_TEST(test6);
	CPPUNIT_TEST(test7);
	CPPUNIT_TEST(test8);
	CPPUNIT_TEST(test_one);
	CPPUNIT_TEST(test_ten);

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
