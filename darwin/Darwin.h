#ifndef Darwin_h
#define Darwin_h

#define DEBUG true

// --------
// includes
#include <cassert>		// assert
//#include <cstddef>		// ptrdiff_t, size_t
#include <vector>		// vector
#include <functional>	// operators
#include <typeinfo>		// typeid
#include <stdexcept>
#include <string>

using std::vector;
using std::cout;
using std::cerr;
using std::endl;
using std::string;

class Creature{
	friend std::ostream& operator<<(std::ostream &strm, const Creature &c) {
		return strm << c.sigil;
	}
	private:
		int i;
	
	public:
		char sigil;
		char direction;
		unsigned turn;
		vector<int> program;
		
		Creature()
		: i(5), sigil('.'), direction('-'), program(0)
		{
			
		}
		
		void execute(){
			
			
			
		}
		
		void test(){
			
			if(DEBUG)cerr << "BOOM!: " << *this << endl;
			
		}
};

class Grid{
	private:
		vector< vector<Creature> > _g;
	
	public:
		unsigned turn;
		
	Grid(int rows, int cols)
	: _g(rows, vector<Creature>(cols)), turn(0)
	{
		
		
	}
	
	void place(const Creature &x, int r, int c){
		_g[r][c] = x;
	}
	
	void runTurn(){
		for(int r = 0; r < nRows(); ++r)
			for(int c = 0; c < nCols() and _g[r][c].sigil != '.'; ++c){
				_g[r][c].turn = turn;		// using up turn
				hop(r, c);
			}
		
		++turn;
	}
	
	void hop(int r, int c){
		Creature& creature = _g[r][c];
		//creature.turn = turn;		// used up turn
		
		switch(creature.direction){
			case 'e':
				if(++c >= nCols()) return;		// do nothing at wall
				break;
			case 'w':
				if(--c < 0) return;
				break;
			case 'n':
				if(--r < 0) return;
				break;
			case 's':
				if(++r >= nRows()) return;
		}
		
		// inbounds and space empty
		if(_g[r][c].sigil == '.'){
			_g[r][c] = creature;		// move to next space
			creature = Creature();		// set to empty
		}
		
		
	}
	
	void print(){
		//cout << "\nPrinting " << nRows() << " x " << nCols() << " grid:" << endl;
		
		cout << "Turn = " << turn << endl;
		
		
		cout << "  ";
		for(int c = 0; c < nCols(); ++c)
			cout << c % 10;
		cout << endl;
		for(int r = 0; r < nRows(); ++r){
			cout << r % 10 << " ";
			for(int c = 0; c < nCols(); ++c){
				cout <<  _g[r][c];}
			cout << endl;
		}
		
		cout << endl;
	}
	
	int nRows() const{
		return _g.size();
	}
	
	int nCols() const{
		return _g.size() ? _g[0].size() : 0;
	}
};

// ------
// hopper
/*
 0: hop
 1: go 0
*/
class Hopper : public Creature{
	
	public:
	Hopper(char d)
	//: sigil('H')
	{
		sigil = 'h';
		direction = d;
		turn = 0;
	}
};

// ----
// food
/*
 0: left
 1: go 0
*/
class Food : public Creature{
	public:
	Food(){sigil = 'f';}
};

// ----
// trap
/*
 0: if_enemy 3
 1: left
 2: go 0
 3: infect
 4: go 0
*/
class Trap : public Creature{
	public:
	Trap(){sigil = 't';}
};

// -----
// rover
/*
 0: if_enemy 9
 1: if_empty 7
 2: if_random 5
 3: left
 4: go 0
 5: right
 6: go 0
 7: hop
 8: go 0
 9: infect
10: go 0
*/
class Rover : public Creature{
	public:
	Rover(){sigil = 'r';}
};

/*
hop 	The creature moves forward as long as the square it is facing is empty. If moving forward would cause the creature to land on top of another creature or a wall, the hop instruction does nothing.
left 	The creature turns left 90 degrees to face in a new direction.
right 	The creature turns right 90 degrees.
infect 	If the square immediately in front of this creature is occupied by a creature of a different species (an "enemy") that creature is infected to become the same as the infecting species. When a creature is infected, it keeps its position and orientation, but changes its internal species indicator and begins executing the same program as the infecting creature, starting at step 0.
ifempty n 	If the square in front of the creature is unoccupied (by a wall or another creature), update the next instruction field in the creature so that the program continues from step n. If that square is occupied, go on with the next instruction in sequence.
ifwall n 	If the creature is facing a wall, jump to step n; otherwise, go on with the next instruction in sequence.
ifsame n 	If the square the creature is facing is occupied by a creature of the same species, jump to step n; otherwise, go on with the next instruction.
ifenemy n 	If the square the creature is facing is occupied by a creature of an enemy species, jump to step n; otherwise, go on with the next instruction.
ifrandom n 	In order to make it possible to write some creatures capable of exercising what might be called the rudiments of "free will", this instruction jumps to step n half the time and continues with the next instruction the other half of the time.
go n 	This instruction always jumps to step n, independent of any condition.
*/

#endif // Darwin_h
