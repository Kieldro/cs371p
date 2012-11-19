SHELL = /bin/sh

CC = g++
CPPFLAGS = -std=c++0x #-pedantic -Wall

TEST = TestLife.c++
TESTOUT = TestLife.out

RUN = RunLife.c++
RUNOUT = RunLife.out

all: test run log doxygen zip clean

run: $(RUN)
	clear
	$(CC) $(CPPFLAGS) $(RUN) -o $(RUN).app
	#valgrind \
	./$(RUN).app 2>&1 #| tee $(RUNOUT)

test: $(TEST)
	clear
	$(CC) $(CPPFLAGS) $(TEST) -lcppunit -o $(TEST).app
	#valgrind \
	./$(TEST).app 2>&1 #| tee $(TESTOUT)

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
		$(RUN) $(RUNOUT) \
		RunLifeConway.out RunLifeFredkin.out \
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