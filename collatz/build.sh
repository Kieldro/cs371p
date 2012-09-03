# file variables
source="Graph.h"
unitFile="TestGraph.c++"
outFile="TestGraph.out"

clear
echo COMPILING $source and $unitFile...
g++ -O -ansi -pedantic -I/public/linux/include/boost-1_44 -ldl -Wall \
	$unitFile -lcppunit -o $unitFile.app
	if ([ $? == 0 ]); then
echo RUNNING UNIT TESTS...
valgrind ./$unitFile.app #>& $outFile
	fi

<<MULTICOMMENT
echo GENERATING COMMIT LOG...
git log > Graph.log

echo RUNNING DOXYGEN...
#doxygen -g
# EXTRACT_ALL            = YES
# EXTRACT_PRIVATE        = YES
# EXTRACT_STATIC         = YES
# GENERATE_LATEX         = NO
doxygen Doxyfile

zip Graph README.txt html/* Graph.h Graph.log TestGraph.c++ TestGraph.out

turnin --submit reza cs378pj5 Graph.zip
turnin --list   reza cs378pj5
turnin --verify reza cs378pj5
MULTICOMMENT