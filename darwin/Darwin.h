#ifndef Darwin_h
#define Darwin_h

// macros
#define DEBUG true

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
#include <functional>	// operators
#include <typeinfo>		// typeid
#include <stdexcept>
#include <string>

using std::vector;
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
	private:
	public:
		vector< vector<Creature> > _g;
		unsigned turn;
		
		Grid(int rows, int cols);
		void place(int x, char d, int r, int c);
		void runTurn();
		void simulate(int turns, int j);
		void print();
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
		
		Creature(){
			sigil = '.';
		}
		
		void execute(){
			// check if creature already took its turn
			if(turn != grid->turn)
				return;
			
			const vector<Instruction>& p = *program;
			
			
			
			
		}
		
		void hop(){
			Grid& g = *grid;
			int r = row, c = col;
			++turn;		// used up turn
			
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
			}
			// inbounds and space empty
			if(g._g[r][c].sigil == '.'){
				g._g[r][c] = *this;		// move to next space
				g._g[row][col] = Creature();		// set to empty
				row = r;
				col = c;
			}
		}
		friend std::ostream& operator<<(std::ostream &strm, const Creature &c) {
			return strm << c.sigil;
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



Grid::Grid(int rows, int cols)
: _g(rows, vector<Creature>(cols)), turn(0)
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
	if(x == HOPPER)
		_g[r][c] = Hopper(d, r, c, this);
}

void Grid::runTurn(){
	for(int r = 0; r < nRows(); ++r)
		for(int c = 0; c < nCols(); ++c){
			if(_g[r][c].sigil != '.')
				_g[r][c].execute();
		}
	++turn;
}

/*
@param j print the grid every j turns.
*/
void Grid::simulate(int turns, int j){
	print();
	for(int i = 1; i <= 5; ++i){
		runTurn();
		if(i % j == 0)
			print();
	}
}

void Grid::print(){
	//cout << "\nPrinting " << nRows() << " x " << nCols() << " grid:" << endl;
	cout << "Turn = " << turn << endl;
	cout << "  ";
	for(int c = 0; c < nCols(); ++c)
		cout << c % 10;
	cout << endl;
	for(int r = 0; r < nRows(); ++r){
		cout << r % 10 << " ";
		for(int c = 0; c < nCols(); ++c){
			cout << _g[r][c];}
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
