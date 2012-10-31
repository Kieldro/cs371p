#ifndef Darwin_h
#define Darwin_h

// macros
#define DEBUG true
#define BOOYAKASHA	if(DEBUG) cerr << "BOOYAKASHA!" <<  endl;

#define HOP			'H'
#define LEFT		'L'
#define RIGHT		'R'
#define INFECT		'I'
#define IF_EMPTY	'm'
#define IF_ENEMY	'n'
#define IF_WALL		'w'
#define IF_RANDOM	'r'
#define GO			'g'

#define HOPPER		0
#define FOOD		1

// --------
// includes
#include <cassert>		// assert
//#include <cstddef>		// ptrdiff_t, size_t
#include <vector>		// vector
#include <deque>
#include <functional>	// operators
#include <typeinfo>		// typeid
#include <stdexcept>
#include <string>

using std::vector;
using std::deque;
using std::cout;
using std::cerr;
using std::endl;
using std::string;

struct Instruction{
	char op;
	int line;
	Instruction(char o, int l = -1){
		op = o;
		line = l;
	}
};


class Creature;
class Grid{
	public:
		vector< vector<Creature*> > _g;
		deque<Creature> creatureStash;
		unsigned turn;
		
		Grid(int rows, int cols);
		void place(int x, char d, int r, int c);
		void runTurn();
		void simulate(int turns, int j);
		void print();
		bool valid(){
			for(int r = 1; r < nRows(); ++r)
				if(_g[r].size() != _g[r-1].size())
					return false;
				//for(int c = 0; c < nCols(); ++c)
					
			return true;
		}
		int nRows() const{return _g.size();}
		int nCols() const{return _g.size() ? _g[0].size() : 0;}
};

class Creature{
	public:
		char sigil;
		char direction;
		Grid* grid;
		int row;
		int col;
		const vector<Instruction>* program;
		int pc;
		unsigned turn;
		
		Creature(char d, int r, int c, Grid* g, const vector<Instruction>& p, char s)
		: program(&p)
		{
			direction = d;
			row = r;
			col = c;
			sigil = s;
			pc = 0;
			turn = 0;
			grid = g;
		}
		Creature(){}
		
		void execute(){
			// check if creature already took its turn
			if(turn != grid->turn){
				//BOOYAKASHA
				return;
			}
			const vector<Instruction>& p = *program;
			
			hop();
			
			
		}
		
		void hop();
		
		friend std::ostream& operator<<(std::ostream &strm, const Creature &c) {
			return strm << c.sigil;
		}
};

void Creature::hop(){
	Grid& g = *grid;
	int r = row, c = col;
	++turn;		// used up turn
	//(DEBUG) cerr << "BOOYAKASHA! " << row << col <<  endl;
	
	switch(direction){
		case 'e':
			++c;
			if(c >= g.nCols()) return;		// do nothing at wall
			break;
		case 'w':
			--c;
			if(c < 0) return;
			break;
		case 'n':
			--r;
			if(r < 0) return;
			break;
		case 's':
			++r;
			if(r >= g.nRows()) return;
			break;
		default:
			if(DEBUG) cerr << "Invalid creature to hop()" << r << c <<  endl;
			
	}
	// inbounds and space empty
	Creature*& creatureNew = g._g[r][c];
	Creature*& creatureOld = g._g[row][col];
	if(creatureNew == NULL){/*TODO MAKE A GRID OF POINTERS!*/
		if(DEBUG) cerr << "Hopping to " << r << c <<  endl;
		creatureNew = this;		// move to next space COPY ASSIGNMENT
		creatureOld = NULL;		// set to empty
		row = r;
		col = c;
	}
}

// ------
// hopper
/*
 0: hop
 1: go 0
*/
class Hopper : public Creature{
	public:
		static vector<Instruction> program;
		Hopper(char d, int r, int c, Grid* g);
};
vector<Instruction> Hopper::program;

Hopper::Hopper(char d, int r, int c, Grid* g)
: Creature(d, r, c, g, program, 'h')
{
	
}

// ----
// food
/*
 0: left
 1: go 0
*/
class Food : public Creature{
	public:
	Food(char d){sigil = 'f';}
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
	Rover(char d){sigil = 'r';}
};

// -------------------------
// Grid method definitions
Grid::Grid(int rows, int cols)
: _g(rows, vector<Creature*>(cols)), turn(0), creatureStash(0)
{
	// Hopper program initialization
	// TODO Better way?
	if(Hopper::program.size() == 0)
	{
		Hopper::program.push_back(Instruction(HOP));
		Hopper::program.push_back(Instruction(GO , 0));
		//if(DEBUG)cerr << Hopper::program.size() <<  endl;
	}
	assert(Hopper::program.size() == 2);
	
	// Food program
}

void Grid::place(int x, char d, int r, int c){
	if(x == HOPPER){
		//Hopper creature(d, r, c, this);
		creatureStash.push_back(Hopper(d, r, c, this));
		_g[r][c] = &creatureStash.back();
	}
}

void Grid::runTurn(){
	for(int r = 0; r < nRows(); ++r)
		for(int c = 0; c < nCols(); ++c){
			Creature*& creaturePtr =  _g[r][c];
			if(creaturePtr != NULL)
				creaturePtr->execute();
			//BOOYAKASHA
		}
	++turn;
}

/*
@param j print the grid every j turns.
*/
void Grid::simulate(int turns, int j){
	print();
	for(int i = 1; i <= turns; ++i){
		runTurn();
		if(i % j == 0)
			print();
	}
}

void Grid::print(){
	assert(valid());
	//cout << "\nPrinting " << nRows() << " x " << nCols() << " grid:" << endl;
	cout << "Turn = " << turn << endl;
	cout << "  ";
	for(int c = 0; c < nCols(); ++c)
		cout << c % 10;
	cout << endl;
	for(int r = 0; r < nRows(); ++r){
		cout << r % 10 << " ";
		for(int c = 0; c < nCols(); ++c){
			if(_g[r][c] == NULL)
				cout << ".";
			else
				cout << *_g[r][c];
		}
		cout << endl;
	}
	cout << endl;
}
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
