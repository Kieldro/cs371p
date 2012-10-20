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
#include <cassert>		// assert
#include <cstddef>		// ptrdiff_t, size_t
#include <vector>		// vector
#include <functional>	// operators
#include <typeinfo>		// typeid
#include <stdexcept>
#include <string>

using std::vector;
using std::cerr;
using std::endl;
using std::logic_error;
using std::string;

const static string ERROR_STR = "Sizes not equal.";

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
		 * Compares each element of two equally sized matrices to check for equality.
		 * The result of each pairwise operation is stored in a a boolean matrix
		 * of the same size in the corresponding position.
		 * @param lhs a matrix
		 * @param rhs a matrix
		 * @returns a boolean matrix that represents the results of lhs == rhs
		 */
		friend Matrix<bool> operator == (const Matrix& lhs, const Matrix& rhs) {
			return relational(lhs, rhs, std::equal_to<T>());
		}

		// -----------
		// operator !=
		/**
		 * Compares each element of two equally sized matrices to check for inequality.
		 * The result of each pairwise operation is stored in a a boolean matrix
		 * of the same size in the corresponding position.
		 * @param lhs a matrix
		 * @param rhs a matrix
		 * @returns a boolean matrix that represents the results of lhs != rhs
		 */
		friend Matrix<bool> operator != (const Matrix& lhs, const Matrix& rhs) {
			return relational(lhs, rhs, std::not_equal_to<T>());
		}

		// ----------
		// operator <
		/**
		 * Compares each element of two equally sized matrices to check if the left
		 * matrix's element is less than the right matrix's element.
		 * The result of each pairwise operation is stored in a a boolean matrix
		 * of the same size in the corresponding position.
		 * @param lhs a matrix
		 * @param rhs a matrix
		 * @returns a boolean matrix that represents the results of lhs < rhs
		 */
		friend Matrix<bool> operator < (const Matrix& lhs, const Matrix& rhs) {
			return relational(lhs, rhs, std::less<T>());
		}

		// -----------
		// operator <=
		/**
		 * Compares each element of two equally sized matrices to check if the left
		 * matrix's element is less than or equal to the right matrix's element.
		 * The result of each pairwise operation is stored in a a boolean matrix
		 * of the same size in the corresponding position.
		 * @param lhs a matrix
		 * @param rhs a matrix
		 * @returns a boolean matrix that represents the results of lhs <= rhs
		 */
		friend Matrix<bool> operator <= (const Matrix& lhs, const Matrix& rhs) {
			return relational(lhs, rhs, std::less_equal<T>());
		}

		// ----------
		// operator >
		/**
		 * Compares each element of two equally sized matrices to check if the left
		 * matrix's element is greater than the right matrix's element.
		 * The result of each pairwise operation is stored in a a boolean matrix
		 * of the same size in the corresponding position.
		 * @param lhs a matrix
		 * @param rhs a matrix
		 * @returns a boolean matrix that represents the results of lhs > rhs
		 */
		friend Matrix<bool> operator > (const Matrix& lhs, const Matrix& rhs) {
			return relational(lhs, rhs, std::greater<T>());
		}

		// -----------
		// operator >=
		 /**
		 * Compares each element of two equally sized matrices to check if the left
		 * matrix's element is greater than or equal to the right matrix's element.
		 * The result of each pairwise operation is stored in a a boolean matrix
		 * of the same size in the corresponding position.
		 * @param lhs a matrix
		 * @param rhs a matrix
		 * @returns a boolean matrix that represents the results of lhs >= rhs
		 */
		friend Matrix<bool> operator >= (const Matrix& lhs, const Matrix& rhs) {
			return relational(lhs, rhs, std::greater_equal<T>());
		}
		
		// -----------
		// relational
		/**
		 * Compares matricies element by element, 
		 * storing the result of the relational operator into the resulting matrix.
		 * @param A a matrix
		 * @param B a matrix
		 * @bf a binary function
		 * @returns a matrix with the results of each element of A and B applied to the function.
		 */
		template<typename BF>
		static Matrix<bool> relational (const Matrix& A, const Matrix& B, BF bf) {
			assert(A.valid() and B.valid());

			if(A.size() != B.size())
				throw logic_error(ERROR_STR);
			assert(A.size() == B.size());		// equal number of rows
			
			// empty case
			if(A.size() == 0){
				return Matrix<bool>();
			}
			
			if(A[0].size() != B[0].size())
				throw logic_error(ERROR_STR);
			assert(A[0].size() == B[0].size());		// equal number of columns
			
			Matrix<bool> C(A.size(), A[0].size());
			
			for(unsigned r = 0; r < A.size(); ++r){
				for(unsigned c = 0; c < A[0].size(); ++c)
					C[r][c] = bf(A[r][c], B[r][c]);
			}
			
			return C;
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
		* Returns true if the size of all columns are equal.
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
		Matrix (size_type r = 0, size_type c = 0, const T& v = T())
		//: _m(r, vector<T>(c, v))
		{
			_m = vector< vector<T> >(r, vector<T>(c, v));
			
			assert(valid());
		}

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
		reference operator [] (size_type i) {return _m[i];}

		/**
		* Returns a const reference to the ith row.
		*/
		const_reference operator [] (size_type i) const {
			return (*const_cast<Matrix*>(this))[i];
		}

		// -----------
		// operator +=
		/**
		* Adds a scalar value to each element of the matrix.
		*/
		Matrix& operator += (const T& rhs) {
			return scalar(rhs, std::plus<T>());
		}

		/**
		* Adds 2 matrices of the same size togther.
		*/
		Matrix& operator += (const Matrix& rhs) {
			return mArithmetic(rhs, std::plus<T>());
		}

		// -----------
		// operator -=
		/**
		* Decrements all elements in the matrix by scalar rhs.
		*/
		Matrix& operator -= (const T& rhs) {
			return scalar(rhs, std::minus<T>());
		}

		/**
		* Both matricies must have identical dimensions.
		* Decrements the elements of the matrix
		* by the respective element in the other matrix
		*/
		Matrix& operator -= (const Matrix& rhs) {
			return mArithmetic(rhs, std::minus<T>());
		}

		// -----------
		// operator *=
		/**
		* Scalar multiplication of a matrix.
		*/
		Matrix& operator *= (const T& rhs) {
			return scalar(rhs, std::multiplies<T>());
		}

		/**
		* Performs matrix multiplication (cross product) between an A x B matrix
		* and an B x C matrix.
		* Returns the resulting N x N matrix.
		*/
		Matrix& operator *= (const Matrix& rhs) {
			assert(valid() and rhs.valid());
			if(size() == 0){
				assert(rhs.size() == 0);
				return *this;
			}
			assert(_m[0].size() == rhs.size());
			assert(rhs.size() != 0);	// 0 inner would inply a non zero column
			
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
		
		/**
		* Common code for performing scalar operations on a matrix.
		*/
		template<typename BF>
		Matrix& scalar (const T& rhs, BF bf) {
			assert(valid());
			
			for (unsigned int r = 0; r < size(); ++r) {
				for (unsigned int c = 0; c < _m[0].size(); ++c) {
					_m[r][c] = bf(_m[r][c], rhs);
				}
			}
			
			return *this;
		}
		
		/**
		* Common code for performing arithmetic on two similarly-size
		* matrices.
		*/
		template<typename BF>
		Matrix& mArithmetic (const Matrix& rhs, BF bf) {
			assert(valid() and rhs.valid());
			// range checks
			
			if(size() != rhs.size())
				throw logic_error(ERROR_STR);
			
			if(size() == 0)
				return *this;
			assert(_m[0].size() == rhs[0].size());
			
			for(unsigned r = 0; r < size(); ++r){
				for(unsigned c = 0; c < _m[0].size(); ++c)
					_m[r][c] = bf(_m[r][c], rhs[r][c]);
			}
			
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
		
		void printMatrix() const{
			assert(valid());
			cerr << "Printing " << size() << "x" 
				 << (size() ? _m[0].size() : 0) << " matrix at: " << this << endl;
			if(empty())cerr << "[]" << endl;
			else
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
		const_iterator begin () const {
			return const_cast<Matrix*>(this)->begin();
		}

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
