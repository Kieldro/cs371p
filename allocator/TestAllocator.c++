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
		pointer test = x.allocate(1);
		int data_size = sizeof(test[0]); //gets the size of the type in the allocator
		x.deallocate(test, 1);

		//calculates total number of elements to fit in 3 arrays
		int total_can_create = (100 - 3*8) / data_size;

		//figure out the number of elements given to each array
		int n0 = total_can_create / 3;
		int n1 = n0;
		int n2 = total_can_create - n0 - n1; //give n3 the remaining number

		pointer p0 = x.allocate(n0);
		pointer p1 = x.allocate(n1);
		pointer p2 = x.allocate(n2); //this should fill our allocator to almost maximum capacity
		//note - for our allocator, this actually is maximum capacity as there wouldn't be
		//enough room for another element

		try{
			x.allocate(1); // shouldn't work
			CPPUNIT_ASSERT(false);
		}
		catch(...){
			//if(DEBUG) cerr << "CAUGHT!" << endl;
			CPPUNIT_ASSERT(true);
		}

		x.construct(p0, 4);
		x.destroy(p0);

		x.deallocate(p0, n0);
		x.deallocate(p2, n2);
		x.deallocate(p1, n1);

		// should fill back up to near maximum capacity if deallocate worked.
		int maximum_capacity_elems = (100 - 8) / data_size;
		pointer full_pointer = x.allocate(maximum_capacity_elems);
		x.deallocate(full_pointer, maximum_capacity_elems); // restore to memory
	}

	void test8 () {
		A x;
		pointer test = x.allocate(1);
		int data_size = sizeof(test[0]); //gets the size of the type in the allocator
		x.deallocate(test, 1);

		//calculates total number of elements to fit in 3 arrays
		int total_can_create = (100 - 3*8) / data_size;

		//figure out the number of elements given to each array
		int n0 = total_can_create / 3;
		int n1 = n0;
		int n2 = total_can_create - n0 - n1; //give n3 the remaining number

		pointer p0 = x.allocate(n0);
		pointer p1 = x.allocate(n1);
		pointer p2 = x.allocate(n2); //this should fill our allocator to almost maximum capacity
		//note - for our allocator, this actually is maximum capacity as there wouldn't be
		//enough room for another element

		try{
			x.allocate(1); // shouldn't work
			CPPUNIT_ASSERT(false);
		}
		catch(...){
			//if(DEBUG) cerr << "CAUGHT!" << endl;
			CPPUNIT_ASSERT(true);
		}

		x.construct(p0, 4);
		x.destroy(p0);

		x.deallocate(p2, n2); //different ordering
		x.deallocate(p1, n1);
		x.deallocate(p0, n0);

		// should fill back up to near maximum capacity if deallocate worked.
		int maximum_capacity_elems = (100 - 8) / data_size;
		pointer full_pointer = x.allocate(maximum_capacity_elems);
		x.deallocate(full_pointer, maximum_capacity_elems); // restore to memory
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
	tr.addTest(TestAllocator< std::allocator<double> >::suite());
	//if(DEBUG) cerr << "Testing std::allocator<int>... " << endl;
	tr.addTest(TestAllocator< Allocator<double, 100> >::suite());	// uncomment!

	tr.run();

	cout << "Done." << endl;
	return 0;
}
