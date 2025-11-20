CXX = clang++
CXXFLAGS = -std=c++20 -Wall -Werror -Wextra -g
BINARY = a.out

.PHONY: run
run: $(BINARY)
	./$(BINARY)

$(BINARY): main.o parse.o
	$(CXX) main.o parse.o -o a.out

main.o: main.cpp regex.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

parse.o: parse.cpp regex.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f *.o $(BINARY)
