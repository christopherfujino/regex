CXX = clang++
CXXFLAGS = -std=c++20 -Wall -Werror -Wextra -Wpedantic -g
LDFLAGS =

regex.exe: main.o parse.o
	$CXX $LDFLAGS $prereq -o $target

%.o: %.cpp regex.h
	$CXX $CXXFLAGS -c $stem.cpp -o $target

clean:V:
	rm -f *.o *.exe *.a *.d
