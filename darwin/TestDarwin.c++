/*
Ian Buitrago
Jonathan Chen
11-7-2012
CS 371p
project 5 - Darwin

compile:
	$ g++ -std=c++0x -ldl TestDarwin.c++ -lcppunit -o TestDarwin.c++.app
execute:
	$ valgrind ./TestDarwin.c++.app 2>&1 | tee TestDarwin.out
*/

// --------
// includes
#include "cppunit/extensions/HelperMacros.h"	// CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"				// TestFixture
#include "cppunit/TextTestRunner.h"				// TestRunner

#define private public
#include "Darwin.h"

// ----------
// TestDarwin
struct TestDarwin : CppUnit::TestFixture {
	// --------
	// testGrid
	void testGrid0 () {
		Grid g(2, 2);
		
		CPPUNIT_ASSERT(g.nRows() == 2);
		CPPUNIT_ASSERT(g.nCols() == 2);
		CPPUNIT_ASSERT(g.turn == 0);
		CPPUNIT_ASSERT(g.creatureStash.size() == 0);
	}
	
	// --------
	// testCreature
	void testCreature0 () {
		Creature c (NORTH, 1, 2, NULL, HOPPER);
		
		CPPUNIT_ASSERT(c.direction == NORTH);
		CPPUNIT_ASSERT(c.row == 1);
		CPPUNIT_ASSERT(c.col == 2);
		CPPUNIT_ASSERT(c.grid == NULL);
		CPPUNIT_ASSERT(c.sigil == HOPPER);
		CPPUNIT_ASSERT(c.turn == 0);
		CPPUNIT_ASSERT(c.pc == 0);
		CPPUNIT_ASSERT(c.program == &Creature::pHopper);
	}
	
	// --------
	// testPlace
	void testPlace0 () {
		Grid g(3, 3);
		int r = 1;
		int c = 1;
		
		g.place(HOPPER, NORTH, r, c);
		CPPUNIT_ASSERT(g.creatureStash.size() == 1);
		CPPUNIT_ASSERT(g._g[r][c] !=  NULL);
	}
	
	// out of bounds tests
	void testPlace1 () {
		Grid g(3, 3);
		int r = -1;
		int c = -1;
		try{
			g.place(HOPPER, NORTH, r, c);
			CPPUNIT_ASSERT(false);
		}catch(...){
			CPPUNIT_ASSERT(true);
		}			
	}
	
	void testPlace2 () {
		Grid g(3, 3);
		int r = 3;
		int c = 3;
		try{
			g.place(HOPPER, NORTH, r, c);
			CPPUNIT_ASSERT(false);
		}catch(...){
			CPPUNIT_ASSERT(true);
		}
	}
	
	// --------
	// testNextCell
	void testNextCell0 () {
		Grid g (3, 3);
		Creature& creature = g.place(HOPPER, SOUTH, 0, 1);
		
		int row = 0;
		int col = 0;
		CPPUNIT_ASSERT( creature.nextCell(row, col) );
		CPPUNIT_ASSERT(row == 1);
		CPPUNIT_ASSERT(col == 1);
	}
	
	void testNextCell1 () {
		Grid g (3, 3);
		Creature& creature = g.place(HOPPER, EAST, 1, 0);
		
		int row = -1;
		int col = -1;
		CPPUNIT_ASSERT( creature.nextCell(row, col) );
		CPPUNIT_ASSERT(row == 1);
		CPPUNIT_ASSERT(col == 1);
	}
	
	void testNextCell2 () {
		Grid g (3, 3);
		Creature& creature = g.place(HOPPER, SOUTH, 2, 0);
		
		int row = 4;
		int col = 4;
		CPPUNIT_ASSERT( !creature.nextCell(row, col) );
		CPPUNIT_ASSERT(row == 3);
		CPPUNIT_ASSERT(col == 0);
	}
	
	// ----------
	// testIfWall
	void testIfWall0 () {
		// not a wall
		Grid g (3, 3);
		Creature& c = g.place(HOPPER, EAST, 0, 1);
		
		CPPUNIT_ASSERT(c.pc == 0);
		c.ifWall();
		CPPUNIT_ASSERT(c.pc == 1);
	}
	
	void testIfWall1 () {
		// an east wall
		Grid g (3, 3);
		Creature& c = g.place(HOPPER, EAST, 0, 2);
		
		CPPUNIT_ASSERT(c.pc == 0);
		c.ifWall();
		//if(DEBUG) cerr << "BOOYAKASHA!" << c.pc <<  endl;
		CPPUNIT_ASSERT(c.pc == (*c.program)[0].line );
	}
	
