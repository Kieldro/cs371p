// --------------------------
// projects/collatz/Collatz.h
// Copyright (C) 2012
// Glenn P. Downing
// --------------------------

#define DEBUG true

// --------
// includes
#include <cassert>  // assert
#include <iostream> // endl, istream, ostream

// ------------
// collatz_read
/**
 * reads two ints into i and j
 * @param r a  std::istream
 * @param i an int by reference
 * @param j an int by reference
 * @return true if that succeeds, false otherwise
 */
bool collatz_read (std::istream& r, int& i, int& j) {
	r >> i;
	if (!r)
		return false;
	r >> j;
	assert(i > 0);
	assert(j > 0);
	return true;
}

// ------------
// cycleLength
/**
 * @param n positive number
 * @return the cycle length of n
 */
//static 
int cycleLength(unsigned long n){
	assert(n < 1000000);
	int v = 1;
	const int CACHE_SIZE = 1000;
	int cache [CACHE_SIZE];
		
	while(n != 1){
		if(n < CACHE_SIZE and cache[n] > 0){
			;//v += cache[n] - 1;
			//break;
		}
		
		if(n & 1){		// odd
			//n = (3*n + 1) / 2;
			n = n + (n >> 1) + 1;
			++v;
		}else			// even
			n /= 2;
		++v;
	}
	
	if(n < CACHE_SIZE)
		cache[n] = v;
	return v;
}

// ------------
// collatz_eval
/**
 * @param i the beginning of the range, inclusive
 * @param j the end       of the range, inclusive
 * @return the max cycle length in the range [i, j]
 */
int collatz_eval (int i, int j) {
	assert(i > 0);
	assert(j > 0);
	
	i = std::max(i, j/2);
	if(i > j)
		std::swap(i, j);
	
	int v = 0;
	
	for(int k = i; k <= j; ++k){
		v = std::max(v, cycleLength(k));
	}
	
	assert(v > 0);
	
	return v;
}

// -------------
// collatz_print
/**
 * prints the values of i, j, and v
 * @param w a std::ostream
 * @param i the beginning of the range, inclusive
 * @param j the end       of the range, inclusive
 * @param v the max cycle length
 */
void collatz_print (std::ostream& w, int i, int j, int v) {
	assert(i > 0);
	assert(j > 0);
	assert(v > 0);
	w << i << " " << j << " " << v << std::endl;
}

// -------------
// collatz_solve
/**
 * read, eval, print loop
 * @param r a std::istream
 * @param w a std::ostream
 */
void collatz_solve (std::istream& r, std::ostream& w) {
	int i;
	int j;
	while (collatz_read(r, i, j)) {
		const int v = collatz_eval(i, j);
		collatz_print(w, i, j, v);
	}

}

// -------
// defines
#ifdef ONLINE_JUDGE
	#define NDEBUG
	// ----
	// main
	int main () {
		using namespace std;
		ios_base::sync_with_stdio(false);
		collatz_solve(cin, cout);
		return 0;
	}
#endif