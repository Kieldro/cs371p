SHELL = /bin/sh

CC = g++
CPPFLAGS = -ansi -pedantic -ldl -Wall
TEST = TestAllocator.c++
OUTFILE = TestAllocator.out

all: test run log doxygen zip

clean:
	rm *.app

test: $(TEST)
	clear
	$(CC) $(CPPFLAGS) $(TEST) -lcppunit -o $(TEST).app
	valgrind ./$(TEST).app > TestAllocator.out 2>&1 ; cat $(OUTFILE)

run: test

log:
	git log > Allocator.log

doxygen:
	doxygen Doxyfile
	#doxygen -g
	# EXTRACT_ALL			= YES
	# EXTRACT_PRIVATE		= YES
	# EXTRACT_STATIC		= YES
	# GENERATE_LATEX		= NO

zip:
	zip Allocator README.txt html/* Allocator.h Allocator.log \
	$(TEST) TestAllocator.out

# turnin --submit dmj cs371ppj3 Allocator.zip
# turnin --list   dmj cs371ppj3
# turnin --verify dmj cs371ppj3

scratch: scratch.c++
	g++ -std=c++0x scratch.c++ -o scratch.c++.app
	scratch.c++.app