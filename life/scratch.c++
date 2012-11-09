#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <stdexcept>

using namespace std;


struct A{
	int i;
	virtual int qux(){}
};

struct B : A{
	int qux(){}
	
	vector<int> v [2];
	
	B()
	:v()
	{}
};

int main(){
	
	B b;
	cout << "&b = " << &b << endl;
	
	
	cout << "b.v[0].size() = " << b.v[0].size() << endl;
	
	return 0;
}