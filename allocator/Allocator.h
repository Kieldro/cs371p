// ------------------------------
// projects/allocator/Allocator.h
// Copyright (C) 2011
// Glenn P. Downing
// ------------------------------

#ifndef Allocator_h
#define Allocator_h

#define DEBUG true

// --------
// includes
#include <cassert>			// assert
#include <cstddef>			// size_t
#include <new>				// new
#include <stdexcept>		// invalid_argument
#include <cmath>			// abs

using std::cerr;
using std::endl;
using std::abs;

// ---------
// Allocator
template <typename T, std::size_t N>
class Allocator {
	public:
		// --------
		// typedefs
		typedef T					value_type;

		typedef std::size_t			size_type;
		typedef std::ptrdiff_t		difference_type;

		typedef value_type*			pointer;
		typedef const value_type*	const_pointer;

		typedef value_type& 	 	reference;
		typedef const value_type&	const_reference;
		

	public:
		// -----------
		// operator ==
		friend bool operator == (const Allocator&, const Allocator&) {
			return true;
		}
		
		// -----------
		// operator !=
		friend bool operator != (const Allocator& lhs, const Allocator& rhs) {
			return !(lhs == rhs);
		}

	private:
		// ----
		// data
		char a[N];
		
		int* intP(int i) const{
			return (int*)(a + i);
		}
		
		int& sentinel(int idx) const{
			return *((int*)(a + idx));
		}
		
		// -----
		// valid
		/**
		* O(1) in space
		* O(n) in time
		* <your documentation>
		*/
		bool valid () const
		{
			int b = 0;
			int e = 4 + abs(sentinel(b));
			
			while(b <= int(N - 4)){
				//if(DEBUG) cerr << "b: " << sentinel(b) << endl;
				//if(DEBUG) cerr << "e: " << sentinel(e) << endl;
				assert(b >= 0 && b <= int(N - 4));
				assert(e >= 0 && e <= int(N - 4));
				assert(abs(sentinel(e)) <= int(N - 8));
				assert(abs(sentinel(b)) <= int(N - 8));
				
				if(sentinel(b) != sentinel(e))
					return false;
				
				b = e + 4;
				e = b + 4 + abs(sentinel(b));	
			}
			
			return true;
		}

	public:
		// ------------
		// constructors
		/**
		* O(1) in space
		* O(1) in time
		* <your documentation>
		*/
		Allocator (){
			assert(N >= 8);
			
			sentinel(0) = N - 8;
			sentinel(N-4) = N - 8;
			/**reinterpret_cast<int*>(a) = N - 8;
			*reinterpret_cast<int*>(a + N - 4) = N - 8;
			
			if(DEBUG) cerr << "reinterpret_cast: " << std::dec << *reinterpret_cast<int*>(a) << endl;
			if(DEBUG) cerr << "reinterpret_cast: " << std::dec << *reinterpret_cast<int*>(a + N - 4) << endl;
			if(DEBUG) cerr << "reinterpret_cast: 0x" << std::hex << (int)a[0] << endl;
			*/
			
			assert(valid());
		}
		
		// Default copy, destructor, and copy assignment
		// Allocator  (const Allocator<T>&);
		// ~Allocator ();
		// Allocator& operator = (const Allocator&);
		
		//findOpen
		
		// --------
		// allocate
		/**
		* O(1) in space
		* O(n) in time
		* <your documentation>
		* after allocation there must be enough space left for a valid block
		* the smallest allowable block is sizeof(T) + (2 * sizeof(int))
		* choose the first block that fits
		*/
		pointer allocate (size_type n) {
			if(DEBUG) cerr << "allocate:" << endl;
			assert(n >= 0);
			assert(valid());
			int b = 0;
			int e = 4 + abs(sentinel(b));
			int bytesRequested = int(n * sizeof(value_type));
			
			while(b <= int(N - 4)) {
				//if(DEBUG) cerr << "b: " << sentinel(b) << endl;
				//if(DEBUG) cerr << "e: " << sentinel(e) << endl;
				assert(b >= 0 && b < int(N - 4));
				
				if(sentinel(b) >= bytesRequested) {
					int remainingSpace = sentinel(b) - (bytesRequested + 2*4);
					
					// updates old begin sentinel
					sentinel(b) = -bytesRequested;
					// creates new end sentinel
					sentinel(b + 4 + bytesRequested) = -bytesRequested;
					// set up new begin sentinel for remaining space
					sentinel(b + 2*4 + bytesRequested) = remainingSpace;
					// updates old end sentinel
					sentinel(e) = remainingSpace;
					
					assert(valid());
					return (pointer)(a + b + 4);
				}
				
				b = e + 4;
				e = 4 + abs(sentinel(b));
			}
			
			return 0;
		}

		// ---------
		// construct
		/**
		* O(1) in space
		* O(1) in time
		* <your documentation>
		*/
		void construct (pointer p, const_reference v) {
			// new (p) T(v);		// uncomment!
			
			
			assert(valid());
		}

		// ----------
		// deallocate
		/**
		* O(1) in space
		* O(1) in time
		* <your documentation>
		* after deallocation adjacent free blocks must be coalesced
		*/
		void deallocate (pointer p, size_type = 0) {
			// <your code>
			
			
			assert(valid());
		}

		// -------
		// destroy
		/**
		* O(1) in space
		* O(1) in time
		* <your documentation>
		*/
		void destroy (pointer p) {
			// p->~T();		// uncomment!
			
			
			
			assert(valid());
		}
	};
#endif // Allocator_h
