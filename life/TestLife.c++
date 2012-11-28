/*
Ian Buitrago
Graham Benevelli
11-28-2012
CS 371p
project 6 - Life

compile:
	$ g++ -std=c++0x -ldl TestLife.c++ -lcppunit -o TestLife.c++.app
execute:
	$ valgrind ./TestLife.c++.app 2>&1 | tee TestLife.out
*/

// --------
// includes
#include "cppunit/extensions/HelperMacros.h"	// CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"				// TestFixture
#include "cppunit/TextTestRunner.h"				// TestRunner
#include <sstream>

#define private public
#define protected public

#include "ConwayCell.h"
#include "FredkinCell.h"
#include "Cell.h"

using std::ostringstream;
unsigned dummy = 0;

// --------
// TestLife
struct TestLife : CppUnit::TestFixture {
	// --------
	// testLife
	void testLife0 () {
		Life<ConwayCell> game("RunLifeConway.in");
		
		CPPUNIT_ASSERT(game.generation == 0);
		CPPUNIT_ASSERT(game.population == 35);
		CPPUNIT_ASSERT(game.nRows() == 109);
		CPPUNIT_ASSERT(game.nCols() == 69);
	}
	void testLife1 () {
		Life<FredkinCell> game("RunLifeFredkin.in");
		
		CPPUNIT_ASSERT(game.generation == 0);
		CPPUNIT_ASSERT(game.population == 4);
		CPPUNIT_ASSERT(game.nRows() == 20);
		CPPUNIT_ASSERT(game.nCols() == 20);
	}
	void testLife2 () {
		Life<FredkinCell> game(5, 5);
		
		CPPUNIT_ASSERT(game.generation == 0);
		CPPUNIT_ASSERT(game.population == 0);
		CPPUNIT_ASSERT(game.nRows() == 5);
		CPPUNIT_ASSERT(game.nCols() == 5);
	}
	void testLife3 () {
		Life<ConwayCell> game(5, 5);
		
		CPPUNIT_ASSERT(game.generation == 0);
		CPPUNIT_ASSERT(game.population == 0);
		CPPUNIT_ASSERT(game.nRows() == 5);
		CPPUNIT_ASSERT(game.nCols() == 5);
	}
	void testLife4 () {
		Life<Cell> game(2, 2);
		
		CPPUNIT_ASSERT(game.generation == 0);
		CPPUNIT_ASSERT(game.population == 0);
		CPPUNIT_ASSERT(game.nRows() == 2);
		CPPUNIT_ASSERT(game.nCols() == 2);
		CPPUNIT_ASSERT(game._g[0][0][0].cell != 0);
	}
	void testLife5 () {
		Life<Cell> game("RunLife.in");
		
		CPPUNIT_ASSERT(game.generation == 0);
		CPPUNIT_ASSERT(game.population == 6);
		CPPUNIT_ASSERT(game.nRows() == 20);
		CPPUNIT_ASSERT(game.nCols() == 20);
	}
	
	void testUpdate0() {
		Life<ConwayCell> game(7, 5);
		game._g[0][2][1].alive = true;
		game._g[0][3][1].alive = true;
		game._g[0][4][1].alive = true;
		game._g[0][5][1].alive = true;
		
		//cout << game.countNeighborsAdjacent(2, 1) << endl;
		CPPUNIT_ASSERT(game.countNeighborsAdjacent(1, 1) == 1);
		CPPUNIT_ASSERT(game.countNeighborsAdjacent(2, 1) == 1);
		CPPUNIT_ASSERT(game.countNeighborsAdjacent(3, 1) == 2);
		CPPUNIT_ASSERT(game.countNeighborsAdjacent(3, 2) == 1);
		CPPUNIT_ASSERT(game.countNeighborsAdjacent(0, 0) == 0);
	}
	
	void testRunTurn0() {
		Life<ConwayCell> game(3, 3);
		game.runTurn();
		//game.print();
		CPPUNIT_ASSERT(1);		
	}
	
	void testSimulateTurn0() {
		Life<ConwayCell> game(3, 3);
		//game.simulate(5, 1);
		CPPUNIT_ASSERT(1);		
	}

	// ----------------------------
	// testConwayDefaultConstructor
	void testConwayDefaultConstructor0 () {
		ConwayCell c;
		CPPUNIT_ASSERT(!c.alive);
	}

	void testConwayDefaultConstructor1 () {
		ConwayCell c1;
		CPPUNIT_ASSERT(!c1.alive);
		ConwayCell c2;
		CPPUNIT_ASSERT(!c2.alive);
	}

	void testConwayDefaultConstructor2 () {
		ConwayCell c1;
		ConwayCell c2;
		CPPUNIT_ASSERT(!c1.alive);
		CPPUNIT_ASSERT(!c2.alive);
	}

	// -------------------------
	// testConwayBoolConstructor
	void testConwayBoolConstructor0 () {
		ConwayCell c(false);
		CPPUNIT_ASSERT(!c.alive);
	}

	void testConwayBoolConstructor1 () {
		ConwayCell c(true);
		CPPUNIT_ASSERT(c.alive);
	}

	void testConwayBoolConstructor2 () {
		ConwayCell c1(false);
		CPPUNIT_ASSERT(!c1.alive);
		ConwayCell c2(true);
		CPPUNIT_ASSERT(c2.alive);
	}

	// --------------------
	// testConwayIsNeighbor
	void testConwayIsNeighbor0 () {
		ConwayCell c(false);
		CPPUNIT_ASSERT(!c.isNeighbor());
	}

	void testConwayIsNeighbor1 () {
		ConwayCell c(true);
		CPPUNIT_ASSERT(c.isNeighbor());
	}

	void testConwayIsNeighbor2 () {
		ConwayCell c1(false);
		CPPUNIT_ASSERT(!c1.isNeighbor());
		ConwayCell c2(true);
		CPPUNIT_ASSERT(c2.isNeighbor());
	}

	// -------------------------
	// testConwayCopyConstructor
	void testConwayCopyConstructor0 () {
		ConwayCell c1(false);
		ConwayCell c2(c1);
		CPPUNIT_ASSERT(!c2.alive);
	}

	void testConwayCopyConstructor1 () {
		ConwayCell c1(true);
		ConwayCell c2(c1);
		CPPUNIT_ASSERT(c2.alive);
	}

