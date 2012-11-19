#include <ctime>
#include <iostream>

using namespace std;

int main(){
	
	long t0 = clock();
	cout << "time0: " << t0 << endl;
	
	
	for(int i = 0; i < 444444444; ++i)
		int y = i*35;
	
	long t1 = clock();
	cout << "time: " << t1 - t0 << endl;
	
	return 0;
}