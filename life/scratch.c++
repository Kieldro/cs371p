#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <stdexcept>

using namespace std;

struct B{
	int i;
	B(){i = 5;}
	
};
struct A{
	int* i;
	B* b;
	
	A() : i(new int)
	{
		*i = 0;
		b = new B;
	}
	
	~A(){
		
		delete i;
		delete b;
	}
};


int main(){
	A a;
	std::cout << "i = " << a.b->i << std::endl;
	
	return 0;
}