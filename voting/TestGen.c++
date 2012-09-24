#include <iostream>
#include <list>
#include <iterator>
#include <cassert>

using std::cout;
using std::endl;
using std::list;
using std::advance;

void ballot(int);
void election();


const int cases = 10;
const int LINES = 1000;
int totalLines = 0;

int main(){
	cout << cases << endl;
	totalLines += 1;
	
	for(int i = 0; i < cases; ++i){
		cout << endl;
		++totalLines;
		election();
	}
	
	assert(totalLines >= LINES);
	return 0;
}

void election(){
	int numCan = rand() % 20 + 1;
	cout << numCan << endl;
	++totalLines;
	
	for(int j = 1; j <= numCan; ++j){
		cout << "Candidate" << j << endl;
		++totalLines;
	}
	
	int numBallots = rand() % (LINES / cases * 2) + 1;
	for(int k = 0; k < numBallots; ++k){
		ballot(numCan);
	}
}

void ballot(int numCan){
	list<int> choices;
	for(int i = 1; i <= numCan; ++i){
		choices.push_back(i);
	}
	
	for(int i = 0; i < numCan; ++i){
		auto a = choices.begin();
		advance(a, rand() % choices.size());
		cout << *a << " ";
		auto it = choices.erase(a);
	}
	cout << endl;
	++totalLines;
}