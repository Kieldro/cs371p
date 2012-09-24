SHELL = /bin/sh

CC = g++
CPPFLAGS = -pedantic -ldl -Wall -std=c++0x
SOURCE = RunVoting.c++


all: test run

clean:
	rm *.app

RunVoting: $(SOURCE)
	$(CC) $(CPPFLAGS) $(SOURCE) -o $(SOURCE).app

test: TestVoting.c++
	$(CC) $(CPPFLAGS) TestVoting.c++ -lcppunit -o TestVoting.c++.app
	./TestVoting.c++.app

run: RunVoting
	./$(SOURCE).app

GEN = something
gen: TestGen.c++
	$(CC) -std=c++0x TestGen.c++ -o TestGen.c++.app
	./TestGen.c++.app