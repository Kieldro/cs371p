SHELL = /bin/sh

CC = g++
CPPFLAGS = -pedantic -ldl -Wall -std=c++0x
SOURCE = RunVoting.c++
GEN = TestGen.c++


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

gen: $(GEN)
	$(CC) -std=c++0x $(GEN) -o $(GEN).app
	./$(GEN).app