# file variables
#source="metaCacheGen.h"
unitFile="TestVoting.c++"
source=$unitFile

clear
echo COMPILING $source...
g++ -pedantic -ldl -Wall -std=c++0x $source -lcppunit -o $source.app

	if ([ $? == 0 ]); then
echo RUNNING UNIT TESTS...
valgrind \
./$source.app #>& RunVoting.out < RunVoting.in
	fi
echo EXECUTION COMPLETE.
<<MULTICOMMENT

echo GENERATING COMMIT LOG...
git log > Voting.log

echo RUNNING DOXYGEN...
#doxygen -g
# EXTRACT_ALL			= YES
# EXTRACT_PRIVATE		= YES
# EXTRACT_STATIC		= YES
# GENERATE_LATEX		= NO
doxygen Doxyfile

echo CREATING SPHERE FILE...
cp Voting.h UVaVoting.c++

echo ZIPPING FILES...
zip Voting README.txt html/* Voting.h Voting.log \
  RunVoting.c++ RunVoting.in RunVoting.out \
 UVaVoting.c++ TestVoting.c++ TestVoting.out

	
turnin --submit reza cs371ppj2 Voting.zip
turnin --list   reza cs371ppj2
turnin --verify reza cs371ppj2
MULTICOMMENT