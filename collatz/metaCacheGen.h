using namespace std;

#include <iostream>

int cycleLength(int n){
	int v = 1;
	
	while(n != 1){
		if(n & 1){		// odd
			n = n + (n >> 1) + 1;
			++v;
		}else			// even
			n /= 2;
		++v;
	}
	
	return v;
}
int main(){
	int maxLen = 0;
	
	for (int i = 0; i < 1000; ++i){
		int cLen = cycleLength(i);
		maxLen = std::max(maxLen, cLen);		
	
		cout << "cycle length of " << i << " = " << cLen << endl;
	}
	
	
	return 0;
}