/*
Ian Buitrago
Jonathan Chen
11-7-2012
CS 371p
project 5 - Darwin
*/
#ifndef Darwin_h
#define Darwin_h

// --------
// includes
#include <cassert>		// assert
#include <vector>		// vector
#include <deque>
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

// ------
// macros
#define DEBUG !true
#define BOOYAKASHA	if(DEBUG) cerr << "BOOYAKASHA!" <<  endl;

#define HOPPER		'h'
#define FOOD		'f'
#define TRAP		't'
#define ROVER		'r'
#define BEST		'b'

enum op{HOP, LEFT, RIGHT, INFECT, IF_EMPTY, IF_ENEMY, IF_WALL, IF_RANDOM, GO};
enum dir{WEST, NORTH, EAST, SOUTH};

struct Instruction{
	op opCode;
	int line;
	
	Instruction(op o, int l = -1){
		opCode = o;
		line = l;
	}
	Instruction(){
		opCode = LEFT;
		line = 0;
	}
};

class Creature;

// ------
// Grid
class Grid{
	friend class Creature;
	private:
		vector< vector<Creature*> > _g;
		deque<Creature> creatureStash;
		unsigned turn;
		
		bool valid();
	public:
		Grid(int rows, int cols);
		void place(char x, dir d, int r, int c);
		void runTurn();
		void print(std::ostream& = cout);
		void printCount();
		void simulate(int turns, int j);
		void randPlace(char, int);
		int nRows() const{return _g.size();}
		int nCols() const{return _g.size() ? _g[0].size() : 0;}
};

class Creature{
	private:
		dir direction;
		int row;
		int col;
		const vector<Instruction>* program;
		Grid* grid;
		int pc;
		unsigned turn;
	public:
		char sigil;
		static vector<Instruction> pHopper;
		static vector<Instruction> pFood;
		static vector<Instruction> pTrap;
		static vector<Instruction> pRover;
		static vector<Instruction> pBest;
		
		Creature(dir d, int r, int c, Grid* g, char s);
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

/**
Creature constructor.
*/
Creature::Creature(dir d, int r, int c, Grid* g, char s){
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
/**
Executes a creature's program until it completes an action.
*/
void Creature::execute(){
	const vector<Instruction>& p = *program;
	
	// check if creature already took its turn
	while(turn == grid->turn){/*
		if(DEBUG) cerr << "*creature: " << sigil << endl;
		if(DEBUG) cerr << "pc: " << pc << endl;
		if(DEBUG) cerr << "instruction: " << p[pc].op << endl;
		if(DEBUG) cerr << "target line: " << p[pc].line << endl;*/
		switch(p[pc].opCode){
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

// Actions
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
	direction = dir((direction + 3) % 4);
}

void Creature::right(){
	++pc;
	++turn;		// used up turn
	direction = dir((direction + 1) % 4);
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

// Control instructions
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
@param r Row in the grid that will be changed to the cell the creature faces.
@param c Column in the grid that will be changed to the cell the creature faces.
@return true if in range, false if out of bounds.
*/
bool Creature::nextCell(int& r, int& c){
	Grid& g = *grid;
	switch(direction){
		case EAST:
			++c;
			if(c >= g.nCols()) return false;		// do nothing at wall
			break;
		case WEST:
			--c;
			if(c < 0) return false;
			break;
		case NORTH:
			--r;
			if(r < 0) return false;
			break;
		case SOUTH:
			++r;
			if(r >= g.nRows()) return false;
			break;
		default:
			throw logic_error("Invalid direction: " + (int)direction);
	}
	return true;
}

// Static program initializations
vector<Instruction> initHopper(){
	Creature::pHopper.push_back(Instruction(HOP));
	Creature::pHopper.push_back(Instruction(GO, 0));
}
vector<Instruction> initFood(){
	Creature::pFood.push_back(Instruction(LEFT));
	Creature::pFood.push_back(Instruction(GO, 0));
}
vector<Instruction> initTrap(){
	Creature::pTrap.push_back(Instruction(IF_ENEMY, 3));
	Creature::pTrap.push_back(Instruction(LEFT));
	Creature::pTrap.push_back(Instruction(GO , 0));
	Creature::pTrap.push_back(Instruction(INFECT));
	Creature::pTrap.push_back(Instruction(GO , 0));
}
vector<Instruction> initRover(){
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
}
vector<Instruction> initBest(){
	Creature::pBest.push_back(Instruction(IF_ENEMY, 9));
	Creature::pBest.push_back(Instruction(IF_EMPTY, 4));
	Creature::pBest.push_back(Instruction(RIGHT));	// friend
	Creature::pBest.push_back(Instruction(GO , 0));
	Creature::pBest.push_back(Instruction(IF_RANDOM, 7));
	Creature::pBest.push_back(Instruction(HOP));
	Creature::pBest.push_back(Instruction(GO , 0));
	Creature::pBest.push_back(Instruction(RIGHT));
	Creature::pBest.push_back(Instruction(GO , 0));
	Creature::pBest.push_back(Instruction(INFECT));
	Creature::pBest.push_back(Instruction(GO , 0));
}
vector<Instruction> Creature::pHopper = initHopper();
vector<Instruction> Creature::pFood = initFood();
vector<Instruction> Creature::pTrap = initTrap();
vector<Instruction> Creature::pRover = initRover();
vector<Instruction> Creature::pBest = initBest();

// -----------------------
// Grid method definitions
/**
Grid Constructor
*/
Grid::Grid(int rows, int cols)
: _g(rows, vector<Creature*>(cols)), turn(0)//, creatureStash()
{
	assert(valid());
}

/**
Places a created creature into the grid.
@param d direction the creature will face.
@param r row of the grid.
@param c column of the grid.
*/
void Grid::place(char creatureType, dir d, int r, int c){
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
void Grid::print(std::ostream& out){
	out << "Turn = " << turn << "." << endl;
	out << "  ";
	for(int c = 0; c < nCols(); ++c)
		out << c % 10;
	out << endl;
	for(int r = 0; r < nRows(); ++r){
		out << r % 10 << " ";
		for(int c = 0; c < nCols(); ++c){
			if(_g[r][c] == NULL)
				out << ".";
			else
				out << *_g[r][c];
		}
		out << endl;
	}
	out << endl;
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
		dir direction = dir(rand() % 4);
	
		place(type, direction, r, c);
	}
}

/**
Checks if all rows are equal in size.
*/
bool Grid::valid(){
	for(int r = 1; r < nRows(); ++r)
		if(_g[r].size() != _g[r-1].size())
			return false;
			
	return true;
}
#endif // Darwin_h
