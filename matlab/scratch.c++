//#include<string>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void baz(int* a){
	
	cout << sizeof(a) << endl;
	++a;
	
}

template<typename I, typename T>
bool eq(I b, I e, T x){
	
	for(;b != e; ++b, ++x){
		if(*b != *x)
			return false;
	}
	
	return true;
}

template<typename I, typename T>
void f(I b, I e, const T& v){
	for(;b != e; ++b){
		*b = v;
	}
	
}

template<typename I, typename T>
T c(I b, I e, T x){
	for(;b != e; ++b, ++x){
		*x = *b;
	}
	
	return x;
}



int main(){
	vector<int> x;
	
	cout << "x: " << x[0] << endl;
	
	
	
	
	return 0;
}