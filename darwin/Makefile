SHELL = /bin/sh

CC = g++
CPPFLAGS = -std=c++0x #-pedantic -Wall
SOURCE = Darwin.h
TEST = TestDarwin.c++
RUN = RunDarwin.c++
RUNOUT = RunDarwin.out
TESTOUT = TestDarwin.out

all: test run log doxygen zip clean

run: $(RUN)
	clear
	$(CC) $(CPPFLAGS) $(RUN) -o $(RUN).app
	valgrind \
	./$(RUN).app 2>&1 | tee $(RUNOUT)

test: $(TEST)
	clear
	$(CC) $(CPPFLAGS) -ldl $(TEST) -lcppunit -o $(TEST).app
	valgrind \
	./$(TEST).app 2>&1 | tee $(TESTOUT)

log:
	git log > Darwin.log

doxygen:
	doxygen Doxyfile
	#doxygen -g
	# EXTRACT_ALL			= YES
	# EXTRACT_PRIVATE		= YES
	# EXTRACT_STATIC		= YES
	# GENERATE_LATEX		= NO

zip:
	zip Darwin README.txt html/* $(SOURCE) Darwin.pdf \
	Darwin.log $(RUN) $(TEST) \
	$(RUNOUT) $(TESTOUT)

# turnin --submit dmj cs371ppj5 Darwin.zip
# turnin --list   dmj cs371ppj5
# turnin --verify dmj cs371ppj5

clean:
	rm *.app

scratch: scratch.c++
	g++ -std=c++0x scratch.c++ -o scratch.c++.app
	./scratch.c++.app