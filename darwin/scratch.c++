#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <stdexcept>

using namespace std;


struct A{
	static int i;
	
};
int A::i = 5;

int main(){
	//int(*m)(const int&, const int&) = std::max<int>;
	
	cout << A::i << endl;
	
	
	
	return 0;
}