# file variables
source="TestAllocator.c++"

clear
echo MAKE...
make
#g++ -pedantic -ldl -Wall -std=c++0x $source -lcppunit -o $source.app

	if ([ $? == 0 ]); then
echo EXECTUING...
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

	
turnin --submit dmj cs371ppj3 Allocator.zip
turnin --list   dmj cs371ppj3
turnin --verify dmj cs371ppj3
MULTICOMMENT