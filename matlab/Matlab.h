// ------------------------
// projects/matLab/MatLab.h
// Copyright (C) 2012
// Glenn P. Downing
// ------------------------

#ifndef MatLab_h
#define MatLab_h

// --------
// includes
#include <cassert>		// assert
#include <cstddef>		// size_t
#include <cstdlib>		// rand

// ------
// concat
/**
 * Horizontally concatinates two matrices. Given matrices X and Y
 * with R rows, with respective collumns C1 and C2, the resulting
 * matrix will be of size [R x C1+C2].
 * http://www.mathworks.com/help/matlab/ref/horzcat.html
 * @param x a matrix of size C1 x R
 * @param y a matrix of size C2 x R
 * @return the horizontally concatinated matrix of size R x C1+C2
 */
template <typename T>
T horzcat (const T& x, const T& y) {
	assert(x.size() == y.size());
	unsigned rows = x.size();
	if(rows == 0)
		return T();
	unsigned cols = x[0].size() + y[0].size();
	T z(rows, cols);
	
	for(unsigned r = 0; r < rows; ++r)
		for(unsigned c = 0; c < cols; ++c)
			if(c < x[0].size())
				z[r][c] = x[r][c];
			else
				z[r][c] = y[r][c - x[0].size()];
	
	return z;
}

/**
 * Vertically concatinates two matrices. Given matrices X and Y
 * with C collumns, with respective rows R1 and R2, the resulting
 * matrix will be of the size [R1+R2 x C].
 * http://www.mathworks.com/help/matlab/ref/vertcat.html
 * @param x a matrix of size R1 x C
 * @param y a matrix of size R2 x C
 * @return the vertically concatinated matrix of size R1+R2 x C
 */
template <typename T>
T vertcat (const T& x, const T& y) {
	if(x.size() == 0){
		assert(y.size() == 0);		// sizes must match
		return y;
	}
	assert(y.size() != 0);
	assert(x[0].size() == y[0].size());
	unsigned rows = x.size() + y.size();
	unsigned cols = x[0].size();
	T z(rows, cols);
	
	for(unsigned r = 0; r < rows; ++r)
		for(unsigned c = 0; c < cols; ++c)
			if(r < x.size())
				z[r][c] = x[r][c];
			else
				z[r][c] = y[r - x.size()][c];
	
	return z;
}

// ----
// diag
/**
 * Given a matrix, returns the diagonal as a column vector.
 * http://www.mathworks.com/help/matlab/ref/diag.html
 * @param x any matrix
 * @return the diagonal of the matrix as a column vector
 */
template <typename T>
T diag (const T& x) {
	if(x.size() == 0 or x[0].size() == 0)
		return T();
	
	int len = std::min(x.size(), x[0].size());
	T result(len, 1);
	
	for(int r = 0; r < len; ++r)
		result[r][0] = x[r][r];
	
	return result;
}

// ---
// dot
/**
 * Calculates the dot product of 2 matricies or vectors.
 * Matricies must be the same size.
 * Vectors must be trasposable to equal size.
 * http://www.mathworks.com/help/matlab/ref/dot.html
 * @param x a matrix of size m x n
 * @param y a matrix of size m x n
 * @return the dot product of the two matrices
 */
template <typename T>
T dot (const T& x, const T& y) {
	T A = x;
	T B = y;
	if(A.empty()){
		assert(B.empty());		// must both be empty
		return T();
	}
	
	// non empty
	assert(!B.empty());
	if(A.size() != B.size()){
		// they must be vectors
		assert(A.size() == 1 or B.size() == 1);
		assert(A.size() == B[0].size());
		assert(A[0].size() == B.size());
		if(A.size() == 1)
			A = transpose(A);		// form column vector
		else
			B = transpose(B);
	}
	assert(A[0].size() == B[0].size());
	
	// equal size
	if(A.size() == 1){
		// create 2 column vectors
		A = transpose(A);
		B = transpose(B);
	}
	
	const unsigned cols = A[0].size();
	T result(1, cols, 0);
	/*
	if(DEBUG)A.printMatrix();
	if(DEBUG)B.printMatrix();
	if(DEBUG)result.printMatrix();
	*/
	for(unsigned r = 0; r < A.size(); ++r)
		for(unsigned c = 0; c < cols; ++c){
			//if(DEBUG)cerr << "BOOM! r: " << r << endl;
			result[0][c] += A[r][c] * B[r][c];
		}
	
	return result;
}