	void testConwayCopyConstructor2 () {
		ConwayCell c1(false);
		ConwayCell c2(c1);
		CPPUNIT_ASSERT(!c2.alive);
		c2.alive = true;
		CPPUNIT_ASSERT(!c1.alive);
		CPPUNIT_ASSERT(c2.alive);
	}

	// --------------------
	// testConwayTransform
	void testConwayTransform0 () {
		ConwayCell c;
			CPPUNIT_ASSERT(!c.transform());
	}

	// ------------------
	// testConwayReadChar
	void testConwayReadChar0 () {
		ConwayCell c;
		CPPUNIT_ASSERT(c.readChar('*'));
		CPPUNIT_ASSERT(c.alive);
	}
	void testConwayReadChar1 () {
		ConwayCell c;
		CPPUNIT_ASSERT(!c.readChar('.'));
		CPPUNIT_ASSERT(!c.alive);
	}
	void testConwayReadChar2 () {
		ConwayCell c;
		CPPUNIT_ASSERT(!c.readChar('0'));
		CPPUNIT_ASSERT(!c.alive);
	}
	
	// ----------------
	// testConwayUpdate
	void testConwayUpdate0 () {
		ConwayCell c;
		unsigned population = 0;
		c.update(2, 0, &population);
		
		CPPUNIT_ASSERT(!c.alive);
		CPPUNIT_ASSERT(population == 0);
	}
	void testConwayUpdate1 () {
		ConwayCell c;
		unsigned population = 0;
		c.update(3, 0, &population);
		
		CPPUNIT_ASSERT(c.alive);
		CPPUNIT_ASSERT(population == 1);
	}
	void testConwayUpdate2 () {
		ConwayCell c;
		c.alive= true;
		unsigned population = 0;
		
		c.update(3, 0, &population);
		CPPUNIT_ASSERT(c.alive);
		CPPUNIT_ASSERT(population == 1);
		
		c.update(2, 0, &population);
		CPPUNIT_ASSERT(c.alive);
		CPPUNIT_ASSERT(population == 2);
		
		c.update(1, 0, &population);
		CPPUNIT_ASSERT(!c.alive);
		CPPUNIT_ASSERT(population == 2);
	}
	void testConwayUpdate3 () {
		ConwayCell c;
		c.alive= true;
		c.update(4, 0, &dummy);
		
		CPPUNIT_ASSERT(!c.alive);
	}

	//----------------
	// testConwayPrint
	void testConwayPrint0 () {
		ConwayCell c(false);
			CPPUNIT_ASSERT(c.print() == '.');
	}

	void testConwayPrint1 () {
		ConwayCell c(true);
			CPPUNIT_ASSERT(c.print() =='*');
	}

	void testConwayPrint2 () {
		ConwayCell c(false);
		CPPUNIT_ASSERT(c.print() =='.');
		c.alive = true;
			CPPUNIT_ASSERT(c.print() =='*');
	}

	// --------------------
	// testConwayOperator<<
	void testConwayOperator0 () {
		ConwayCell c;
		c.readChar('*');
		std::ostringstream w;
		w << c;
		CPPUNIT_ASSERT(w.str() == "*");
	}

	void testConwayOperator1 () {
		ConwayCell c;
		c.readChar('.');
		std::ostringstream w;
		w << c;
		CPPUNIT_ASSERT(w.str() == ".");
	}

	void testConwayOperator2 () {
		ConwayCell c1;
		c1.readChar('*');
		ConwayCell c2;
		c2.readChar('.');
		std::ostringstream w;
		w << c1 << c2;
		CPPUNIT_ASSERT(w.str() == "*.");
	}
	
	// ---------------
	// testConwayClone
	void testConwayClone0 () {
		ConwayCell c1;
		c1.readChar('*');
		ConwayCell* c2 = c1.clone();
		CPPUNIT_ASSERT(c2->alive == true);
	}
	
	void testConwayClone1 () {
		ConwayCell c1;
		c1.readChar('.');
		ConwayCell* c2 = c1.clone();
		CPPUNIT_ASSERT(c2->alive == false);
	}
	
	void testConwayClone2 () {
		ConwayCell c1;
		c1.readChar('*');
		ConwayCell* c2 = c1.clone();
		CPPUNIT_ASSERT(c2->alive == true);
	}

	// ------------------------------
	// testFredkinDefaultConstructor0
	void testFredkinDefaultConstructor0 () {
		FredkinCell c;
		CPPUNIT_ASSERT(c.alive == false);
		CPPUNIT_ASSERT(c.age == 0);
	}

	void testFredkinDefaultConstructor1 () {
		FredkinCell c1;
		CPPUNIT_ASSERT(c1.alive == false);
		CPPUNIT_ASSERT(c1.age == 0);
		FredkinCell c2;
		CPPUNIT_ASSERT(c2.alive == false);
		CPPUNIT_ASSERT(c2.age == 0);
	}

	void testFredkinDefaultConstructor2 () {
		FredkinCell c1;
		FredkinCell c2;
		CPPUNIT_ASSERT(c1.alive == false);
		CPPUNIT_ASSERT(c1.age == 0);
		CPPUNIT_ASSERT(c2.alive == false);
		CPPUNIT_ASSERT(c2.age == 0);
	}

	// ----------------------------
	// testFredkinBoolIntConstrutor
	void testFredkinBoolIntConstructor0 () {
		FredkinCell c(false, 0);
		CPPUNIT_ASSERT(c.alive == false);
		CPPUNIT_ASSERT(c.age == 0);
	}

	void testFredkinBoolIntConstructor1 () {
		FredkinCell c(false, 9);
		CPPUNIT_ASSERT(c.alive == false);
		CPPUNIT_ASSERT(c.age == 9);
	}

	void testFredkinBoolIntConstructor2 () {
		FredkinCell c(true, 3);
		CPPUNIT_ASSERT(c.alive == true);
		CPPUNIT_ASSERT(c.age == 3);
	}

	// --------------------------
	// testFredkinCopyConstructor
	// --------------------------

	void testFredkinCopyConstructor0 () {
		FredkinCell c1(false, 0);
		FredkinCell c2(c1);
		CPPUNIT_ASSERT(c2.alive == false);
		CPPUNIT_ASSERT(c2.age == 0);
	}

	void testFredkinCopyConstructor1 () {
		FredkinCell c1(true, 6);
		FredkinCell c2(c1);
		CPPUNIT_ASSERT(c2.alive == true);
		CPPUNIT_ASSERT(c2.age == 6);
	}

