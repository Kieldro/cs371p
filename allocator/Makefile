SHELL = /bin/sh

CC = g++
CPPFLAGS = -ansi -pedantic -ldl -Wall
TEST = TestAllocator.c++


all: test run log doxygen zip

clean:
	rm *.app

test: $(TEST)
	clear
	$(CC) $(CPPFLAGS) $(TEST) -lcppunit -o $(TEST).app
	./$(TEST).app #>& TestAllocator.out

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
	TestAllocator.c++ TestAllocator.out

# turnin --submit dmj cs371ppj3 Allocator.zip
# turnin --list   dmj cs371ppj3
# turnin --verify dmj cs371ppj3