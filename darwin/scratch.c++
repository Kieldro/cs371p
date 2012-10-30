#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <stdexcept>

using namespace std;


struct A{
	int i;
	int& j;
	
	A()
	:j(i)
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
	//int(*m)(const int&, const int&) = std::max<int>;
	A a;
	B b;
	
	cout << "B::i = " << B::i << endl;
	cout << "a.qux() = " << a.qux() << endl;
	cout << "b.qux() = " << b.qux() << endl;
	
	
	
	return 0;
}