	void testFredkinCopyConstructor2 () {
		FredkinCell c1(true, 9);
		FredkinCell c2(c1);
		CPPUNIT_ASSERT(c2.alive == true);
		CPPUNIT_ASSERT(c2.age == 9);
	}

	// ---------------------
	// testFredkinIsNeighbor
	void testFredkinIsNeighbor0 () {
		FredkinCell c(true, 0);
		CPPUNIT_ASSERT(c.isNeighbor());
	}

	void testFredkinIsNeighbor1 () {
		FredkinCell c(false, 0);
		CPPUNIT_ASSERT(!c.isNeighbor());
	}

	void testFredkinIsNeighbor2 () {
		FredkinCell c1(true, 0);
		CPPUNIT_ASSERT(c1.isNeighbor());
		FredkinCell c2(false, 0);
		CPPUNIT_ASSERT(!c2.isNeighbor());
	}

	// -------------------
	// testFredkinReadChar
	void testFredkinReadChar0 () {
		FredkinCell c;
		CPPUNIT_ASSERT(!c.readChar('.'));
		CPPUNIT_ASSERT(c.age == 0);
	}
	void testFredkinReadChar1 () {
		FredkinCell c;
		CPPUNIT_ASSERT(c.readChar('+'));
		CPPUNIT_ASSERT(c.age >= 10);
	}
	void testFredkinReadChar2 () {
		FredkinCell c;
		CPPUNIT_ASSERT(c.readChar('0'));
		CPPUNIT_ASSERT(c.age == 0);
	}
	void testFredkinReadChar3 () {
		FredkinCell c;
		CPPUNIT_ASSERT(c.readChar('7'));
		CPPUNIT_ASSERT(c.age == 7);
	}
	
	// --------
	// testFredkinUpdate
	void testFredkinUpdate0 () {
		FredkinCell f;
		f.alive= true;
		f.age = 10;
		f.update(0, 0, &dummy);
		
		CPPUNIT_ASSERT(!f.alive);
		CPPUNIT_ASSERT(f.age == 10);
	}
	void testFredkinUpdate1 () {
		FredkinCell f;
		f.alive= true;
		f.age = 10;
		
		f.update(1, 0, &dummy);
		CPPUNIT_ASSERT(f.alive);
		CPPUNIT_ASSERT(f.age == 11);
		
		f.update(3, 0, &dummy);
		CPPUNIT_ASSERT(f.alive);
		CPPUNIT_ASSERT(f.age == 12);
	}
	void testFredkinUpdate2 () {
		FredkinCell f;
		
		CPPUNIT_ASSERT(!f.alive);
		CPPUNIT_ASSERT(f.age == 0);
		
		f.update(1, 0, &dummy);
		CPPUNIT_ASSERT(f.alive);
		CPPUNIT_ASSERT(f.age == 0);
		
		f.update(3, 0, &dummy);
		CPPUNIT_ASSERT(f.alive);
		CPPUNIT_ASSERT(f.age == 1);
	}
	void testFredkinUpdate3 () {
		FredkinCell f;
		
		f.update(0, 0, &dummy);
		CPPUNIT_ASSERT(!f.alive);
		CPPUNIT_ASSERT(f.age == 0);
		
		f.update(2, 0, &dummy);
		CPPUNIT_ASSERT(!f.alive);
		CPPUNIT_ASSERT(f.age == 0);
		
		f.update(4, 0, &dummy);
		CPPUNIT_ASSERT(!f.alive);
		CPPUNIT_ASSERT(f.age == 0);
	}
	void testFredkinUpdate4 () {
		FredkinCell f(true, 0);
		unsigned population = 0;
		
		f.update(1, 0, &population);
		CPPUNIT_ASSERT(f.alive);
		CPPUNIT_ASSERT(f.age == 1);
		CPPUNIT_ASSERT(population == 1);
		
		f.update(2, 0, &population);
		CPPUNIT_ASSERT(!f.alive);
		CPPUNIT_ASSERT(f.age == 1);
		CPPUNIT_ASSERT(population == 1);
		
		f.update(3, 0, &population);
		CPPUNIT_ASSERT(f.alive);
		CPPUNIT_ASSERT(f.age == 1);
		CPPUNIT_ASSERT(population == 2);
	}

	// ---------------------
	// testFredkinOperator<<
	void testFredkinOperator0 () {
		FredkinCell c(false, 0);
		std::ostringstream w;
		w << c;
		CPPUNIT_ASSERT(w.str() == "-");
	}

	void testFredkinOperator1 () {
		FredkinCell c(true, 0);
		std::ostringstream w;
		w << c;
		CPPUNIT_ASSERT(w.str() == "0");
	}

	void testFredkinOperator2 () {
		FredkinCell c1(true, 0);
		FredkinCell c2(false, 6);
		FredkinCell c3(true, 9);
		std::ostringstream w;
		w << c1 << c2 << c3;
		CPPUNIT_ASSERT(w.str() == "0-9");
	}
	
	// ----------------
	// testFredkinClone
	void testFredkinClone0 () {
		FredkinCell c1(true, 3);
		AbstractCell* c2 = c1.clone();
		CPPUNIT_ASSERT(c2->alive == true);
		CPPUNIT_ASSERT(((FredkinCell*) c2)->age == 3);
		CPPUNIT_ASSERT(&c1 != c2);
	}
	
	void testFredkinClone1 () {
		FredkinCell c1(false, 5);
		AbstractCell* c2 = c1.clone();
		CPPUNIT_ASSERT(c2->alive == false);
		CPPUNIT_ASSERT(((FredkinCell*) c2)->age == 5);
		CPPUNIT_ASSERT(&c1 != c2);
	}
	
	void testFredkinClone2 () {
		FredkinCell c1(true, 10);
		AbstractCell* c2 = c1.clone();
		CPPUNIT_ASSERT(c2->alive == true);
		CPPUNIT_ASSERT(((FredkinCell*) c2)->age == 10);
		CPPUNIT_ASSERT(&c1 != c2);
	}

	// --------------------
	// testFredkinTransform
	void testFredkinTransform0 () {
		FredkinCell f(false, 0);
			CPPUNIT_ASSERT(!f.transform());
	}

	void testFredkinTransform1 () {
		FredkinCell f(false, 2);
			CPPUNIT_ASSERT(!f.transform());
	}

	void testFredkinTransform2 () {
		FredkinCell f(true, 0);
			CPPUNIT_ASSERT(!f.transform());
	}