	void testIfWall2 () {
		// a south wall
		Grid g (3, 3);
		Creature& c = g.place(HOPPER, SOUTH, 2, 1);
		
		CPPUNIT_ASSERT(c.pc == 0);
		c.ifWall();
		CPPUNIT_ASSERT(c.pc == (*c.program)[0].line);
	}
	
	// ----------
	// testIfRandom
	void testIfRandom0 () {
		Grid g (3, 3);
		Creature& c = g.place(FOOD, EAST, 0, 0);
		
		CPPUNIT_ASSERT(c.pc == 0);
		srand(0);
		c.ifRandom();
		CPPUNIT_ASSERT(c.pc == (*c.program)[0].line);
	}
	
	void testIfRandom1 () {
		Grid g (3, 3);
		Creature& c = g.place(FOOD, EAST, 0, 0);
		
		CPPUNIT_ASSERT(c.pc == 0);
		srand(2);
		c.ifRandom();
		CPPUNIT_ASSERT(c.pc == 1);
	}
	
	// ----------
	// testIfEnemy
	void testIfEnemy0 () {
		Grid g (3, 3);
		Creature& c = g.place(HOPPER, EAST, 0, 0);
		
		CPPUNIT_ASSERT(c.pc == 0);
		c.ifEnemy();
		CPPUNIT_ASSERT(c.pc == 1);
	}
	
	void testIfEnemy1 () {
		Grid g (3, 3);
		Creature& c = g.place(HOPPER, EAST, 0, 0);
		g.place(FOOD, EAST, 0, 1);		// enemy
		
		CPPUNIT_ASSERT(c.pc == 0);
		c.ifEnemy();
		CPPUNIT_ASSERT(c.pc == (*c.program)[0].line);
	}
	
	// ----------
	// testIfEmpty
	void testIfEmpty0 () {
		Grid g (3, 3);
		Creature& c = g.place(HOPPER, EAST, 0, 0);
		
		CPPUNIT_ASSERT(c.pc == 0);
		c.ifEmpty();
		CPPUNIT_ASSERT(c.pc == (*c.program)[0].line);
	}
	
	void testIfEmpty1 () {
		Grid g (3, 3);
		Creature& c = g.place(HOPPER, EAST, 0, 0);
		g.place(HOPPER, EAST, 0, 1);
		
		CPPUNIT_ASSERT(c.pc == 0);
		c.ifEmpty();
		CPPUNIT_ASSERT(c.pc == 1);
	}
	
	void testIfEmpty2 () {
		Grid g (3, 3);
		Creature& c = g.place(HOPPER, EAST, 0, 2);
		
		CPPUNIT_ASSERT(c.pc == 0);
		c.ifEmpty();
		CPPUNIT_ASSERT(c.pc == 1);
	}
	
	// ----------
	// testLeft
	void testLeft0 () {
		Grid g (3, 3);
		Creature& c = g.place(HOPPER, EAST, 0, 0);
		
		CPPUNIT_ASSERT(c.direction == EAST);
		c.left();
		CPPUNIT_ASSERT(c.direction == NORTH);
	}
	void testLeft1 () {
		Grid g (3, 3);
		Creature& c = g.place(HOPPER, SOUTH, 0, 0);
		
		CPPUNIT_ASSERT(c.direction == SOUTH);
		c.left();
		CPPUNIT_ASSERT(c.direction == EAST);
	}
	void testLeft2 () {
		Grid g (3, 3);
		Creature& c = g.place(HOPPER, WEST, 0, 0);
		
		CPPUNIT_ASSERT(c.direction == WEST);
		c.left();
		CPPUNIT_ASSERT(c.direction == SOUTH);
	}
	void testLeft3 () {
		Grid g (3, 3);
		Creature& c = g.place(HOPPER, NORTH, 0, 0);
		
		CPPUNIT_ASSERT(c.direction == NORTH);
		c.left();
		CPPUNIT_ASSERT(c.direction == WEST);
	}
	
	// ----------
	// testRight
	void testRight0 () {
		Grid g (3, 3);
		Creature& c = g.place(HOPPER, EAST, 0, 0);
		
		CPPUNIT_ASSERT(c.direction == EAST);
		c.right();
		CPPUNIT_ASSERT(c.direction == SOUTH);
	}
	void testRight1 () {
		Grid g (3, 3);
		Creature& c = g.place(HOPPER, SOUTH, 0, 0);
		
		CPPUNIT_ASSERT(c.direction == SOUTH);
		c.right();
		CPPUNIT_ASSERT(c.direction == WEST);
	}
	void testRight2 () {
		Grid g (3, 3);
		Creature& c = g.place(HOPPER, WEST, 0, 0);
		
		CPPUNIT_ASSERT(c.direction == WEST);
		c.right();
		CPPUNIT_ASSERT(c.direction == NORTH);
	}
	void testRight3 () {
		Grid g (3, 3);
		Creature& c = g.place(HOPPER, NORTH, 0, 0);
		
		CPPUNIT_ASSERT(c.direction == NORTH);
		c.right();
		CPPUNIT_ASSERT(c.direction == EAST);
	}
	
