#define DEBUG !true

// includes
#include <cassert>  // assert
#include <ctime>
#include <vector>
#include <iostream> // endl, istream, ostream

// read
/**
 * reads two ints into i and j
 * @param r a  std::istream
 * @param i an int by reference
 * @param j an int by reference
 * @return true if that succeeds, false otherwise
 */
bool read (std::istream& r, int& i, int& j) {
	r >> i;
	if (!r)
		return false;
	r >> j;
	assert(i > 0);
	assert(j > 0);
	return true;
}

// print
/**
 * prints the values of i, j, and v
 * @param w a std::ostream
 * @param i the beginning of the range, inclusive
 * @param j the end       of the range, inclusive
 * @param v the max cycle length
 */
void print (std::ostream& w, int i, int j, int v) {
	assert(i > 0);
	assert(j > 0);
	assert(v > 0);
	w << i << " " << j << " " << v << std::endl;
}


// defines
#ifdef ONLINE_JUDGE
	#define NDEBUG
	// main
	int main () {
		//using namespace std;
		//ios_base::sync_with_stdio(false);
		solve(cin, cout);
		
		return 0;
	}
#endif