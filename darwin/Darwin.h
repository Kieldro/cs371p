/*
Ian Buitrago
Jonathan Chen
11-7-2012
CS 371p
project 5 - Darwin
*/
#ifndef Darwin_h
#define Darwin_h

// ------
// macros
#define DEBUG !true
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

#define NORTH		0
#define EAST		1
#define SOUTH		2
#define WEST		3

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
using std::out_of_range;

static const vector<char> DIRECTION = {'n', 'e', 's', 'w'};

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
		void printCount();
		void simulate(int turns, int j);
		bool valid();
		void randPlace(char, int);
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
vector<Instruction> Creature::pHopper;
vector<Instruction> Creature::pFood;
vector<Instruction> Creature::pTrap;
vector<Instruction> Creature::pRover;
vector<Instruction> Creature::pBest;

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
		//if(DEBUG) cerr << "Hopping to " << r << c <<  endl;
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
		//if(DEBUG) cerr << "Infecting creature at " << r << c <<  endl;
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

/**
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
	assert(NULL == 0);
	// static program initializations
	// TODO Better way?
	if(Creature::pHopper.size() == 0)
	{
		Creature::pHopper.push_back(Instruction(HOP));
		Creature::pHopper.push_back(Instruction(GO, 0));
		// ----
		// food
		Creature::pFood.push_back(Instruction(LEFT));
		Creature::pFood.push_back(Instruction(GO, 0));
		// ----
		// trap
		Creature::pTrap.push_back(Instruction(IF_ENEMY, 3));
		Creature::pTrap.push_back(Instruction(LEFT));
		Creature::pTrap.push_back(Instruction(GO , 0));
		Creature::pTrap.push_back(Instruction(INFECT));
		Creature::pTrap.push_back(Instruction(GO , 0));
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
		Creature::pRover.push_back(Instruction(IF_ENEMY, 9));
		Creature::pRover.push_back(Instruction(IF_EMPTY, 7));
		Creature::pRover.push_back(Instruction(IF_RANDOM, 5));
		Creature::pRover.push_back(Instruction(LEFT));
		Creature::pRover.push_back(Instruction(GO , 0));
		Creature::pRover.push_back(Instruction(RIGHT));
		Creature::pRover.push_back(Instruction(GO , 0));
		Creature::pRover.push_back(Instruction(HOP));
		Creature::pRover.push_back(Instruction(GO , 0));
		Creature::pRover.push_back(Instruction(INFECT));
		Creature::pRover.push_back(Instruction(GO , 0));
		// -----
		// Best
		Creature::pBest.push_back(Instruction(IF_ENEMY, 9));
		Creature::pBest.push_back(Instruction(IF_EMPTY, 4));
		Creature::pBest.push_back(Instruction(LEFT));	// friend
		Creature::pBest.push_back(Instruction(GO , 0));
		Creature::pBest.push_back(Instruction(IF_RANDOM, 7));
		Creature::pBest.push_back(Instruction(HOP));
		Creature::pBest.push_back(Instruction(GO , 0));
		Creature::pBest.push_back(Instruction(LEFT));
		Creature::pBest.push_back(Instruction(GO , 0));
		Creature::pBest.push_back(Instruction(INFECT));
		Creature::pBest.push_back(Instruction(GO , 0));
	}
	//assert(Hopper::program.size() == 2);
}

/**
Places a created creature into the grid.
@param d direction the creature will face.
@param r row of the grid.
@param c column of the grid.
*/
void Grid::place(char creatureType, char d, int r, int c){
	if(r < 0 or r >= nRows() or c < 0 or c >= nCols())
		throw out_of_range("Coordinates out of range: " + r + c);
	if(_g[r][c] != NULL)
		throw logic_error("Creature cannot be placed ontop of preexisting creature at " + r + c);
	creatureStash.push_back(Creature(d, r, c, this, creatureType));
	_g[r][c] = &creatureStash.back();
}

/*
Runs a single turn by running through the grid row by row.
*/
void Grid::runTurn(){
	for(int r = 0; r < nRows(); ++r)
		for(int c = 0; c < nCols(); ++c){
			Creature*& creaturePtr =  _g[r][c];
			if(creaturePtr != NULL){
				creaturePtr->execute();
			}
		}
	assert(valid());
	++turn;
}

/**
@param turns the number turns to run the game.
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

/**
Prints the grid and turn number.
*/
void Grid::print(){
	cout << "Turn = " << turn << "." << endl;
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
	if(DEBUG)printCount();
}

/**
Debugging function thats prints the count of each creature.
*/
void Grid::printCount(){
	int numHopper = 0;
	int numBest = 0;
	int numRover = 0;
	int numFood = 0;
	int numTrap = 0;
	
	for(int i = 0; i < creatureStash.size(); ++i){
		switch(creatureStash[i].sigil){
			case HOPPER:
				++numHopper;
				break;
			case BEST:
				++numBest;
				break;
			case ROVER:
				++numRover;
				break;
			case FOOD:
				++numFood;
				break;
			case TRAP:
				++numTrap;
				break;
		}
	}
	
	cerr << BEST << " = " << numBest << endl;
	cerr << ROVER << " = " << numRover << endl;
	cerr << HOPPER << " = " << numHopper << endl;
	cerr << FOOD << " = " << numFood << endl;
	cerr << TRAP << " = " << numTrap << endl;
}

/**
Randomly places count creatures of type type.
*/
void Grid::randPlace(char type, int count){
	for(int i = 0; i < count; ++i){
		int pos = rand() % (nRows() * nCols());
		int r = pos / nRows();
		int c = pos % nCols();
		char direction = DIRECTION[rand() % 4];
	
		place(type, direction, r, c);
	}
}

/**
Checks if all rows are euqal in size.
*/
bool Grid::valid(){
	for(int r = 1; r < nRows(); ++r)
		if(_g[r].size() != _g[r-1].size())
			return false;
			
	return true;
}
#endif // Darwin_h
