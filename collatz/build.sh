# file variables
source="Collatz.h"
unitFile="TestCollatz.c++"

clear
echo COMPILING $source and $unitFile...
g++ -pedantic -ldl -Wall -std=c++0x\
	$unitFile -lcppunit -o $unitFile.app
	if ([ $? == 0 ]); then

echo RUNNING UNIT TESTS...
valgrind ./$unitFile.app #>& $unitFile.out
	fi

<<MULTICOMMENT
echo GENERATING COMMIT LOG...
git log > Collatz.log

echo RUNNING DOXYGEN...
#doxygen -g
# EXTRACT_ALL			= YES
# EXTRACT_PRIVATE		= YES
# EXTRACT_STATIC		= YES
# GENERATE_LATEX		= NO
doxygen Doxyfile

zip Collatz README.txt html/* Collatz.h Collatz.log TestCollatz.c++ TestCollatz.out

turnin --submit reza cs371ppj1 Collatz.zip
turnin --list   reza cs371ppj1
turnin --verify reza cs371ppj1
MULTICOMMENT