// ---
// eye
/**
 * Creates an [r x c] Identity matrix. Essentially, 
 * a matrix with 1's on the diagonals and 0's everywhere else.
 * http://www.mathworks.com/help/matlab/ref/eye.html
 * @param r the number of rows
 * @param c the number of columns
 * @return an Identity matrix of size r x c
 */
template <typename T>
T eye (std::size_t r, std::size_t c) {
	T x(r, c, 0);
	int n = std::min(r, c);
	for(int i = 0; i < n; ++i)
		x[i][i] = 1;
	
	return x;
}

// ----------------
// linsolve (bonus)
/**
 * <your documentation>
 * http://www.mathworks.com/help/matlab/ref/linsolve.html
 */
template <typename T>
T linsolve (const T& x, const T& y) {
	
	
	
	
	return x;
}

// ----
// ones
/**
 * Creates an r x c matrix filled with 1's.
 * http://www.mathworks.com/help/matlab/ref/ones.html
 * @param r the number of rows
 * @param c the number of columns
 * @return a matrix filled with 1's of size r x c
 */
template <typename T>
T ones (std::size_t r, std::size_t c) {
	T x(r, c, 1);
	return x;
}

// ----
// rand
/**
 * Fills r x c matrix with random values (0, 100).
 * http://www.mathworks.com/help/matlab/ref/rand.html
 * @param r the number of rows
 * @param c the number of columns
 * @return a randomly generated r x c matrix.
 */
template <typename T>
T rand (std::size_t r, std::size_t c) {
	T x(r, c);
	
	for(unsigned r = 0; r < x.size(); ++r)
		for(unsigned c = 0; c < x[0].size(); ++c)
			x[r][c] = std::rand() % 99 + 1;
	
	return x;
}

// ---------
// transpose
/**
 * Transposes the given matrix.
 * @param x any matrix
 * @return a new matrix equal to the given matrix transposed.
 * http://www.mathworks.com/help/matlab/ref/transpose.html
 */
template <typename T>
T transpose (const T& x) {
	if(x.size() == 0 or x[0].size() == 0)
		return T();
	
	T result(x[0].size(), x.size());
	
	for(unsigned r = 0; r < x[0].size(); ++r)
		for(unsigned c = 0; c < x.size(); ++c)
			result[r][c] = x[c][r];
	
	return result;
}

// ----
// tril
/**
 * Returns the lower triangular part of a given matrix.
 * All other elements are set to 0.
 * http://www.mathworks.com/help/matlab/ref/tril.html
 * @param x any matrix
 * @return the lower triangular part of the matrix
 */
template <typename T>
T tril (const T& x) {
	T result(x);
	
	// write 0s
	for(unsigned r = 0; r < x.size(); ++r)
		for(unsigned c = 0; c < x[0].size(); ++c)
			if(r < c)
				result[r][c] = 0;
	
	return result;
}

// ----
// triu
/**
 * Returns the upper triangular part of a given matrix.
 * All other elements are set to 0.
 * @param x any matrix
 * @return the upper triangular part of the matrix
 * http://www.mathworks.com/help/matlab/ref/triu.html
 */
template <typename T>
T triu (const T& x) {
	T result(x);
	
	// write 0s
	for(unsigned r = 0; r < x.size(); ++r)
		for(unsigned c = 0; c < x[0].size(); ++c)
			if(r > c)
				result[r][c] = 0;
	
	return result;
}

// -----
// zeros
/**
 * Creates an r x c matrix filled with 0's.
 * http://www.mathworks.com/help/matlab/ref/zeros.html
 * @param r the number of rows
 * @param c the number of collumns
 * @return a matrix filled with 0's of size r x c
 */
template <typename T>
T zeros (std::size_t r, std::size_t c) {
	T x(r, c, 0);
	return x;
}

#endif // MatLab_h
