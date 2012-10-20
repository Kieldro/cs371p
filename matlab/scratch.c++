#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <stdexcept>

using namespace std;

struct A{
	static 
	void bar(){
		
		cout << "POW: " << endl;
		
	}
	void baz(){
		auto x = bar;
		x();
		cout << "ASDFPK: " << endl;
		
	}
	
};

int f(bool){
	
	cout << "BOOM: " << endl;
	return 0;
}

int main(){
	
	int (*foo)(bool) = f;
	cout << "auto: " << typeid(foo).name() << endl;
	foo(true);
	
	A a;
	void (*b)() = A::bar;
	b();
	a.baz();
	
	//int(*m)(const int&, const int&) = std::max<int>;
	
	return 0;
}