	void testFredkinTransform3 () {
		FredkinCell f(true, 2);
			CPPUNIT_ASSERT(f.transform());
	}

	// ----------------
	// testFredkinPrint
	void testFredkinPrint0 () {
		FredkinCell f(false, 9);
			CPPUNIT_ASSERT(f.print() == '-');
	}

	void testFredkinPrint1 () {
		FredkinCell f(true, 9);
			CPPUNIT_ASSERT(f.print() =='9');
	}

	void testFredkinPrint2 () {
		FredkinCell f(true, 10);
			CPPUNIT_ASSERT(f.print() =='+');
	}
	
	// -------------------
	// testCellConstructor
	void testCellConstructor0 () {
		Cell c;
		CPPUNIT_ASSERT(c.cell != NULL);
	}
	
	void testCellConstructor1 () {
		Cell c1;
		CPPUNIT_ASSERT(c1.cell != NULL);
		Cell c2;
		CPPUNIT_ASSERT(c2.cell != NULL);
	}
	
	void testCellConstructor2 () {
		Cell c1;
		CPPUNIT_ASSERT(c1.cell != NULL);
		Cell c2;
		CPPUNIT_ASSERT(c2.cell != NULL);
		Cell c3;
		CPPUNIT_ASSERT(c3.cell != NULL);
	}
	
	// --------------------------
	// testCellPointerConstructor
	void testCellPointerConstructor0 () {
		Cell c = new ConwayCell;
		CPPUNIT_ASSERT(c.cell->alive == false);
		CPPUNIT_ASSERT(c.cell->print() == '.');
	}
	
	void testCellPointerConstructor1 () {
		Cell c = new FredkinCell(true, 5);
		CPPUNIT_ASSERT(c.cell->alive == true);
		CPPUNIT_ASSERT(c.cell->print() == '5');
	}
	
	void testCellPointerConstructor2 () {
		Cell c = new FredkinCell(false, 5);
		CPPUNIT_ASSERT(c.cell->alive == false);
		CPPUNIT_ASSERT(c.cell->print() == '-');
	}
	
	// -----------------------
	// testCellCopyConstructor
	void testCellCopyConstructor0 () {
		Cell c1;
		Cell c2 = c1;
		CPPUNIT_ASSERT(c1.cell != c2.cell);
		CPPUNIT_ASSERT(c1.cell->alive == c2.cell->alive);
		CPPUNIT_ASSERT(c1.cell->print() == c2.cell->print());
	}
	
	void testCellCopyConstructor1 () {
		ConwayCell* cc = new ConwayCell;
		cc->readChar('*');
		Cell c1 = cc;
		Cell c2 = c1;
		CPPUNIT_ASSERT(c1.cell != c2.cell);
		CPPUNIT_ASSERT(c1.cell->alive == c2.cell->alive);
		CPPUNIT_ASSERT(c1.cell->print() == c2.cell->print());
	}
	
	void testCellCopyConstructor2 () {
		FredkinCell* fc = new FredkinCell(true, 5);
		Cell c1 = fc;
		Cell c2 = c1;
		CPPUNIT_ASSERT(c1.cell != c2.cell);
		CPPUNIT_ASSERT(c1.cell->alive == c2.cell->alive);
		CPPUNIT_ASSERT(c1.cell->print() == c2.cell->print());
	}
	
	// ----------------
	// testCellReadChar
	void testCellReadChar0 () {
		Cell c;
		c.readChar('0');
		CPPUNIT_ASSERT(c.cell->alive == true);
		CPPUNIT_ASSERT(c.cell->print() == '0');
	}
	
	void testCellReadChar1 () {
		Cell c;
		c.readChar('-');
		CPPUNIT_ASSERT(c.cell->alive == false);
		CPPUNIT_ASSERT(c.cell->print() == '-');
	}
	
	void testCellReadChar2 () {
		Cell c;
		c.readChar('*');
		CPPUNIT_ASSERT(c.cell->alive == true);
		CPPUNIT_ASSERT(c.cell->print() == '*');
	}
	
	// --------------
	// testIsNeighbor
	void testIsNeighbor0 () {
		Cell c;
		c.readChar('0');
		CPPUNIT_ASSERT(c.isNeighbor());
	}
	
	void testIsNeighbor1 () {
		Cell c;
		c.readChar('*');
		CPPUNIT_ASSERT(c.cell->alive == true);
		CPPUNIT_ASSERT(c.isNeighbor());
	}
	
	void testIsNeighbor2 () {
		Cell c;
		c.readChar('-');
		CPPUNIT_ASSERT(!c.isNeighbor());
	}
	
	// --------------
	// testCellUpdate
	void testCellUpdate0 () {
		Cell c = new FredkinCell(true, 0);
		unsigned int pop = 0;
		c.update(1, 3, &pop);
		CPPUNIT_ASSERT(pop == 1);
		CPPUNIT_ASSERT(c.cell->alive == true);
		CPPUNIT_ASSERT(c.cell->print() == '1');
	}
	
	void testCellUpdate1 () {
		Cell c = new FredkinCell(true, 1);
		unsigned int pop = 0;
		c.update(2, 3, &pop);
		CPPUNIT_ASSERT(pop == 0);
		CPPUNIT_ASSERT(c.cell->alive == false);
		CPPUNIT_ASSERT(c.cell->print() == '-');
	}
	
	void testCellUpdate2 () {
		Cell c = new FredkinCell(false, 0);
		unsigned int pop = 0;
		c.update(1, 3, &pop);
		CPPUNIT_ASSERT(pop == 1);
		CPPUNIT_ASSERT(c.cell->alive == true);
		CPPUNIT_ASSERT(c.cell->print() == '0');
	}
	
	void testCellUpdate3 () {
		Cell c = new FredkinCell(false, 0);
		unsigned int pop = 0;
		c.update(0, 3, &pop);
		CPPUNIT_ASSERT(pop == 0);
		CPPUNIT_ASSERT(c.cell->alive == false);
		CPPUNIT_ASSERT(c.cell->print() == '-');
	}
	
	void testCellUpdate4 () {
		Cell c = new FredkinCell(true, 1);
		unsigned int pop = 0;
		c.update(1, 3, &pop);
		CPPUNIT_ASSERT(pop == 1);
		CPPUNIT_ASSERT(c.cell->alive == true);
		CPPUNIT_ASSERT(c.cell->print() == '*');
	}
	
