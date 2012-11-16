SHELL = /bin/sh

CC = g++
CPPFLAGS = -std=c++0x -pedantic -Wall

TEST = TestLife.c++
TESTOUT = TestLife.out

RUNCELL = RunLife.c++
RUNOUT = RunLife.out

RUNCONWAY = RunLifeConway.c++
RUNFREDKIN = RunLifeFredkin.c++

all: test run log doxygen zip clean

run: Conway Fredkin Cell

Cell: $(RUNCELL)
	clear
	$(CC) $(CPPFLAGS) $(RUNCELL) -o $(RUNCELL).app
	#valgrind \
	./$(RUNCELL).app 2>&1 #| tee $(RUNOUT)

Conway: $(RUNCONWAY)
	clear
	$(CC) $(CPPFLAGS) $(RUNCONWAY) -o $(RUNCONWAY).app
	#valgrind \
	./$(RUNCONWAY).app 2>&1 #| tee RunLifeConway.out

Fredkin: $(RUNFREDKIN)
	clear
	$(CC) $(CPPFLAGS) $(RUNFREDKIN) -o $(RUNFREDKIN).app
	#valgrind \
	./$(RUNFREDKIN).app 2>&1 #| tee RunLifeFredkin.out

test: $(TEST)
	clear
	$(CC) $(CPPFLAGS) $(TEST) -lcppunit -o $(TEST).app
	#valgrind \
	./$(TEST).app 2>&1 | tee $(TESTOUT)

log:
	git log > Life.log

doxygen:
	doxygen Doxyfile
	#doxygen -g
	# EXTRACT_ALL			= YES
	# EXTRACT_PRIVATE		= YES
	# EXTRACT_STATIC		= YES
	# GENERATE_LATEX		= NO

zip:
	zip Life README.txt html/* AbstractCell.h Cell.h \
		ConwayCell.h FredkinCell.h \
		Life.h Life.log Life.pdf \
		$(RUNCELL) $(RUNOUT) \
		$(RUNCONWAY) RunLifeConway.out \
		$(RUNFREDKIN) RunLifeFredkin.out \
		$(TEST) $(TESTOUT)

# turnin --submit reza cs371ppj6 Life.zip
# turnin --list   reza cs371ppj6
# turnin --verify reza cs371ppj6

clean:
	rm *.app

scratch: scratch.c++
	clear
	$(CC) $(CPPFLAGS) scratch.c++ -o scratch.c++.app
	#valgrind \
	./scratch.c++.app