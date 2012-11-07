#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <stdexcept>

using namespace std;

struct B{
	int x;
	B(){cout << "B() " << endl;}
	B(const B& b){
		cout << "B(B) " << endl;
		x = b.x;
	}
	
};

struct A{
	static B s;
	
};

B qux(){
	B b;
	cout << "b " << &b << endl;
	b.x = 1;
	return b;
}

B A::s = qux();


int main(){
	cout << "s " << &A::s << endl;
	cout << "s " << A::s.x << endl;
	
	return 0;
}