	void testCellUpdate5 () {
		Cell c = new ConwayCell(true);
		unsigned int pop = 0;
		c.update(2, 0, &pop);
		CPPUNIT_ASSERT(pop == 1);
		CPPUNIT_ASSERT(c.cell->alive == true);
		CPPUNIT_ASSERT(c.cell->print() == '*');
	}
	
	void testCellUpdate6 () {
		Cell c = new ConwayCell(true);
		unsigned int pop = 0;
		c.update(1, 0, &pop);
		CPPUNIT_ASSERT(pop == 0);
		CPPUNIT_ASSERT(c.cell->alive == false);
		CPPUNIT_ASSERT(c.cell->print() == '.');
	}
	
	void testCellUpdate7 () {
		Cell c = new ConwayCell(false);
		unsigned int pop = 0;
		c.update(3, 0, &pop);
		CPPUNIT_ASSERT(pop == 1);
		CPPUNIT_ASSERT(c.cell->alive == true);
		CPPUNIT_ASSERT(c.cell->print() == '*');
	}
	
	void testCellUpdate8 () {
		Cell c = new ConwayCell(false);
		unsigned int pop = 0;
		c.update(2, 0, &pop);
		CPPUNIT_ASSERT(pop == 0);
		CPPUNIT_ASSERT(c.cell->alive == false);
		CPPUNIT_ASSERT(c.cell->print() == '.');
	}

	// ----------------------
	// testCellCopyAssignment
	void testCellCopyAssignment0 () {
		Cell c1 = new ConwayCell(true);
		Cell c2;
		c2 = c1;
		CPPUNIT_ASSERT(c1.cell != c2.cell);
			CPPUNIT_ASSERT(c2.cell->print() == '*');
	}

	void testCellCopyAssignment1 () {
		Cell c1 = new ConwayCell(false);
		Cell c2;
		c2 = c1;
		CPPUNIT_ASSERT(c1.cell != c2.cell);
			CPPUNIT_ASSERT(c2.cell->print() == '.');
	}

	void testCellCopyAssignment2 () {
		Cell c1 = new FredkinCell(true, 4);
		Cell c2;
		c2 = c1;
		CPPUNIT_ASSERT(c1.cell != c2.cell);
			CPPUNIT_ASSERT(c2.cell->print() == '4');
	}	

	// -----------------
	// testConstructGrid
	// -----------------

	void testConstructGrid0 () {
		Life<ConwayCell> l(0, 0);
		l.constructGrids(1, 1);
		CPPUNIT_ASSERT(l._g[0].size() == 1);
		CPPUNIT_ASSERT(l._g[0][0].size() == 1);
		CPPUNIT_ASSERT(l._g[1].size() == 1);
			CPPUNIT_ASSERT(l._g[1][0].size() == 1);
	}

	void testConstructGrid1 () {
		Life<ConwayCell> l(0, 0);
		l.constructGrids(100, 100);
		CPPUNIT_ASSERT(l._g[0].size() == 100);
		CPPUNIT_ASSERT(l._g[0][0].size() == 100);
		CPPUNIT_ASSERT(l._g[1].size() == 100);
			CPPUNIT_ASSERT(l._g[1][0].size() == 100);
	}

	void testConstructGrid2 () {
		Life<ConwayCell> l(0, 0);
		l.constructGrids(100, 1);
		CPPUNIT_ASSERT(l._g[0].size() == 100);
		CPPUNIT_ASSERT(l._g[0][0].size() == 1);
		CPPUNIT_ASSERT(l._g[1].size() == 100);
			CPPUNIT_ASSERT(l._g[1][0].size() == 1);
	}

	// -------------
	// testLifenRows
	// -------------

	void testLifenRows0 () {
		Life<ConwayCell> l(100, 1);
			CPPUNIT_ASSERT(l.nRows() == 100);
	}

	void testLifenRows1 () {
		Life<ConwayCell> l(1, 100);
			CPPUNIT_ASSERT(l.nRows() == 1);
	}

	void testLifenRows2 () {
		Life<ConwayCell> l(9, 2);
			CPPUNIT_ASSERT(l.nRows() == 9);
	}

	// -------------
	// testLifenCols
	// -------------

	void testLifenCols0 () {
		Life<ConwayCell> l(100, 1);
			CPPUNIT_ASSERT(l.nCols() == 1);
	}

	void testLifenCols1 () {
		Life<ConwayCell> l(1, 100);
			CPPUNIT_ASSERT(l.nCols() == 100);
	}

	void testLifenCols2 () {
		Life<ConwayCell> l(19, 2);
			CPPUNIT_ASSERT(l.nCols() == 2);
	}

	// -------------------------
	// testLifeConstructorString
	// -------------------------

	void testLiveonstrucotrString0 () {
		Life<ConwayCell> l("./keo-tests/RunConway1.in");
		CPPUNIT_ASSERT(l.nRows() == 48);
		CPPUNIT_ASSERT(l.nCols() == 50);
		CPPUNIT_ASSERT(l._g[0][0][2].print() == '*');
			CPPUNIT_ASSERT(l._g[0][0][1].print() == '.');
	}

	void testLiveonstrucotrString1 () {
		Life<ConwayCell> l("./keo-tests/RunConway2.in");
		CPPUNIT_ASSERT(l.nRows() == 50);
		CPPUNIT_ASSERT(l.nCols() == 80);
		CPPUNIT_ASSERT(l._g[0][5][1].print() == '*');
			CPPUNIT_ASSERT(l._g[0][5][0].print() == '.');
	}

	void testLiveonstrucotrString2 () {
		Life<ConwayCell> l("./keo-tests/RunConway3.in");
		CPPUNIT_ASSERT(l.nRows() == 17);
		CPPUNIT_ASSERT(l.nCols() == 17);
		CPPUNIT_ASSERT(l._g[0][4][2].print() == '*');
			CPPUNIT_ASSERT(l._g[0][4][1].print() == '.');
	}

	// -------------------------
	// testLifeConstructorIntInt
	// -------------------------

	void testLifeConstructorIntInt0 () {
		Life<ConwayCell> l(1, 1);
		CPPUNIT_ASSERT(l.nRows() == 1);
			CPPUNIT_ASSERT(l.nCols() == 1);
	}

	void testLifeConstructorIntInt1 () {
		Life<ConwayCell> l(10, 10);
		CPPUNIT_ASSERT(l.nRows() == 10);
			CPPUNIT_ASSERT(l.nCols() == 10);
	}

