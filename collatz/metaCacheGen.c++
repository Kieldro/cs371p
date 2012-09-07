using namespace std;

#include <iostream>
#include <cassert>
int cycleLength(long n){
	assert(n > 0);
	int v = 1;
	
	while(n != 1){
		assert(n > 0);
		//cerr << "n " << n << endl;
		if(n & 1){		// odd
			n = n + (n >> 1) + 1;
			++v;
		}else			// even
			n /= 2;
		++v;
	}
	
	assert(v > 0);
	return v;
}

int main(){
	int maxLen = 0;
	cerr << "sizeof long" << sizeof (long) << endl;
	for (int i = 559780; i < 1000000; ++i){
		int cLen = cycleLength(i);
		maxLen = std::max(maxLen, cLen);		
	
		cout << "cycle length of " << i << " = " << cLen << endl;
	}
	cout << "max cycle length = " << maxLen << endl;
	
	return 0;
}