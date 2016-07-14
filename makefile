FILES :=                              \
    .travis.yml                       \
    Voting.c++                       \
    Voting.h                         \
    Voting.log                       \
    html                              \
    RunVoting.c++                    \
    RunVoting.in                     \
    RunVoting.out                    \
    TestVoting.c++                   \
    TestVoting.out

CXX        := g++-4.8
CXXFLAGS   := -pedantic -std=c++11 -Wall
LDFLAGS    := -lgtest -lgtest_main -pthread
GCOV       := gcov-4.8
GCOVFLAGS  := -fprofile-arcs -ftest-coverage
GPROF      := gprof
GPROFFLAGS := -pg
VALGRIND   := valgrind

check:
	@not_found=0;                                 \
    for i in $(FILES);                            \
    do                                            \
        if [ -e $$i ];                            \
        then                                      \
            echo "$$i found";                     \
        else                                      \
            echo "$$i NOT FOUND";                 \
            not_found=`expr "$$not_found" + "1"`; \
        fi                                        \
    done;                                         \
    if [ $$not_found -ne 0 ];                     \
    then                                          \
        echo "$$not_found failures";              \
        exit 1;                                   \
    fi;                                           \
    echo "success";

clean:
	rm -f *.gcda
	rm -f *.gcno
	rm -f *.gcov
	rm -f RunVoting
	rm -f RunVoting.out
	rm -f TestVoting
	rm -f TestVoting.out

config:
	git config -l

scrub:
	make clean
	rm -f  Voting.log
	rm -rf voting-tests
	rm -rf html
	rm -rf latex

status:
	make clean
	@echo
	git branch
	git remote -v
	git status

test: RunVoting.out TestVoting.out

html: Doxyfile Voting.h Voting.c++ RunVoting.c++ TestVoting.c++
	doxygen Doxyfile

Voting.log:
	git log > Voting.log

Doxyfile:
	doxygen -g

RunVoting: Voting.h Voting.c++ RunVoting.c++
	$(CXX) $(CXXFLAGS) $(GCOVFLAGS) Voting.c++ RunVoting.c++ -o RunVoting

RunVoting.out: RunVoting
	./RunVoting < RunVoting.in > RunVoting.out

TestVoting: Voting.h Voting.c++ TestVoting.c++
	$(CXX) $(CXXFLAGS) $(GCOVFLAGS) Voting.c++ TestVoting.c++ -o TestVoting $(LDFLAGS)

TestVoting.out: TestVoting
	$(VALGRIND) ./TestVoting                                       >  TestVoting.out 2>&1
	$(GCOV) -b Voting.c++     | grep -A 5 "File 'Voting.c++'"     >> TestVoting.out
	$(GCOV) -b TestVoting.c++ | grep -A 5 "File 'TestVoting.c++'" >> TestVoting.out
	cat TestVoting.out
