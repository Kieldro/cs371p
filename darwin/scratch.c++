#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <stdexcept>

using namespace std;


struct A{
	int i;
	
	A(int x){
		i = x;
	}
	A()
	{
		i = 7;
	}
	
	int qux(){return i;}
};

struct B : A{
	static int i;
	
};
int B::i = 5;
int z = 2;

int baz(int& x = z){
	return x;
}

int main(){
	int a = 11;
	cout << "coasid = " << baz(a) << endl;
	
	return 0;
}