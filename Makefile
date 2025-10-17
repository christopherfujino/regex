CXXFLAGS = -std=c++20 -Wall -g
BINARY = ./a.out

.PHONY: run
run: $(BINARY)
	$(BINARY)

$(BINARY): main.o parse.o
	clang++ main.o parse.o -o a.out

main.o: main.cpp regex.hpp
	clang++ $(CXXFLAGS) -c $< -o $@

parse.o: parse.cpp regex.hpp
	clang++ $(CXXFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f *.o $(BINARY)
