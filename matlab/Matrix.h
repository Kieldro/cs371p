// ------------------------
// projects/matlab/Matrix.h
// Copyright (C) 2012
// Glenn P. Downing
// ------------------------

#ifndef Matrix_h
#define Matrix_h

// --------
// includes
#include <cassert>	// assert
#include <cstddef>	// ptrdiff_t, size_t
#include <vector>	// vector

using std::vector;

// ------
// Matrix
template <typename T>
class Matrix {
	public:
		// --------
		// typedefs
		typedef typename std::vector< std::vector<T> >		container_type;
		typedef typename container_type::value_type			value_type;

		typedef typename container_type::size_type			size_type;
		typedef typename container_type::difference_type	difference_type;

		typedef typename container_type::pointer			pointer;
		typedef typename container_type::const_pointer		const_pointer;
		
		typedef typename container_type::reference			reference;
		typedef typename container_type::const_reference	const_reference;
		
		typedef typename container_type::iterator			iterator;
		typedef typename container_type::const_iterator		const_iterator;



	public:
		// -----------
		// operator ==
		/**
		* <your documentation>
		*/
		friend bool operator == (const Matrix& a, const Matrix& b) {
			assert(a.valid() and b.valid());
			
			if(&a == &b or (a.size() == 0 and b.size() == 0) )
				return true;
			
			if(a.size() != b.size())
				return false;
			
			if(a[0].size() != b[0].size())
				return false;
			
			for(unsigned r = 0; r < a.size(); ++r){
				for(unsigned c = 0; c < a[0].size(); ++c)
					if(a[r][c] != b[r][c])
						return false;
			}
			
			
			return true;
		}

		// -----------
		// operator !=
		/**
		* <your documentation>
		*/
		friend bool operator != (const Matrix& lhs, const Matrix& rhs) {
			return !(lhs == rhs);
		}

		// ----------
		// operator <
		/**
		* <your documentation>
		*/
		friend bool operator < (const Matrix& lhs, const Matrix& rhs) {
			// <your code>
			return false;
		}

		// -----------
		// operator <=
		/**
		* <your documentation>
		*/
		friend bool operator <= (const Matrix& lhs, const Matrix& rhs) {
			return !(rhs < lhs);
		}

		// ----------
		// operator >
		/**
		* <your documentation>
		*/
		friend bool operator > (const Matrix& lhs, const Matrix& rhs) {
			return (rhs < lhs);
		}

		// -----------
		// operator >=
		/**
		* <your documentation>
		*/
		friend bool operator >= (const Matrix& lhs, const Matrix& rhs) {
			return !(lhs < rhs);
		}

		// ----------
		// operator +
		/**
		* <your documentation>
		*/
		friend Matrix operator + (Matrix lhs, const T& rhs) {
			return lhs += rhs;
		}

		/**
		* <your documentation>
		*/
		friend Matrix operator + (Matrix lhs, const Matrix& rhs) {
			return lhs += rhs;
		}

		// ----------
		// operator -
		/**
		* <your documentation>
		*/
		friend Matrix operator - (Matrix lhs, const T& rhs) {
			return lhs -= rhs;
		}

		/**
		* <your documentation>
		*/
		friend Matrix operator - (Matrix lhs, const Matrix& rhs) {
			return lhs -= rhs;
		}

		// ----------
		// operator *
		/**
		* <your documentation>
		*/
		friend Matrix operator * (Matrix lhs, const T& rhs) {
			return lhs *= rhs;
		}

		/**
		* <your documentation>
		*/
		friend Matrix operator * (Matrix lhs, const Matrix& rhs) {
			return lhs *= rhs;
		}

	private:
		// ----
		// data
		std::vector< std::vector<T> > _m;

		// -----
		// valid
		/**
		* <your documentation>
		*/
		bool valid () const {
			if(size() == 0)
				return true;
			
			// all rows same length
			unsigned nCol = _m[0].size();
			for(unsigned r = 1; r < size(); ++r)
				if(_m[r].size() != nCol)
					return false;
			
			return true;
		}

	public:
		// ------------
		// constructors
		/**
		* <your documentation>
		*/
		Matrix (size_type r = 0, size_type c = 0, const T& v = T()):
		_m(r, vector<T>(c, v))
		{
			
			
			assert(valid());
		}
		
		
		// Canonical methods
		// Default copy, destructor, and copy assignment
		// Matrix  (const Matrix<T>&);
		// ~Matrix ();
		// Matrix& operator = (const Matrix&);

		// -----------
		// operator []
		/**
		* <your documentation>
		*/
		reference operator [] (size_type i) {
			return _m[i];
		}
		
		// -----------
		// const operator []
		/**
		* <your documentation>
		*/
		const_reference operator [] (size_type i) const {
			return (*const_cast<Matrix*>(this))[i];
		}

		// -----------
		// operator +=
		/**
		* <your documentation>
		*/
		Matrix& operator += (const T& rhs) {
			// <your code>
			return *this;
		}

		/**
		* <your documentation>
		*/
		Matrix& operator += (const Matrix& rhs) {
			// <your code>
			return *this;
		}

		// -----------
		// operator -=
		/**
		* <your documentation>
		*/
		Matrix& operator -= (const T& rhs) {
			// <your code>
			return *this;
		}

		/**
		* <your documentation>
		*/
		Matrix& operator -= (const Matrix& rhs) {
			// <your code>
			return *this;
		}

		// -----------
		// operator *=
		/**
		* <your documentation>
		*/
		Matrix& operator *= (const T& rhs) {
			// <your code>
			return *this;
		}

		/**
		* <your documentation>
		*/
		Matrix& operator *= (const Matrix& rhs) {
			// <your code>
			return *this;
		}

		// -----
		// begin
		/**
		* <your documentation>
		*/
		iterator begin () {
			return _m.begin();
		}

		/**
		* <your documentation>
		*/
		const_iterator begin () const {
			return const_cast<Matrix*>(this)->begin();
		}

		// ---
		// end
		/**
		* <your documentation>
		*/
		iterator end () {
			return _m.end();
		}

		/**
		* <your documentation>
		*/
		const_iterator end () const {
			return const_cast<Matrix*>(this)->end();
		}

		// ----
		// size
		/**
		* <your documentation>
		*/
		size_type size () const {
			return _m.size();
		}
};

#endif // Matrix_h
