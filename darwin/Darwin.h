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

#define HOPPER		'h'
#define FOOD		'f'
#define TRAP		't'
#define ROVER		'r'
#define BEST		'b'

// --------
// includes
#include <cassert>		// assert
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
using std::logic_error;

struct Instruction{
	char op;
	int line;
	Instruction(char o, int l = -1){
		op = o;
		line = l;
	}
	Instruction(){
		op = 'a';
		line = 0;
	}
};

class Creature;
class Grid{
	public:
		vector< vector<Creature*> > _g;
		deque<Creature> creatureStash;
		unsigned turn;
		
		Grid(int rows, int cols);
		void place(char x, char d, int r, int c);
		void runTurn();
		void print();
		void simulate(int turns, int j);
		bool valid();
		int nRows() const{return _g.size();}
		int nCols() const{return _g.size() ? _g[0].size() : 0;}
};

class Creature{
	public:
		char sigil;
		char direction;
		int row;
		int col;
		const vector<Instruction>* program;
		int pc;
		unsigned turn;
		Grid* grid;
		static vector<Instruction> pHopper;
		static vector<Instruction> pFood;
		static vector<Instruction> pTrap;
		static vector<Instruction> pRover;
		static vector<Instruction> pBest;
		
		Creature(char d, int r, int c, Grid* g, char s);
		Creature(){}
		void execute();
		void hop();
		void left();
		void right();
		void infect();
		void ifEnemy();
		void ifEmpty();
		void ifRandom();
		void ifWall();
		bool nextCell(int& r, int& c);
		friend std::ostream& operator<<(std::ostream &strm, const Creature &c) {
			return strm << c.sigil;
		}
};
vector<Instruction> Creature::pHopper(2);
vector<Instruction> Creature::pFood(2);
vector<Instruction> Creature::pTrap(5);
vector<Instruction> Creature::pRover(11);
vector<Instruction> Creature::pBest(11);

Creature::Creature(char d, int r, int c, Grid* g, char s){
	if(d != 'n' and d != 'e' and d != 's' and d != 'w')
		throw logic_error("Invalid direction: " + d);
	direction = d;
	row = r;
	col = c;
	sigil = s;
	grid = g;
	pc = 0;
	turn = 0;
	
	switch(sigil){
		case HOPPER:
			program = &pHopper;
			//if(DEBUG) cerr << "size() " << program->size() <<  endl;
			break;
		case FOOD:
			program = &pFood;
			break;
		case TRAP:
			program = &pTrap;
			break;
		case ROVER:
			program = &pRover;
			break;
		case BEST:
			program = &pBest;
			break;
		default:
			throw logic_error("Invalid creature type: " + sigil);
	}
}

void Creature::execute(){
	const vector<Instruction>& p = *program;
	
	// check if creature already took its turn
	while(turn == grid->turn){/*
		if(DEBUG) cerr << "*creature: " << sigil << endl;
		if(DEBUG) cerr << "pc: " << pc << endl;
		if(DEBUG) cerr << "instruction: " << p[pc].op << endl;
		if(DEBUG) cerr << "target line: " << p[pc].line << endl;*/
		
		switch(p[pc].op){
			case HOP:
				hop();
				break;
			case LEFT:
				left();
				break;
			case RIGHT:
				right();
				break;
			case INFECT:
				infect();
				break;
			case IF_ENEMY:
				ifEnemy();
				break;
			case IF_EMPTY:
				ifEmpty();
				break;
			case IF_RANDOM:
				ifRandom();
				break;
			case IF_WALL:
				ifWall();
				break;
			case GO:
				pc = p[pc].line;		// jump to line
				break;
			default:
				;
		}
	}
}

void Creature::hop(){
	Grid& g = *grid;
	int r = row, c = col;
	++pc;
	++turn;		// used up turn
	
	if(!nextCell(r, c))
		return;		// out of bounds, do nothing
	
	// inbounds and space empty
	Creature*& creatureNew = g._g[r][c];
	Creature*& creatureOld = g._g[row][col];
	if(creatureNew == NULL){
		if(DEBUG) cerr << "Hopping to " << r << c <<  endl;
		creatureNew = this;		// move to next space
		creatureOld = NULL;		// set to empty
		row = r;
		col = c;
	}
}

void Creature::left(){
	++pc;
	++turn;		// used up turn
	switch(direction){
		case 'e':
			direction = 'n';
			break;
		case 'w':
			direction = 's';
			break;
		case 'n':
			direction = 'w';
			break;
		case 's':
			direction = 'e';
			break;
		default:
			;//if(DEBUG) cerr << "Invalid creature to hop()" << r << c <<  endl;
	}
}

void Creature::right(){
	++pc;
	++turn;		// used up turn
	switch(direction){
		case 'e':
			direction = 's';
			break;
		case 'w':
			direction = 'n';
			break;
		case 'n':
			direction = 'e';
			break;
		case 's':
			direction = 'w';
			break;
		default:
			;//if(DEBUG) cerr << "Invalid creature to hop()" << r << c <<  endl;
	}
}

void Creature::infect(){
	Grid& g = *grid;
	int r = row, c = col;
	++pc;
	++turn;		// used up turn
	
	if(!nextCell(r, c))
		return;
	
	// inbounds
	Creature*& creatureNew = g._g[r][c];
	if(creatureNew != NULL and creatureNew->sigil != sigil){
		if(DEBUG) cerr << "Infecting creature at " << r << c <<  endl;
		creatureNew->sigil = sigil;
		creatureNew->program = program;
		creatureNew->pc = 0;
	}
}