	void testLifeConstructorIntInt2 () {
		Life<ConwayCell> l(1, 1);
		CPPUNIT_ASSERT(l.nRows() == 1);
			CPPUNIT_ASSERT(l.nCols() == 1);
	}

	// ------------------------------
	// testLifecountNeighborsAdjacent
	// ------------------------------

	void testLifecountNeighborsAdjacent0 () {
		Life<ConwayCell> l(1, 1);
			CPPUNIT_ASSERT(l.countNeighborsAdjacent(0, 0) == 0);
	}

	void testLifecountNeighborsAdjacent1 () {
		Life<ConwayCell> l(3, 3);
		/*
		...
		...
		...
			*/
		CPPUNIT_ASSERT(l.countNeighborsAdjacent(1, 1) == 0);
	}

	void testLifecountNeighborsAdjacent2 () {
		Life<ConwayCell> l(3, 3);
		/*
		**.
		*..
			...
		*/
		l._g[0][0][0].alive = true;
		l._g[0][0][1].alive = true;
		l._g[0][1][0].alive = true;
		CPPUNIT_ASSERT(l.countNeighborsAdjacent(1, 1) == 2);
	}

	// --------------------------
	// testLifecountNeighborsDiag
	// --------------------------

	void testLifecountNeighborsDiag0 () {
		Life<ConwayCell> l(1, 1);
		CPPUNIT_ASSERT(l.countNeighborsDiag(0, 0) == 0);
	}

	void testLifecountNeighborsDiag1 () {
		Life<ConwayCell> l(3, 3);
		CPPUNIT_ASSERT(l.countNeighborsDiag(1, 1) == 0);
	}

	void testLifecountNeighborsDiag2 () {
		Life<ConwayCell> l(3, 3);
		l._g[0][0][0].alive = true;
		l._g[0][0][1].alive = true;
		l._g[0][1][0].alive = true;
		CPPUNIT_ASSERT(l.countNeighborsDiag(1, 1) == 1);
	}

	// -------------
	// testLifePrint
	void testLifePrint0 () {
		Life<ConwayCell> l(3, 3);
		l._g[0][0][0].alive = true;
		l._g[0][0][1].alive = true;
		l._g[0][1][0].alive = true;
		std::ostringstream w;
		l.print(w);
		string s = "Generation = 0, Population = 0.\n";
		s += "**.\n";
		s += "*..\n";
		s += "...\n\n";
		l._g[0][0][0].alive = true;
		l._g[0][0][1].alive = true;
		l._g[0][1][0].alive = true;
		CPPUNIT_ASSERT(w.str() == s);
	}

	void testLifePrint1 () {
		Life<ConwayCell> l(3, 3);
		l._g[0][2][2].alive = true;
		l._g[0][0][1].alive = true;
		l._g[0][1][0].alive = true;
		std::ostringstream w;
		l.print(w);
		string s = "Generation = 0, Population = 0.\n";
		s += ".*.\n";
		s += "*..\n";
		s += "..*\n\n";
		l._g[0][0][0].alive = true;
		l._g[0][0][1].alive = true;
		l._g[0][1][0].alive = true;
		CPPUNIT_ASSERT(w.str() == s);
	}

	void testLifePrint2 () {
		Life<FredkinCell> l(3, 3);
		l._g[0][0][0].alive = true;
		l._g[0][0][0].age = 0;
		l._g[0][0][1].alive = true;
		l._g[0][0][1].age = 1;
		l._g[0][0][2].alive = true;
		l._g[0][0][2].age = 2;
		l._g[0][1][0].alive = true;
		l._g[0][1][0].age = 3;
		std::ostringstream w;
		l.print(w);
		string s = "Generation = 0, Population = 0.\n";
		s += "012\n";
		s += "3--\n";
		s += "---\n\n";
		l._g[0][0][0].alive = true;
		l._g[0][0][1].alive = true;
		l._g[0][1][0].alive = true;
		CPPUNIT_ASSERT(w.str() == s);
	}

	// ---------------
	// testLifeRunTurn
	void testLifeRunTurn0 () {
		Life<ConwayCell> l(1,1);
		l.runTurn();
		CPPUNIT_ASSERT(l._g[1][0][0].alive == false);
		CPPUNIT_ASSERT(l.generation == 1);
	}

	void testLifeRunTurn1 () {
		Life<ConwayCell> l(3,3);
		l._g[0][1][0].alive = true;
		l._g[0][1][1].alive = true;
		l._g[0][1][2].alive = true;
		l.runTurn();
		CPPUNIT_ASSERT(l._g[1][0][0].alive == false);
		CPPUNIT_ASSERT(l._g[1][0][1].alive == true);
		CPPUNIT_ASSERT(l._g[1][0][2].alive == false);
		CPPUNIT_ASSERT(l._g[1][1][0].alive == false);
		CPPUNIT_ASSERT(l._g[1][1][1].alive == true);
		CPPUNIT_ASSERT(l._g[1][1][2].alive == false);
		CPPUNIT_ASSERT(l._g[1][2][0].alive == false);
		CPPUNIT_ASSERT(l._g[1][2][1].alive == true);
		CPPUNIT_ASSERT(l._g[1][2][2].alive == false);
		CPPUNIT_ASSERT(l.generation== 1);
	}

	void testLifeRunTurn2 () {
		Life<FredkinCell> l(3,3);
		/*
		-2-
		33-
		-+-
		*/
		l._g[0][0][1].alive = true;
		l._g[0][0][1].age = 2;
		l._g[0][1][0].alive = true;
		l._g[0][1][0].age = 3;
		l._g[0][1][1].alive = true;
		l._g[0][1][1].age = 3;
		l._g[0][2][1].alive = true;
		l._g[0][2][1].age = 10;
		l.runTurn();
		/*
		-30
		4-0
		-+0
		*/
		CPPUNIT_ASSERT(l._g[1][0][0].alive == false);
		CPPUNIT_ASSERT(l._g[1][0][0].age == 0);
		CPPUNIT_ASSERT(l._g[1][0][1].alive == true);
		CPPUNIT_ASSERT(l._g[1][0][1].age == 3);
		CPPUNIT_ASSERT(l._g[1][0][2].alive == true);
		CPPUNIT_ASSERT(l._g[1][0][2].age == 0);
		CPPUNIT_ASSERT(l._g[1][1][0].alive == true);
		CPPUNIT_ASSERT(l._g[1][1][0].age == 4);
		CPPUNIT_ASSERT(l._g[1][1][1].alive == true);
		CPPUNIT_ASSERT(l._g[1][1][1].age == 4);
		CPPUNIT_ASSERT(l._g[1][1][2].alive == true);
		CPPUNIT_ASSERT(l._g[1][1][2].age == 0);
		CPPUNIT_ASSERT(l._g[1][2][0].alive == false);
		CPPUNIT_ASSERT(l._g[1][2][0].age == 0);
		CPPUNIT_ASSERT(l._g[1][2][1].alive == true);
		CPPUNIT_ASSERT(l._g[1][2][1].age == 11);
		CPPUNIT_ASSERT(l._g[1][2][2].alive == true);
		CPPUNIT_ASSERT(l._g[1][2][2].age == 0);
		CPPUNIT_ASSERT(l.generation== 1);
	}

