#include "Cell.h"

struct A{
	int* i;
	
	A() : i(new int)
	{
		std::cout << "A() BOOM " << 1 << std::endl;
		*i = 0;
	}
	
	~A(){
		
		std::cout << "~A() BOOM " << NULL << std::endl;
		delete i;
	}
};

struct B{
	int i;
	//A a [2];
	
	allocator<A> x;
	
	B()
	//: a(x.allocate(2))
	{
		std::cout << "B() BOOM " << NULL << std::endl;
		//std::cout << "POW" << 1 << std::endl;
		
		i = 5;
	}
	
	B(const B& b){
		std::cout << "B(const B&) BOOM " << NULL << std::endl;
		i = b.i;
	}
	~B(){
		
		std::cout << "~B() BOOM " << NULL << std::endl;
		
	}
	
};

//inline
void qux(int* i){
	delete i;
	
}


int main(){
	
	int* s;
	qux(s);
	//vector<A> v(4);
	/*B b;
	b.i = 7;
	B b1(b);
	*/
	cout << "i = " << 1 << endl;
	return 0;
}