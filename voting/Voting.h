#define DEBUG true

// includes
#include <string>
#include <vector>
#include <deque>
//#include <queue>
#include <cassert>  // assert
#include <ctime>
#include <iterator>
#include <iostream> // endl, istream, ostream

using std::cout;
using std::cerr;
using std::endl;
using std::istream;
using std::string;
using std::vector;
using std::deque;
using std::getline;

/*
CRC
ballot: store preferences: NA
election: inputs ballots, candidates : everything

*/

// prototypes
class Election;
class Ballot;
class Candidate;

/**
Represents 1 ballot with all the remaining choices.
@param numCan is the number of candidates
*/
class Ballot{
	public:
	deque<int> choices;
	int numCandidiates;		// can't use const
	static int total;
	
	public:
	Ballot(const int numCan);
	void input(istream&);
};

// Initialize static variable
int Ballot::total = 0;

// Constructor
Ballot::Ballot(const int numCan) :
	choices(numCan), numCandidiates(numCan)
{
		++total;
}

/**
inputs a line of numbers
@param in an input stream
*/
void Ballot::input(istream& in){
	int j;
	for(int i = 0; i < numCandidiates; ++i){
		in >> choices[i];
		if(DEBUG) cerr << choices[i];
	}
	if(DEBUG) cerr << " choices" << endl;
}

class Candidate{
	public:
		string name;
		vector<Ballot> votes;
		
		Candidate();
};

// Constructor
Candidate::Candidate(): votes()
{
	
}

/**
Represents and entire election
*/
class Election{
	private:
	vector<Candidate> candidates;
	int numCan;
	istream& in;
	deque<int> lowIdx;
	
	public:
	Election(istream& in);
	void input();
	void solve();
	void redistribute();
};

Election::Election(istream& i):
	in(i), candidates(), lowIdx()
{
	Ballot::total = 0;
	if(DEBUG) cerr << "Ballot::total: " << Ballot::total << endl;
}

/**
Stores all the input into data structures.
*/
void Election::input(){
	in >> numCan;
	if(DEBUG) cerr << "# numCan: " << numCan << endl;
	candidates.resize(numCan);
	
	//if(DEBUG) cerr << "in.peek(): " << in.peek() << endl;
	in.ignore();	//
	for(int i = 0; i < numCan; ++i){
		getline(in, candidates[i].name);
		if(DEBUG) cerr << "candidate i: " << candidates[i].name << endl;
	}
	
	string str;
	while(in)
	{
		Ballot b(numCan);
		b.input(in);
		candidates[b.choices[0]-1].votes.push_back(b);
		//if(DEBUG) cerr << "i: " << i << endl;
		string s;
		getline(in, s);
		if (in.peek() == 10){		// check for blank line
			break;
		}
	}
}

/**
Finds the winner or losers.
*/
void Election::solve(){
	if(DEBUG) cerr << "Total ballots: " << Ballot::total << endl;
	
	// base cases
	if(Ballot::total == 0 || candidates.size() == 0)
		return;
	if(candidates.size() == 1){
		if(DEBUG) cout << "Winner! ";
		cout << candidates.front().name << endl;
		return;
	}
	
	while(candidates.size() > 1){
		int lowest = Ballot::total;
		for(int i = 0; i < candidates.size(); ++i){
			// win condition
			if(candidates[i].votes.size() > Ballot::total / 2){
				if(DEBUG) cout << "Winner! ";
				cout << candidates[i].name << endl;
				return;
			}
			
			// look for losers
			if(candidates[i].votes.size() < lowest){
				lowest = candidates[i].votes.size();
				lowIdx.clear();
			}
			if(candidates[i].votes.size() == lowest){
				lowIdx.push_back(i);
			}
			
			if(DEBUG) cerr << candidates[i].name << " " << candidates[i].votes.size() << endl;
		}
		
		// Remove losers
		redistribute();
	}
}

/**
Gives all the losers' ballots to other candidates.
*/
void Election::redistribute(){
	for(;lowIdx.size() != 0; lowIdx.pop_back()){
		Candidate& loser = candidates[lowIdx.back()];
		assert(&loser == &candidates[lowIdx.back()]);
		
		while(loser.votes.size() != 0){
			Ballot& b = loser.votes.back();
			assert(&b == &loser.votes.back());
			
			// move to next choice on ballot
			b.choices.pop_front();
			int nextCan = b.choices.front();
			// remove ballot from loser
			loser.votes.pop_back();
			
			// give ballot to new candidate
			candidates[nextCan].votes.push_back(b);
		}
		
		
		vector<Candidate>::iterator it = candidates.begin() + lowIdx.back();
		candidates.erase(it);
	}
	
	assert(lowIdx.size() == 0);
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
			e.solve();
		}
		
		
		return 0;
	}
#endif