void Creature::ifEnemy(){
	Grid& g = *grid;
	const vector<Instruction>& p = *program;
	int r = row, c = col;
	
	if(!nextCell(r, c)){
		++pc;
		return;
	}
	
	// inbounds
	Creature*& creatureNew = g._g[r][c];
	if(creatureNew != NULL and creatureNew->sigil != sigil){
		pc = p[pc].line;
	}else
		++pc;
}

void Creature::ifEmpty(){
	Grid& g = *grid;
	const vector<Instruction>& p = *program;
	int r = row, c = col;
	
	if(!nextCell(r, c)){
		++pc;
		return;
	}
	
	// inbounds
	Creature*& creatureNew = g._g[r][c];
	if(creatureNew == NULL){
		pc = p[pc].line;
	}else
		++pc;
}

void Creature::ifWall(){
	Grid& g = *grid;
	const vector<Instruction>& p = *program;
	int r = row, c = col;
	
	if(!nextCell(r, c)){
		pc = p[pc].line;
	}else
		++pc;
}

void Creature::ifRandom(){
	Grid& g = *grid;
	const vector<Instruction>& p = *program;
	int r = row, c = col;
	
	if(rand()){
		pc = p[pc].line;
	}else
		++pc;
}

/*
@return true if in range, false if out of bounds.
*/
bool Creature::nextCell(int& r, int& c){
	Grid& g = *grid;
	switch(direction){
		case 'e':
			++c;
			if(c >= g.nCols()) return false;		// do nothing at wall
			break;
		case 'w':
			--c;
			if(c < 0) return false;
			break;
		case 'n':
			--r;
			if(r < 0) return false;
			break;
		case 's':
			++r;
			if(r >= g.nRows()) return false;
			break;
		default:
			throw logic_error("Invalid direction: " + direction);
	}
	
	return true;
}


// -------------------------
// Grid method definitions
Grid::Grid(int rows, int cols)
: _g(rows, vector<Creature*>(cols)), turn(0), creatureStash(0)
{
	// static program initializations
	// TODO Better way?
	if(Creature::pHopper[0].op == 'a')
	{
		Creature::pHopper[0] = Instruction(HOP);
		Creature::pHopper[1] = Instruction(GO, 0);
		// ----
		// food
		/*
		0: left
		1: go 0
		*/
		Creature::pFood[0] = Instruction(LEFT);
		Creature::pFood[1] = Instruction(GO, 0);
		// ----
		// trap
		/*
		0: if_enemy 3
		1: left
		2: go 0
		3: infect
		4: go 0
		*/
		Creature::pTrap[0] = Instruction(IF_ENEMY, 3);
		Creature::pTrap[1] = Instruction(LEFT);
		Creature::pTrap[2] = Instruction(GO , 0);
		Creature::pTrap[3] = Instruction(INFECT);
		Creature::pTrap[4] = Instruction(GO , 0);

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
		Creature::pRover[0] = Instruction(IF_ENEMY, 9);
		Creature::pRover[1] = Instruction(IF_EMPTY, 7);
		Creature::pRover[2] = Instruction(IF_RANDOM, 5);
		Creature::pRover[3] = Instruction(GO , 0);
		Creature::pRover[4] = Instruction(LEFT);
		Creature::pRover[5] = Instruction(GO , 0);
		Creature::pRover[6] = Instruction(RIGHT);
		Creature::pRover[7] = Instruction(GO , 0);
		Creature::pRover[8] = Instruction(HOP);
		Creature::pRover[9] = Instruction(GO , 0);
		Creature::pRover[10] = Instruction(INFECT);
		// -----
		// Best
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
		Creature::pBest[0] = Instruction(IF_ENEMY, 9);
		Creature::pBest[1] = Instruction(IF_EMPTY, 7);
		Creature::pBest[2] = Instruction(IF_RANDOM, 5);
		Creature::pBest[3] = Instruction(GO , 0);
		Creature::pBest[4] = Instruction(LEFT);
		Creature::pBest[5] = Instruction(GO , 0);
		Creature::pBest[6] = Instruction(RIGHT);
		Creature::pBest[7] = Instruction(GO , 0);
		Creature::pBest[8] = Instruction(HOP);
		Creature::pBest[9] = Instruction(GO , 0);
		Creature::pBest[10] = Instruction(INFECT);
	}
	//assert(Hopper::program.size() == 2);
}

void Grid::place(char creatureType, char d, int r, int c){
	creatureStash.push_back(Creature(d, r, c, this, creatureType));
	_g[r][c] = &creatureStash.back();
}

void Grid::runTurn(){
	for(int r = 0; r < nRows(); ++r)
		for(int c = 0; c < nCols(); ++c){
			Creature*& creaturePtr =  _g[r][c];
			if(creaturePtr != NULL){
				creaturePtr->execute();
				//BOOYAKASHA
			}
		}
	assert(valid());
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
bool Grid::valid(){
			for(int r = 1; r < nRows(); ++r)
				if(_g[r].size() != _g[r-1].size())
					return false;
				//for(int c = 0; c < nCols(); ++c)
					
			return true;
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
