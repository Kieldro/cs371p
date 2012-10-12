SHELL = /bin/sh

CC = g++
CPPFLAGS = -std=c++0x -ansi -pedantic -ldl -Wall
TEST = TestMatrix.c++


all: test run log doxygen zip

run: test

test: $(TEST)
	clear
	$(CC) $(CPPFLAGS) $(TEST) -lcppunit -o $(TEST).app
	./$(TEST).app #> TestMatlab.out 2>&1

log:
	git log > Matlab.log

doxygen:
	doxygen Doxyfile
	#doxygen -g
	# EXTRACT_ALL			= YES
	# EXTRACT_PRIVATE		= YES
	# EXTRACT_STATIC		= YES
	# GENERATE_LATEX		= NO

zip:
	zip Matlab README.txt html/* Matlab.h Matlab.log \
	$(TEST) TestMatrix.c++ TestMatlab.out TestMatrix.out

# turnin --submit reza cs371ppj4 Matlab.zip
# turnin --list   reza cs371ppj4
# turnin --verify reza cs371ppj4

clean:
	rm *.app

scratch: scratch.c++
	g++ -std=c++0x scratch.c++ -o scratch.c++.app
	scratch.c++.app