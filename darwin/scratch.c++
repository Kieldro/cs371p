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

vector<int> baz(){
	
	;
	
}

int main(){
	vector<int> x = baz();
	cout << "coasid = " << x.size() << endl;
	
	return 0;
}