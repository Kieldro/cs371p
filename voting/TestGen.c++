#include <iostream>
#include <random>

using namespace std;

int main(){
	
	int cases = 10;
	const int LINES = 1000;
	
	default_random_engine gen();
	cerr << gen.min() << endl;
	
	return 0;
}