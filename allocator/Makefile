SHELL = /bin/sh

CC = g++
CPPFLAGS = -O2
SOURCE = RunAllocator.c++
TEST = TestAllocator.c++


all: test run log doxygen zip

clean:
	rm *.app

test: $(TEST)
	clear
	$(CC) $(CPPFLAGS) $(TEST) -lcppunit -o $(TEST).app
	./$(TEST).app

run: $(SOURCE)
	$(CC) $(CPPFLAGS) $(SOURCE) -o $(SOURCE).app
	./$(SOURCE).app

log:
	git log > Allocator.log

doxygen:
	doxygen Doxyfile

zip:
	zip Allocator README.txt html/* Allocator.h Allocator.log \
	RunAllocator.c++