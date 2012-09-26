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
using std::getline;

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
	int numCandidiates;		// can't use const
	
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
	int j;
	for(int i = 0; i < numCandidiates; ++i){
		in >> choices[i];
		if(DEBUG) cerr << "choices i " << choices[i] << endl;
	}
}

class Election{
	private:
	vector<Ballot> ballots;
	vector<string> candidates;
	int numCan;
	istream& in;
	
	public:
	Election(istream& in);
	void input();
};

Election::Election(istream& i):
	in(i), candidates(), ballots(){
	if(DEBUG) cerr << "size " << candidates.size() << endl;
}

void Election::input(){
	in >> numCan;
	if(DEBUG) cerr << "# numCan: " << numCan << endl;
	candidates.resize(numCan);
	
	//if(DEBUG) cerr << "in.peek(): " << in.peek() << endl;
	in.ignore();	//
	for(int i = 0; i < numCan; ++i){
		getline(in, candidates[i]);
		if(DEBUG) cerr << "candidate i: " << candidates[i] << endl;
	}
	
	string str;
	while(in)
	{
		Ballot b(numCan);
		b.input(in);
		ballots.push_back(b);
		//if(DEBUG) cerr << "i: " << i << endl;
		string s;
		getline(in, s);
		if (in.peek() == 10){		// check for blank line
			break;
		}
		//if(DEBUG) cerr << "in.peek(): " << in.peek() << endl;
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
		if(DEBUG) cerr << "BOOYAKASHAcases: " << cases << endl;
		
		for(int i = 0; i < cases; ++i){
			Election e(cin);
			e.input();
		}
		return 0;
	}
#endif