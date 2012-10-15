// ------------------------
// projects/matlab/Matrix.h
// Copyright (C) 2012
// Glenn P. Downing
// ------------------------

#ifndef Matrix_h
#define Matrix_h

// --------
// includes
#include <cassert> // assert
#include <cstddef> // ptrdiff_t, size_t
#include <vector>  // vector

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
		typedef typename std::vector< std::vector<T> >	container_type;
		typedef typename container_type::value_type	  value_type;

		typedef typename container_type::size_type		size_type;
		typedef typename container_type::difference_type  difference_type;

		typedef typename container_type::pointer		pointer;
		typedef typename container_type::const_pointer    const_pointer;

		typedef typename container_type::reference		reference;
		typedef typename container_type::const_reference  const_reference;

		typedef typename container_type::iterator		 iterator;
		typedef typename container_type::const_iterator   const_iterator;

	public:
		// -----------
		// operator ==
		/**
		 *  
		 */
		friend Matrix<bool> operator == (const Matrix& A, const Matrix& B) {
			assert(A.valid() and B.valid());
			assert(A.size() == B.size());
			
			// empty case
			if(A.empty())
				return Matrix<bool>();
			
			assert(A[0].size() == B[0].size());
			
			Matrix<bool> C(A.size(), A[0].size(), true);
			
			if(&A == &B)		// same object
				return C;
			
			for(unsigned r = 0; r < A.size(); ++r){
				for(unsigned c = 0; c < A[0].size(); ++c)
					if(A[r][c] != B[r][c])
						C[r][c] = false;
			}
			
			return C;
		}

		// -----------
		// operator !=
		/**
		 * <your documentation>
		 */
		friend Matrix<bool> operator != (const Matrix& lhs, const Matrix& rhs) {
			// <your code>
			return true;
		}

		// ----------
		// operator <
		/**
		 * <your documentation>
		 */
		friend Matrix<bool> operator < (const Matrix& lhs, const Matrix& rhs) {
			// <your code>
			return false;
		}

		// -----------
		// operator <=
		/**
		 * <your documentation>
		 */
		friend Matrix<bool> operator <= (const Matrix& lhs, const Matrix& rhs) {
			// <your code>
			return true;
		}

		// ----------
		// operator >
		/**
		 * <your documentation>
		 */
		friend Matrix<bool> operator > (const Matrix& lhs, const Matrix& rhs) {
			// <your code>
			return true;
		}

		// -----------
		// operator >=
		 /**
		 * <your documentation>
		 */
		friend Matrix<bool> operator >= (const Matrix& lhs, const Matrix& rhs) {
			// <your code>
			return true;
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
			// <your code>
			return true;
		}

	public:
		// ------------
		// constructors
		/**
		* <your documentation>
		*/
		Matrix (size_type r = 0, size_type c = 0, const T& v = T()):
		_m(r, vector<T>(c, v)) {
			assert(valid());
		}

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

		// --
		// eq
		/**
		* Returns true only if both matrix have identical dimensions and values.
		*/
		bool eq (const Matrix& B) const {
			assert((*this).valid() and B.valid());
			
			if(&(*this) == &B)		// same object
				return true;
			
			if((*this).size() != B.size())
				return false;
			
			if((*this).size() == 0)		// empty matrix
				return true;
			
			if((*this)[0].size() != B[0].size())
				return false;
			
			if((*this)[0].size() == 0)	// empty rows
				return true;
			
			for(unsigned r = 0; r < (*this).size(); ++r){
				for(unsigned c = 0; c < (*this)[0].size(); ++c)
					if((*this)[r][c] != B[r][c])
						return false;
			}
			
			return true;
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
		
		// ----
		// empty
		/**
		* Returns true if any of the dimensions are 0.
		*/
		bool empty() const {return _m.size() ? !_m[0].size() : true;}
	};

#endif // Matrix_h
