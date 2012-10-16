// ------------------------
// projects/matLab/MatLab.h
// Copyright (C) 2012
// Glenn P. Downing
// ------------------------

#ifndef MatLab_h
#define MatLab_h

// --------
// includes
#include <cassert> // assert
#include <cstddef> // size_t
#include <cstdlib> // rand

// ------
// concat
/**
 * <your documentation>
 * http://www.mathworks.com/help/matlab/ref/horzcat.html
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
 * <your documentation>
 * http://www.mathworks.com/help/matlab/ref/vertcat.html
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
 * <your documentation>
 * http://www.mathworks.com/help/matlab/ref/diag.html
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
 * <your documentation>
 * http://www.mathworks.com/help/matlab/ref/dot.html
 */
template <typename T>
T dot (const T& x, const T& y) {
	assert(x.size() == y.size());
	// empty case
	if(x.size() == 0)
		return T();
	assert(x[0].size() == y[0].size());
	if(x[0].size() == 0)
		return T();
	
	T result;
	
	for(unsigned i = 0; i < x.size(); ++i)
		result[0][0] += x[i][0] * y[i][0];
	
	return result;
}

// ---
// eye
/**
 * <your documentation>
 * http://www.mathworks.com/help/matlab/ref/eye.html
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
 * <your documentation>
 * http://www.mathworks.com/help/matlab/ref/ones.html
 */
template <typename T>
T ones (std::size_t r, std::size_t c) {
	T x(r, c, 1);
	return x;
}

// ----
// rand
/**
 * Fills r x c matrix with random values (0, 100) 
 * http://www.mathworks.com/help/matlab/ref/rand.html
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
 * <your documentation>
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
 * <your documentation>
 * http://www.mathworks.com/help/matlab/ref/tril.html
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
 * <your documentation>
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
 * <your documentation>
 * http://www.mathworks.com/help/matlab/ref/zeros.html
 */
template <typename T>
T zeros (std::size_t r, std::size_t c) {
	T x(r, c, 0);
	return x;
}

#endif // MatLab_h
