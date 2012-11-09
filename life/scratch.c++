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

int main(){
	
	for(int i = 0; i < 3; ++i){
		A a(i);
		cout << "&a = " << &a << endl;
	}
	
	
	
	return 0;
}