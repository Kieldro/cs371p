#include "Voting.h"

using std::cin;

int main (){
	int cases;
	cin >> cases;
	if(DEBUG) cerr << "cases: " << cases << endl;
	
	for(int i = 0; i < cases; ++i){
		Election e(cin);
		e.input();
		e.solve();
	}
	
	
	return 0;
}