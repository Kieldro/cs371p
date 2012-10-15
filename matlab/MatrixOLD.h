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
		typedef typename std::vector< vector<T> >			container_type;
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
		friend Matrix<bool> operator == (const Matrix& A, const Matrix& B) {
			assert(A.valid() and B.valid());
			
			if(&A == &B)		// same object
				return Matrix<bool>(A.size(), A[0].size(), true);
			
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
		* Returns true if matricies are not equal.
		*/
		friend Matrix<bool> operator != (const Matrix& lhs, const Matrix& rhs) {
			return !(lhs == rhs);
		}

		// ----------
		// operator <
		/**
		* <your documentation>
		*/
		friend Matrix<bool> operator < (const Matrix& lhs, const Matrix& rhs) {
			
			
			
			
			return false;
		}

		// -----------
		// operator <=
		/**
		* <your documentation>
		*/
		friend Matrix<bool> operator <= (const Matrix& lhs, const Matrix& rhs) {
			return !(rhs < lhs);
		}

		// ----------
		// operator >
		/**
		* <your documentation>
		*/
		friend Matrix<bool> operator > (const Matrix& lhs, const Matrix& rhs) {
			return (rhs < lhs);
		}

		// -----------
		// operator >=
		/**
		* <your documentation>
		*/
		friend Matrix<bool> operator >= (const Matrix& lhs, const Matrix& rhs) {
			return !(lhs < rhs);
		}

		// ----------
		// operator +
		/**
		* Adds scalar rhs to each element in matrix lhs and returns a matrix.
		*/
		friend Matrix operator + (Matrix lhs, const T& rhs) {
			return lhs += rhs;
		}

		/**
		* Adds matricies lhs and rhs together and returns the resulting matrix.
		*/
		friend Matrix operator + (Matrix lhs, const Matrix& rhs) {
			return lhs += rhs;
		}

		// ----------
		// operator -
		/**
		* Subtracts scalar rhs from each element in matrix lhs and returns the result.
		*/
		friend Matrix operator - (Matrix lhs, const T& rhs) {
			return lhs -= rhs;
		}

		/**
		* Matrix substraction, rhs from lhs and returns a matrix.
		*/
		friend Matrix operator - (Matrix lhs, const Matrix& rhs) {
			return lhs -= rhs;
		}

		// ----------
		// operator *
		/**
		* Multiplies scalar rhs to each element in matrix lhs and returns a matrix.
		*/
		friend Matrix operator * (Matrix lhs, const T& rhs) {
			return lhs *= rhs;
		}

		/**
		* Multiplies matricies lhs and rhs together and returns the resulting matrix.
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
		* Returns true if 
		*/
		bool valid () const {
			if(empty())
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
		* Initializes a Matrix with r rows and c columns with value v.
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
		* Returns a reference to the ith row.
		*/
		reference operator [] (size_type i) {
			return _m[i];
		}
		
		// -----------
		// const operator []
		/**
		* Returns a const reference to the ith row.
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
			if(empty())
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
			if(empty())
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
		* Scalar multiplication of a matrix.
		*/
		Matrix& operator *= (const T& rhs) {
			assert(valid());
			
			for(unsigned r = 0; r < size(); ++r){
				for(unsigned c = 0; c < _m[0].size(); ++c)
					_m[r][c] *= rhs;
			}
			
			return *this;
		}

		/**
		* Matrix multiplication.
		*/
		Matrix& operator *= (const Matrix& rhs) {
			assert(valid() and rhs.valid());
			if(empty() and rhs.empty())
				return *this;
			assert(!empty() and !empty());
			assert(_m[0].size() == rhs.size());
			
			int innerD = rhs.size();		// inner dimension
			Matrix C(size(), rhs[0].size(), 0);
			
			for(unsigned r = 0; r < C.size(); ++r){
				for(unsigned c = 0; c < C[0].size(); ++c){
					for(int i = 0; i < innerD; ++i)
						C[r][c] += _m[r][i] * rhs[i][c];
				}
			}
			
			*this = C;
			
			assert(valid());
			return *this;
		}
		
		/*
		Returns the product of 2 vectors.
		*/
		T dot(value_type& v0, value_type& v1 ) const{
			assert(v0.size() == v1.size());
			
			T result = 0;
			
			for(unsigned i = 0; i < v0.size(); ++i)
				result += v0[i] * v1[i];
			
			return result;
		}
		
		void printMatrix() const{
			assert(valid());
			if(empty()){
				cerr << "Matrix empty. " << this << endl;
				return;
			}
			cerr << "Printing " << size() << "x" 
				 << _m[0].size() << " matrix at: " << this << endl;
			for(unsigned r = 0; r < size(); ++r){
				for(unsigned c = 0; c < _m[0].size(); ++c){
					cerr << _m[r][c] << " ";
				}
				cerr << endl;
			}
		}

		// -----
		// begin
		/**
		* Returns an iterator to the begining of the 2d vector.
		*/
		iterator begin () {return _m.begin();}

		/**
		* Returns a constant iterator to the begining of the 2d vector.
		*/
		const_iterator begin () const {return const_cast<Matrix*>(this)->begin();}

		// ---
		// end
		/**
		* Returns an iterator to the end of the 2d vector.
		*/
		iterator end () {return _m.end();}

		/**
		* Returns a constant iterator to the end of the 2d vector.
		*/
		const_iterator end () const {return const_cast<Matrix*>(this)->end();}

		// ----
		// size
		/**
		* Returns the number of rows.
		*/
		size_type size () const {return _m.size();}
		
		// ----
		// empty
		/**
		* Returns true if any of the dimensions are 0.
		*/
		bool empty() const {return _m.size() ? !_m[0].size() : true;}
};

#endif // Matrix_h
