#ifndef Darwin_h
#define Darwin_h

#define DEBUG true

// --------
// includes
#include <cassert>		// assert
//#include <cstddef>		// ptrdiff_t, size_t
#include <vector>		// vector
#include <functional>	// operators
#include <typeinfo>		// typeid
#include <stdexcept>
#include <string>

using std::vector;
using std::cerr;
using std::endl;
using std::string;

// abstract class
class Creature{
	int i;
	
	virtual void move(){
		
		;
	}
	
};
#endif // Darwin_h