	// --------
	// testHop
	void testHop0 () {
		Grid g (3, 3);
		Creature& c = g.place(HOPPER, EAST, 0, 0);
		
		CPPUNIT_ASSERT(c.col == 0);
		c.hop();
		CPPUNIT_ASSERT(c.col == 1);
	}
	// hop into a creature
	void testHop1 () {
		Grid g (3, 3);
		Creature& c = g.place(HOPPER, EAST, 0, 0);
		g.place(FOOD, EAST, 0, 1);
		
		CPPUNIT_ASSERT(c.col == 0);
		c.hop();
		CPPUNIT_ASSERT(c.col == 0);
	}
	// hop into wall
	void testHop2 () {
		Grid g (3, 3);
		Creature& c = g.place(HOPPER, EAST, 0, 2);
		
		CPPUNIT_ASSERT(c.col == 2);
		c.hop();
		CPPUNIT_ASSERT(c.col == 2);
	}
	
	// --------
	// testInfect
	void testInfect0 () {
		Grid g (3, 3);
		Creature& c = g.place(HOPPER, EAST, 0, 0);
		Creature& victim = g.place(FOOD, EAST, 0, 1);
		victim.pc = 5;
		
		CPPUNIT_ASSERT(victim.sigil == FOOD);
		CPPUNIT_ASSERT(victim.pc == 5);
		c.infect();
		CPPUNIT_ASSERT(victim.sigil == c.sigil);
		CPPUNIT_ASSERT(victim.pc == 0);
	}
	void testInfect1 () {
		Grid g (3, 3);
		Creature& c = g.place(HOPPER, EAST, 0, 0);
		Creature& victim = g.place(HOPPER, EAST, 0, 1);
		victim.pc = 5;
		
		CPPUNIT_ASSERT(victim.sigil == c.sigil);
		CPPUNIT_ASSERT(victim.pc == 5);
		c.infect();
		CPPUNIT_ASSERT(victim.sigil == c.sigil);
		CPPUNIT_ASSERT(victim.pc == 5);
	}
	void testInfect2 () {
		Grid g (3, 3);
		Creature& c = g.place(HOPPER, EAST, 0, 2);
		
		c.infect();
		CPPUNIT_ASSERT(true);
	}
	
	// --------
	// testExecute
	void testExecute0 () {
		Grid g (3, 3);
		Creature& c = g.place(HOPPER, EAST, 0, 0);
		
		CPPUNIT_ASSERT(c.col == 0);
		c.execute();
		CPPUNIT_ASSERT(c.col == 1);
	}
	void testExecute1 () {
		Grid g (3, 3);
		Creature& c = g.place(FOOD, EAST, 0, 0);
		
		CPPUNIT_ASSERT(c.direction == EAST);
		c.execute();
		CPPUNIT_ASSERT(c.direction == NORTH);
	}
	void testExecute2 () {
		Grid g (3, 3);
		Creature& c = g.place(ROVER, EAST, 0, 0);
		Creature& victim = g.place(FOOD, EAST, 0, 1);
		
		CPPUNIT_ASSERT(victim.sigil == FOOD);
		c.execute();
		CPPUNIT_ASSERT(victim.sigil == ROVER);
	}
	
	// --------
	// testValid
	void testValid0 () {
		Grid g (3, 3);
		
		CPPUNIT_ASSERT(g.valid());
	}
	void testValid1 () {
		Grid g (3, 3);
		
		g._g[0].pop_back();
		CPPUNIT_ASSERT( !g.valid());
	}
	
	// --------
	// testRunTurn
	void testRunTurn0 () {
		Grid g (3, 3);
		
		g.runTurn();
		CPPUNIT_ASSERT(true);
	}
	void testRunTurn1 () {
		Grid g (3, 3);
		Creature& c = g.place(HOPPER, EAST, 0, 0);
		
		CPPUNIT_ASSERT(c.col == 0);
		g.runTurn();
		CPPUNIT_ASSERT(c.col == 1);
	}
	
	
	
	
	
	
	
	
	
	
	
	
	// --------
	// testFood
	void testFood0 () {
		Grid g(2, 2);
		
		g.place(FOOD, SOUTH, 0, 0);
		g.simulate(2, 1);
	}
	
