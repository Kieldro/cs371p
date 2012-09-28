# file variables
source="TestAllocator.c++"

	if ([ $? == 0 ]); then
echo EXECTUING...
valgrind \
./$source.app #>& RunVoting.out < RunVoting.in
	fi
echo EXECUTION COMPLETE.
<<MULTICOMMENT
echo CREATING SPHERE FILE...
cp Voting.h UVaVoting.c++

MULTICOMMENT