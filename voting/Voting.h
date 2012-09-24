#define DEBUG true

// includes
#include <string>
#include <vector>
#include <cassert>  // assert
#include <ctime>
#include <iostream> // endl, istream, ostream

using std::cout;
using std::cerr;
using std::endl;
using std::istream;
using std::string;
using std::vector;

/*
CRC
ballot: store preferences: NA
election: inputs ballots, candidates : everything

*/

bool read(istream& in, int& cases, int& candidates){
	in >> cases;
	if(DEBUG) cerr << "cases: " << cases << endl;
	
	for(int i = 0; i < cases; ++i){
		Election e();
		
		in >> candidates;
		if(DEBUG) cerr << "# candidates: " << candidates << endl;
		vector<string> names(candidates);
		
		Ballot b(candidates);
		b.input(in);
		
		
		string b;
		in >> b;
		if(DEBUG) cerr << "b: " << b << endl;
	}
	
	return true;
}

class Ballot{
	private:
	vector<int> choices();
	const int numCandidiates;
	
	public:
	Ballot(const int numCan) : choices(numCan), numCandidiates(numCan){
		
	}
	
	void input(istream& in){
		for(int i = 0; i < numCandidiates; ++i)
			int c;
			in << c;
			choices[i] = atoi(c);
			if(DEBUG) cerr << "choices[i]: " << choices[i] << endl;
			
		
	}
};

class Election{
	private:
	vector<Ballot> ballots();
	
	void input(){
		;
		
	}
};