	// ----------------
	// testLifeSimulate
	void testLifeSimulate0 () {
		Life<ConwayCell> l(1,1);
		l.runTurn();
		std::ostringstream w;
		l.simulate(100, 100, w);
		CPPUNIT_ASSERT(l._g[1][0][0].alive == false);
		CPPUNIT_ASSERT(l.generation == 101);
	}

	void testLifeSimulate1 () {
		Life<ConwayCell> l(3,3);
		l._g[0][1][0].alive = true;
		l._g[0][1][1].alive = true;
		l._g[0][1][2].alive = true;
		std::ostringstream w;
		l.simulate(9, 1, w);
		CPPUNIT_ASSERT(l._g[1][0][0].alive == false);
		CPPUNIT_ASSERT(l._g[1][0][1].alive == true);
		CPPUNIT_ASSERT(l._g[1][0][2].alive == false);
		CPPUNIT_ASSERT(l._g[1][1][0].alive == false);
		CPPUNIT_ASSERT(l._g[1][1][1].alive == true);
		CPPUNIT_ASSERT(l._g[1][1][2].alive == false);
		CPPUNIT_ASSERT(l._g[1][2][0].alive == false);
		CPPUNIT_ASSERT(l._g[1][2][1].alive == true);
		CPPUNIT_ASSERT(l._g[1][2][2].alive == false);
		CPPUNIT_ASSERT(l.generation== 9);
	}

	void testLifeSimulate2 () {
		Life<FredkinCell> l(3,3);
		/*
		-2-
		33-
		-+-
		*/
		l._g[0][0][1].alive = true;
		l._g[0][0][1].age = 2;
		l._g[0][1][0].alive = true;
		l._g[0][1][0].age = 3;
		l._g[0][1][1].alive = true;
		l._g[0][1][1].age = 3;
		l._g[0][2][1].alive = true;
		l._g[0][2][1].age = 10;
		std::ostringstream w;
		l.simulate(1, 1, w);
		/*
		-30
		4-0
		-+0
		*/
		CPPUNIT_ASSERT(l._g[1][0][0].alive == false);
		CPPUNIT_ASSERT(l._g[1][0][0].age == 0);
		CPPUNIT_ASSERT(l._g[1][0][1].alive == true);
		CPPUNIT_ASSERT(l._g[1][0][1].age == 3);
		CPPUNIT_ASSERT(l._g[1][0][2].alive == true);
		CPPUNIT_ASSERT(l._g[1][0][2].age == 0);
		CPPUNIT_ASSERT(l._g[1][1][0].alive == true);
		CPPUNIT_ASSERT(l._g[1][1][0].age == 4);
		CPPUNIT_ASSERT(l._g[1][1][1].alive == true);
		CPPUNIT_ASSERT(l._g[1][1][1].age == 4);
		CPPUNIT_ASSERT(l._g[1][1][2].alive == true);
		CPPUNIT_ASSERT(l._g[1][1][2].age == 0);
		CPPUNIT_ASSERT(l._g[1][2][0].alive == false);
		CPPUNIT_ASSERT(l._g[1][2][0].age == 0);
		CPPUNIT_ASSERT(l._g[1][2][1].alive == true);
		CPPUNIT_ASSERT(l._g[1][2][1].age == 11);
		CPPUNIT_ASSERT(l._g[1][2][2].alive == true);
		CPPUNIT_ASSERT(l._g[1][2][2].age == 0);
			CPPUNIT_ASSERT(l.generation== 1);
	}

	// -----
	// suite
	CPPUNIT_TEST_SUITE(TestLife);
	
