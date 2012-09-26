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

// prototypes
class Election;
class Ballot;

class Ballot{
	private:
	vector<int> choices;
	const int numCandidiates;
	
	public:
	Ballot(const int numCan);
	void input(istream&);
};

// Constructor
Ballot::Ballot(const int numCan) :
	choices(numCan), numCandidiates(numCan){
		
}


// inputs a line of numbers
void Ballot::input(istream& in){
	for(int i = 0; i < numCandidiates; ++i){
		in >> choices[i];
		if(DEBUG) cerr << "choices[i]: " << choices[i] << endl;
	}
	
}

class Election{
	private:
	vector<Ballot> ballots();
	vector<string> candidates;
	int numCan;
	istream& in;
	
	public:
	Election(istream& in);
	void input();
};

Election::Election(istream& i):
	in(i), candidates(){
	if(DEBUG) cerr << "size " << candidates.size() << endl;
}

void Election::input(){
	in >> numCan;
	if(DEBUG) cerr << "# numCan: " << numCan << endl;
	candidates.resize(numCan);
	
	for(int i = 0; i < numCan; ++i){
		in >> candidates[i];
		if(DEBUG) cerr << "candidate i: " << candidates[i] << endl;
	}
	
	string str;
	while(std::getLine(in, str) && in){
		Ballot b(str);
		ballots.push_back(b);
	}
		
}

// -------
// defines
#ifdef ONLINE_JUDGE
	#define NDEBUG
	using std::cin;

	int main (){
		int cases;
		cin >> cases;
		if(DEBUG) cerr << "cases: " << cases << endl;
		
		for(int i = 0; i < cases; ++i){
			Election e(cin);
			e.input();
		}
		return 0;
	}
#endif