#include <cstdlib>
#include <iostream>

using namespace std;


int main(){
	
	for(int i = 0; i < 1000; ++i){
		cout << rand() % 1000000 + 1 << " " << rand() % 1000000 + 1 << endl;
		cerr << i << end;
	}
	
	return 0;
}