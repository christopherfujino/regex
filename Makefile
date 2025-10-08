CFLAGS = -std=c++20 -Wall

.PHONY: run
run: a.out
	./a.out

a.out: main.o parse.o
	clang++ main.o parse.o -o a.out

main.o: main.cpp regex.hpp
	clang++ $(CFLAGS) -c main.cpp -o main.o

parse.o: parse.cpp regex.hpp
	clang++ $(CFLAGS) -c parse.cpp -o parse.o
