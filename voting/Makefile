SHELL = /bin/sh

CC = g++
CPPFLAGS = -O2
SOURCE = RunVoting.c++
GEN = TestGen.c++


all: test run UVafile log doxygen zip

clean:
	rm *.app

RunVoting: $(SOURCE)
	$(CC) $(CPPFLAGS) $(SOURCE) -o $(SOURCE).app

test: TestVoting.c++
	clear
	$(CC) $(CPPFLAGS) TestVoting.c++ -lcppunit -o TestVoting.c++.app
	valgrind ./TestVoting.c++.app &> test

run: RunVoting
	valgrind ./$(SOURCE).app < RunVoting.in > RunVoting.out

gen: $(GEN)
	$(CC) -std=c++0x $(GEN) -o $(GEN).app
	./$(GEN).app
	cat RunVoting.in

UVafile:
	cp Voting.h UVaVoting.c++

log:
	git log > Voting.log

doxygen:
	doxygen Doxyfile

zip:
	zip Voting README.txt html/* Voting.h Voting.log \
	RunVoting.c++ RunVoting.in RunVoting.out \
	UVaVoting.c++ TestVoting.c++ TestVoting.out