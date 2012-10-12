// ------------------------
// projects/matlab/Matrix.h
// Copyright (C) 2012
// Glenn P. Downing
// ------------------------

#ifndef Matrix_h
#define Matrix_h

#define DEBUG true

// --------
// includes
#include <cassert>	// assert
#include <cstddef>	// ptrdiff_t, size_t
#include <vector>	// vector

using std::vector;
using std::cerr;
using std::endl;

// ------
// Matrix
template <typename T>
class Matrix {
	public:
		// --------
		// typedefs
		typedef typename std::vector< vector<T> >		container_type;
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
		* Returns true only if both matrix have identical dimensions and values.
		*/
		friend bool operator == (const Matrix& A, const Matrix& B) {
			assert(A.valid() and B.valid());
			
			if(&A == &B)		// same object
				return true;
			
			if(A.size() != B.size())
				return false;
			
			if(A.size() == 0)		// empty matrix
				return true;
			
			if(A[0].size() != B[0].size())
				return false;
			
			if(A[0].size() == 0)	// empty rows
				return true;
			
			for(unsigned r = 0; r < A.size(); ++r){
				for(unsigned c = 0; c < A[0].size(); ++c)
					if(A[r][c] != B[r][c])
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
		vector< vector<T> > _m;

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
			//assert(nCol != 0);
			
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
		 ~Matrix (){
		 	//if(DEBUG)cerr << "~Matrix() destructed at: " << this << endl;
		 }
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
		* Adds the scalar rhs to every element in the matrix.
		*/
		Matrix& operator += (const T& rhs) {
			assert(valid());
			
			for(unsigned r = 0; r < size(); ++r){
				for(unsigned c = 0; c < _m[0].size(); ++c)
					_m[r][c] += rhs;
			}
				
			return *this;
		}

		/**
		* Both matricies must have identical dimensions.
		* Increments the elements of the matrix
		* by the respective element in the other matrix
		*/
		Matrix& operator += (const Matrix& rhs) {
			// range checks
			assert(valid() and rhs.valid());
			assert((*this).size() == rhs.size());
			if(size() == 0)
				return *this;
			
			assert(_m[0].size() == rhs[0].size());
			
			for(unsigned r = 0; r < size(); ++r){
				for(unsigned c = 0; c < _m[0].size(); ++c)
					_m[r][c] += rhs[r][c];
			}
			
			return *this;
		}

		// -----------
		// operator -=
		/**
		* Decrements all elements in the matrix by scalar rhs.
		*/
		Matrix& operator -= (const T& rhs) {
			return *this += -rhs;
		}

		/**
		* Both matricies must have identical dimensions.
		* Decrements the elements of the matrix
		* by the respective element in the other matrix
		*/
		Matrix& operator -= (const Matrix& rhs) {
			// range checks
			assert(valid() and rhs.valid());
			assert((*this).size() == rhs.size());
			if(size() == 0)
				return *this;
			
			assert(_m[0].size() == rhs[0].size());
			
			for(unsigned r = 0; r < size(); ++r){
				for(unsigned c = 0; c < _m[0].size(); ++c)
					_m[r][c] -= rhs[r][c];
			}
			
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
