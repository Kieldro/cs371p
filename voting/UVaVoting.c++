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
	void print();
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
	int token;
	for(int i = 0; i < numCandidiates; ++i){
		in >> token;
		//if(token == 0) return;
		//if(DEBUG) cerr << "token " << token << endl;
		assert(token <= 20);
		assert(token >= 1);
		if(DEBUG) cerr << token << " ";
		choices[i] = token;
	}
	if(DEBUG) cerr << " choices" << endl;
}

void Ballot::print()
{
	//cerr << "printing all ballots for " << name << endl;
	
	for(int i = 0; i < choices.size(); ++i){
		cerr << choices[i] << " ";
	}
	cerr << endl;
}

class Candidate{
	public:
		string name;
		vector<Ballot> votes;
		
		Candidate();
		void print();
};

// Constructor
Candidate::Candidate(): votes()
{
	
}

void Candidate::print()
{
	
	cerr << "printing all " << votes.size() << " ballots for " << name << endl;
	
	for(int i = 0; i < votes.size(); ++i){
		votes[i].print();
		//cerr << endl;
	}
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
	int nContenders;
	
	public:
	Election(istream& in);
	void input();
	void solve();
	void redistribute();
};

Election::Election(istream& i):
	in(i), candidates(), lowIdx(), nContenders(0)
{
	Ballot::total = 0;
}

/**
Stores all the input into data structures.
*/
void Election::input(){
	in >> numCan;
	if(DEBUG) cerr << "# numCan: " << numCan << endl;
	candidates.resize(numCan);
	nContenders = numCan;
	
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
		//if(DEBUG) cerr << "in.peek(): " << in.peek() << endl;
		if (in.peek() == 10 or in.peek() == -1){		// check for blank line
			break;
		}
	}
	if(DEBUG) cerr << "Ballot::total: " << Ballot::total << endl;
}

/**
Finds the winner or losers.
*/
void Election::solve(){
	if(DEBUG) cerr << "Solving..." << endl;

	// base cases
	if(Ballot::total == 0 || candidates.size() == 0)
		return;
	if(candidates.size() == 1){
		if(DEBUG) cout << "Winner! ";
		cout << candidates.front().name << endl;
		return;
	}
	
	while(true or candidates.size() > 1){
		int lowest = Ballot::total;
		for(int i = 0; i < candidates.size(); ++i){
			// win condition
			if(candidates[i].votes.size() > Ballot::total / 2){// or lowidx.size){
				if(DEBUG) cout << "Winner! ";
				cout << candidates[i].name << endl;
				return;
			}
			
			// look for losers
			if(candidates[i].votes.size() != 0 and candidates[i].votes.size() < lowest){
				lowest = candidates[i].votes.size();
			}
			if(candidates[i].votes.size() == lowest){
				lowIdx.push_back(i);
			}
			
			if(DEBUG) cerr << candidates[i].name << " " << candidates[i].votes.size() << endl;
		}
		
		if(DEBUG) cerr << "lowest: " << lowest << endl;
		//if(DEBUG) cerr << "Total ballots: " << Ballot::total << endl;
		// Remove losers
		redistribute();
	}
}

/**
Gives all the losers' ballots to other candidates.
*/
void Election::redistribute(){
	if(DEBUG) cerr << "redistribute..." << endl;
	if(DEBUG) cerr << "lowIdx.size " << lowIdx.size() << endl;
	
	for(;lowIdx.size() != 0; lowIdx.pop_back()){
		Candidate& loser = candidates[lowIdx.back()];
		assert(&loser == &candidates[lowIdx.back()]);
		if(DEBUG) cerr << "can: " << loser.name << endl;
		if(DEBUG) cerr << "lowidx: " << lowIdx.back() << endl;
		
		if(DEBUG) cerr << "candidates.size: " << candidates.size() << endl;
		//if(DEBUG) candidates.at(12).print();

		while(loser.votes.size() != 0){
			//if(DEBUG) cerr << "size! " <<  candidates[lowIdx.back()].votes.size() <<endl;
			Ballot& b = loser.votes.back();
			assert(&b == &loser.votes.back());
			
			// move to next choice on ballot
			int nextCan;
			do{
				b.choices.pop_front();
				nextCan = b.choices.front() - 1;
			}while(candidates[nextCan].votes.size() == 0);
			
			if(DEBUG) cerr << "candidates.size: " << candidates.size() << endl;
			if(DEBUG) cerr << "nextCan: " << nextCan << endl;
			if(DEBUG) loser.print();
			if(DEBUG) cerr << "BOOYAKASHA!" << candidates[nextCan].votes.size() <<endl;

			// give ballot to new candidate
			candidates[nextCan].votes.push_back(b);
				
			// remove ballot from loser
			loser.votes.pop_back();
		}
		/*
		vector<Candidate>::iterator it = candidates.begin() + lowIdx.back();
		candidates.erase(it);*/
	}

	//lowIdx.clear();
	assert(lowIdx.size() == 0);
}

// -------
// defines
#ifdef ONLINE_JUDGE
	#define NDEBUG		// turns off assertions
	using std::cin;

	void RunElection();

	int main (){
		int cases;
		cin >> cases;
		if(DEBUG) cerr << "cases: " << cases << endl;
		
		for(int i = 0; i < cases; ++i){
			RunElection();
		}
		
		return 0;
	}

	void RunElection(){
		Election e (cin);
		e.input();
		e.solve();
	}
#endif