	// --------
	// testTrap
	void testTrap0 () {
		Grid g(2, 2);
		
		g.place(TRAP, SOUTH, 0, 0);
		g.simulate(2, 1);
	}
	void testTrap1 () {
		Grid g(3, 3);
		
		g.place(TRAP, EAST, 1, 1);
		g.place(FOOD, SOUTH, 1, 2);
		g.simulate(2, 1);
	}
	
	// --------
	// testRover
	void testRover0 () {
		Grid g(4, 4);
		srand(0);
		
		g.place(ROVER , EAST, 1, 1);
		g.place(FOOD  , SOUTH, 1, 3);
		g.place(HOPPER, EAST, 2, 2);
		g.simulate(6, 1);
	}
	
	// --------
	// testBest
	void testBest0 () {
		Grid g(5, 5);
		srand(0);
		
		g.place(BEST  , EAST, 0, 0);
		g.place(ROVER , EAST, 1, 1);
		g.place(FOOD  , SOUTH, 1, 3);
		g.place(HOPPER, EAST, 2, 2);
		g.simulate(10, 1);
	}
	
	// --------
	// testBest
	void testBest1 () {
		Grid g(50, 50);
		srand(0);
		
		g.randPlace(BEST  , 5);
		g.randPlace(ROVER , 5);
		g.randPlace(FOOD  , 5);
		g.randPlace(HOPPER, 5);
		g.randPlace(TRAP  , 5);
		g.simulate(500, 50);
	}
	void testBest2 () {
		Grid g(80, 80);
		srand(0);
		
		g.randPlace(BEST  , 13);
		g.randPlace(ROVER , 13);
		g.randPlace(FOOD  , 13);
		g.randPlace(HOPPER, 13);
		g.randPlace(TRAP  , 13);
		g.simulate(1000, 500);
	}
	
	// -----
	// suite
	CPPUNIT_TEST_SUITE(TestDarwin);
	
	CPPUNIT_TEST(testGrid0);
	CPPUNIT_TEST(testCreature0);
	CPPUNIT_TEST(testPlace0);
	CPPUNIT_TEST(testPlace1);
	CPPUNIT_TEST(testPlace2);
	CPPUNIT_TEST(testNextCell0);
	CPPUNIT_TEST(testNextCell1);
	CPPUNIT_TEST(testNextCell2);
	CPPUNIT_TEST(testIfWall0);
	CPPUNIT_TEST(testIfWall1);
	CPPUNIT_TEST(testIfWall2);
	CPPUNIT_TEST(testIfRandom0);
	CPPUNIT_TEST(testIfRandom1);
	CPPUNIT_TEST(testIfEnemy0);
	CPPUNIT_TEST(testIfEnemy1);
	CPPUNIT_TEST(testIfEmpty0);
	CPPUNIT_TEST(testIfEmpty1);
	CPPUNIT_TEST(testIfEmpty2);
	CPPUNIT_TEST(testLeft0);
	CPPUNIT_TEST(testLeft1);
	CPPUNIT_TEST(testLeft2);
	CPPUNIT_TEST(testLeft3);
	CPPUNIT_TEST(testRight0);
	CPPUNIT_TEST(testRight1);
	CPPUNIT_TEST(testRight2);
	CPPUNIT_TEST(testRight3);
	CPPUNIT_TEST(testHop0);
	CPPUNIT_TEST(testHop1);
	CPPUNIT_TEST(testHop2);
	CPPUNIT_TEST(testInfect0);
	CPPUNIT_TEST(testInfect1);
	CPPUNIT_TEST(testInfect2);
	CPPUNIT_TEST(testExecute0);
	CPPUNIT_TEST(testExecute1);
	CPPUNIT_TEST(testExecute2);
	CPPUNIT_TEST(testValid0);
	CPPUNIT_TEST(testValid1);
	CPPUNIT_TEST(testRunTurn0);
	CPPUNIT_TEST(testRunTurn1);
	/*
	CPPUNIT_TEST(testRunTurn2);
	CPPUNIT_TEST(testFood0);
	CPPUNIT_TEST(testTrap0);
	CPPUNIT_TEST(testTrap1);
	CPPUNIT_TEST(testRover0);
	CPPUNIT_TEST(testBest0);
	CPPUNIT_TEST(testBest1);
	CPPUNIT_TEST(testBest2);
	*/
	
	CPPUNIT_TEST_SUITE_END();
};

// ----
// main
int main () {
	using namespace std;
	ios_base::sync_with_stdio(false);	// turn off synchronization with C I/O
	cout << "TestDarwin.c++" << endl;

	CppUnit::TextTestRunner tr;
	tr.addTest(TestDarwin::suite());
	tr.run();

	cout << "Done." << endl;
	return 0;
}
