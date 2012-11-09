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
	
};

int main(){
	
	B b;
	cout << "&b = " << &b << endl;
	
	
	
	return 0;
}