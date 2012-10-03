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
	
	int a[] = {1, 2, 3, 4};
	int b[] = {1, 2, 3, 4};
	
	cout << boolalpha << equal(a, a+4, b) << endl;
	cout << boolalpha << eq   (a, a+4, b) << endl;
	
	vector<int> x = {1, 2, 3, 4};
	vector<int> y (3, 2);
	vector<int> w (3, 4);
	
	cout << boolalpha << equal(x.begin(), x.end(), b) << endl;
	//cout << boolalpha << equal(x.begin(), x.end(), y.begin()) << endl;
	//cout << boolalpha << eq   (a, a+4, b) << endl;
	
	f(y.begin(), y.end(), 4);
	cout << boolalpha << (count(y.begin(), y.end(), 4) == 3) << endl;
	
	c(a, a+4, y.begin());
	cout << boolalpha << "copy: " << equal(y.begin(), y.end(), b) << endl;
	
	
	
	
	return 0;
}