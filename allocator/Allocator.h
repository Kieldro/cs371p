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
		int* const FINAL_SENTINEL;
		
		int* intP(int i) const{
			return (int*)(a + i);
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
			const int* sBegin	= intP(0);
			const int* sEnd		= intP(4 + abs(*sBegin));
			
			while(sBegin <= FINAL_SENTINEL) {
				//if(DEBUG) cerr << "sBegin: " << *sBegin << endl;
				//if(DEBUG) cerr << "sEnd: " << *sEnd << endl;
				assert(sBegin >= intP(0) && sBegin <= FINAL_SENTINEL);
				assert(sEnd >= intP(0) && sEnd <= FINAL_SENTINEL);
				assert(abs(*sBegin) <= (int)(N - 8));
				assert(abs(*sEnd) <= (int)(N - 8));
				
				if(*sBegin != *sEnd) return false;
				
				sBegin = sEnd + 1;
				
				sEnd = intP(4 + abs(*sBegin));
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
		Allocator (): FINAL_SENTINEL(intP(N-4)) {
			assert(N >= 8);
			
			*intP(0) = N - 8;
			*FINAL_SENTINEL = N - 8;
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
			if(DEBUG) cerr << "allocate..." << endl;
			int* sBegin = intP(0);
			int* sEnd   = intP(4 + abs(*sBegin));
			
			while(sBegin <= intP(N - 4)) {
				if(DEBUG) cerr << "sizeof int: " << sizeof(int) << endl;
				//if(DEBUG) cerr << "sBegin: " << *sBegin << endl;
				//if(DEBUG) cerr << "sEnd: " << *sEnd << endl;
				assert(sBegin >= intP(0) && sBegin < intP(N - 4));
				
				if(*sBegin >= (int)(n * sizeof(value_type))) {
					//int update_this_sentinel = *sBegin;
					//int new_remaining_size = update_this_sentinel - 8 - n;
					//set up new begin node for remingin space
					//*(sBegin) = -n; //updates old begin node to negative n
					//*(sBegin + 1) = ;//set up new end node for consumed space
					
					assert(valid());
					return (pointer)(sBegin+1);
				}
				
				sBegin = sEnd + 1;
				
				sEnd = intP(4 + abs(*sBegin));
			}
			
			return (pointer)0;
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
