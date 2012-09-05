# file variables
source="metaCacheGen.h"
unitFile="TestCollatz.c++"
source=$unitFile

clear
echo COMPILING $source...
g++ -pedantic -ldl -Wall -std=c++0x $source -lcppunit -o $source.app

	if ([ $? == 0 ]); then
echo RUNNING UNIT TESTS...
valgrind ./$source.app #>& $unitFile.out
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