SHELL = /bin/sh

CC = g++
CPPFLAGS = -O2
SOURCE = RunVoting.c++
GEN = TestGen.c++


all: test run

clean:
	rm *.app

RunVoting: $(SOURCE)
	$(CC) $(CPPFLAGS) $(SOURCE) -o $(SOURCE).app

test: TestVoting.c++
	clear
	$(CC) $(CPPFLAGS) TestVoting.c++ -lcppunit -o TestVoting.c++.app
	./TestVoting.c++.app

run: RunVoting
	./$(SOURCE).app < Sample.in

gen: $(GEN)
	$(CC) -std=c++0x $(GEN) -o $(GEN).app
	./$(GEN).app
	cat RunVoting.in