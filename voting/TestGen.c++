#include <iostream>

//using namespace std;
using std::cout;
using std::endl;


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
	
	return 0;
}

void election(){
	int numCan = rand() % 20 + 1;
	cout << numCan << endl;
	++totalLines;
	
	for(int j = 0; j < numCan; ++j){
		cout << "Candidate" << j << endl;
		++totalLines;
	}
	
	int numBallots = rand() % (LINES / cases * 2) + 1;
	for(int k = 0; k < numBallots; ++k){
		ballot(numCan);
	}
}

void ballot(int numCan){
	
	for(int i = 0; i < numCan; ++i){
		
		cout << i << " ";
	}
	cout << endl;
	++totalLines;
}

