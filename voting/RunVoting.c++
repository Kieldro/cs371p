#include "Voting.h"

using std::cin;

void RunElection();

int main (){
	int cases;
	cin >> cases;
	if(DEBUG) cerr << "cases: " << cases << endl;
	if(cases == 0) return 0;

	for(int i = 0; i < cases; ++i){
		RunElection();
		if(i != cases-1) cout << endl;
	}
	
	return 0;
}

void RunElection(){
	Election e (cin);
	e.input();
	e.solve();
}