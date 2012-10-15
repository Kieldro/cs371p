//#include<string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

template<typename T>
void baz(T f){
	int i = 0;
	
	cout << "i: " << f(i, 3) << endl;
}


int main(){
	int i = 0;
	not_equal_to<int> ne;
	plus<int> p;
	
	cout << "i: " << ne(i, 3) << endl;
	cout << "i: " << plus<int>()(i, 3) << endl;
	
	
	baz(p);
	
	
	return 0;
}