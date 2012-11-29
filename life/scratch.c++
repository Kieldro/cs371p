#include <ctime>
#include <iostream>

using namespace std;

struct Parent {
	Parent() { cout << "Parent()" << endl; }
	Parent(int) { cout << "Parent(int)" << endl; }
	
};


struct Child : Parent {
	Child() { cout << "Child()" << endl; }
	Child(int) { cout << "Child(int)" << endl; }
	
};

int main(){
	
	Parent p;
	Parent(5);
	Child c(7);
	
	return 0;
}