	CPPUNIT_TEST(testFredkinClone0);
	CPPUNIT_TEST(testLife0);
	CPPUNIT_TEST(testLife1);
	CPPUNIT_TEST(testLife2);
	CPPUNIT_TEST(testLife3);
	CPPUNIT_TEST(testLife4);
	CPPUNIT_TEST(testLife5);
	CPPUNIT_TEST(testUpdate0);
	CPPUNIT_TEST(testRunTurn0);
	CPPUNIT_TEST(testSimulateTurn0);
	CPPUNIT_TEST(testConwayDefaultConstructor2);
	CPPUNIT_TEST(testConwayDefaultConstructor2);
	CPPUNIT_TEST(testConwayDefaultConstructor2);
	CPPUNIT_TEST(testConwayBoolConstructor0);
	CPPUNIT_TEST(testConwayBoolConstructor1);
	CPPUNIT_TEST(testConwayBoolConstructor2);
	CPPUNIT_TEST(testConwayCopyConstructor0);
	CPPUNIT_TEST(testConwayCopyConstructor1);
	CPPUNIT_TEST(testConwayCopyConstructor2);
	CPPUNIT_TEST(testConwayIsNeighbor0);
	CPPUNIT_TEST(testConwayIsNeighbor1);
	CPPUNIT_TEST(testConwayIsNeighbor2);
	CPPUNIT_TEST(testConwayReadChar0);
	CPPUNIT_TEST(testConwayReadChar1);
	CPPUNIT_TEST(testConwayReadChar2);
	CPPUNIT_TEST(testConwayOperator0);
	CPPUNIT_TEST(testConwayOperator1);
	CPPUNIT_TEST(testConwayOperator2);
	CPPUNIT_TEST(testConwayClone0);
	CPPUNIT_TEST(testFredkinDefaultConstructor0);
	CPPUNIT_TEST(testFredkinDefaultConstructor1);
	CPPUNIT_TEST(testFredkinDefaultConstructor2);
	CPPUNIT_TEST(testFredkinBoolIntConstructor0);
	CPPUNIT_TEST(testFredkinBoolIntConstructor1);
	CPPUNIT_TEST(testFredkinBoolIntConstructor2);
	CPPUNIT_TEST(testFredkinCopyConstructor0);
	CPPUNIT_TEST(testFredkinCopyConstructor1);
	CPPUNIT_TEST(testFredkinCopyConstructor2);
	CPPUNIT_TEST(testFredkinIsNeighbor0);
	CPPUNIT_TEST(testFredkinIsNeighbor1);
	CPPUNIT_TEST(testFredkinIsNeighbor2);
	CPPUNIT_TEST(testFredkinReadChar0);
	CPPUNIT_TEST(testFredkinReadChar1);
	CPPUNIT_TEST(testFredkinReadChar2);
	CPPUNIT_TEST(testFredkinReadChar3);/*
	CPPUNIT_TEST(testConwayUpdate0);
	CPPUNIT_TEST(testConwayUpdate1);
	CPPUNIT_TEST(testConwayUpdate2);
	CPPUNIT_TEST(testConwayUpdate3);*/
	CPPUNIT_TEST(testConwayTransform0);
	CPPUNIT_TEST(testConwayPrint0);
	CPPUNIT_TEST(testConwayPrint1);
	CPPUNIT_TEST(testConwayPrint2);/*
	CPPUNIT_TEST(testFredkinUpdate0);
	CPPUNIT_TEST(testFredkinUpdate1);
	CPPUNIT_TEST(testFredkinUpdate2);
	CPPUNIT_TEST(testFredkinUpdate3);
	CPPUNIT_TEST(testFredkinUpdate4);*/
	CPPUNIT_TEST(testFredkinOperator0);
	CPPUNIT_TEST(testFredkinOperator1);
	CPPUNIT_TEST(testFredkinOperator2);
	CPPUNIT_TEST(testFredkinClone0);
	CPPUNIT_TEST(testFredkinClone1);
	CPPUNIT_TEST(testFredkinClone2);
	CPPUNIT_TEST(testFredkinTransform0);
	CPPUNIT_TEST(testFredkinTransform1);
	CPPUNIT_TEST(testFredkinTransform2);
	CPPUNIT_TEST(testFredkinTransform3);
	CPPUNIT_TEST(testFredkinPrint0);
	CPPUNIT_TEST(testFredkinPrint1);
	CPPUNIT_TEST(testFredkinPrint2);
	CPPUNIT_TEST(testCellConstructor0);
	CPPUNIT_TEST(testCellConstructor1);
	CPPUNIT_TEST(testCellConstructor2);
	CPPUNIT_TEST(testCellCopyConstructor0);
	CPPUNIT_TEST(testCellCopyConstructor1);
	CPPUNIT_TEST(testCellCopyConstructor2);
	CPPUNIT_TEST(testCellPointerConstructor0);
	CPPUNIT_TEST(testCellPointerConstructor1);
	CPPUNIT_TEST(testCellPointerConstructor2);
	CPPUNIT_TEST(testCellCopyAssignment0);
	CPPUNIT_TEST(testCellCopyAssignment1);
	CPPUNIT_TEST(testCellCopyAssignment2);
	CPPUNIT_TEST(testCellReadChar0);
	CPPUNIT_TEST(testCellReadChar1);
	CPPUNIT_TEST(testCellReadChar2);
	CPPUNIT_TEST(testIsNeighbor0);
	CPPUNIT_TEST(testIsNeighbor1);
	CPPUNIT_TEST(testIsNeighbor2);/*
	CPPUNIT_TEST(testCellUpdate0);
	CPPUNIT_TEST(testCellUpdate1);
	CPPUNIT_TEST(testCellUpdate2);
	CPPUNIT_TEST(testCellUpdate3);
	CPPUNIT_TEST(testCellUpdate4);
	CPPUNIT_TEST(testCellUpdate5);
	CPPUNIT_TEST(testCellUpdate6);
	CPPUNIT_TEST(testCellUpdate7);
	CPPUNIT_TEST(testCellUpdate8);*/
	CPPUNIT_TEST(testConstructGrid0);
	CPPUNIT_TEST(testConstructGrid1);
	CPPUNIT_TEST(testConstructGrid2);
	CPPUNIT_TEST(testLifenRows0);
	CPPUNIT_TEST(testLifenRows1);
	CPPUNIT_TEST(testLifenRows2);
	CPPUNIT_TEST(testLifenCols0);
	CPPUNIT_TEST(testLifenCols1);
	CPPUNIT_TEST(testLifenCols2);
	CPPUNIT_TEST(testLiveonstrucotrString0);
	CPPUNIT_TEST(testLiveonstrucotrString1);
	CPPUNIT_TEST(testLiveonstrucotrString2);
	CPPUNIT_TEST(testLifeConstructorIntInt0);
	CPPUNIT_TEST(testLifeConstructorIntInt1);
	CPPUNIT_TEST(testLifeConstructorIntInt2);
	CPPUNIT_TEST(testLifecountNeighborsAdjacent0);
	CPPUNIT_TEST(testLifecountNeighborsAdjacent1);
	CPPUNIT_TEST(testLifecountNeighborsAdjacent2);
	CPPUNIT_TEST(testLifecountNeighborsDiag0);
	CPPUNIT_TEST(testLifecountNeighborsDiag1);
	CPPUNIT_TEST(testLifecountNeighborsDiag2);
	CPPUNIT_TEST(testLifePrint0);
	CPPUNIT_TEST(testLifePrint1);
	CPPUNIT_TEST(testLifePrint2);
	CPPUNIT_TEST(testLifeRunTurn0);
	CPPUNIT_TEST(testLifeRunTurn1);
	CPPUNIT_TEST(testLifeRunTurn2);
	CPPUNIT_TEST(testLifeSimulate0);
	CPPUNIT_TEST(testLifeSimulate1);
	CPPUNIT_TEST(testLifeSimulate2);
	
	CPPUNIT_TEST_SUITE_END();
};

// ----
// main
int main () {
	using namespace std;
	ios_base::sync_with_stdio(false);	// turn off synchronization with C I/O
	cout << "TestLife.c++" << endl;

	CppUnit::TextTestRunner tr;
	tr.addTest(TestLife::suite());
	long t0 = clock();
	
	tr.run();
	long t1 = clock();
	if(DEBUG) cerr << "t1: " << t1 << endl;
	if(DEBUG) cerr << "Clocks ticks elapsed: " << (t1 - t0)/CLOCKS_PER_SEC << endl;

	cout << "Done." << endl;
	return 0;
}
