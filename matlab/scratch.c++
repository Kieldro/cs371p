//#include<string>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void baz(int* a){
	
	cout << sizeof(a) << endl;
	++a;
	
}


int main(){
	vector<int> x(2);
	
	
	auto i = 0;
	for(auto b = x.begin(); b != x.end(); ++b)
		cout << "i: " << i << endl;
	
	
	
	return 0;
}